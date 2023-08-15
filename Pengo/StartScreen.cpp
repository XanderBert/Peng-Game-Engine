#include "StartScreen.h"

#include "BoxCollider.h"
#include "FontRenderer.h"
#include "LevelManager.h"
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


	// 1 Player Button
	m_pOnePlayerButton = new GameObject();
	m_pOnePlayerButton->SetParent(this, true);
	auto collider = m_pOnePlayerButton->AddComponent<BoxCollider>();
	collider->SetColliderSize({ 80,20 }); s
		//collider->DebugRender(true);
		m_pOnePlayerButton->GetComponent<Transform>()->SetWorldPosition({ 30, 320 });
	const auto font = m_pOnePlayerButton->AddComponent<FontRenderer>();
	font->SetFont("Fonts/8BitDragon.ttf", 12);
	font->SetText("1 Player");

	// VS
	m_pVSModeButton = new GameObject();
	m_pVSModeButton->SetParent(this, true);
	auto colliderVS = m_pVSModeButton->AddComponent<BoxCollider>();
	colliderVS->SetColliderSize({ 80,20 });
	//colliderVS->DebugRender(true);
	m_pVSModeButton->GetComponent<Transform>()->SetWorldPosition({ 110, 320 });
	const auto fontVS = m_pVSModeButton->AddComponent<FontRenderer>();
	fontVS->SetFont("Fonts/8BitDragon.ttf", 12);
	fontVS->SetText("Versus Mode");

	// Co-Op
	m_pCoopModeButton = new GameObject();
	m_pCoopModeButton->SetParent(this, true);
	auto collidercoOp = m_pCoopModeButton->AddComponent<BoxCollider>();
	collidercoOp->SetColliderSize({ 80,20 });
	//collidercoOp->DebugRender(true);
	m_pCoopModeButton->GetComponent<Transform>()->SetWorldPosition({ 210, 320 });
	const auto fontCoOp = m_pCoopModeButton->AddComponent<FontRenderer>();
	fontCoOp->SetFont("Fonts/8BitDragon.ttf", 12);
	fontCoOp->SetText("Co-Op Mode");
}

StartScreen::~StartScreen()
{
}

void StartScreen::Update()
{
	const auto& serviceLocator = ServiceLocator::GetInstance();
	const auto& input = serviceLocator.InputManager.GetService();
	auto& collisionManager = serviceLocator.CollisionManager.GetService();

	if (input.IsLeftMouseButtonPressed())
	{

		if (collisionManager.IsInsideCollider(input.GetLeftMouseButtonPressed(), m_pVSModeButton->GetComponent<BoxCollider>().get()))
		{
			LevelManager::GetInstance().SetAmountOfPlayers(2);
			LevelManager::GetInstance().SetGameMode(GameMode::Versus);
			LevelManager::GetInstance().LoadNextLevel();
		}

		if (collisionManager.IsInsideCollider(input.GetLeftMouseButtonPressed(), m_pOnePlayerButton->GetComponent<BoxCollider>().get()))
		{
			LevelManager::GetInstance().SetAmountOfPlayers(1);
			LevelManager::GetInstance().SetGameMode(GameMode::SinglePlayer);
			LevelManager::GetInstance().LoadNextLevel();
		}

		if (collisionManager.IsInsideCollider(input.GetLeftMouseButtonPressed(), m_pCoopModeButton->GetComponent<BoxCollider>().get()))
		{
			LevelManager::GetInstance().SetAmountOfPlayers(2);
			LevelManager::GetInstance().SetGameMode(GameMode::CoOp);
			LevelManager::GetInstance().LoadNextLevel();
		}
	}



}