#pragma once
#include <string>
#include <memory>
#include "GameObject.h"
#include "Transform.h"
#include  "Component.h"

namespace dae
{
	class Font;
	class Texture2D;
	class TextObject : public Component
	{
	public:
		//Called each frame
		void Update([[maybe_unused]] float deltaT) override;

		//Called at a fixed time step
		//Used for physics & networking
		void FixedUpdate([[maybe_unused]] float fixedTimeStep) override;

		//Called after the Update()
		//Used for camera and deletion of objects -> Deletion could be handled by the double buffer pattern
		void LateUpdate([[maybe_unused]] float deltaT) override;

		//Called each frame
		void Render() const override;

		void SetText(const std::string& text);
		void SetPosition(float x, float y);

		TextObject(const std::string& text, std::shared_ptr<Font> font);
		virtual ~TextObject() = default;
		TextObject(const TextObject& other) = delete;
		TextObject(TextObject&& other) = delete;
		TextObject& operator=(const TextObject& other) = delete;
		TextObject& operator=(TextObject&& other) = delete;
	private:
		bool m_needsUpdate;
		std::string m_text;
		Transform m_transform{};
		std::shared_ptr<Font> m_font;
		std::shared_ptr<Texture2D> m_textTexture;
	};
}
