#include "Achievement.h"
#include "Event.h"

void Achievement::Notify(GameEvent event)
{
	{
		switch (event)
		{

			case GameEvent::Actor100Points:
			{
				Unlock(EAchievements::ACH_WIN_ONE_GAME);
				break;
			}

			case GameEvent::ActorFell:
			{
				break;
			}
		}
	}
}
