#pragma once
#include "Component.h"
#include "Subject.h"
#include "PacManEventObserver.h"
#include "glm/vec2.hpp"

class PacManComponent final : public Component
{
public:
	PacManComponent(GameObject* pParent) : Component(pParent), m_pSubject(std::make_unique<Subject>())
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
	void Notify(GameEvent event, GameObject* object);

	glm::vec2 GetSpawnPos() const { return m_SpawnPos; }

private:

	glm::vec2 m_SpawnPos{ 104, 132 };
	std::unique_ptr<Subject> m_pSubject;
};
