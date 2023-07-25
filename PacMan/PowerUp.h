#pragma once
#include <string>
#include <glm/vec2.hpp>

class GameObject;
class PowerUp final
{
public:
	PowerUp(const std::string& textureLocation, const glm::vec2& location);
	~PowerUp() = default;

	PowerUp(const PowerUp& other) = delete;
	PowerUp(PowerUp&& other) = delete;
	PowerUp& operator=(const PowerUp& other) = delete;
	PowerUp& operator=(PowerUp&& other) = delete;

	GameObject* GetGameObject() const { return m_pGameObject; }
private:
	GameObject* m_pGameObject{};
};
