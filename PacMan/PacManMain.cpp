
#if _DEBUG
#if __has_include(<vld.h>)
#include <vld.h>
#endif
#endif


#include "Minigin.h"
#include "PacDot.h"
#include "ServiceLocator.h"
#include "PacMan.h"
#include "SceneManager.h"
#include "Scene.h"
#include "WallManager.h"
#include "Ghost.h"

glm::vec2 g_WindowSize{ 224, 300 };


void load()
{
	std::srand(static_cast<unsigned int>(std::time(nullptr)));

	//LevelManager::GetInstance().AddStartScreen();
	//auto& audioService = ServiceLocator::GetInstance().AudioService.GetService();
	auto& Startscene = SceneManager::GetInstance().CreateScene("Level0");


	Startscene.Add(PacMan().GetPacMan());
	Startscene.Add(PacDot(50,50).GetGameObject());
	Startscene.Add(Ghost().GetGameObject());
	Startscene.Add(Ghost().GetGameObject());
	Startscene.Add(Ghost().GetGameObject());
	Startscene.Add(Ghost().GetGameObject());

	WallManager wallManager{};
	wallManager.AddWall("Walls/Wall_0x0_5x80.png");
	wallManager.AddWall("Walls/Wall_5x75_40x5.png");
	wallManager.AddWall("Walls/Wall_40x80_5x29.png");
	wallManager.AddWall("Walls/Wall_0x104_40x5.png");
	wallManager.AddWall("Walls/Wall_0x123_45x5.png");
	wallManager.AddWall("Walls/Wall_40x128_5x29.png");
	wallManager.AddWall("Walls/Wall_0x152_40x5.png");
	wallManager.AddWall("Walls/Wall_0x157_5x91.png");
	wallManager.AddWall("Walls/Wall_5x195_16x10.png");
	wallManager.AddWall("Walls/Wall_5x243_219x5.png");
	wallManager.AddWall("Walls/Wall_219x152_5x91.png");
	wallManager.AddWall("Walls/Wall_179x152_40x5.png");
	wallManager.AddWall("Walls/Wall_203x195_16x10.png");
	wallManager.AddWall("Walls/Wall_179x123_5x29.png");
	wallManager.AddWall("Walls/Wall_184x123_40x5.png");
	wallManager.AddWall("Walls/Wall_179x104_45x5.png");
	wallManager.AddWall("Walls/Wall_179x75_5x29.png");
	wallManager.AddWall("Walls/Wall_184x75_40x5.png");
	wallManager.AddWall("Walls/Wall_219x0_5x75.png");
	wallManager.AddWall("Walls/Wall_5x0_214x5.png");
	wallManager.AddWall("Walls/Wall_107x5_10x32.png");
	wallManager.AddWall("Walls/Wall_19x219_74x10.png");
	wallManager.AddWall("Walls/Wall_131x219_74x10.png");
	wallManager.AddWall("Walls/Wall_83x195_58x10.png");
	wallManager.AddWall("Walls/Wall_83x147_58x10.png");
	wallManager.AddWall("Walls/Wall_83x51_58x10.png");
	wallManager.AddWall("Walls/Wall_59x195_10x24.png");
	wallManager.AddWall("Walls/Wall_155x195_10x24.png");
	wallManager.AddWall("Walls/Wall_58x123_12x34.png");
	wallManager.AddWall("Walls/Wall_155x123_10x34.png");
	wallManager.AddWall("Walls/Wall_107x205_10x24.png");
	wallManager.AddWall("Walls/Wall_19x171_26x10.png");
	wallManager.AddWall("Walls/Wall_179x171_26x10.png");
	wallManager.AddWall("Walls/Wall_35x181_10x24.png");
	wallManager.AddWall("Walls/Wall_179x181_10x24.png");
	wallManager.AddWall("Walls/Wall_107x157_10x24.png");
	wallManager.AddWall("Walls/Wall_107x61_10x24.png");
	wallManager.AddWall("Walls/Wall_59x171_34x10.png");
	wallManager.AddWall("Walls/Wall_131x171_34x10.png");
	wallManager.AddWall("Walls/Wall_59x52_10x56.png");
	wallManager.AddWall("Walls/Wall_155x51_10x58.png");
	wallManager.AddWall("Walls/Wall_69x76_23x8.png");
	wallManager.AddWall("Walls/Wall_132x76_23x8.png");
	wallManager.AddWall("Walls/Wall_19x51_26x10.png");
	wallManager.AddWall("Walls/Wall_179x51_26x10.png");
	wallManager.AddWall("Walls/Wall_19x19_26x18.png");
	wallManager.AddWall("Walls/Wall_179x19_26x18.png");
	wallManager.AddWall("Walls/Wall_59x19_34x18.png");
	wallManager.AddWall("Walls/Wall_131x19_34x18.png");



	wallManager.AddWallsToScene(Startscene);
}

int main(int, char* [])
{
	Minigin engine{ "../Data/", g_WindowSize, "Pac Man Xander Berten 2DAE07" };
	engine.Run(load);

	return 0;
}

