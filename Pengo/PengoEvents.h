#pragma once
#include "Observer.h"
#include "GameObject.h"
#include "ServiceLocator.h"
#include "SpriteRenderer.h"
#include "PlayerState.h"
#include "Pengo.h"
#include "IceBlock.h"

enum class GameEvent
{
	CollidingWithIce,
	IceBlockDestroyed,
	SnowBeeKilled
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

		case GameEvent::CollidingWithIce:
		{


			break;
		}
		}
	};
};
