#pragma once

class GameObject;
class StartScreen
{
public:
	StartScreen();
	~StartScreen() = default;

	//void Initialize();

	StartScreen(const StartScreen& other) = delete;
	StartScreen(StartScreen&& other) noexcept = delete;
	StartScreen& operator=(const StartScreen& other) = delete;
	StartScreen& operator=(StartScreen&& other) noexcept = delete;

	GameObject* GetGameObject() const { return m_pGameObject; }


private:
	GameObject* m_pGameObject{};
	GameObject* m_pSinglePlayerButton{};
	GameObject* m_pMultiplayerButton{};
	GameObject* m_pCoOpButton{};
};

