#pragma once
#include "BoxCollider.h"
#include "Singleton.h"

class CollisionManager final : public Singleton<CollisionManager>
{
public:
	void Update();
	void AddBoxCollider(BoxCollider* boxCollider);
private:
	friend class Singleton<CollisionManager>;
	CollisionManager() = default;
	static bool _CheckCollision(const SDL_Rect& rectA, const SDL_Rect& rectB);
	void CheckCollisionAsync(const size_t index);
	std::vector<BoxCollider*> m_BoxColliders;
};
