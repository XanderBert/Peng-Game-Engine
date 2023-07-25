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

SDL_Rect BoxCollider::GetCollider()
{
	const auto position = m_pOwner->GetComponent<Transform>()->GetWorldPosition();
	return SDL_Rect{ m_Collider.x + static_cast<int>(position.x),m_Collider.y + static_cast<int>(position.y), m_Collider.w, m_Collider.h };
}

glm::vec2 BoxCollider::GetColliderMiddlePoint() const
{
	//Top left
	const auto position = m_pOwner->GetComponent<Transform>()->GetWorldPosition();
	const auto x = position.x + m_Collider.w / 2.f;
	const auto y = position.y + m_Collider.h / 2.f;


	return glm::vec2(x + m_Collider.x, y + m_Collider.y);
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
	m_CollidingObjects.clear();
}

void BoxCollider::SetCollidingObjects(const std::vector<BoxCollider*>& pCollidingObjects)
{
	m_CollidingObjects = pCollidingObjects;
}

void BoxCollider::AddCollidingObject(BoxCollider* collider)
{
	m_CollidingObjects.emplace_back(collider);
}

void BoxCollider::RemoveCollidingObject(BoxCollider* collider)
{
	m_CollidingObjects.erase(std::remove(m_CollidingObjects.begin(), m_CollidingObjects.end(), collider), m_CollidingObjects.end());
}


std::vector<BoxCollider*> BoxCollider::GetCollidingBoxes() const
{
	return m_CollidingObjects;
}

std::set<GameObject*> BoxCollider::GetCollidingGameObjects()
{
	std::set<GameObject*> collidingGameObjects{};

	for (auto* pBoxCollider : m_CollidingObjects)
	{
		if (pBoxCollider == nullptr)
		{
			RemoveCollidingObject(pBoxCollider);
			continue;
		}
		if (pBoxCollider->GetGameObject() == nullptr)
		{
			assert(false);
			continue;
		}

		if (pBoxCollider->m_IsTrigger) continue;

		if (pBoxCollider->GetGameObject() != m_pOwner && !pBoxCollider->GetGameObject()->CanBeDeleted())
		{
			collidingGameObjects.insert(pBoxCollider->GetGameObject());
		}

	}
	return collidingGameObjects;
}
