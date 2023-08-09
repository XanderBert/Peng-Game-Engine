#pragma once
#include <iostream>

#include "Component.h"
#include "FontRenderer.h"
#include "GameObjectStorage.h"
#include "HealthComponent.h"
#include "PacManComponent.h"
#include "Scene.h"
#include "SceneManager.h"
#include "ScoreComponent.h"

class HudComponent final : public Component
{
public:
	HudComponent(GameObject* pParent) : Component(pParent)
	{
		for (const auto& object : SceneManager::GetInstance().GetActiveScene()->GetObjects())
		{
			if (object->GetComponent<PacManComponent>())
			{
				m_pOwner->AddComponent<GameObjectStorage>()->StoreGameObject(object);
			}
		}


		m_pOwner->AddComponent<GameObjectStorage>();
	}
	~HudComponent() override = default;

	HudComponent(const HudComponent& other) = delete;
	HudComponent(HudComponent&& other) = delete;
	HudComponent& operator=(const HudComponent& other) = delete;
	HudComponent& operator=(HudComponent&& other) = delete;

	void Update() override;
	void FixedUpdate(float /*fixedTimeMStep*/) override {}
	void LateUpdate() override {}
	void Render() override {}

};

inline void HudComponent::Update()
{
	const auto pacman = m_pOwner->GetComponent<GameObjectStorage>()->GetStoredObject();
	const auto lives = pacman->GetComponent<HealthComponent>()->GetHealth();
	const auto score = pacman->GetComponent<ScoreComponent>()->GetScore();


	const auto font = m_pOwner->GetComponent<FontRenderer>();

	if (font->GetText() != "Lives: " + std::to_string(lives) + "\tScore: " + std::to_string(score))
	{
		font->SetText("Lives: " + std::to_string(lives) + "\tScore: " + std::to_string(score));
	}

}
