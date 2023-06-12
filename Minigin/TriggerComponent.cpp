#include "TriggerComponent.h"
#include "DirectionComponent.h"

TriggerComponent::TriggerComponent(GameObject* owner)
	: Component(owner)
	, m_pBoxCollider{ new BoxCollider(owner) }
	, m_Offset{ 0,0 }
{
	m_pBoxCollider->SetIsTrigger(true);
}

TriggerComponent::~TriggerComponent()
{
	delete m_pBoxCollider;
}

void TriggerComponent::Update()
{
	if (m_IsTriggerActive)
		m_pBoxCollider->Update();

	if (const auto directionComponent = m_pOwner->GetComponent<DirectionComponent>())
	{
		const auto direction = directionComponent->GetDirection();
		m_pBoxCollider->SetColliderOffset({ m_OffsetMultiplier * direction.x + m_Offset.x, m_OffsetMultiplier * direction.y + m_Offset.y });
	}
}

void TriggerComponent::FixedUpdate(float fixedTimeMStep)
{
	if (m_IsTriggerActive)
		m_pBoxCollider->FixedUpdate(fixedTimeMStep);
}

void TriggerComponent::LateUpdate()
{
	if (m_IsTriggerActive)
		m_pBoxCollider->LateUpdate();
}

void TriggerComponent::Render()
{
	if (m_IsTriggerActive)
	{
		m_pBoxCollider->Render();
	}

}

void TriggerComponent::SetColliderSize(const glm::vec2& size) const
{
	m_pBoxCollider->SetColliderSize(size);
}

void TriggerComponent::SetColliderOffset(const glm::vec2& offset)
{
	m_Offset = offset;
}

void TriggerComponent::SetOffsetMultiplier(float multiplier)
{
	m_OffsetMultiplier = multiplier;
}

void TriggerComponent::DebugRender(bool isDebugRendering) const
{
	m_pBoxCollider->DebugRender(isDebugRendering);
}

SDL_Rect TriggerComponent::GetTriggerRect() const
{
	return m_pBoxCollider->GetCollider();
}

std::vector<GameObject*> TriggerComponent::GetCollidingObjects() const
{
	std::vector<GameObject*> vector{};
	for (const auto box : m_pBoxCollider->GetCollidingBoxes())
	{
		vector.emplace_back(box->GetGameObject());

	}

	return vector;
}
void TriggerComponent::DisableTrigger()
{
	m_IsTriggerActive = false;
}

void TriggerComponent::EnableTrigger()
{
	m_IsTriggerActive = true;
}

std::string TriggerComponent::GetTag() const
{
	return m_Tag;
}

void TriggerComponent::SetTag(const std::string& tag)
{
	m_Tag = tag;
}
