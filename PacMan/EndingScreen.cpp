#include "EndingScreen.h"
#include "FontRenderer.h"
#include "GameObject.h"
#include "EndingScreenComponent.h"
#include "Transform.h"


EndingScreen::EndingScreen() : m_pGameObject{ new GameObject {} }
{
	const auto font = m_pGameObject->AddComponent<FontRenderer>();
	font->SetFont("Fonts/8BitDragon.ttf", 12);


	//Set text in LevelLoader
	m_pGameObject->AddComponent<EndingScreenComponent>();


	//Set position
	m_pGameObject->GetComponent<Transform>()->SetWorldPosition({ 20, 20 });
}
