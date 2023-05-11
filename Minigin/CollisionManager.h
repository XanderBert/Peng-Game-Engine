#pragma once
#include "BoxCollider.h"
#include "Singleton.h"

class CollisionManager
{
public:
	CollisionManager() = default;
	~CollisionManager() = default;

	CollisionManager(const CollisionManager& other) = delete;
	CollisionManager(CollisionManager&& other) = delete;
	CollisionManager& operator=(const CollisionManager& other) = delete;
	CollisionManager& operator=(CollisionManager&& other) = delete;

	virtual void Update();
	virtual void AddBoxCollider(BoxCollider* boxCollider);
	virtual void UnRegisterBoxCollider(BoxCollider* boxCollider);
private:
	static bool _CheckCollision(const SDL_Rect& rectA, const SDL_Rect& rectB);
	void CheckCollisionAsync(const size_t index);
	std::vector<BoxCollider*> m_BoxColliders;
};

class null_CollisionManager final : public CollisionManager
{
	virtual void Update() override {}
	virtual void AddBoxCollider([[maybe_unused]] BoxCollider* boxCollider) override {}
	virtual void UnRegisterBoxCollider([[maybe_unused]] BoxCollider* boxCollider) override {}
};
