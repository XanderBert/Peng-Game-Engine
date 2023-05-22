#if _DEBUG
#if __has_include(<vld.h>)
#include <vld.h>
#endif
#endif

#include <iostream>

#include "AudioServiceDebug.h"
#include "SceneManager.h"
#include "Scene.h"
#include "FontRenderer.h"
#include "FPSCounter.h"
#include "GameObject.h"
#include "Minigin.h"
#include "Transform.h"
#include "glm/vec2.hpp"
#include "imgui.h"
#include "IceBlock.h"
#include "Pengo.h"
#include "WallManager.h"
#include "ServiceLocator.h"
#include "SnowBee.h"


glm::vec<2, glm::uint> g_WindowSize{ 600, 400 };

void load()
{
	auto& scene = SceneManager::GetInstance().CreateScene("Demo");

	//FPS Counter
	auto go = new GameObject();
	const auto fpsCounter{ go->AddComponent<FPSCounter>() };
	const auto transComponentFPS{ go->GetComponent<Transform>() };
	transComponentFPS->SetLocalPosition({ 5, 5 });
	const auto fontRendererFPS = go->AddComponent<FontRenderer>();
	fontRendererFPS->SetFont("Lingua.otf", 20);
	scene.Add(go);


	//Player1
	const auto gameac = new Pengo();
	scene.Add(gameac);

	const auto wallManager = new WallManager();
	scene.Add(wallManager);


	auto ice = new IceBlock();
	ice->GetComponent<Transform>()->SetWorldPosition({ 100,100 });
	scene.Add(ice);

	ice = new IceBlock();
	ice->GetComponent<Transform>()->SetWorldPosition({ 116,100 });
	scene.Add(ice);

	ice = new IceBlock();
	ice->GetComponent<Transform>()->SetWorldPosition({ 116,50 });
	scene.Add(ice);

	ice = new IceBlock();
	ice->GetComponent<Transform>()->SetWorldPosition({ 116,66 });
	scene.Add(ice);

	ice = new IceBlock();
	ice->GetComponent<Transform>()->SetWorldPosition({ 116,82 });
	scene.Add(ice);

	const auto snowBee = new SnowBee();
	scene.Add(snowBee);

}

int main(int, char* [])
{
	ServiceLocator::GetInstance().AudioService.SetService(new AudioServiceDebug());
	ServiceLocator::GetInstance().CollisionManager.SetService(new CollisionManager());
	ServiceLocator::GetInstance().InputManager.SetService(new InputManager());
	ServiceLocator::GetInstance().LevelLoader.SetService(new LevelLoader());
	ServiceLocator::GetInstance().Renderer.SetService(new Renderer());
	ServiceLocator::GetInstance().ResourceManager.SetService(new ResourceManager());

	Minigin engine{ "../Data/", g_WindowSize };
	engine.Run(load);


	return 0;
}