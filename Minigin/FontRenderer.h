#pragma once
#include <SDL_pixels.h>
#include <string>
#include "Component.h"
#include "Font.h"
#include "TimeM.h"

class Texture2D;
class FontRenderer : public Component
{
public:
	FontRenderer(GameObject* owner);
	~FontRenderer() override;

	FontRenderer(const FontRenderer& other) = delete;
	FontRenderer(FontRenderer&& other)noexcept = delete;
	FontRenderer& operator=(const FontRenderer& other) = delete;
	FontRenderer& operator=(FontRenderer&& other)noexcept = delete;

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

	void SetText(const std::string& text);
	void SetFont(const std::string& fontPath, int fontSize);

	void SetOffset(const glm::vec2& offset);
	glm::vec2 GetOffset() const;

private:
	void GetColor();
	SDL_Color m_color{};
	std::string m_text{};
	std::shared_ptr<Font> m_font;
	bool m_needsUpdate{ false };
	std::shared_ptr<Texture2D> m_textTexture;
	glm::vec2 m_Offset{};
};
