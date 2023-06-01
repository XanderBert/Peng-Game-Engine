#pragma once
#include "GameObject.h"

class StartScreen final : public GameObject
{
public:
	StartScreen();
	~StartScreen();

	StartScreen(const StartScreen& other) = delete;
	StartScreen(StartScreen&& other)noexcept = delete;
	StartScreen& operator=(const StartScreen& other) = delete;
	StartScreen& operator=(StartScreen&& other)noexcept = delete;

	//Called each frame
	virtual void Update() override;
private:
	glm::vec2 m_Offset{ 50,50 };
	glm::vec2 m_ScreenSize{ 224 + m_Offset.x, 256 + m_Offset.y };
};
