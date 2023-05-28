#pragma once
#include "Component.h"
#include "TextureRenderer.h"
#include "TimeM.h"
#include "Transform.h"
#include "unordered_map"

enum class MovementDirection
{
	Up = 0,
	Down = 1,
	Left = 2,
	Right = 3,
	None = 4
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
	virtual void FixedUpdate(float fixedTimeMStep) override;

	//Called after the Update()
	//Used for camera and deletion of objects -> Deletion could be handled by the double buffer pattern
	virtual void LateUpdate() override;

	//Called each frame
	virtual void Render() override;

	//Set the texture of the TextureRenderer Component
	//This does not need to be called if the Texture is already been set in the  TextureRenderer Component
	void SetTexture(const std::string& texturePath);


	void SetSpriteSize(const glm::vec2& spriteSize) { m_SpriteSize = spriteSize; }
	void AddSpriteFrame(const glm::vec2& position, MovementDirection direction);

	void SetOffset(const glm::vec2& offset);

	void Play() { m_IsPlaying = true; }
	void Pause() { m_IsPlaying = false; }
	bool IsPlaying() const { return  m_IsPlaying; }

	void SetFrameTime(const float frameTime) { m_FrameTime = frameTime; }

	size_t GetLastSpriteIndexForCurrentDirection() const { return m_MovementDirectionMap.find(m_MovementDirection)->second.size() - 1; };
	size_t GetCurrentSpriteIndexForCurrentDirection() const { return m_AnimationFrame; }


	bool IsAnimationFinished() const
	{
		return GetCurrentSpriteIndexForCurrentDirection() == GetLastSpriteIndexForCurrentDirection();
	}

	void SetAnimationFrame(int animationFrame) { m_AnimationFrame = animationFrame; }
private:
	glm::vec2 m_SpriteSize{};

	MovementDirection m_MovementDirection{ MovementDirection::Right };
	std::unordered_map<MovementDirection, std::vector<glm::vec2>> m_MovementDirectionMap{};
	glm::vec2 m_Offset{};

	void SetMovementDirection(const glm::vec2& direction);
	void SetMovementDirection(MovementDirection value);
	MovementDirection ConvertMovementDirection(const glm::vec2& direction);
	MovementDirection GetMovementDirection() const { return m_MovementDirection; }
	glm::vec2 GetMovementDirectionVector() const;

	void SetSourceRect(const glm::vec2& position) const;
	void UpdateAnimationFrame();

	int m_AnimationFrame{};
	float m_AccumulatedFrameTime{};
	float m_FrameTime{};

	float m_TimeFromMovementToStandStill{};
	float m_AccumulatedMoveToStandstillTime{};

	glm::vec2 m_OldDirection{};

	bool m_IsNotInit{true};
	bool m_IsPlaying{ true };

};
