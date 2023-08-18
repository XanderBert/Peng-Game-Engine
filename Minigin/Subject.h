#pragma once
#include <cassert>
#include <memory>
#include <vector>
#include "Observer.h"

class GameObject;

//Should not be a interface.

class Subject final
{
public:
	Subject() = default;
	~Subject() = default;

	Subject(const Subject& other) = delete;
	Subject(Subject&& other) noexcept = delete;
	Subject& operator=(const Subject& other) = delete;
	Subject& operator=(Subject&& other) noexcept = delete;


	void AttachObserver(Observer* observer);
	void RemoveObserver(Observer* observer);

	void Notify(GameEvent event, GameObject* object) const;

private:
	std::vector<std::unique_ptr<Observer>> m_Observers;
};

inline void Subject::AttachObserver(Observer* observer)
{
	m_Observers.emplace_back(observer);
}

inline void Subject::RemoveObserver(Observer* /*observer*/)
{
	assert(false && "Not implemented yet");
}

inline void Subject::Notify(GameEvent event, GameObject* object) const
{
	for (const auto& observer : m_Observers)
	{
		observer->Notify(object, event);
	}
}
