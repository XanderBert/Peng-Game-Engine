#pragma once
#include "Event.h"

class GameEvent : public Event
{
public:
	GameEvent() = default;
	virtual  ~GameEvent() override;

	GameEvent(const GameEvent& other) = delete;
	GameEvent(GameEvent&& other)noexcept = delete;
	GameEvent& operator=(const GameEvent& other) = delete;
	GameEvent& operator=(GameEvent&& other)noexcept = delete;

};
