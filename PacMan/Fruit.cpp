#include "Fruit.h"
#include "GameObject.h"
#include "TextureRenderer.h"
#include "BoxCollider.h"
#include "FruitComponent.h"
#include "Transform.h"

Fruit::Fruit() : m_pGameObject{ new GameObject() }
{
	m_pGameObject->AddComponent<FruitComponent>();

	const auto texture = m_pGameObject->AddComponent<TextureRenderer>();
	texture->SetTexture("Fruit.png");

	const auto collider = m_pGameObject->AddComponent<BoxCollider>();
	collider->SetColliderSize({ 4, 4 });
	collider->SetColliderOffset({ -1,-1 });

	m_pGameObject->GetComponent<Transform>()->SetWorldPosition({ 104, 180 });
}

