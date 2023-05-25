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
	virtual void AddBoxCollider([[maybe_unused]] BoxCollider* boxCollider) = 0;
	virtual void UnRegisterBoxCollider([[maybe_unused]] BoxCollider* boxCollider) = 0;
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
private:
	void CollisionWorker();
	void CheckCollisionAsync(size_t index);
	void CheckCollisionRange(size_t from, size_t to);
	static bool _CheckCollision(const SDL_Rect& rectA, const SDL_Rect& rectB);


	std::vector<BoxCollider*> m_BoxColliders;

	std::vector<BoxCollider*> m_CurrentCollidingObjects;
	std::vector<BoxCollider*> m_NextCollidingObjects;


	std::vector<std::jthread> m_ThreadPool;
	std::queue<std::function<void()>> m_TaskQueue;
	std::mutex m_CollisionMutex;
	std::condition_variable m_ConditionVariable;
	bool m_StopRequested;
};