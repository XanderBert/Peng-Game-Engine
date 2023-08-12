#include "BoxCollider.h"
#include "ServiceLocator.h"
#include "Renderer.h"
#include "Transform.h"


BoxCollider::BoxCollider(GameObject* owner) : Component(owner)
{
	ServiceLocator::GetInstance().CollisionManager.GetService().AddBoxCollider(this);
}

BoxCollider::~BoxCollider()
{
	ServiceLocator::GetInstance().CollisionManager.GetService().UnRegisterBoxCollider(this);

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
	const auto position = m_pOwner->GetComponent<Transform>()->GetWorldPosition();

	return SDL_Rect{ m_Collider.x + static_cast<int>(position.x),m_Collider.y + static_cast<int>(position.y), m_Collider.w, m_Collider.h };
}

glm::vec2 BoxCollider::GetColliderMiddlePoint() const
{
	const auto collider = GetCollider();

	//Top left
	const auto x = collider.w / 2.f;
	const auto y = collider.h / 2.f;

	return { static_cast<float>(collider.x) + x,static_cast<float>(collider.y) + y };
}

void BoxCollider::SetIsTrigger(bool isTrigger)
{
	m_IsTrigger = isTrigger;
}

bool BoxCollider::GetIsTrigger() const
{
	return m_IsTrigger;
}

std::unordered_set<BoxCollider*> BoxCollider::GetCollidingBoxes() const
{
	return m_CollidedWith;
}

std::set<GameObject*> BoxCollider::GetCollidingGameObjects() const
{
	std::set<GameObject*> collidingGameObjects{};

	for (const auto* pBoxCollider : m_CollidedWith)
	{
		if (pBoxCollider == nullptr)
		{
			assert(false && "BoxCollider is nullptr");
			continue;
		}
		if (pBoxCollider->GetGameObject() == nullptr)
		{
			assert(false && "GameObject is nullptr");
			continue;
		}

		if (pBoxCollider->GetGameObject() != m_pOwner && !pBoxCollider->GetGameObject()->CanBeDeleted())
		{
			collidingGameObjects.insert(pBoxCollider->GetGameObject());
		}
	}

	return collidingGameObjects;
}

bool BoxCollider::HasCollidedWith(BoxCollider* collider) const
{
	return m_CollidedWith.contains(collider);
}

void BoxCollider::MarkCollidedWith(BoxCollider* collider)
{
	m_CollidedWith.insert(collider);
}

void BoxCollider::ClearCollidedWith(BoxCollider* collider)
{
	m_CollidedWith.erase(collider);
}
