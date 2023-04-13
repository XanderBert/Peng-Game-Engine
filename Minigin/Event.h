#pragma once

class Event
{
public:
	Event() = default;
	virtual ~Event() = default;

	Event(const Event& other) = delete;
	Event(Event&& other)noexcept = delete;
	Event& operator=(const Event& other) = delete;
	Event& operator=(Event&& other)noexcept = delete;

};