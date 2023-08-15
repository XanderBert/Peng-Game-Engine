#include "IntersectionTile.h"
#include "IntersectionComponent.h"

IntersectionTile::IntersectionTile(const glm::vec2& position, const std::vector<glm::vec2>& possibleDirection) : m_pGameObject(new GameObject())
{
	const auto transform = m_pGameObject->GetComponent<Transform>();
	transform->SetWorldPosition(position);

	const auto trigger = m_pGameObject->AddComponent<TriggerComponent>();
	trigger->SetColliderSize({ 4,4 });
	trigger->SetColliderOffset({ 6,6 });
	trigger->SetOffsetMultiplier(1.f);

	//trigger->DebugRender(true);



	m_pGameObject->AddComponent<IntersectionComponent>()->SetDirections(possibleDirection);

}