#pragma once
#include <memory>
#include <glm/vec2.hpp>

#include "GameObject.h"
#include "Observer.h"
#include "Event.h"

class GameObject;

class GameActor : public GameObject
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
	bool GetUsesController() const { return m_UsesController; }

	//This can range between 0 & 4
	void SetControllerIndex(int index);
	int GetControllerIndex() const { return m_ControllerID; }

	void AddObeserver(Observer* observer)
	{
		m_Observers.push_back(observer);
	}

	void RemoveObserver(Observer* observer)
	{
		m_Observers.erase(std::remove(m_Observers.begin(), m_Observers.end(), observer), m_Observers.end());
	}

protected:

	void NotifyObserver(const Event::GameEvent event)
	{
		for (const auto observer : m_Observers){ observer->Notify(event, this); }
	}

private:
	bool m_UsesController{ false };
	int m_ControllerID{};
	float m_Speed{ 150.f };

	std::vector<Observer*> m_Observers;
};
