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
	static bool CheckCollision(const SDL_Rect& rectA, const SDL_Rect& rectB);
	std::vector<BoxCollider*> m_BoxColliders;
};
