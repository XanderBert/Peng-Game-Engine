#pragma once
#include <condition_variable>
#include <queue>
#include <SDL_mixer.h>
#include <unordered_map>

class AudioServiceImpl final
{
public:
	AudioServiceImpl();
	~AudioServiceImpl();

	AudioServiceImpl(const AudioServiceImpl& other) = delete;
	AudioServiceImpl(AudioServiceImpl&& other) = delete;
	AudioServiceImpl& operator=(const AudioServiceImpl& other) = delete;
	AudioServiceImpl& operator=(AudioServiceImpl&& other) = delete;

	void Play(int id);
	void Stop(int id);
	Mix_Chunk* AddSound(const int id, const std::string& file);
	int GetLastId() const;

private:
	std::unordered_map<int, Mix_Chunk*> m_Sounds{};
	std::jthread m_AudioThread{};
	std::queue<int> m_AudioQueue{};
	std::mutex m_AudioMutex{};
	std::condition_variable m_ConditionVariable{};
	bool m_StopRequested{};

	void PlayAudioAsync();
};
