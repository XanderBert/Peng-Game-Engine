#include "AudioServiceDebug.h"

#include <iostream>

AudioServiceDebug::AudioServiceDebug() : m_Impl(new AudioServiceImpl())
{
}

AudioServiceDebug::~AudioServiceDebug()
{
	delete m_Impl;
}

void AudioServiceDebug::Play(int id)
{
	AudioService::Play(id);
	std::cout << "\nAudioServiceDebug::Play(int id)\n";
	std::cout << "id = " << id << "\n";
}

void AudioServiceDebug::AddSound(const int id, const std::string& file)
{
	AudioService::AddSound(id, file);
	std::cout << "\nAudioServiceDebug::AddSound(const int id, const std::string& file)\n";
	std::cout << "id = " << id << "\n";
	std::cout << "file = " << file << "\n";
}

int AudioServiceDebug::GetLastId() const
{
	const auto lastId = AudioService::GetLastId();
	std::cout << "\nAudioServiceDebug::GetLastId() const\n";
	std::cout << "return = " << lastId << "\n";
	return lastId;
}
