﻿#include "CollisionManager.h"
#include "BoxCollider.h"
#include <future>
#include <iostream>

//Possible collision detection algorithms

//Quadtree: A quadtree is a tree data structure in which each internal node has exactly four children.
//It is often used to partition a two - dimensional space by recursively subdividing it into four quadrants or regions.
//With a quadtree, you can reduce the number of collisions checks by grouping colliders that are in the same quadrant of the space.

//Spatial hashing : Spatial hashing is a technique for efficiently grouping objects that are near each other in a grid.
//Each cell in the grid contains a list of objects that occupy that cell or overlap with it.
//This reduces the number of collision checks that need to be done by only checking for collisions between objects that occupy the same cell or adjacent cells.

//Sweep and prune : Sweep and prune is a broad - phase collision detection algorithm that works by projecting the colliders onto a line and sorting them by their position on the line.
//Then, it sweeps a line segment across the line and detects collisions between colliders that intersect with the line segment at each point in time.
//This approach is particularly efficient when most of the colliders are stationary.


CollisionManager::CollisionManager() : m_StopRequested(false)
{
	//number of available threads
	const Uint32 numThreads = std::thread::hardware_concurrency();

	//Create threads
	for (uint32_t i{}; i < numThreads; ++i)
	{
		m_ThreadPool.emplace_back(&CollisionManager::CollisionWorker, this);
	}

}

CollisionManager::~CollisionManager()
{
	//Stop threads
	std::unique_lock lock(m_CollisionMutex);
	m_StopRequested = true;
	m_ConditionVariable.notify_all();
}

void CollisionManager::Update()
{
	std::unique_lock lock(m_CollisionMutex);

	//Implement double buffering to synchronise colliding objects
	std::swap(m_CurrentCollidingObjects, m_NextCollidingObjects);

	// Clear the next buffer
	m_NextCollidingObjects.clear();




	// Call OnCollision for each game object involved in a collision
	for (auto* collider : m_CurrentCollidingObjects)
	{
		const auto& collidingObjects = collider->GetCollidingObjects();

		for (auto* collidingCollider : collidingObjects)
		{
			//First i need to check each game object if there is one that is marked for deletion.
			//If so i need to remove it from the list of colliders inside the BoxCollider.h file.
			//Also The OnCollision should not be triggered if the object it collides with is marked for deletion.
			if (collidingCollider->CanBeDeleted())
			{
				collider->RemoveCollidingObject(collidingCollider);
				continue;
			}

			collider->GetGameObject()->OnCollision(collidingCollider);
		}
	}

	// Remove any BoxColliders that have been flagged as removed
	m_BoxColliders.erase(std::remove_if(m_BoxColliders.begin(), m_BoxColliders.end(), [](BoxCollider* collider)
		{
			return collider->CanBeDeleted();
		}), m_BoxColliders.end());




	const size_t amountofThreads = m_ThreadPool.size();
	const size_t amountofColliders = m_BoxColliders.size();
	const size_t collidersPerThread = amountofColliders / amountofThreads;

	// Divide the work among the threads
	for (size_t i = 0; i < amountofThreads; ++i)
	{
		const size_t startIndex = i * collidersPerThread;
		const size_t endIndex = (i == amountofThreads - 1) ? amountofColliders : startIndex + collidersPerThread;

		// Create the task function pointer
		std::function<void()> task = [this, startIndex, endIndex]() { CheckCollisionRange(startIndex, endIndex); };

		// Add the task to the queue
		m_TaskQueue.push(task);

		// Notify a thread that there is work to do
		m_ConditionVariable.notify_one();
	}



	//for (size_t i = 0; i < m_BoxColliders.size(); ++i)
	//{
	//	std::unique_lock lock(m_CollisionMutex);

	//	//Create the task function pointer
	//	std::function task = [this, i]() {CheckCollisionAsync(i);  };

	//	//Add the task to the queue
	//	m_TaskQueue.push(task);

	//	//Notify a thread that there is work to do
	//	m_ConditionVariable.notify_one();
	//}
}

void CollisionManager::AddBoxCollider(BoxCollider* boxCollider)
{
	std::unique_lock lock(m_CollisionMutex);
	m_BoxColliders.push_back(boxCollider);
}

void CollisionManager::UnRegisterBoxCollider(BoxCollider* boxCollider)
{
	std::unique_lock lock(m_CollisionMutex);
	const auto it = std::ranges::find(m_BoxColliders, boxCollider);

	if (it != m_BoxColliders.end())
	{
		m_BoxColliders.erase(it);
	}
}

void CollisionManager::CollisionWorker()
{
	//Runs on a seperate thread
	while (true)
	{
		//Get the task from the queue
		std::function<void()> task;
		{

			std::unique_lock lock(m_CollisionMutex);

			m_ConditionVariable.wait(lock, [this]() {return !m_TaskQueue.empty() || m_StopRequested; });

			if (m_StopRequested) { return; }

			task = m_TaskQueue.front();

			m_TaskQueue.pop();
		}
		//Execute the task
		task();
	}
}

void CollisionManager::CheckCollisionAsync(size_t index)
{
	std::unique_lock lock(m_CollisionMutex);

	BoxCollider* colliderA = m_BoxColliders[index];

	for (size_t j = index + 1; j < m_BoxColliders.size(); ++j)
	{
		BoxCollider* colliderB = m_BoxColliders[j];


		// Check if the BoxColliders are colliding
		if (_CheckCollision(colliderA->GetCollider(), colliderB->GetCollider()))
		{
			// Add the objects as colliding objects
			// As of now they are stored with a mutex in the BoxCollider Component.
			// I don't know if i need to go with that or if i should store a std::vector<std::vector<GameObjects*>> in this class to store the collisions.
			// This approach avoids the need for a mutex in the BoxCollider component but requires additional memory allocation.
			colliderA->AddCollidingObject(colliderB->GetGameObject());
			colliderB->AddCollidingObject(colliderA->GetGameObject());
		}
	}
}

void CollisionManager::CheckCollisionRange(size_t from, size_t to)
{
	std::unique_lock lock(m_CollisionMutex);
	for (size_t i = from; i < to; ++i)
	{
		BoxCollider* colliderA = m_BoxColliders[i];

		for (size_t j = i + 1; j < m_BoxColliders.size(); ++j)
		{
			BoxCollider* colliderB = m_BoxColliders[j];

			// Check if the BoxColliders are colliding
			if (_CheckCollision(colliderA->GetCollider(), colliderB->GetCollider()))
			{
				// Add the objects as colliding objects
				colliderA->AddCollidingObject(colliderB->GetGameObject());
				colliderB->AddCollidingObject(colliderA->GetGameObject());

				// Add the colliders to the next colliding objects vector
				m_NextCollidingObjects.push_back(colliderA);
				m_NextCollidingObjects.push_back(colliderB);
			}
		}
	}
}

bool CollisionManager::_CheckCollision(const SDL_Rect& rectA, const SDL_Rect& rectB)
{
	//AABB Collision Check
	return  rectA.x < rectB.x + rectB.w &&
		rectA.x + rectA.w > rectB.x &&
		rectA.y < rectB.y + rectB.h &&
		rectA.y + rectA.h > rectB.y;
}