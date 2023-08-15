#include "StartScreen.h"

#include "BoxCollider.h"
#include "FontRenderer.h"
#include "GameObject.h"
#include "StartScreenComponent.h"
#include "TextureRenderer.h"
#include "Transform.h"


StartScreen::StartScreen()
	: m_pGameObject{ new GameObject{} }

	, m_pSinglePlayerButton{ new GameObject{} }
	, m_pMultiplayerButton{ new GameObject{} }
	, m_pCoOpButton{ new GameObject{} }
{
	m_pGameObject->AddComponent<StartScreenComponent>();


	//Texture
	//const auto texture = m_pGameObject->AddComponent<TextureRenderer>();

	//Singleplayer Button
	m_pSinglePlayerButton->GetComponent<Transform>()->SetWorldPosition({ 20, 20 });
	m_pSinglePlayerButton->SetParent(m_pGameObject, true);

	const auto sCollider = m_pSinglePlayerButton->AddComponent<BoxCollider>();
	sCollider->SetColliderSize({ 80, 20 });

	const auto font = m_pSinglePlayerButton->AddComponent<FontRenderer>();
	font->SetFont("Fonts/8BitDragon.ttf", 12);
	font->SetText("Singleplayer");




	//Multiplayer Button
	m_pMultiplayerButton->GetComponent<Transform>()->SetWorldPosition({ 20, 20 });
	m_pMultiplayerButton->SetParent(m_pGameObject, true);
	const auto mCollider = m_pMultiplayerButton->AddComponent<BoxCollider>();
	mCollider->SetColliderSize({ 80, 20 });
	mCollider->SetColliderOffset({ 0, 30 });

	const auto mfont = m_pSinglePlayerButton->AddComponent<FontRenderer>();
	mfont->SetFont("Fonts/8BitDragon.ttf", 12);
	mfont->SetOffset({ 0,30 });
	mfont->SetText("Versus");



	//Co-Op Button
	m_pCoOpButton->GetComponent<Transform>()->SetWorldPosition({ 20, 20 });
	m_pCoOpButton->SetParent(m_pGameObject, true);
	const auto cCollider = m_pCoOpButton->AddComponent<BoxCollider>();
	cCollider->SetColliderSize({ 80, 20 });
	cCollider->SetColliderOffset({ 0, 60 });

	const auto cfont = m_pSinglePlayerButton->AddComponent<FontRenderer>();
	cfont->SetFont("Fonts/8BitDragon.ttf", 12);
	cfont->SetText("Co-Op");
	cfont->SetOffset({ 0,60 });


}

