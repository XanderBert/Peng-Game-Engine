#pragma once
#include <memory>
#include <SDL_rect.h>
#include <string>
#include "Component.h"
#include "glm/vec2.hpp"

class Texture2D;
class TextureRenderer final : public Component
{
public:
	TextureRenderer(GameObject* owner);
	virtual ~TextureRenderer() override;

	TextureRenderer(const TextureRenderer& other) = delete;
	TextureRenderer(TextureRenderer&& other) = delete;
	TextureRenderer& operator=(const TextureRenderer& other) = delete;
	TextureRenderer& operator=(TextureRenderer&& other) = delete;

	//Called each frame
	void Update() override;

	//Called at a fixed time step
	//Used for physics & networking
	void FixedUpdate(float fixedTimeMStep) override;

	//Called after the Update()
	//Used for camera and deletion of objects -> Deletion could be handled by the double buffer pattern
	void LateUpdate() override;

	//Called each frame
	void Render() override;

	void SetTexture(const std::string& texturePath);
	glm::vec2 GetSize();
	void SetSourceRect(const glm::vec2& position, const glm::vec2 size);
private:
	std::shared_ptr<Texture2D> m_pTexture{};
	SDL_Rect m_SrcRect{};
	bool m_usesSrcRect{ false };
};