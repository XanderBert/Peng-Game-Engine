#pragma once
#include <memory>
#include <glm/vec2.hpp>

#include "GameObject.h"


//Could GameActor be the same as a GameObject?
//Can GameActor be a wrapper around a GameObject?
//Why would i need a wrapper?
//What if i want 2 players but just a different texture?
//So yes, GameActor will be a wrapper around a GameObject

//What is the point of a wrapper?
//What is an actor?

//And Actor is a playable GameObject -> so it is a wrapper and it has a input component?



class GameObject;

class GameActor final : public GameObject
{
public:
	GameActor();
	virtual ~GameActor() override;

	GameActor(const GameActor& other) = delete;
	GameActor(GameActor&& other)noexcept = delete;
	GameActor& operator=(const GameActor& other) = delete;
	GameActor& operator=(GameActor&& other)noexcept = delete;

	void Jump();
	void Move(const glm::vec2& direction);
};
