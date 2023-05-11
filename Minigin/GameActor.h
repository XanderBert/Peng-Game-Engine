#pragma once
#include <memory>
#include <glm/vec2.hpp>

#include "GameObject.h"
#include "Observer.h"
#include "Event.h"
#include "Achievement.h"


class GameActor : public GameObject
{
public:
	GameActor();
	virtual ~GameActor() override;

	GameActor(const GameActor& other) = delete;
	GameActor(GameActor&& other)noexcept = delete;
	GameActor& operator=(const GameActor& other) = delete;
	GameActor& operator=(GameActor&& other)noexcept = delete;

	//Called each frame
	virtual void Update() override;

	void Jump();
	virtual void Move(const glm::vec2& direction);
	void Die();
	virtual void Attack() {}

	void TakeDammage(const int dammage);
	int GetHealth() const { return m_Health; }

	std::string* GetHealthAsString()
	{
		m_HealthString = std::to_string(m_Health);
		return &m_HealthString;
	}

	int GetPoints() const { return  m_Points; }
	std::string* GetPointsAsString() {
		m_PointString = std::to_string(m_Points);
		return &m_PointString;
	}
	void GainPoints(int ammountOfPoints);

	bool GetUsesController() const { return m_UsesController; }

	//This can range between 0 & 4
	void SetControllerIndex(int index);
	int GetControllerIndex() const { return m_ControllerID; }

	void AddObeserver(std::shared_ptr<Observer> observer)
	{
		m_Observers.push_back(observer);
	}

	void RemoveObserver(Observer* observer)
	{
		m_Observers.erase(std::remove_if(m_Observers.begin(), m_Observers.end(), [observer](const std::shared_ptr<Observer>& ptr) {
			if (ptr.get() == observer) {
				return true;
			}
			return false;
			}), m_Observers.end());
	}


	virtual void OnCollision(GameObject* other) override;

protected:
	void NotifyObserver(const GameEvent event) const
	{
		for (size_t i{}; i < m_Observers.size(); ++i)
		{
			m_Observers[i]->Notify(event);
		}
	}

private:
	bool m_UsesController{ false };
	int m_ControllerID{};
	float m_Speed{ 50.f };
	int m_Health{ 3 };
	std::string m_HealthString{ std::to_string(m_Health) };
	int m_Points{ 0 };
	std::string m_PointString{ std::to_string(m_Points) };
	std::vector<std::shared_ptr<Observer>> m_Observers;

	void SetTextureDirection(const glm::vec2& direction);
};
