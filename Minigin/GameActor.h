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

	virtual void OnCollision(GameObject* other) override;

	float GetVelocity() const { return  m_Velocity; }
	void SetVelocity(const float velocity) { m_Velocity = velocity; }



private:
	bool m_UsesController{ false };
	int m_ControllerID{};
	float m_Velocity{ 50.f };

	int m_Health{ 3 };
	std::string m_HealthString{ std::to_string(m_Health) };
	int m_Points{ 0 };
	std::string m_PointString{ std::to_string(m_Points) };
	std::vector<std::shared_ptr<Observer>> m_Observers;

	//void SetTextureDirection(const glm::vec2& direction);
};
