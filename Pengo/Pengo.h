#pragma once
#include "GameActor.h"
#include "IceBlock.h"
#include "PengoIceBlockTrigger.h"
#include "PlayerCommands.h"
#include "PlayerState.h"

class Pengo final : public GameActor
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
	virtual void OnCollision(GameObject* other) override;

	PlayerState* GetState() const { return m_pState; }
	PengoIceBlockTrigger* GetPengoIceBlockTrigger() const { return m_pIceBlockTrigger; }

private:
	PengoIceBlockTrigger* m_pIceBlockTrigger{};
	PlayerState* m_pState;

	//Multiplies the the direction of the previous location to prevent tunneling
	float m_TunnelingMultiplier{ 3.f };

	void StopMovement() const;
	void UpdateState();


};
