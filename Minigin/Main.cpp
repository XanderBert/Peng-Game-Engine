#include <SDL.h>
#if _DEBUG
// ReSharper disable once CppUnusedIncludeDirective
#if __has_include(<vld.h>)
#include <vld.h>
#endif
#endif

#include "Minigin.h"
#include "SceneManager.h"
#include "ResourceManager.h"
#include "Scene.h"
#include "Time.h"


#include "GameObject.h"
#include "Transform.h"
#include "TextureRenderer.h"
#include "FontRenderer.h"
#include "FPSCounter.h"

void load()
{
	auto& scene = SceneManager::GetInstance().CreateScene("Demo");

	//Background Image
	auto go = std::make_shared<GameObject>();
	const auto textureRendererBackground = go->AddComponent<TextureRenderer>();
	textureRendererBackground->SetTexture(ResourceManager::GetInstance().LoadTexture("background.tga"));
	scene.Add(go);

	//DAE Logo
	go = std::make_shared<GameObject>();
	const auto transComponentLogo = go->GetComponent<Transform>();
	transComponentLogo->SetLocalPosition({ 216, 180 });
	const auto textureRendererLogo = go->AddComponent<TextureRenderer>();
	textureRendererLogo->SetTexture(ResourceManager::GetInstance().LoadTexture("logo.tga"));
	scene.Add(go);


	//Top Text
	go = std::make_shared<GameObject>();
	const auto transComponentFont{ go->GetComponent<Transform>() };
	transComponentFont->SetLocalPosition({ 80, 20 });
	const auto fontRenderer = go->AddComponent<FontRenderer>();
	fontRenderer->SetFont("Lingua.otf", 36);
	fontRenderer->SetText("Programming 4 Assignment TEST");
	scene.Add(go);


	//FPS Counter
	go = std::make_shared<GameObject>();
	const auto fpsCounter{ go->AddComponent<FPSCounter>() };
	const auto transComponentFPS{ go->GetComponent<Transform>() };
	transComponentFPS->SetLocalPosition({ 10, 10 });
	const auto fontRendererFPS = go->AddComponent<FontRenderer>();
	fontRendererFPS->SetFont("Lingua.otf", 36);
	scene.Add(go);

}

int main(int, char* []) {
	Minigin engine("../Data/");
	engine.Run(load);
	return 0;
}