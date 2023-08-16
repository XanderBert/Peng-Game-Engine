
#if _DEBUG
#if __has_include(<vld.h>)
#include <vld.h>
#endif
#endif


#include "Minigin.h"
#include "ServiceLocator.h"
#include "InputHandler.h"
#include "IntersectionTile.h"
#include "LevelLoader.h"
#include "PacManComponent.h"


glm::vec2 g_WindowSize{ 224, 300 };


void load()
{
	std::srand(static_cast<unsigned int>(std::time(nullptr)));

	ServiceLocator::GetInstance().AudioService.GetService().AddSound(0, "Sounds/munch_1.wav");
	ServiceLocator::GetInstance().AudioService.GetService().AddSound(1, "Sounds/munch_2.wav");
	ServiceLocator::GetInstance().AudioService.GetService().AddSound(2, "Sounds/power_pellet.wav");
	ServiceLocator::GetInstance().AudioService.GetService().AddSound(3, "Sounds/eat_ghost.wav");
	ServiceLocator::GetInstance().AudioService.GetService().AddSound(4, "Sounds/retreating.wav");
	ServiceLocator::GetInstance().AudioService.GetService().AddSound(5, "Sounds/siren_1.wav");
	ServiceLocator::GetInstance().AudioService.GetService().AddSound(5, "Sounds/siren_1.wav");
	ServiceLocator::GetInstance().AudioService.GetService().AddSound(6, "Sounds/death_1.wav");

	LevelLoader::GetInstance().LoadStartScene();
}

int main(int, char* [])
{
	Minigin engine{ "../Data/", g_WindowSize, "Pac Man Xander Berten 2DAE07" };
	engine.Run(load);

	return 0;
}

