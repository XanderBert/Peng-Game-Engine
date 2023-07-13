#pragma once

class GameObject;
class PacMan final
{
public:
	PacMan();
	~PacMan() = default;
	
	PacMan(const PacMan& other) = delete;
	PacMan(PacMan&& other) = delete;
	PacMan& operator=(const PacMan& other) = delete;
	PacMan& operator=(PacMan&& other) = delete;

	GameObject* GetPacMan() const { return m_pGameObject; }
private:
	GameObject* m_pGameObject{};
};


