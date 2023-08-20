#pragma once
#include <iostream>

#include "Component.h"
#include "FontRenderer.h"
#include "GameObjectStorage.h"
#include "HealthComponent.h"
#include "InputHandler.h"
#include "PacManComponent.h"
#include "Scene.h"
#include "SceneManager.h"
#include "ScoreComponent.h"
#include "ServiceLocator.h"
#include "SkipLevelCommand.h"

class HudComponent final : public Component
{
public:
	HudComponent(GameObject* pParent) : Component(pParent)
	{
		m_pOwner->AddComponent<GameObjectStorage>();

		//Get Pacman('s)
		for (const auto& object : SceneManager::GetInstance().GetActiveScene()->GetObjects())
		{
			if (object->GetComponent<PacManComponent>() != nullptr)
			{
				//Multiplayer
				if (object->GetComponent<InputHandler>()->IsMultiplayer())
				{
					m_pOwner->GetComponent<GameObjectStorage>()->AddGameObjectToVector(object);
					m_HighScore.reserve(2);
					m_HighScore.push_back(0);
					m_HighScore.push_back(0);
					m_IsMultiplayer = true;
				}
				//Singleplayer
				else
				{
					m_pOwner->GetComponent<GameObjectStorage>()->StoreGameObject(object);
					m_HighScore.reserve(1);
					m_HighScore.push_back(0);
					break;
				}
			}
		}
	}




	~HudComponent() override = default;

	HudComponent(const HudComponent& other) = delete;
	HudComponent(HudComponent&& other) = delete;
	HudComponent& operator=(const HudComponent& other) = delete;
	HudComponent& operator=(HudComponent&& other) = delete;


	bool IsMultiplayer() const { return m_IsMultiplayer; }
	std::vector<int> GetHighScore() const { return m_HighScore; }

	void Update() override;
	void FixedUpdate(float /*fixedTimeMStep*/) override {}
	void LateUpdate() override {}
	void Render() override {}

private:

	inline static std::vector<int> m_HighScore{};

	bool m_IsMultiplayer{ false };
	void UpdateSinglePlayer();
	void UpdateMultiPlayer();
};

inline void HudComponent::Update()
{


	if (!m_IsMultiplayer)
	{
		UpdateSinglePlayer();
		return;
	}


	UpdateMultiPlayer();
}



inline void HudComponent::UpdateSinglePlayer()
{

	const auto pacman = m_pOwner->GetComponent<GameObjectStorage>()->GetStoredObject();
	const auto lives = pacman->GetComponent<HealthComponent>()->GetHealth();
	const auto score = pacman->GetComponent<ScoreComponent>()->GetScore();


	const auto font = m_pOwner->GetComponent<FontRenderer>();

	const auto text = "Lives: " + std::to_string(lives) + " Score: " + std::to_string(score);

	if (font->GetText() != text)
	{
		font->SetText(text);

		if (score > m_HighScore[0])
		{
			m_HighScore[0] = score;
		}
	}
}

inline void HudComponent::UpdateMultiPlayer()
{
	//Multiplayer
//
	const auto pacmans = m_pOwner->GetComponent<GameObjectStorage>()->GetStoredObjects();


	//Pacman 0
	const auto lives0 = pacmans[0]->GetComponent<HealthComponent>()->GetHealth();
	const auto score0 = pacmans[0]->GetComponent<ScoreComponent>()->GetScore();

	//Pacman 1
	const auto lives1 = pacmans[1]->GetComponent<HealthComponent>()->GetHealth();
	const auto score1 = pacmans[1]->GetComponent<ScoreComponent>()->GetScore();


	//Set text
	const auto font = m_pOwner->GetComponent<FontRenderer>();
	auto text = "Lives: " + std::to_string(lives0) + " Score: " + std::to_string(score0);
	text += " \nLives: " + std::to_string(lives1) + " Score: " + std::to_string(score1);

	//Only Update if text updated
	if (font->GetText() != text)
	{
		if (score0 > m_HighScore[0])
		{
			m_HighScore[0] = score0;
		}

		if (score1 > m_HighScore[1])
		{
			m_HighScore[1] = score1;
		}

		font->SetText(text);
	}
}