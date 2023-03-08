#pragma once
#include <SDL_pixels.h>

#include "Component.h"
class Color : public Component
{
public:
	Color(GameObject* owner);
	~Color() override;

	Color(const Color& other) = delete;
	Color(Color&& other)noexcept = delete;
	Color& operator=(const Color& other) = delete;
	Color& operator=(Color&& other)noexcept = delete;

	//Called each frame
	virtual void Update() override;

	//Called at a fixed time step
	//Used for physics & networking
	virtual void FixedUpdate(float fixedTimeStep) override;

	//Called after the Update()
	//Used for camera and deletion of objects -> Deletion could be handled by the double buffer pattern
	virtual void LateUpdate() override;

	//Called each frame
	virtual void Render() const override;

	SDL_Color GetColor() const;

	//RGB Color range from 0 -> 255
	void SetColor(const SDL_Color& color);
private:
	SDL_Color m_color{ 255, 255, 255 };
};
