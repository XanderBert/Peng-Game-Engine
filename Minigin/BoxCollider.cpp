#include "BoxCollider.h"

#include "CollisionManager.h"
#include "Renderer.h"
#include "Transform.h"

BoxCollider::BoxCollider(GameObject* owner) : Component(owner)
{
	CollisionManager::GetInstance().AddBoxCollider(this);
}

BoxCollider::~BoxCollider()
{
}

void BoxCollider::Update()
{
}

void BoxCollider::FixedUpdate([[maybe_unused]]float fixedTimeMStep)
{
}

void BoxCollider::LateUpdate()
{
}

void BoxCollider::Render()
{
	if(m_DebugRender)
	Renderer::GetInstance().RenderRect(GetCollider());
}

void BoxCollider::SetColliderSize(const glm::vec2& size)
{
	m_Collider.w = static_cast<int>(size.x);
	m_Collider.h = static_cast<int>(size.y);
}

void BoxCollider::SetColliderOffset(const glm::vec2& offset)
{
	m_Collider.x = static_cast<int>(offset.x);
	m_Collider.y = static_cast<int>(offset.y);
}

void BoxCollider::DebugRender(bool isDebugRendering)
{
	m_DebugRender = isDebugRendering;
}

SDL_Rect BoxCollider::GetCollider() const
{

	//Todo: this will make the dirty flag pattern obsolete for the objects that will use collision
	//Wich is almost all the game objects. 
	const auto position = GetComponent<Transform>()->GetWorldPosition();

	return SDL_Rect{ m_Collider.x + static_cast<int>(position.x),m_Collider.y + static_cast<int>(position.y), m_Collider.w, m_Collider.h };

}
