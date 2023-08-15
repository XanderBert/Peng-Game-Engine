#include "PacDot.h"
#include "GameObject.h"
#include "Transform.h"
#include "TextureRenderer.h"
#include "BoxCollider.h"
#include "PacDotComponent.h"

PacDot::PacDot() : m_pGameObject{ new GameObject() }
{
	Initialize();
}


PacDot::PacDot(float x, float y) : m_pGameObject{ new GameObject() }
{
	m_pGameObject->GetComponent<Transform>()->SetWorldPosition({ x,y });
	Initialize();
}

void PacDot::Initialize()
{
	m_pGameObject->AddComponent<PacDotComponent>();

	const auto texture = m_pGameObject->AddComponent<TextureRenderer>();
	texture->SetTexture("PacDot.png");

	const auto collider = m_pGameObject->AddComponent<BoxCollider>();
	collider->SetColliderSize({ 4, 4 });
	collider->SetColliderOffset({ -1,-1 });
}