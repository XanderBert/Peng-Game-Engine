#pragma once
#include "Observer.h"
#include "GameObject.h"
#include "LevelManager.h"


enum class GameEvent
{
	IceBlockDestroyed,
	SnowBeeKilled,
	PengoControllerKilled,
	PengoKeyboardKilled,
	NewLevelLoaded,
	DiamondBlockThreeInARow,
};


class PengoEvent : public Observer
{
public:
	PengoEvent() = default;
	virtual ~PengoEvent() = default;

	PengoEvent(const PengoEvent& other) = delete;
	PengoEvent(PengoEvent&& other)noexcept = delete;
	PengoEvent& operator=(const PengoEvent& other) = delete;
	PengoEvent& operator=(PengoEvent&& other)noexcept = delete;


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
