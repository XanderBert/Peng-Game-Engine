#pragma once

class Event final
{
public:
	Event() = default;
	~Event() = default;

	//Event(const Event& other) = delete;
	//Event(Event&& other)noexcept = delete;
	//Event& operator=(const Event& other) = delete;
	//Event& operator=(Event&& other)noexcept = delete;

	enum class GameEvent
	{
		ActorDied,
		ActorFell
	};

};