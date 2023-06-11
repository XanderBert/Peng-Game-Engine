#pragma once
#include "Component.h"
#include "Observer.h"

class ObserverComponent final : public Component
{
public:
	ObserverComponent(GameObject* owner);
	virtual ~ObserverComponent() override = default;

	ObserverComponent(const ObserverComponent& other) = delete;
	ObserverComponent(ObserverComponent&& other) noexcept = delete;
	ObserverComponent& operator=(const ObserverComponent& other) = delete;
	ObserverComponent& operator=(ObserverComponent&& other) noexcept = delete;

	//Called each frame
	void Update() override {}

	//Called at a fixed time step
	//Used for physics & networking
	void FixedUpdate(float /*fixedTimeMStep*/) override {}

	//Called after the Update()
	//Used for camera and deletion of objects -> Deletion could be handled by the double buffer pattern
	void LateUpdate() override {}

	//Called each frame
	void Render() override {}


	void AddObserver(std::shared_ptr<Observer> observer)
	{
		m_Observers.emplace_back(observer);
	}

	void RemoveObserver(Observer* observer)
	{
		std::erase_if(m_Observers, [observer](const std::shared_ptr<Observer>& ptr) {
			if (ptr.get() == observer)
			{
				return true;
			}
			return false;
			});
	}

	void NotifyObserver(GameObject* object, const GameEvent event) const
	{
		for (const auto& obsrv : m_Observers)
		{
			obsrv->Notify(object, event);
		}
	}


private:
	std::vector<std::shared_ptr<Observer>> m_Observers{};
};
