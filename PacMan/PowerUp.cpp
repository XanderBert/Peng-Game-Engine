#include "PowerUp.h"
#include "PowerUpComponent.h"
#include "GameObject.h"
#include "TextureRenderer.h"
#include "BoxCollider.h"
#include "Transform.h"


PowerUp::PowerUp(const std::string& textureLocation, const glm::vec2& location) : m_pGameObject{ new GameObject() }
{
	//PowerUpComponent
	const auto powerUp = m_pGameObject->AddComponent<PowerUpComponent>();

	//Texture Component
	const auto textureRenderer = m_pGameObject->AddComponent<TextureRenderer>();
	textureRenderer->SetTexture(textureLocation);

	//Collider Component
	const auto collider = m_pGameObject->AddComponent<BoxCollider>();
	collider->SetColliderSize({ 6,6 });
#ifdef _DEBUG
	collider->DebugRender(true);
#endif // _DEBUG

	//Transform Component
	m_pGameObject->GetComponent<Transform>()->SetWorldPosition(location);
}
