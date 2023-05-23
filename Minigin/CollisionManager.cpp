#include "CollisionManager.h"
#include "BoxCollider.h"
#include <future>

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
	//TODO Implement one of the following Optimizations
	//Quadtree: A quadtree is a tree data structure in which each internal node has exactly four children.
	//It is often used to partition a two - dimensional space by recursively subdividing it into four quadrants or regions.
	//With a quadtree, you can reduce the number of collisions checks by grouping colliders that are in the same quadrant of the space.

	//Spatial hashing : Spatial hashing is a technique for efficiently grouping objects that are near each other in a grid.
	//Each cell in the grid contains a list of objects that occupy that cell or overlap with it.
	//This reduces the number of collision checks that need to be done by only checking for collisions between objects that occupy the same cell or adjacent cells.

	//Sweep and prune : Sweep and prune is a broad - phase collision detection algorithm that works by projecting the colliders onto a line and sorting them by their position on the line.
	//Then, it sweeps a line segment across the line and detects collisions between colliders that intersect with the line segment at each point in time.
	//This approach is particularly efficient when most of the colliders are stationary.


	for (size_t i = 0; i < m_BoxColliders.size(); ++i)
	{
		//Create the task function pointer
		std::function task = [this, i]() {CheckCollisionAsync(i);  };

		//Add the task to the queue
		{
			std::unique_lock lock(m_CollisionMutex);
			m_TaskQueue.push(task);
		}

		//Notify a thread that there is work to do
		m_ConditionVariable.notify_one();
	}
}

void CollisionManager::AddBoxCollider(BoxCollider* boxCollider)
{
	m_BoxColliders.push_back(boxCollider);
}

void CollisionManager::UnRegisterBoxCollider(BoxCollider* boxCollider)
{
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
			if (m_StopRequested)
			{
				return;
			}
			task = m_TaskQueue.front();
			m_TaskQueue.pop();
		}
		//Execute the task
		task();
	}
}

void CollisionManager::CheckCollisionAsync(size_t index)
{
	for (size_t j = index + 1; j < m_BoxColliders.size(); ++j)
	{
		BoxCollider* colliderA = m_BoxColliders[index];
		BoxCollider* colliderB = m_BoxColliders[j];


		// Check if the BoxColliders are colliding
		if (_CheckCollision(colliderA->GetCollider(), colliderB->GetCollider()))
		{
			// Call a function on the game objects to handle the collision
			colliderA->GetGameObject()->OnCollision(colliderB->GetGameObject());
			colliderB->GetGameObject()->OnCollision(colliderA->GetGameObject());
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