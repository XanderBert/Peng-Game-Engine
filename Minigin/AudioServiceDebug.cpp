#include "AudioServiceDebug.h"
#include "AudioService.h"
#include <iostream>

AudioServiceDebug::AudioServiceDebug() : null_AudioService()
{
	m_pAudioService = new AudioService();
}

AudioServiceDebug::~AudioServiceDebug()
{
	delete m_pAudioService;
}

void AudioServiceDebug::Play(int id)
{
	m_pAudioService->Play(id);
	std::cout << "\nAudioServiceDebug::Play(int id)\n";
	std::cout << "id = " << id << "\n";
}

void AudioServiceDebug::Stop(int id)
{
	m_pAudioService->Stop(id);
	std::cout << "\nAudioServiceDebug::Stop(int id)\n";
	std::cout << "id = " << id << "\n";
}

void AudioServiceDebug::AddSound(const int id, const std::string& file)
{
	m_pAudioService->AddSound(id, file);
	std::cout << "\nAudioServiceDebug::AddSound(const int id, const std::string& file)\n";
	std::cout << "id = " << id << "\n";
	std::cout << "file = " << file << "\n";
}

int AudioServiceDebug::GetLastId() const
{
	const auto lastId = m_pAudioService->GetLastId();
	std::cout << "\nAudioServiceDebug::GetLastId() const\n";
	std::cout << "return = " << lastId << "\n";
	return lastId;
}
