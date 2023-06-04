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

		}
	}
};
