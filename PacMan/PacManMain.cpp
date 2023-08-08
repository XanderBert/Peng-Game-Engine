
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
#include "Hud.h"
#include "IntersectionTile.h"
#include "PacManComponent.h"
#include "PowerUp.h"

glm::vec2 g_WindowSize{ 224, 300 };


void load()
{
	std::srand(static_cast<unsigned int>(std::time(nullptr)));

	//LevelManager::GetInstance().AddStartScreen();
	//auto& audioService = ServiceLocator::GetInstance().AudioService.GetService();
	auto& Startscene = SceneManager::GetInstance().CreateScene("Level0");

	auto observer = new PowerUpObserver();

	const auto pacMan = PacMan();
	pacMan.GetPacMan()->GetComponent<PacManComponent>()->AttachObserver(observer);

	Startscene.Add(pacMan.GetPacMan());
	//Startscene.Add(PacDot(50,50).GetGameObject());

	Startscene.Add(PowerUp("Cherry.png", { 50,50 }).GetGameObject());



	Startscene.Add(Ghost().GetGameObject());
	Startscene.Add(Ghost().GetGameObject());
	Startscene.Add(Ghost().GetGameObject());
	Startscene.Add(Ghost().GetGameObject());

	Startscene.Add(Hud().GetGameObject());

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


	//  , { {-1,0}, {1,0}, {0, 1}, {0, -1} }
	Startscene.Add(IntersectionTile({4,4},{{1,0}, {0, 1}}).GetGameObject());
	Startscene.Add(IntersectionTile({4,36},{{1,0}, {0, 1},{0,-1}}).GetGameObject());
	Startscene.Add(IntersectionTile({4,60},{{1,0},{0,-1}}).GetGameObject());
	Startscene.Add(IntersectionTile({4,156},{{1,0},{0,1}}).GetGameObject());
	Startscene.Add(IntersectionTile({4,180},{{1,0},{0,-1}}).GetGameObject());
	Startscene.Add(IntersectionTile({4,204},{{1,0},{0,1}}).GetGameObject());
	Startscene.Add(IntersectionTile({4,228},{{1,0},{0,-1}}).GetGameObject());

	Startscene.Add(IntersectionTile({44,4},{{-1,0}, {1,0}, {0, 1}}).GetGameObject());
	Startscene.Add(IntersectionTile({44,36}, { {-1,0}, {1,0}, {0, 1}, {0, -1} }).GetGameObject());
	Startscene.Add(IntersectionTile({44,60},{{-1, 0}, {0,-1}, {0,1}}).GetGameObject());
	Startscene.Add(IntersectionTile({44,108}, { {-1,0}, {1,0}, {0, 1}, {0, -1} }).GetGameObject());
	Startscene.Add(IntersectionTile({44,156}, { {-1,0}, {1,0}, {0, 1}, {0, -1} }).GetGameObject());
	Startscene.Add(IntersectionTile({44,180}, {  {1,0}, {0, 1}, {0, -1} }).GetGameObject());
	Startscene.Add(IntersectionTile({44,204}, { {-1,0},   {0, -1} }).GetGameObject());

	Startscene.Add(IntersectionTile({68,36}, { {-1,0},   {1, 0} ,   {0, 1} }).GetGameObject());
	Startscene.Add(IntersectionTile({68,60}, { {1, 0} ,   {0, -1} }).GetGameObject());
	Startscene.Add(IntersectionTile({68,84}, { {1, 0} ,   {0, 1} }).GetGameObject());
	Startscene.Add(IntersectionTile({68,108}, { {-1, 0} ,   {0, -1},   {0, 1} }).GetGameObject());
	Startscene.Add(IntersectionTile({68,132}, { {1, 0} ,   {0, -1},   {0, 1} }).GetGameObject());
	Startscene.Add(IntersectionTile({68,156}, { {1, 0} ,   {-1, 0},   {0, -1} }).GetGameObject());
	Startscene.Add(IntersectionTile({68,180}, { {1, 0} ,   {-1, 0},   {0, 1} }).GetGameObject());
	Startscene.Add(IntersectionTile({ 68,204 }, { {1, 0} ,   {0, -1}}).GetGameObject());
	
	Startscene.Add(IntersectionTile({ 92,4 }, { {-1, 0} ,   {0, 1}}).GetGameObject());
	Startscene.Add(IntersectionTile({ 92,36 }, { {-1, 0} ,   {1, 0},   {0, -1} }).GetGameObject());
	Startscene.Add(IntersectionTile({ 92,60 }, { {-1, 0} ,   {0, 1} }).GetGameObject());
	Startscene.Add(IntersectionTile({ 92,84 }, { {-1, 0} ,   {1, 0},{0,-1} }).GetGameObject());
	Startscene.Add(IntersectionTile({ 92,156 }, { {-1, 0} ,{0,1} }).GetGameObject());
	Startscene.Add(IntersectionTile({ 92,180 }, { {-1, 0} ,{1,0},{0,-1} }).GetGameObject());
	Startscene.Add(IntersectionTile({ 92,204 }, { {-1, 0} ,{0,1} }).GetGameObject());
	Startscene.Add(IntersectionTile({ 92,228 }, { {-1, 0},{1,0} ,{0,-1} }).GetGameObject());

	Startscene.Add(IntersectionTile({ 116,4 }, { {1, 0} ,   {0, 1} }).GetGameObject());
	Startscene.Add(IntersectionTile({ 116,36 }, { {1, 0} ,   {-1, 0},   {0, -1} }).GetGameObject());
	Startscene.Add(IntersectionTile({ 116,60 }, { {1, 0} ,   {0, 1} }).GetGameObject());
	Startscene.Add(IntersectionTile({ 116,84 }, { {1, 0} ,   {-1, 0},{0,-1} }).GetGameObject());
	Startscene.Add(IntersectionTile({ 116,156 }, { {1, 0} ,{0,1} }).GetGameObject());
	Startscene.Add(IntersectionTile({ 116,180 }, { {1, 0} ,{-1,0},{0,-1} }).GetGameObject());
	Startscene.Add(IntersectionTile({ 116,204 }, { {1, 0} ,{0,1} }).GetGameObject());
	Startscene.Add(IntersectionTile({ 116,228 }, { {1, 0},{-1,0} ,{0,-1} }).GetGameObject());

	Startscene.Add(IntersectionTile({ 140 ,36 }, { {1,0},   {-1, 0} ,   {0, 1} }).GetGameObject());
	Startscene.Add(IntersectionTile({ 140 ,60 }, { {-1, 0} ,   {0, -1} }).GetGameObject());
	Startscene.Add(IntersectionTile({ 140 ,84 }, { {-1, 0} ,   {0, 1} }).GetGameObject());
	Startscene.Add(IntersectionTile({ 140 ,108 }, { {1, 0} ,   {0, -1},   {0, 1} }).GetGameObject());
	Startscene.Add(IntersectionTile({ 140 ,132 }, { {-1, 0} ,   {0, -1},   {0, 1} }).GetGameObject());
	Startscene.Add(IntersectionTile({ 140 ,156 }, { {-1, 0} ,   {1, 0},   {0, -1} }).GetGameObject());
	Startscene.Add(IntersectionTile({ 140 ,180 }, { {-1, 0} ,   {1, 0},   {0, 1} }).GetGameObject());
	Startscene.Add(IntersectionTile({ 140 ,204 }, { {-1, 0} ,   {0, -1} }).GetGameObject());


	Startscene.Add(IntersectionTile({ 164,4 }, { {1,0}, {-1,0}, {0, 1} }).GetGameObject());
	Startscene.Add(IntersectionTile({ 164,36 }, { {1,0}, {-1,0}, {0, 1}, {0, -1} }).GetGameObject());
	Startscene.Add(IntersectionTile({ 164,60 }, { {1, 0}, {0,-1}, {0,1} }).GetGameObject());
	Startscene.Add(IntersectionTile({ 164,108 }, { {1,0}, {-1,0}, {0, 1}, {0, -1} }).GetGameObject());
	Startscene.Add(IntersectionTile({ 164,156 }, { {1,0}, {-1,0}, {0, 1}, {0, -1} }).GetGameObject());
	Startscene.Add(IntersectionTile({ 164,180 }, { {-1,0}, {0, 1}, {0, -1} }).GetGameObject());
	Startscene.Add(IntersectionTile({ 164,204 }, { {1,0},   {0, -1} }).GetGameObject());


	Startscene.Add(IntersectionTile({ 204,4 }, { {-1,0}, {0, 1} }).GetGameObject());
	Startscene.Add(IntersectionTile({ 204,36 }, { {-1,0}, {0, 1},{0,-1} }).GetGameObject());
	Startscene.Add(IntersectionTile({ 204,60 }, { {-1,0},{0,-1} }).GetGameObject());
	Startscene.Add(IntersectionTile({ 204,156 }, { {-1,0},{0,1} }).GetGameObject());
	Startscene.Add(IntersectionTile({ 204,180 }, { {-1,0},{0,-1} }).GetGameObject());
	Startscene.Add(IntersectionTile({ 204,204 }, { {-1,0},{0,1} }).GetGameObject());
	Startscene.Add(IntersectionTile({ 204,228 }, { {-1,0},{0,-1} }).GetGameObject());




	Startscene.Add(IntersectionTile({ 20,180 }, { {-1,0},{0,1} }).GetGameObject());
	Startscene.Add(IntersectionTile({ 20,204 }, { {-1,0},{1,0} ,{0,-1} }).GetGameObject());
	Startscene.Add(IntersectionTile({ 188,180 }, { {1,0},{0,-1} }).GetGameObject());
	Startscene.Add(IntersectionTile({ 188,204 }, { {-1,0},{1,0} ,{0,-1} }).GetGameObject());

}

int main(int, char* [])
{
	Minigin engine{ "../Data/", g_WindowSize, "Pac Man Xander Berten 2DAE07" };
	engine.Run(load);

	return 0;
}

