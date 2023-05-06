#if _DEBUG
#if __has_include(<vld.h>)
#include <vld.h>
#endif
#endif

#include <iostream>

#include "SceneManager.h"
#include "Scene.h"
#include "FontRenderer.h"
#include "FPSCounter.h"
#include "GameObject.h"
#include "Minigin.h"
#include "Transform.h"
#include "glm/vec2.hpp"
#include "imgui.h"
#include "GameActor.h"
#include "Pengo.h"
#include "WallManager.h"


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
}

int main(int, char* [])
{
	Minigin engine{ "../Data/", g_WindowSize };
	engine.Run(load);
	return 0;
}