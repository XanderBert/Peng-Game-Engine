#pragma once
#include "Component.h"

class GameObjectStorage final : public  Component
{
public:
	GameObjectStorage(GameObject* pOwner);
	virtual  ~GameObjectStorage() override;

	GameObjectStorage(const GameObjectStorage& other) = delete;
	GameObjectStorage(GameObjectStorage&& other) = delete;
	GameObjectStorage& operator=(const GameObjectStorage& other) = delete;
	GameObjectStorage& operator=(GameObjectStorage&& other) = delete;

	void Update() override;
	void FixedUpdate(float fixedTimeMStep) override;
	void LateUpdate() override;
	void Render() override;

	void StoreGameObject(GameObject* pGameObject);
	GameObject* GetGameObject() const { return m_pGameObject; }

private:
	GameObject* m_pGameObject{};
	//std::vector<GameObject*> m_pGameObjects{};
};
