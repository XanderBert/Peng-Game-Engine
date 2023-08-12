#pragma once
#include <functional>
#include <mutex>
#include <queue>
#include <thread>
#include "BoxCollider.h"


class null_CollisionManager
{
public:
	null_CollisionManager() = default;
	virtual ~null_CollisionManager() = default;

	null_CollisionManager(const null_CollisionManager& other) = delete;
	null_CollisionManager(null_CollisionManager&& other) = delete;
	null_CollisionManager& operator=(const null_CollisionManager& other) = delete;
	null_CollisionManager& operator=(null_CollisionManager&& other) = delete;

	virtual void Update() = 0;
	virtual void AddBoxCollider(BoxCollider* boxCollider) = 0;
	virtual void UnRegisterBoxCollider(BoxCollider* boxCollider) = 0;
	virtual void Clear() = 0;
	virtual bool IsInsideCollider(glm::vec2 pos, BoxCollider* collider) = 0;
};

class CollisionManager final : public null_CollisionManager
{
public:
	CollisionManager();
	virtual ~CollisionManager() override;

	CollisionManager(const CollisionManager& other) = delete;
	CollisionManager(CollisionManager&& other) = delete;
	CollisionManager& operator=(const CollisionManager& other) = delete;
	CollisionManager& operator=(CollisionManager&& other) = delete;

	virtual void Update() override;
	virtual void AddBoxCollider(BoxCollider* boxCollider) override;
	virtual void UnRegisterBoxCollider(BoxCollider* boxCollider) override;
	virtual void Clear() override {}
	virtual bool IsInsideCollider(glm::vec2 pos, BoxCollider* collider) override;
private:
	void CollisionWorker();
	void CheckCollisionRange(size_t from, size_t to);
	static bool _CheckCollision(const SDL_Rect& rectA, const SDL_Rect& rectB);

	std::vector<BoxCollider*> m_BoxColliders;
	std::vector<BoxCollider*> m_CurrentCollidingObjects;
	std::vector<BoxCollider*> m_NextCollidingObjects;



	//Holds the box collider an all the objects it collides with.
	std::vector<std::pair<BoxCollider*, std::vector<BoxCollider*>>> m_CalculatingCollidersPairs;

	std::vector<std::jthread> m_ThreadPool;
	std::queue<std::function<void()>> m_TaskQueue;
	std::mutex m_CollisionMutex;
	std::condition_variable m_ConditionVariable;
	bool m_StopRequested;
};


class CollisionManagerSingleThread final : public null_CollisionManager
{
public:
	CollisionManagerSingleThread() = default;
	virtual ~CollisionManagerSingleThread() override = default;

	CollisionManagerSingleThread(const CollisionManagerSingleThread& other) = delete;
	CollisionManagerSingleThread(CollisionManagerSingleThread&& other) = delete;
	CollisionManagerSingleThread& operator=(const CollisionManagerSingleThread& other) = delete;
	CollisionManagerSingleThread& operator=(CollisionManagerSingleThread&& other) = delete;
	virtual void Clear() override { m_BoxColliders.clear(); }
	virtual void Update() override;
	virtual void AddBoxCollider(BoxCollider* boxCollider) override;
	virtual void UnRegisterBoxCollider(BoxCollider* boxCollider) override;
	virtual bool IsInsideCollider(glm::vec2 pos, BoxCollider* collider) override;

private:
	std::unordered_set<BoxCollider*> m_BoxColliders;
	bool CheckCollision(const SDL_Rect& rectA, const SDL_Rect& rectB);
	bool DoesBoxNeedsToBeSkipped(BoxCollider* boxCollider);
};

