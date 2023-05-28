#pragma once
#include "Component.h"


template <typename TPlayer>
class GameActorComponent final : public Component
{
public:
	GameActorComponent() = default;
	virtual ~GameActorComponent() override;

	GameActorComponent(const GameActorComponent& other) = delete;
	GameActorComponent(GameActorComponent&& other) noexcept = delete;
	GameActorComponent& operator=(const GameActorComponent& other) = delete;
	GameActorComponent& operator=(GameActorComponent&& other) noexcept = delete;


	//Called each frame
	virtual void Update() override;

	//Called at a fixed time step
	//Used for physics & networking
	virtual void FixedUpdate(float fixedTimeMStep) override;

	//Called after the Update()
	//Used for camera and deletion of objects -> Deletion could be handled by the double buffer pattern
	virtual void LateUpdate() override;

	//Called each frame
	virtual void Render() override;

	virtual void OnCollision(GameObject* other) override;

	TPlayer* GetPlayer()
	{
		if (m_Player)
		{
			return m_Player;
		}

		throw std::exception("Actor Object is not set");
	}

	void SetPlayer(TPlayer* player)
	{
		m_Player = player;
	}


	float GetVelocity() const { return  m_Velocity; }
	void SetVelocity(const float velocity) { m_Velocity = velocity; }



private:
	float m_Velocity{ 50 };
	TPlayer* m_Player;
};

template <typename TPlayer>
void GameActorComponent<TPlayer>::Update()
{
	if (m_Player)
	{
		m_Player->Update();
	}
}

template <typename TPlayer>
void GameActorComponent<TPlayer>::FixedUpdate(float fixedTimeMStep)
{
	if (m_Player)
	{
		m_Player->FixedUpdate(fixedTimeMStep);
	}
}

template <typename TPlayer>
void GameActorComponent<TPlayer>::LateUpdate()
{
	if (m_Player)
	{
		m_Player->LateUpdate();
	}
}

template <typename TPlayer>
void GameActorComponent<TPlayer>::Render()
{
	if (m_Player)
	{
		m_Player->Render();
	}
}

template <typename TPlayer>
void GameActorComponent<TPlayer>::OnCollision(GameObject* other)
{
	if (m_Player)
		m_Player->OnCollision(other);
}
