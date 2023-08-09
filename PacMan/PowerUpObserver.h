#pragma once
#include "Observer.h"
enum class GameEvent
{
	PowerUpEaten,
	PacDotEaten,
	GhostEaten,
	PacManDied,

};

class PowerUpObserver final : public Observer
{
public:
	void Notify(GameObject* gameObject, GameEvent event) override;
	~PowerUpObserver()override;
};

