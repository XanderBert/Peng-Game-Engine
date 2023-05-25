#include "ServiceLocator.h"

//Declarations are also put in the cpp file. Otherwise the linker will not find the definitions in release.
DefaultServiceLocator<null_AudioService, AudioService> ServiceLocator::AudioService;
DefaultServiceLocator<null_CollisionManager, CollisionManager> ServiceLocator::CollisionManager;
DefaultServiceLocator<null_InputManager, InputManager> ServiceLocator::InputManager;
DefaultServiceLocator<Renderer, null_Renderer> ServiceLocator::Renderer;
DefaultServiceLocator<ResourceManager, null_ResourceManager> ServiceLocator::ResourceManager;

void ServiceLocator::Cleanup()
{
	AudioService.Cleanup();
	CollisionManager.Cleanup();
	InputManager.Cleanup();
	Renderer.Cleanup();
	ResourceManager.Cleanup();
}
