#pragma once
class GameActor;
class Event;

class Observer
{
public:

	Observer() = default;
	virtual  ~Observer() = default;

	Observer(const Observer& other) = delete;
	Observer(Observer&& other)noexcept = delete;
	Observer& operator=(const Observer& other) = delete;
	Observer& operator=(Observer&& other)noexcept = delete;

	virtual void Notify(Event& event, GameActor* actor);
};
