#if _DEBUG
#if __has_include(<vld.h>)
#include <vld.h>
#endif
#endif

#include <iostream>

#include "AudioServiceDebug.h"
#include "ControllerComponent.h"
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
#include "InputComponent.h"
#include "Pengo.h"
#include "WallRow.h"
#include "ServiceLocator.h"
#include "SnowBee.h"
#include "PengoLevel.h"
#include "PengoLevelLoader.h"

//https://archive.org/details/arcade_pengo

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




	PengoLevelLoader levelLoader;
	PengoLevel* level01 = levelLoader.LoadLevel("Level1.xml");
	level01->AddGameObjectsToScene(&scene);


	auto object = new Pengo();
	const auto controllerComponent = object->AddComponent<ControllerComponent>();
	controllerComponent->RegisterController(0);
	controllerComponent->AddBinding(Controller::ControllerButton::DPadLeft, new MoveCommand(object, { -1, 0 }));
	controllerComponent->AddBinding(Controller::ControllerButton::DPadRight, new MoveCommand(object, { 1, 0 }));
	controllerComponent->AddBinding(Controller::ControllerButton::DPadUp, new MoveCommand(object, { 0, -1 }));
	controllerComponent->AddBinding(Controller::ControllerButton::DPadDown, new MoveCommand(object, { 0, 1 }));

	object->GetComponent<Transform>()->SetWorldPosition({ 100,100 });
	scene.Add(object);

	//Player2
}

int main(int, char* [])
{
	ServiceLocator::GetInstance().AudioService.SetService(new AudioServiceDebug());
	ServiceLocator::GetInstance().CollisionManager.SetService(new CollisionManager());
	ServiceLocator::GetInstance().InputManager.SetService(new InputManager());
	ServiceLocator::GetInstance().Renderer.SetService(new Renderer());
	ServiceLocator::GetInstance().ResourceManager.SetService(new ResourceManager());

	Minigin engine{ "../Data/", g_WindowSize };
	engine.Run(load);


	return 0;
}