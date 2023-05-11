#include "ServiceLocator.h"



void ServiceLocator::Cleanup()
{
	AudioService.Cleanup();
	CollisionManager.Cleanup();
	InputManager.Cleanup();
	LevelLoader.Cleanup();
	Renderer.Cleanup();
	ResourceManager.Cleanup();
}
