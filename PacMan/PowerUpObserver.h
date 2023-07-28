#pragma once
#include "Observer.h"
class PowerUpObserver final : public Observer
{
public:
	void Notify(GameObject* gameObject, GameEvent event) override;
	~PowerUpObserver()override;
};

