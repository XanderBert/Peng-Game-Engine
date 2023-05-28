#include "GameActor.h"
#include <iostream>
#include "BoxCollider.h"
#include "FontRenderer.h"
#include "GameObject.h"
#include "InputManager.h"
#include "ResourceManager.h"
#include "ServiceLocator.h"



GameActor::GameActor() : GameObject()
{}

GameActor::~GameActor()
{

}

void GameActor::Update()
{
	GameObject::Update();
}



void GameActor::TakeDammage(const int dammage)
{
	if (!m_Health) return;

	m_Health -= dammage;
	m_HealthString = std::to_string(m_Health);

}

void GameActor::GainPoints(int ammountOfPoints)
{
	m_Points += ammountOfPoints;
	m_PointString = std::to_string(m_Points);
}

void GameActor::SetControllerIndex(int index)
{
	m_UsesController = true;
	m_ControllerID = index;
	const auto& controllers = ServiceLocator::GetInstance().InputManager.GetService().GetControllers();

	for (const auto& controller : controllers)
	{
		if (controller->GetControllerID() == index)
		{
			controller->SetActor(this);
		}
	}

}

void GameActor::OnCollision(GameObject* other)
{
	GameObject::OnCollision(other);
}
