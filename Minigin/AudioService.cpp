#include "AudioService.h"
#include "ServiceLocator.h"

AudioService::AudioService() : m_Impl(new AudioServiceImpl())
{
}

AudioService::~AudioService()
{
	delete m_Impl;
}

void AudioService::Play(int id)
{
	m_Impl->Play(id);
}

void AudioService::AddSound(const int id, const std::string& file)
{
	m_Impl->AddSound(id, file);
}

int AudioService::GetLastId() const
{
	return m_Impl->GetLastId();
}