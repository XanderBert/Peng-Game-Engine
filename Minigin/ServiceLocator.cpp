#include "ServiceLocator.h"

//Declarations are also put in the cpp file. Otherwise the linker will not find the definitions in release.
DefaultServiceLocator<AudioService, null_AudioService> ServiceLocator::AudioService;
DefaultServiceLocator<CollisionManager, null_CollisionManager> ServiceLocator::CollisionManager;
DefaultServiceLocator<InputManager, null_InputManager> ServiceLocator::InputManager;
DefaultServiceLocator<LevelLoader, null_LevelLoader> ServiceLocator::LevelLoader;
DefaultServiceLocator<Renderer, null_Renderer> ServiceLocator::Renderer;
DefaultServiceLocator<ResourceManager, null_ResourceManager> ServiceLocator::ResourceManager;

void ServiceLocator::Cleanup()
{
	AudioService.Cleanup();
	CollisionManager.Cleanup();
	InputManager.Cleanup();
	LevelLoader.Cleanup();
	Renderer.Cleanup();
	ResourceManager.Cleanup();
}
