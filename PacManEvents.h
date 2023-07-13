#pragma once
#include "Observer.h"
#include "GameObject.h"

enum class GameEvent
{
	PacManKilled,
	PacManClearedLevel,
	GhostKilled
};


class PacManEvent : public Observer
{
public:
	PacManEvent() = default;
	virtual ~PacManEvent() = default;

	PacManEvent(const PacManEvent& other) = delete;
	PacManEvent(PacManEvent&& other)noexcept = delete;
	PacManEvent& operator=(const PacManEvent& other) = delete;
	PacManEvent& operator=(PacManEvent&& other)noexcept = delete;


	//Do not call any level loading functions here, this will cause undefined behaviour
	//The deletion of items happens in a certain order and that will disrupt that order

	virtual void Notify(GameObject* /*object*/, GameEvent event) override
	{
		switch (event)
		{

		case GameEvent::SnowBeeKilled:
		{
			LevelManager::GetInstance().AddScore(100);
			LevelManager::GetInstance().SnowBeeDied();
			break;
		}
		case GameEvent::PengoKeyboardKilled:
		{
			LevelManager::GetInstance().PlayerDied();
			break;
		}
		case GameEvent::PengoControllerKilled:
		{
			LevelManager::GetInstance().PlayerDied();
			break;
		}
		case GameEvent::DiamondBlockThreeInARow:
		{
			LevelManager::GetInstance().AddScore(200);
			LevelManager::GetInstance().DiamondThreeInARow();
			break;
		}

		}
	}
};
