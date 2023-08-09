#pragma once
#include "Component.h"
#include "PowerUpObserver.h"

class PacManComponent final : public Component
{
public:
	PacManComponent(GameObject* pParent) : Component(pParent)
	{}
	~PacManComponent() override = default;

	PacManComponent(const PacManComponent& other) = delete;
	PacManComponent(PacManComponent&& other) = delete;
	PacManComponent& operator=(const PacManComponent& other) = delete;
	PacManComponent& operator=(PacManComponent&& other) = delete;

	void Update() override {}
	void FixedUpdate(float /*fixedTimeMStep*/) override {}
	void LateUpdate() override {}
	void Render() override {}

	void AttachObserver(Observer* observer);
	void NotifyObservers(GameEvent event, GameObject* object);

private:
	std::vector<std::unique_ptr<Observer>> m_Observers;

};
