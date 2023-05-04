#include "CollisionManager.h"

#include <future>

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
        auto func = [this, i]() { CheckCollisionAsync(i); };
        auto asycnFunc = std::async(std::launch::async, func);
    }
}

void CollisionManager::AddBoxCollider(BoxCollider* boxCollider)
{
    m_BoxColliders.push_back(boxCollider);
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