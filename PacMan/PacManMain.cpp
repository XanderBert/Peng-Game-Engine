
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


	//Row_01
	Startscene.Add(PacDot(11, 11).GetGameObject());
	Startscene.Add(PacDot(11, 19).GetGameObject());
	Startscene.Add(PacDot(11, 35).GetGameObject());
	Startscene.Add(PacDot(11, 43).GetGameObject());
	Startscene.Add(PacDot(11, 51).GetGameObject());
	Startscene.Add(PacDot(11, 59).GetGameObject());
	Startscene.Add(PacDot(11, 67).GetGameObject());
	Startscene.Add(PacDot(11, 163).GetGameObject());
	Startscene.Add(PacDot(11, 171).GetGameObject());
	Startscene.Add(PacDot(11, 179).GetGameObject());
	Startscene.Add(PacDot(11, 211).GetGameObject());
	Startscene.Add(PacDot(11, 219).GetGameObject());
	Startscene.Add(PacDot(11, 227).GetGameObject());
	Startscene.Add(PacDot(11, 235).GetGameObject());
	//Row_02
	Startscene.Add(PacDot(19, 11).GetGameObject());
	Startscene.Add(PacDot(19, 43).GetGameObject());
	Startscene.Add(PacDot(19, 67).GetGameObject());
	Startscene.Add(PacDot(19, 163).GetGameObject());
	Startscene.Add(PacDot(19, 187).GetGameObject());
	Startscene.Add(PacDot(19, 211).GetGameObject());
	Startscene.Add(PacDot(19, 235).GetGameObject());
	//Row_03
	Startscene.Add(PacDot(27, 11).GetGameObject());
	Startscene.Add(PacDot(27, 43).GetGameObject());
	Startscene.Add(PacDot(27, 67).GetGameObject());
	Startscene.Add(PacDot(27, 163).GetGameObject());
	Startscene.Add(PacDot(27, 187).GetGameObject());
	Startscene.Add(PacDot(27, 195).GetGameObject());
	Startscene.Add(PacDot(27, 203).GetGameObject());
	Startscene.Add(PacDot(27, 211).GetGameObject());
	Startscene.Add(PacDot(27, 235).GetGameObject());
	//Row_04
	Startscene.Add(PacDot(35, 11).GetGameObject());
	Startscene.Add(PacDot(35, 35).GetGameObject());
	Startscene.Add(PacDot(35, 43).GetGameObject());
	Startscene.Add(PacDot(35, 67).GetGameObject());
	Startscene.Add(PacDot(35, 163).GetGameObject());
	Startscene.Add(PacDot(35, 211).GetGameObject());
	Startscene.Add(PacDot(35, 235).GetGameObject());
	//Row_05
	Startscene.Add(PacDot(43, 11).GetGameObject());
	Startscene.Add(PacDot(43, 35).GetGameObject());
	Startscene.Add(PacDot(43, 43).GetGameObject());
	Startscene.Add(PacDot(43, 67).GetGameObject());
	Startscene.Add(PacDot(43, 163).GetGameObject());
	Startscene.Add(PacDot(43, 211).GetGameObject());
	Startscene.Add(PacDot(43, 235).GetGameObject());
	//Row_06
	Startscene.Add(PacDot(51, 11).GetGameObject());
	Startscene.Add(PacDot(51, 19).GetGameObject());
	Startscene.Add(PacDot(51, 27).GetGameObject());
	Startscene.Add(PacDot(51, 35).GetGameObject());
	Startscene.Add(PacDot(51, 43).GetGameObject());
	Startscene.Add(PacDot(51, 51).GetGameObject());
	Startscene.Add(PacDot(51, 59).GetGameObject());
	Startscene.Add(PacDot(51, 67).GetGameObject());
	Startscene.Add(PacDot(51, 75).GetGameObject());
	Startscene.Add(PacDot(51, 75).GetGameObject());
	Startscene.Add(PacDot(51, 83).GetGameObject());
	Startscene.Add(PacDot(51, 91).GetGameObject());
	Startscene.Add(PacDot(51, 99).GetGameObject());
	Startscene.Add(PacDot(51, 107).GetGameObject());
	Startscene.Add(PacDot(51, 115).GetGameObject());
	Startscene.Add(PacDot(51, 123).GetGameObject());
	Startscene.Add(PacDot(51, 131).GetGameObject());
	Startscene.Add(PacDot(51, 139).GetGameObject());
	Startscene.Add(PacDot(51, 147).GetGameObject());
	Startscene.Add(PacDot(51, 155).GetGameObject());
	Startscene.Add(PacDot(51, 163).GetGameObject());
	Startscene.Add(PacDot(51, 171).GetGameObject());
	Startscene.Add(PacDot(51, 179).GetGameObject());
	Startscene.Add(PacDot(51, 187).GetGameObject());
	Startscene.Add(PacDot(51, 195).GetGameObject());
	Startscene.Add(PacDot(51, 203).GetGameObject());
	Startscene.Add(PacDot(51, 211).GetGameObject());
	Startscene.Add(PacDot(51, 235).GetGameObject());
	//Row_07
	Startscene.Add(PacDot(59, 11).GetGameObject());
	Startscene.Add(PacDot(59, 43).GetGameObject());
	Startscene.Add(PacDot(59, 163).GetGameObject());
	Startscene.Add(PacDot(59, 187).GetGameObject());
	Startscene.Add(PacDot(59, 235).GetGameObject());
	//Row_08
	Startscene.Add(PacDot(67, 11).GetGameObject());
	Startscene.Add(PacDot(67, 43).GetGameObject());
	Startscene.Add(PacDot(67, 163).GetGameObject());
	Startscene.Add(PacDot(67, 187).GetGameObject());
	Startscene.Add(PacDot(67, 235).GetGameObject());
	//Row_09
	Startscene.Add(PacDot(75, 11).GetGameObject());
	Startscene.Add(PacDot(75, 43).GetGameObject());
	Startscene.Add(PacDot(75, 51).GetGameObject());
	Startscene.Add(PacDot(75, 59).GetGameObject());
	Startscene.Add(PacDot(75, 67).GetGameObject());
	Startscene.Add(PacDot(75, 163).GetGameObject());
	Startscene.Add(PacDot(75, 187).GetGameObject());
	Startscene.Add(PacDot(75, 195).GetGameObject());
	Startscene.Add(PacDot(75, 203).GetGameObject());
	Startscene.Add(PacDot(75, 211).GetGameObject());
	Startscene.Add(PacDot(75, 235).GetGameObject());
	//Row_10
	Startscene.Add(PacDot(83, 11).GetGameObject());
	Startscene.Add(PacDot(83, 43).GetGameObject());
	Startscene.Add(PacDot(83, 67).GetGameObject());
	Startscene.Add(PacDot(83, 163).GetGameObject());
	Startscene.Add(PacDot(83, 187).GetGameObject());
	Startscene.Add(PacDot(83, 211).GetGameObject());
	Startscene.Add(PacDot(83, 235).GetGameObject());
	//Row_11
	Startscene.Add(PacDot(91, 11).GetGameObject());
	Startscene.Add(PacDot(91, 43).GetGameObject());
	Startscene.Add(PacDot(91, 67).GetGameObject());
	Startscene.Add(PacDot(91, 163).GetGameObject());
	Startscene.Add(PacDot(91, 187).GetGameObject());
	Startscene.Add(PacDot(91, 211).GetGameObject());
	Startscene.Add(PacDot(91, 235).GetGameObject());
	//Row_12
	Startscene.Add(PacDot(99, 11).GetGameObject());
	Startscene.Add(PacDot(99, 19).GetGameObject());
	Startscene.Add(PacDot(99, 27).GetGameObject());
	Startscene.Add(PacDot(99, 35).GetGameObject());
	Startscene.Add(PacDot(99, 43).GetGameObject());
	Startscene.Add(PacDot(99, 67).GetGameObject());
	Startscene.Add(PacDot(99, 163).GetGameObject());
	Startscene.Add(PacDot(99, 171).GetGameObject());
	Startscene.Add(PacDot(99, 179).GetGameObject());
	Startscene.Add(PacDot(99, 187).GetGameObject());;
	Startscene.Add(PacDot(99, 211).GetGameObject());
	Startscene.Add(PacDot(99, 219).GetGameObject());
	Startscene.Add(PacDot(99, 227).GetGameObject());
	Startscene.Add(PacDot(99, 235).GetGameObject());
	//Row_13
	Startscene.Add(PacDot(107, 43).GetGameObject());
	Startscene.Add(PacDot(107, 235).GetGameObject());
	//Row_14
	Startscene.Add(PacDot(115, 43).GetGameObject());
	Startscene.Add(PacDot(115, 235).GetGameObject());
	//Row_15
	Startscene.Add(PacDot(123, 11).GetGameObject());
	Startscene.Add(PacDot(123, 19).GetGameObject());
	Startscene.Add(PacDot(123, 27).GetGameObject());
	Startscene.Add(PacDot(123, 35).GetGameObject());
	Startscene.Add(PacDot(123, 43).GetGameObject());
	Startscene.Add(PacDot(123, 67).GetGameObject());
	Startscene.Add(PacDot(123, 163).GetGameObject());
	Startscene.Add(PacDot(123, 171).GetGameObject());
	Startscene.Add(PacDot(123, 179).GetGameObject());
	Startscene.Add(PacDot(123, 187).GetGameObject());;
	Startscene.Add(PacDot(123, 211).GetGameObject());
	Startscene.Add(PacDot(123, 219).GetGameObject());
	Startscene.Add(PacDot(123, 227).GetGameObject());
	Startscene.Add(PacDot(123, 235).GetGameObject());
	//Row_16
	Startscene.Add(PacDot(131, 11).GetGameObject());
	Startscene.Add(PacDot(131, 43).GetGameObject());
	Startscene.Add(PacDot(131, 67).GetGameObject());
	Startscene.Add(PacDot(131, 163).GetGameObject());
	Startscene.Add(PacDot(131, 187).GetGameObject());
	Startscene.Add(PacDot(131, 211).GetGameObject());
	Startscene.Add(PacDot(131, 235).GetGameObject());
	//Row_17
	Startscene.Add(PacDot(139, 11).GetGameObject());
	Startscene.Add(PacDot(139, 43).GetGameObject());
	Startscene.Add(PacDot(139, 67).GetGameObject());
	Startscene.Add(PacDot(139, 163).GetGameObject());
	Startscene.Add(PacDot(139, 187).GetGameObject());
	Startscene.Add(PacDot(139, 211).GetGameObject());
	Startscene.Add(PacDot(139, 235).GetGameObject());
	//Row_18
	Startscene.Add(PacDot(147, 11).GetGameObject());
	Startscene.Add(PacDot(147, 43).GetGameObject());
	Startscene.Add(PacDot(147, 51).GetGameObject());
	Startscene.Add(PacDot(147, 59).GetGameObject());
	Startscene.Add(PacDot(147, 67).GetGameObject());
	Startscene.Add(PacDot(147, 163).GetGameObject());
	Startscene.Add(PacDot(147, 187).GetGameObject());
	Startscene.Add(PacDot(147, 195).GetGameObject());
	Startscene.Add(PacDot(147, 203).GetGameObject());
	Startscene.Add(PacDot(147, 211).GetGameObject());
	Startscene.Add(PacDot(147, 235).GetGameObject());
	//Row_19
	Startscene.Add(PacDot(155, 11).GetGameObject());
	Startscene.Add(PacDot(155, 43).GetGameObject());
	Startscene.Add(PacDot(155, 163).GetGameObject());
	Startscene.Add(PacDot(155, 187).GetGameObject());
	Startscene.Add(PacDot(155, 235).GetGameObject());
	//Row_20
	Startscene.Add(PacDot(163, 11).GetGameObject());
	Startscene.Add(PacDot(163, 43).GetGameObject());
	Startscene.Add(PacDot(163, 163).GetGameObject());
	Startscene.Add(PacDot(163, 187).GetGameObject());
	Startscene.Add(PacDot(163, 235).GetGameObject());
	//Row_21
	Startscene.Add(PacDot(171, 11).GetGameObject());
	Startscene.Add(PacDot(171, 19).GetGameObject());
	Startscene.Add(PacDot(171, 27).GetGameObject());
	Startscene.Add(PacDot(171, 35).GetGameObject());
	Startscene.Add(PacDot(171, 43).GetGameObject());
	Startscene.Add(PacDot(171, 51).GetGameObject());
	Startscene.Add(PacDot(171, 59).GetGameObject());
	Startscene.Add(PacDot(171, 67).GetGameObject());
	Startscene.Add(PacDot(171, 75).GetGameObject());
	Startscene.Add(PacDot(171, 75).GetGameObject());
	Startscene.Add(PacDot(171, 83).GetGameObject());
	Startscene.Add(PacDot(171, 91).GetGameObject());
	Startscene.Add(PacDot(171, 99).GetGameObject());
	Startscene.Add(PacDot(171, 107).GetGameObject());
	Startscene.Add(PacDot(171, 115).GetGameObject());
	Startscene.Add(PacDot(171, 123).GetGameObject());
	Startscene.Add(PacDot(171, 131).GetGameObject());
	Startscene.Add(PacDot(171, 139).GetGameObject());
	Startscene.Add(PacDot(171, 147).GetGameObject());
	Startscene.Add(PacDot(171, 155).GetGameObject());
	Startscene.Add(PacDot(171, 163).GetGameObject());
	Startscene.Add(PacDot(171, 171).GetGameObject());
	Startscene.Add(PacDot(171, 179).GetGameObject());
	Startscene.Add(PacDot(171, 187).GetGameObject());
	Startscene.Add(PacDot(171, 195).GetGameObject());
	Startscene.Add(PacDot(171, 203).GetGameObject());
	Startscene.Add(PacDot(171, 211).GetGameObject());
	Startscene.Add(PacDot(171, 235).GetGameObject());
	//Row_2
	Startscene.Add(PacDot(179, 11).GetGameObject());
	Startscene.Add(PacDot(179, 35).GetGameObject());
	Startscene.Add(PacDot(179, 43).GetGameObject());
	Startscene.Add(PacDot(179, 67).GetGameObject());
	Startscene.Add(PacDot(179, 163).GetGameObject());
	Startscene.Add(PacDot(179, 211).GetGameObject());
	Startscene.Add(PacDot(179, 235).GetGameObject());
	//Row_23
	Startscene.Add(PacDot(187, 11).GetGameObject());
	Startscene.Add(PacDot(187, 35).GetGameObject());
	Startscene.Add(PacDot(187, 43).GetGameObject());
	Startscene.Add(PacDot(187, 67).GetGameObject());
	Startscene.Add(PacDot(187, 163).GetGameObject());
	Startscene.Add(PacDot(187, 211).GetGameObject());
	Startscene.Add(PacDot(187, 235).GetGameObject());
	//Row_24
	Startscene.Add(PacDot(195, 11).GetGameObject());
	Startscene.Add(PacDot(195, 43).GetGameObject());
	Startscene.Add(PacDot(195, 67).GetGameObject());
	Startscene.Add(PacDot(195, 163).GetGameObject());
	Startscene.Add(PacDot(195, 187).GetGameObject());
	Startscene.Add(PacDot(195, 195).GetGameObject());
	Startscene.Add(PacDot(195, 203).GetGameObject());
	Startscene.Add(PacDot(195, 211).GetGameObject());
	Startscene.Add(PacDot(195, 235).GetGameObject());
	//Row_25
	Startscene.Add(PacDot(203, 11).GetGameObject());
	Startscene.Add(PacDot(203, 43).GetGameObject());
	Startscene.Add(PacDot(203, 67).GetGameObject());
	Startscene.Add(PacDot(203, 163).GetGameObject());
	Startscene.Add(PacDot(203, 187).GetGameObject());
	Startscene.Add(PacDot(203, 211).GetGameObject());
	Startscene.Add(PacDot(203, 235).GetGameObject());
	//Row_26
	Startscene.Add(PacDot(211, 11).GetGameObject());
	Startscene.Add(PacDot(211, 19).GetGameObject());
	Startscene.Add(PacDot(211, 35).GetGameObject());
	Startscene.Add(PacDot(211, 43).GetGameObject());
	Startscene.Add(PacDot(211, 51).GetGameObject());
	Startscene.Add(PacDot(211, 59).GetGameObject());
	Startscene.Add(PacDot(211, 67).GetGameObject());
	Startscene.Add(PacDot(211, 163).GetGameObject());
	Startscene.Add(PacDot(211, 171).GetGameObject());
	Startscene.Add(PacDot(211, 179).GetGameObject());
	Startscene.Add(PacDot(211, 211).GetGameObject());
	Startscene.Add(PacDot(211, 219).GetGameObject());
	Startscene.Add(PacDot(211, 227).GetGameObject());
	Startscene.Add(PacDot(211, 235).GetGameObject());


	Startscene.Add(PowerUp("PacBoost.png", { 8,24 }).GetGameObject());
	Startscene.Add(PowerUp("PacBoost.png", { 8,184 }).GetGameObject());
	Startscene.Add(PowerUp("PacBoost.png", { 208,24 }).GetGameObject());
	Startscene.Add(PowerUp("PacBoost.png", { 208,184 }).GetGameObject());

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
	//Ghost StartingBox
	wallManager.AddWall("Walls/Wall_84x100_20x4.png");
	wallManager.AddWall("Walls/Wall_120x100_20x4.png");
	wallManager.AddWall("Walls/Wall_84x104_4x28.png");
	wallManager.AddWall("Walls/Wall_136x104_4x28.png");
	wallManager.AddWall("Walls/Wall_88x128_48x4.png");



	wallManager.AddWallsToScene(Startscene);


	//  , { {-1,0}, {1,0}, {0, 1}, {0, -1} }
	Startscene.Add(IntersectionTile({ 4,4 }, { {1,0}, {0, 1} }).GetGameObject());
	Startscene.Add(IntersectionTile({ 4,36 }, { {1,0}, {0, 1},{0,-1} }).GetGameObject());
	Startscene.Add(IntersectionTile({ 4,60 }, { {1,0},{0,-1} }).GetGameObject());
	Startscene.Add(IntersectionTile({ 4,156 }, { {1,0},{0,1} }).GetGameObject());
	Startscene.Add(IntersectionTile({ 4,180 }, { {1,0},{0,-1} }).GetGameObject());
	Startscene.Add(IntersectionTile({ 4,204 }, { {1,0},{0,1} }).GetGameObject());
	Startscene.Add(IntersectionTile({ 4,228 }, { {1,0},{0,-1} }).GetGameObject());

	Startscene.Add(IntersectionTile({ 44,4 }, { {-1,0}, {1,0}, {0, 1} }).GetGameObject());
	Startscene.Add(IntersectionTile({ 44,36 }, { {-1,0}, {1,0}, {0, 1}, {0, -1} }).GetGameObject());
	Startscene.Add(IntersectionTile({ 44,60 }, { {-1, 0}, {0,-1}, {0,1} }).GetGameObject());
	Startscene.Add(IntersectionTile({ 44,108 }, { {-1,0}, {1,0}, {0, 1}, {0, -1} }).GetGameObject());
	Startscene.Add(IntersectionTile({ 44,156 }, { {-1,0}, {1,0}, {0, 1}, {0, -1} }).GetGameObject());
	Startscene.Add(IntersectionTile({ 44,180 }, { {1,0}, {0, 1}, {0, -1} }).GetGameObject());
	Startscene.Add(IntersectionTile({ 44,204 }, { {-1,0},   {0, -1} }).GetGameObject());

	Startscene.Add(IntersectionTile({ 68,36 }, { {-1,0},   {1, 0} ,   {0, 1} }).GetGameObject());
	Startscene.Add(IntersectionTile({ 68,60 }, { {1, 0} ,   {0, -1} }).GetGameObject());
	Startscene.Add(IntersectionTile({ 68,84 }, { {1, 0} ,   {0, 1} }).GetGameObject());
	Startscene.Add(IntersectionTile({ 68,108 }, { {-1, 0} ,   {0, -1},   {0, 1} }).GetGameObject());
	Startscene.Add(IntersectionTile({ 68,132 }, { {1, 0} ,   {0, -1},   {0, 1} }).GetGameObject());
	Startscene.Add(IntersectionTile({ 68,156 }, { {1, 0} ,   {-1, 0},   {0, -1} }).GetGameObject());
	Startscene.Add(IntersectionTile({ 68,180 }, { {1, 0} ,   {-1, 0},   {0, 1} }).GetGameObject());
	Startscene.Add(IntersectionTile({ 68,204 }, { {1, 0} ,   {0, -1} }).GetGameObject());

	Startscene.Add(IntersectionTile({ 92,4 }, { {-1, 0} ,   {0, 1} }).GetGameObject());
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




	Startscene.Add(IntersectionTile({ 104,84 }, { {-1,0},{1,0} }).GetGameObject());

}

int main(int, char* [])
{
	Minigin engine{ "../Data/", g_WindowSize, "Pac Man Xander Berten 2DAE07" };
	engine.Run(load);

	return 0;
}

