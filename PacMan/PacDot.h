#pragma once	

class GameObject;
class PacDot final
{
public:
	PacDot();
	PacDot(float x, float y);
	~PacDot() = default;

	void Initialize();

	PacDot(const PacDot& other) = delete;
	PacDot(PacDot&& other) noexcept = delete;
	PacDot& operator=(const PacDot& other) = delete;
	PacDot& operator=(PacDot&& other) noexcept = delete;

	GameObject* GetGameObject() const { return m_pGameObject; }



private:
	GameObject* m_pGameObject{};
};

