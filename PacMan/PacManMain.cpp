
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

glm::vec2 g_WindowSize{ 324, 400 };


void load()
{
	//LevelManager::GetInstance().AddStartScreen();
	//auto& audioService = ServiceLocator::GetInstance().AudioService.GetService();
	auto& Startscene = SceneManager::GetInstance().CreateScene("Level0");


	Startscene.Add(PacMan().GetPacMan());
	Startscene.Add(PacDot(50,50).GetGameObject());
}

int main(int, char* [])
{
	Minigin engine{ "../Data/", g_WindowSize, "Pac Man Xander Berten 2DAE07" };
	engine.Run(load);

	return 0;
}

