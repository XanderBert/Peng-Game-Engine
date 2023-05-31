#include "BoxCollider.h"
#include "ServiceLocator.h"
#include "Renderer.h"
#include "Transform.h"
#include "mutex"

BoxCollider::BoxCollider(GameObject* owner) : Component(owner)
{
	ServiceLocator::GetInstance().CollisionManager.GetService().AddBoxCollider(this);
}

BoxCollider::~BoxCollider()
{
	//Is this not a viable solution? TODO Check this out!
	//ServiceLocator::GetInstance().CollisionManager.GetService().RemoveBoxCollider(this);
}

void BoxCollider::Update() {}

void BoxCollider::FixedUpdate(float /*fixedTimeMStep*/) {}

void BoxCollider::LateUpdate() {}

void BoxCollider::Render()
{
	if (m_DebugRender)
	{
		ServiceLocator::GetInstance().Renderer.GetService().RenderRect(GetCollider());
	}
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
	if (m_pOwner->CanBeDeleted())
	{
		return SDL_Rect{ 0,0,0,0 };
	}

	const auto position = m_pOwner->GetComponent<Transform>()->GetWorldPosition();
	return SDL_Rect{ m_Collider.x + static_cast<int>(position.x),m_Collider.y + static_cast<int>(position.y), m_Collider.w, m_Collider.h };
}

void BoxCollider::SetIsTrigger(bool isTrigger)
{
	m_IsTrigger = isTrigger;
}

bool BoxCollider::GetIsTrigger() const
{
	return m_IsTrigger;
}

void BoxCollider::ClearCollidingObjects()
{
	std::unique_lock lock(m_CollidingObjectsMutex);
	m_CollidingObjects.clear();
}

void BoxCollider::SetCollidingObjects(const std::vector<GameObject*>& pCollidingObjects)
{
	std::unique_lock lock(m_CollidingObjectsMutex);
	m_CollidingObjects = pCollidingObjects;
}

void BoxCollider::AddCollidingObject(GameObject* collider)
{
	std::unique_lock lock(m_CollidingObjectsMutex);
	m_CollidingObjects.emplace_back(collider);
}

void BoxCollider::RemoveCollidingObject(GameObject* collider)
{
	std::unique_lock lock(m_CollidingObjectsMutex);
	m_CollidingObjects.erase(std::remove(m_CollidingObjects.begin(), m_CollidingObjects.end(), collider), m_CollidingObjects.end());
}


std::vector<GameObject*> BoxCollider::GetCollidingObjects() const
{
	//std::unique_lock lock(m_CollidingObjectsMutex);
	return m_CollidingObjects;
}