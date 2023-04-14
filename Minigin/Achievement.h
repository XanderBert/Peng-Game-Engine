#pragma once
#include "Observer.h"
#include "Event.h"

class Achievement final : public Observer
{
public:
	void Notify(Event::GameEvent event, GameActor* /*actor*/) override
	{
		switch (event) {
		case Event::GameEvent::ActorDied:
			{
			break;
			}
		
		case Event::GameEvent::ActorFell:
			{
			break;
			}
		}
	}
private:
	void Unlock(Achievement achievement)
	{
		// code to unlock an achievement...
	}
};
