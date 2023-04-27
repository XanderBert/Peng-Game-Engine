#include <stdexcept>
#define WIN32_LEAN_AND_MEAN 
#include <windows.h>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include "Minigin.h"

#include <chrono>
//#include <steam_api_common.h>

#include "imgui.h"
#include "InputManager.h"
#include "SceneManager.h"
#include "Renderer.h"
#include "ResourceManager.h"
#include "Time.h"

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
}
//TODO: Fix Deletion of Components (Destructor Gets Called but memory does not get freed).
//TODO: Fix Deletion of GameObjects (Function Take Unique pointer)

//TODO: place huge amounts of data in components to check if everything gets deleted (This Data is now in TextureRenderer)
//Just like i taught the memory does not get freed until the whole program terminates

//TODO: Implement something like juce's safe pointers.
//Holds a pointer to some type of Component, which automatically becomes null if the component is deleted.
//TODO: If there is time, place all data from big to small inside a class
//Todo: Put the cold path data in a class and put a pointer to it in the component

Minigin::Minigin(const std::string& dataPath)
	:fixedTimeStep(0.2f)
{
	PrintSDLVersion();

	if (SDL_Init(SDL_INIT_VIDEO) != 0)
	{
		throw std::runtime_error(std::string("SDL_Init Error: ") + SDL_GetError());
	}

	g_window = SDL_CreateWindow(
		"Programming 4 assignment",
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		m_WindowWidth,
		m_WindowHeight,
		SDL_WINDOW_OPENGL
	);
	if (g_window == nullptr)
	{
		throw std::runtime_error(std::string("SDL_CreateWindow Error: ") + SDL_GetError());
	}

	Renderer::GetInstance().Init(g_window);

	ResourceManager::GetInstance().Init(dataPath);
}

Minigin::~Minigin()
{
	Renderer::GetInstance().Destroy();
	SDL_DestroyWindow(g_window);
	g_window = nullptr;
	SDL_Quit();
}

void Minigin::Run(const std::function<void()>& load)
{
	load();

	const auto& renderer = Renderer::GetInstance();
	auto& sceneManager = SceneManager::GetInstance();
	auto& input = InputManager::GetInstance();

	bool doContinue = true;
	auto lastTime = std::chrono::high_resolution_clock::now();
	float lag = 0.f;

	while (doContinue)
	{
		auto currentTime = std::chrono::high_resolution_clock::now();
		const float deltaT = std::chrono::duration<float>(currentTime - lastTime).count();
		lag += deltaT;

		doContinue = input.ProcessInput();

		while (lag >= fixedTimeStep)
		{
			sceneManager.FixedUpdate(fixedTimeStep);
			lag -= fixedTimeStep;
		}

		Time::GetInstance().Update(deltaT);

		//SteamAPI_RunCallbacks();

		sceneManager.Update();
		sceneManager.LateUpdate();
		renderer.Render();

		lastTime = currentTime;

		auto t2 = std::chrono::high_resolution_clock::now() - currentTime;
		currentTime += std::chrono::milliseconds(17) - t2; // we want ~60 fps
		std::this_thread::sleep_until(currentTime);
	}
}