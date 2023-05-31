#pragma once
#include <mutex>
#include <SDL_rect.h>
#include <glm/vec2.hpp>
#include "Component.h"


class BoxCollider final : public Component
{
public:
	BoxCollider(GameObject* owner);
	~BoxCollider() override;

	BoxCollider(const BoxCollider& other) = delete;
	BoxCollider(BoxCollider&& other) = delete;
	BoxCollider& operator=(const BoxCollider& other) = delete;
	BoxCollider& operator=(BoxCollider&& other) = delete;

	//Called each frame
	void Update() override;

	//Called at a fixed time step
	//Used for physics & networking
	void FixedUpdate(float fixedTimeMStep) override;

	//Called after the Update()
	//Used for camera and deletion of objects -> Deletion could be handled by the double buffer pattern
	void LateUpdate() override;

	//Called each frame
	void Render() override;

	void SetColliderSize(const glm::vec2& size);
	void SetColliderOffset(const glm::vec2& offset);

	void DebugRender(bool isDebugRendering);

	SDL_Rect GetCollider() const;


	void SetIsTrigger(bool isTrigger);
	bool GetIsTrigger() const;
	void ClearCollidingObjects();
	void SetCollidingObjects(const std::vector<GameObject*>& pCollidingObjects);
	void AddCollidingObject(GameObject* collider);
	void RemoveCollidingObject(GameObject* collider);
	std::vector<GameObject*> GetCollidingObjects() const;
private:
	std::mutex m_CollidingObjectsMutex{};
	std::vector<GameObject*> m_CollidingObjects;
	SDL_Rect m_Collider{ 0,0,5,5 };
	bool m_DebugRender{};
	bool m_IsTrigger{ false };
};
