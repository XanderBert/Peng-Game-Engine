#include "Pengo.h"

#include "BoxCollider.h"
#include "SpriteRenderer.h"
#include "Wall.h"
#include "WallManager.h"

Pengo::Pengo() : GameActor()
{
	const auto textureRenderer{ AddComponent<TextureRenderer>() };
	textureRenderer->SetTexture("Pengo.png");

	const auto spriteRenderer{ AddComponent<SpriteRenderer>() };
	spriteRenderer->SetSpriteSize({ 16,16 });

	spriteRenderer->AddSpriteFrame({ 0,0 }, MovementDirection::Down);
	spriteRenderer->AddSpriteFrame({ 16,0 }, MovementDirection::Down);
	spriteRenderer->AddSpriteFrame({ 32,0 }, MovementDirection::Left);
	spriteRenderer->AddSpriteFrame({ 48,0 }, MovementDirection::Left);
	spriteRenderer->AddSpriteFrame({ 64,0 }, MovementDirection::Up);
	spriteRenderer->AddSpriteFrame({ 80,0 }, MovementDirection::Up);
	spriteRenderer->AddSpriteFrame({ 96,0 }, MovementDirection::Right);
	spriteRenderer->AddSpriteFrame({ 112,0 }, MovementDirection::Right);

	const auto boxCollision{ AddComponent<BoxCollider>() };
	boxCollision->SetColliderSize({16,16});
	//boxCollision->DebugRender(true);
}

Pengo::~Pengo()
{
}

void Pengo::Update()
{
	GameActor::Update();
}

void Pengo::OnCollision(GameObject* other)
{
	if(reinterpret_cast<Wall*>(other))
	{
		const auto transform = GetComponent<Transform>();
		transform->SetWorldPosition(transform->GetLastWorldPosition());
	}
}

