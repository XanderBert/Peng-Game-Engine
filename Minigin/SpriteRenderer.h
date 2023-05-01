#pragma once
#include "Component.h"
#include "TextureRenderer.h"
#include "Transform.h"

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
	void SetSourceRect(const glm::vec2& position, const glm::vec2 size);

private:
	glm::vec2 m_SpriteSize{};

	enum class MovmentDirection
	{
		Up,
		Down,
		Left,
		Right
	};

};
