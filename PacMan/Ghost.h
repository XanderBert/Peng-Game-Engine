#pragma once

class GameObject;
class Ghost final
{
public:
	Ghost();
	~Ghost() = default;

	Ghost(const Ghost& other) = delete;
	Ghost(Ghost&& other) = delete;
	Ghost& operator=(const Ghost& other) = delete;
	Ghost& operator=(Ghost&& other) = delete;

	GameObject* GetGameObject() const { return m_pGameObject; }
private:
	GameObject* m_pGameObject{};
};
