#pragma once

class GameObject;
class Hud final
{
public:
	Hud();
	~Hud() = default;

	Hud(const Hud& other) = delete;
	Hud(Hud&& other) = delete;
	Hud& operator=(const Hud& other) = delete;
	Hud& operator=(Hud&& other) = delete;

	GameObject* GetGameObject() const { return m_pGameObject; }
private:
	GameObject* m_pGameObject{};
};
