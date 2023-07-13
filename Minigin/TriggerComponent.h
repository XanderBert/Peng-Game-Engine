#pragma once
#include "Component.h"
#include "ServiceLocator.h"

class TriggerComponent final : public Component
{
public:
	TriggerComponent(GameObject* owner);
	virtual ~TriggerComponent() override;

	TriggerComponent(const TriggerComponent& other) = delete;
	TriggerComponent(TriggerComponent&& other) noexcept = delete;
	TriggerComponent& operator=(const TriggerComponent& other) = delete;
	TriggerComponent& operator=(TriggerComponent&& other) noexcept = delete;

	void Update() override;
	void FixedUpdate(float fixedTimeMStep) override;
	void LateUpdate() override;
	void Render() override;

	void SetColliderSize(const glm::vec2& size) const;
	void SetColliderOffset(const glm::vec2& offset);
	void SetOffsetMultiplier(float multiplier);

	void DebugRender(bool isDebugRendering) const;

	SDL_Rect GetTriggerRect()const;

	std::vector<GameObject*> GetCollidingObjects() const;


	void DisableTrigger();
	void EnableTrigger();
	//TODO
	std::string GetTag() const;
	void SetTag(const std::string& tag);

private:
	glm::vec2 m_Offset;
	BoxCollider* m_pBoxCollider{};
	bool m_IsTriggerActive{ true };

	//When set to true, the trigger will change its location according to the object forward vector.
	//Otherwise it will stay static at the location of the object
	bool m_IsPlacedInFrontOfObject{ true };
	float m_OffsetMultiplier{ 2.f };
	std::string m_Tag{};
};
