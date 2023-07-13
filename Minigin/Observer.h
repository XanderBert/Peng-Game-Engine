#pragma once

class GameObject;
enum class GameEvent;

class Observer
{
public:
	Observer() = default;
	virtual  ~Observer() = default;

	Observer(const Observer& other) = delete;
	Observer(Observer&& other)noexcept = delete;
	Observer& operator=(const Observer& other) = delete;
	Observer& operator=(Observer&& other)noexcept = delete;

	virtual void Notify(GameObject* gameObject, GameEvent event) = 0;
};