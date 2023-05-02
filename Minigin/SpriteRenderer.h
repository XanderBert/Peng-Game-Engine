#pragma once
#include "Component.h"
#include "TextureRenderer.h"
#include "Time.h"
#include "Transform.h"
#include "unordered_map"

enum class MovementDirection
{
	Up = 0,
	Down = 1,
	Left = 2,
	Right = 3
};


class SpriteRenderer : public Component
{
public:
	SpriteRenderer(GameObject* owner);
	~SpriteRenderer() override;

	SpriteRenderer(const SpriteRenderer& other) = delete;
	SpriteRenderer(SpriteRenderer&& other)noexcept = delete;
	SpriteRenderer& operator=(const SpriteRenderer& other) = delete;
	SpriteRenderer& operator=(SpriteRenderer&& other)noexcept = delete;

	//Called each frame
	virtual void Update() override;

	//Called at a fixed time step
	//Used for physics & networking
	virtual void FixedUpdate(float fixedTimeStep) override;

	//Called after the Update()
	//Used for camera and deletion of objects -> Deletion could be handled by the double buffer pattern
	virtual void LateUpdate() override;

	//Called each frame
	virtual void Render() override;

	//Set the texture of the TextureRenderer Component
	//This does not need to be called if the Texture is already been set in the  TextureRenderer Component
	void SetTexture(const std::string& texturePath);
	void SetMovementDirection(MovementDirection value)
	{
		m_MovementDirection = value;
		m_AccumulatedMoveToStandstillTime = 0.f;
	}

	void SetSpriteSize(const glm::vec2& spriteSize) { m_SpriteSize = spriteSize; }

private:
	glm::vec2 m_SpriteSize{};
	MovementDirection m_MovementDirection{ MovementDirection::Right };
	std::unordered_map<MovementDirection, glm::vec2> m_MovementDirectionMap{};

	void SetSourceRect(const glm::vec2& position);


	float m_TimeFromMovementToStandStill{};
	float m_AccumulatedMoveToStandstillTime{};
};
