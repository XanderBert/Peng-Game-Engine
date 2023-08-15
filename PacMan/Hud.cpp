#include "Hud.h"

#include "FontRenderer.h"
#include "GameObject.h"
#include "HudComponent.h"
#include "Transform.h"


Hud::Hud() : m_pGameObject{ new GameObject() }
{
	m_pGameObject->AddComponent<HudComponent>();

	const auto font = m_pGameObject->AddComponent<FontRenderer>();
	font->SetFont("Lingua.otf", 12);
	font->SetText("Lives: 0");

	m_pGameObject->GetComponent<Transform>()->SetWorldPosition({ 0,250 });
}
