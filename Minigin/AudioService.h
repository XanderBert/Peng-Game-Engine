#pragma once
#include <condition_variable>
#include <queue>
#include <string>
#include <unordered_map>
#include "SDL_mixer.h"


class AudioService
{
public:
	AudioService();
	virtual ~AudioService();

	AudioService(const AudioService& other) = delete;
	AudioService(AudioService&& other) = delete;
	AudioService& operator=(const AudioService& other) = delete;
	AudioService& operator=(AudioService&& other) = delete;

	void Play(int id);
	//void Stop(int id);
	//void StopAllSounds();

	Mix_Chunk* AddSound(const int id, const std::string& file);
	int GetLastId() const;
	//bool RemoveSound(int id);

private:
	std::unordered_map<int, Mix_Chunk*> m_Sounds{};

	std::jthread m_AudioThread{};
	std::queue<int> m_AudioQueue{};
	std::mutex m_AudioMutex{};
	std::condition_variable m_ConditionVariable{};
	bool m_StopRequested{};

	void PlayAudioAsync();
};

class null_AudioService final : public AudioService
{

};
