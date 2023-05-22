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


enum class Action
{
	Move = 0,
	Attack = 1,
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
	void SetMovementDirection(MovementDirection value);
	void SetMovementDirection(const glm::vec2& direction);
	MovementDirection GetMovementDirection() const { return m_MovementDirection; }

	void SetSpriteSize(const glm::vec2& spriteSize) { m_SpriteSize = spriteSize; }
	void AddSpriteFrame(const glm::vec2& position, MovementDirection direction);

	void SetActionOffset(const glm::vec2& offset, Action action);
	void SetAction(Action action) { m_Action = action; }

	void Play() { m_IsPlaying = true; }
	void Pause() { m_IsPlaying = false; }
	bool IsPlaying() const { return  m_IsPlaying; }

	void SetFrameTime(const float frameTime) { m_FrameTime = frameTime; }

	size_t GetLastSpriteIndexForCurrentDirection() const { return m_MovementDirectionMap.find(m_MovementDirection)->second.size() - 1; };
	size_t GetCurrentSpriteIndexForCurrentDirection() const { return m_AnimationFrame; }

private:
	glm::vec2 m_SpriteSize{};

	MovementDirection m_MovementDirection{ MovementDirection::Right };
	std::unordered_map<MovementDirection, std::vector<glm::vec2>> m_MovementDirectionMap{};

	Action m_Action{ Action::Move };
	std::unordered_map<Action, glm::vec2> m_ActionmapOffset{};

	void SetSourceRect(const glm::vec2& position);

	int m_AnimationFrame{};
	float m_AccumulatedFrameTime{};
	float m_FrameTime{};

	float m_TimeFromMovementToStandStill{};
	float m_AccumulatedMoveToStandstillTime{};

	bool m_IsPlaying{ true };

};
