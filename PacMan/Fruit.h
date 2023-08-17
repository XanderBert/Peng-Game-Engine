#pragma once

class GameObject;
class Fruit final
{
public:
	Fruit();
	~Fruit() = default;

	Fruit(const Fruit& other) = delete;
	Fruit(Fruit&& other) noexcept = delete;
	Fruit& operator=(const Fruit& other) = delete;
	Fruit& operator=(Fruit&& other) noexcept = delete;

	GameObject* GetGameObject() const { return m_pGameObject; }

private:
	GameObject* m_pGameObject{};
};

