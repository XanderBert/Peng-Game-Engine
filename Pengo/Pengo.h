#pragma once
#include "GameObject.h"
#include "PengoEvents.h"


class PlayerState;
class IceBlock;
class Observer;
class Pengo final : public GameObject
{
public:
	Pengo();
	virtual ~Pengo() override;

	Pengo(const Pengo& other) = delete;
	Pengo(Pengo&& other)noexcept = delete;
	Pengo& operator=(const Pengo& other) = delete;
	Pengo& operator=(Pengo&& other)noexcept = delete;

	//Called each frame
	virtual void Update() override;
	virtual void LateUpdate() override;
	virtual void OnCollision(GameObject* other, bool isTrigger, bool isSenderTrigger) override;

	PlayerState* GetState() const { return m_pState; }

private:
	PlayerState* m_pState;
	std::shared_ptr<Observer> m_pObserver{ std::make_shared<PengoEvent>() };
	void UpdateState();


};
