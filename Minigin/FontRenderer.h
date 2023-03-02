#pragma once
#include <SDL_pixels.h>
#include <string>
#include "Component.h"
#include "Font.h"

class Texture2D;
class FontRenderer : public Component
{
public:
	FontRenderer();
	~FontRenderer() override;

	FontRenderer(const FontRenderer& other) = delete;
	FontRenderer(FontRenderer&& other)noexcept = delete;
	FontRenderer& operator=(const FontRenderer& other) = delete;
	FontRenderer& operator=(FontRenderer&& other)noexcept = delete;

	//Called each frame
	virtual void Update(float deltaT) override;

	//Called at a fixed time step
	//Used for physics & networking
	virtual void FixedUpdate(float fixedTimeStep) override;

	//Called after the Update()
	//Used for camera and deletion of objects -> Deletion could be handled by the double buffer pattern
	virtual void LateUpdate(float deltaT) override;

	//Called each frame
	virtual void Render() const override;

	void SetText(const std::string& text);
	void SetFont(const std::string& fontPath, int fontSize);
private:
	void GetColor();
	SDL_Color m_color{};

	std::string m_text{};
	std::shared_ptr<Font> m_font;
	bool m_needsUpdate{ false };
	std::shared_ptr<Texture2D> m_textTexture;
};
