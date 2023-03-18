#pragma once
#include <array>
#include <memory>
#include <string>

#include "Component.h"

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
	void FixedUpdate(float fixedTimeStep) override;

	//Called after the Update()
	//Used for camera and deletion of objects -> Deletion could be handled by the double buffer pattern
	void LateUpdate() override;

	//Called each frame
	void Render() override;

	void SetTexture(const std::string& texturePath);
private:
	std::shared_ptr<Texture2D> m_pTexture{};
	//std::array<int, 100000000> bigData{};
};