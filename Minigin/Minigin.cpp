#include <stdexcept>
#define WIN32_LEAN_AND_MEAN 
#include <windows.h>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include "Minigin.h"

#include <chrono>
//#include <steam_api_common.h>

#include "AudioServiceDebug.h"
#include "imgui.h"
#include "InputManager.h"
#include "SceneManager.h"
#include "Renderer.h"
#include "ResourceManager.h"
#include "ServiceLocator.h"
#include "TimeM.h"

SDL_Window* g_window{};

void PrintSDLVersion()
{
	SDL_version version{};
	SDL_VERSION(&version);
	printf("We compiled against SDL version %u.%u.%u ...\n",
		version.major, version.minor, version.patch);

	SDL_GetVersion(&version);
	printf("We are linking against SDL version %u.%u.%u.\n",
		version.major, version.minor, version.patch);

	SDL_IMAGE_VERSION(&version);
	printf("We compiled against SDL_image version %u.%u.%u ...\n",
		version.major, version.minor, version.patch);

	version = *IMG_Linked_Version();
	printf("We are linking against SDL_image version %u.%u.%u.\n",
		version.major, version.minor, version.patch);

	SDL_TTF_VERSION(&version)
		printf("We compiled against SDL_ttf version %u.%u.%u ...\n",
			version.major, version.minor, version.patch);

	version = *TTF_Linked_Version();
	printf("We are linking against SDL_ttf version %u.%u.%u.\n",
		version.major, version.minor, version.patch);

	SDL_MIXER_VERSION(&version)
		printf("We compiled against SDL_mixer version %u.%u.%u ...\n",
			version.major, version.minor, version.patch);

	version = *Mix_Linked_Version();
	printf("We are linking against SDL_mixer version %u.%u.%u.\n",
		version.major, version.minor, version.patch);
}

Minigin::Minigin(const std::string& dataPath, const glm::vec2 windowSize, const std::string& windowName)
	:fixedTimeMStep(0.2f)
{
	ServiceLocator::GetInstance().AudioService.SetService(new AudioService());
	ServiceLocator::GetInstance().CollisionManager.SetService(new CollisionManagerSingleThread());
	ServiceLocator::GetInstance().InputManager.SetService(new InputManager());
	ServiceLocator::GetInstance().Renderer.SetService(new Renderer());
	ServiceLocator::GetInstance().ResourceManager.SetService(new ResourceManager());



	PrintSDLVersion();

	if (SDL_Init(SDL_INIT_VIDEO) != 0)
	{
		throw std::runtime_error(std::string("SDL_Init Error: ") + SDL_GetError());
	}

	g_window = SDL_CreateWindow
	(
		windowName.c_str(),
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		static_cast<UINT32>(windowSize.x),
		static_cast<UINT32>(windowSize.y),
		SDL_WINDOW_OPENGL
	);

	if (g_window == nullptr)
	{
		throw std::runtime_error(std::string("SDL_CreateWindow Error: ") + SDL_GetError());
	}

	ServiceLocator::GetInstance().Renderer.GetService().Init(g_window);
	ServiceLocator::GetInstance().ResourceManager.GetService().Init(dataPath);
}

Minigin::~Minigin()
{
	ServiceLocator::GetInstance().Renderer.GetService().Destroy();
	Mix_CloseAudio();
	SDL_DestroyWindow(g_window);
	g_window = nullptr;
	SDL_Quit();
	ServiceLocator::GetInstance().Cleanup();
}

void Minigin::Run(const std::function<void()>& load)
{




	load();



	const auto& renderer = ServiceLocator::GetInstance().Renderer.GetService();
	auto& sceneManager = SceneManager::GetInstance();
	auto& input = ServiceLocator::GetInstance().InputManager.GetService();

	bool doContinue = true;
	auto lastTimeM = std::chrono::high_resolution_clock::now();
	float lag = 0.f;

	while (doContinue)
	{
		auto currentTimeM = std::chrono::high_resolution_clock::now();
		const float deltaT = std::chrono::duration<float>(currentTimeM - lastTimeM).count();
		lag += deltaT;

		doContinue = input.ProcessInput();

		while (lag >= fixedTimeMStep)
		{
			sceneManager.FixedUpdate(fixedTimeMStep);
			lag -= fixedTimeMStep;
		}

		TimeM::GetInstance().Update(deltaT);

		sceneManager.Update();
		sceneManager.LateUpdate();
		renderer.Render();

		lastTimeM = currentTimeM;

		auto t2 = std::chrono::high_resolution_clock::now() - currentTimeM;

#ifndef _DEBUG
		currentTimeM += std::chrono::milliseconds(17) - t2; // we want ~60 fps
		std::this_thread::sleep_until(currentTimeM);
#endif
	}
}