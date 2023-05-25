#pragma once
#include "Singleton.h"
#include "AudioService.h"
#include "CollisionManager.h"
#include "InputManager.h"
#include "Renderer.h"
#include "ResourceManager.h"
#include "SceneManager.h"


template<typename T, typename DefaultService>
class DefaultServiceLocator
{
public:
	static T& GetService()
	{
		if (m_Service) return *m_Service;

		return GetDefaultService();
	}

	static void SetService(T* service)
	{
		//Delete the service if it is not the default service
		if (m_Service && m_Service != &GetDefaultService()) delete m_Service;
		m_Service = service;
	}

	// Cleanup the service if it's not the default one
	static void Cleanup()
	{
		if (m_Service && m_Service != &GetDefaultService())
		{
			delete m_Service;
			m_Service = nullptr;
		}
	}

private:
	// Get the default service instance
	static T& GetDefaultService()
	{
		static DefaultService defaultService;
		return defaultService;
	}

	// Pointer to the registered service instance
	static T* m_Service;
};

// Define the static member variable for the service
template<typename T, typename DefaultService>
T* DefaultServiceLocator<T, DefaultService>::m_Service = nullptr;



class ServiceLocator final : public Singleton<ServiceLocator>
{
public:
	static DefaultServiceLocator<null_AudioService, AudioService> AudioService;
	static DefaultServiceLocator<null_CollisionManager, CollisionManager> CollisionManager;
	static DefaultServiceLocator<null_InputManager, InputManager> InputManager;
	static DefaultServiceLocator<Renderer, null_Renderer> Renderer;
	static DefaultServiceLocator<ResourceManager, null_ResourceManager> ResourceManager;


	static void Cleanup();
private:
	friend class Singleton<ServiceLocator>;
	ServiceLocator() = default;
};