#pragma once

class GameObject;
class FpsCounter final
{
public:
	FpsCounter();
	~FpsCounter() = default;

	FpsCounter(const FpsCounter& other) = delete;
	FpsCounter(FpsCounter&& other) noexcept = delete;
	FpsCounter& operator=(const FpsCounter& other) = delete;
	FpsCounter& operator=(FpsCounter&& other) noexcept = delete;

	GameObject* GetGameObject() const { return m_pGameObject; }

private:
	GameObject* m_pGameObject{};
};

