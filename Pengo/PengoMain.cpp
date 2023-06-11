#if _DEBUG
#if __has_include(<vld.h>)
#include <vld.h>
#endif
#endif

#include "AudioServiceDebug.h"
#include "Minigin.h"
#include "LevelManager.h"
#include "ServiceLocator.h"


//https://archive.org/details/arcade_pengo

glm::vec<2, glm::uint> g_WindowSize{ 324, 400 };

void load()
{
	LevelManager::GetInstance().AddStartScreen();
	auto& audioService = ServiceLocator::GetInstance().AudioService.GetService();
	audioService.AddSound(1, "Sounds/ActStart.mp3");
	audioService.AddSound(2, "Sounds/ActOver.mp3");
	audioService.AddSound(3, "Sounds/ActClear.mp3");
}

int main(int, char* [])
{
	Minigin engine{ "../Data/", g_WindowSize };
	engine.Run(load);

	return 0;
}