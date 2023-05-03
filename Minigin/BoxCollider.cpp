#include "BoxCollider.h"

#include "Transform.h"

BoxCollider::BoxCollider(GameObject* owner) : Component(owner)
{
}

BoxCollider::~BoxCollider()
{
}

void BoxCollider::Update()
{
}

void BoxCollider::FixedUpdate(float fixedTimeStep)
{
}

void BoxCollider::LateUpdate()
{
}

void BoxCollider::Render()
{
}

void BoxCollider::SetColliderSize(const glm::vec2& size)
{
	m_Collider.w = size.x;
	m_Collider.h = size.y;
}

void BoxCollider::SetColliderOffset(const glm::vec2& offset)
{
	m_Collider.x = offset.x;
	m_Collider.y = offset.y;
}

SDL_Rect BoxCollider::GetCollider() const
{

	//Todo: this will make the dirty flag pattern obsolete for the objects that will use collision
	//Wich is almost all the game objects. 
	const auto position = GetComponent<Transform>()->GetWorldPosition();

	return SDL_Rect{ m_Collider.x + static_cast<int>(position.x),m_Collider.y + static_cast<int>(position.y), m_Collider.w, m_Collider.h };

}
