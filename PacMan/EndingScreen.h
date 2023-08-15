#pragma once

class GameObject;
class EndingScreen
{
public:
	EndingScreen();
	~EndingScreen() = default;

	EndingScreen(const EndingScreen& other) = delete;
	EndingScreen(EndingScreen&& other) noexcept = delete;
	EndingScreen& operator=(const EndingScreen& other) = delete;
	EndingScreen& operator=(EndingScreen&& other) noexcept = delete;

	GameObject* GetGameObject() const { return m_pGameObject; }

private:
	GameObject* m_pGameObject{};

};
