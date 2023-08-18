#pragma once
#include "Observer.h"
enum class GameEvent
{
	PowerUpEaten,
	PacDotEaten,
	GhostEaten,
	FruitEaten,
	PacManDied,
};

class PacManEventObserver final : public Observer
{
public:
	void Notify(GameObject* gameObject, GameEvent event) override;
	~PacManEventObserver()override;
private:
	bool IsLevelCompleted();
	void LoadNextLevel();
	int m_PacDotEatenSoundIndex{};
};

