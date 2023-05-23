#pragma once
#include <functional>
#include <mutex>
#include <queue>
#include <thread>
#include "BoxCollider.h"


class CollisionManager
{
public:
	CollisionManager();
	virtual ~CollisionManager();

	CollisionManager(const CollisionManager& other) = delete;
	CollisionManager(CollisionManager&& other) = delete;
	CollisionManager& operator=(const CollisionManager& other) = delete;
	CollisionManager& operator=(CollisionManager&& other) = delete;

	virtual void Update();
	virtual void AddBoxCollider(BoxCollider* boxCollider);
	virtual void UnRegisterBoxCollider(BoxCollider* boxCollider);
private:
	void CheckCollisionAsync(size_t index);
	void CollisionWorker();
	static bool _CheckCollision(const SDL_Rect& rectA, const SDL_Rect& rectB);
	//void CheckCollisionAsync(const size_t index);

	std::vector<BoxCollider*> m_BoxColliders;
	std::vector<std::jthread> m_ThreadPool;
	std::queue<std::function<void()>> m_TaskQueue;
	std::mutex m_CollisionMutex;
	std::condition_variable m_ConditionVariable;
	bool m_StopRequested;
};

class null_CollisionManager final : public CollisionManager
{
	virtual void Update() override {}
	virtual void AddBoxCollider([[maybe_unused]] BoxCollider* boxCollider) override {}
	virtual void UnRegisterBoxCollider([[maybe_unused]] BoxCollider* boxCollider) override {}
};
