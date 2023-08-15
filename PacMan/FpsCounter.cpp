#include "FpsCounter.h"
#include <FPSCounter.h>

#include "FontRenderer.h"
#include "GameObject.h"


FpsCounter::FpsCounter() :m_pGameObject{ new GameObject() }
{
	m_pGameObject->AddComponent<FPSCounter>();
	const auto font = m_pGameObject->AddComponent<FontRenderer>();
	font->SetFont("Fonts/8BitDragon.ttf", 16);


	//FPS Counter
	//m_Fps = new GameObject();
	//const auto fpsCounter{ m_Fps->AddComponent<FPSCounter>() };
	//const auto transComponentFPS{ m_Fps->GetComponent<Transform>() };
	//transComponentFPS->SetLocalPosition({ 5, 5 });

	//const auto fontRendererFPS = m_Fps->AddComponent<FontRenderer>();
	//fontRendererFPS->SetFont("Fonts/8BitDragon.ttf", 16);
	//activeScene->Add(m_Fps);
}
