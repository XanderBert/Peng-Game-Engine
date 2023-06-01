#include "StartScreen.h"

#include "BoxCollider.h"
#include "FontRenderer.h"
#include "Scene.h"
#include "ServiceLocator.h"
#include "TextureRenderer.h"
#include "Transform.h"


StartScreen::StartScreen()
{
	GetComponent<Transform>()->SetWorldPosition(m_Offset);

	const auto texture = AddComponent<TextureRenderer>();
	texture->SetTexture("StartScreen/PengoTitle.png");

	const auto fontRenderer = AddComponent<FontRenderer>();
	fontRenderer->SetText("Press Left Mouse To Start");
	fontRenderer->SetFont("Fonts/8BitDragon.ttf", 16);
	fontRenderer->SetOffset({ 0, m_ScreenSize.y });
}

StartScreen::~StartScreen()
{
}

void StartScreen::Update()
{
	const auto input = ServiceLocator::GetInstance().InputManager.GetService().IsLeftMouseButtonPressed();
	if (input)
	{
		std::cout << "INPUT";
		auto& sceneManager = SceneManager::GetInstance();
		sceneManager.SetActiveScene(sceneManager.GetSceneByName("Demo"));

	}
}


