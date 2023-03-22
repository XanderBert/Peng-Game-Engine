#include "GameActor.h"

#include <iostream>

#include "GameObject.h"
#include "ResourceManager.h"
#include "TextureRenderer.h"
#include "Transform.h"

GameActor::GameActor()
{
	const auto textureRenderer{ AddComponent<TextureRenderer>() };
	//TODO: Set with function or in constructor?
	textureRenderer->SetTexture("Pacman320.png");

}

GameActor::~GameActor()
{
}

void GameActor::Jump()
{
	//glm::vec2 pos = direction * speed * dt;
	//m_pActor->GetComponent<Transform>().get()->SetLocalPosition();
	std::cout << "Jump\n";
}

void GameActor::Move(const glm::vec2& direction)
{
	direction;
}
