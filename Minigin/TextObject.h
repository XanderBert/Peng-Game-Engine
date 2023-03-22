#pragma once
#include <string>
#include <memory>

#include "TextObject.h"
#include "Transform.h"

class Component;
class Font;
class Texture2D;
class TextObject : public GameObject
{
public:
	TextObject(const std::string& text, std::shared_ptr<Font> font);
	virtual ~TextObject() = default;

	TextObject(const TextObject& other) = delete;
	TextObject(TextObject&& other) = delete;
	TextObject& operator=(const TextObject& other) = delete;
	TextObject& operator=(TextObject&& other) = delete;

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

private:
	bool m_needsUpdate;
	std::string m_text;

	std::shared_ptr<Font> m_font;
	std::shared_ptr<Texture2D> m_textTexture;
};

