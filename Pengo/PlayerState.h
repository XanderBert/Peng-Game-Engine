#pragma once
#include "InputManager.h"
#include "GameObject.h"

class PlayerState
{
public:
	PlayerState(GameObject* object) : m_pActor{ object } {}
	virtual ~PlayerState() = default;

	virtual PlayerState* HandleInput() = 0;
	virtual void Update() = 0;
	virtual void OnCollision(GameObject* other) = 0;

private:
	virtual void OnEnter() = 0;
protected:
	GameObject* m_pActor{};
};

