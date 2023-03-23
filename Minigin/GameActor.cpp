#include "GameActor.h"

#include <iostream>

#include "GameObject.h"
#include "InputManager.h"
#include "ResourceManager.h"
#include "TextureRenderer.h"
#include "Time.h"
#include "Transform.h"

GameActor::GameActor()
{
	const auto textureRenderer{ AddComponent<TextureRenderer>() };
	//TODO: Set with function or in constructor?
	textureRenderer->SetTexture("Pacman320.png");

	InputManager::GetInstance().AddActor(this);
	std::cout << "\nActor Made\n";
}

GameActor::~GameActor()
{

}

void GameActor::Jump()
{
	//std::cout << "The actor Jumps!\n";
	//glm::vec2 pos = direction * speed * dt;
	//m_pActor->GetComponent<Transform>().get()->SetLocalPosition();
}

void GameActor::Move(const glm::vec2& direction)
{
	const auto transform = GetComponent<Transform>();
	transform->SetLocalPosition(transform->GetLocalPosition() += direction * m_Speed * Time::GetInstance().GetDeltaTime());
}
