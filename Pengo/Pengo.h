#pragma once
#include "GameActor.h"

class Pengo final : public GameActor
{
public:
	Pengo();
	virtual ~Pengo() override;

	Pengo(const Pengo& other) = delete;
	Pengo(Pengo&& other)noexcept = delete;
	Pengo& operator=(const Pengo& other) = delete;
	Pengo& operator=(Pengo&& other)noexcept = delete;

	void Attack() override;

	//Called each frame
	virtual void Update() override;
	virtual void OnCollision(GameObject* other) override;
private:
	GameObject* m_CollidingObject{};
	bool m_IsCollidingWithIce{};
	void StopMovement() const;
};
