#include "AudioServiceImpl.h"

#include <iostream>

#include "ServiceLocator.h"

AudioServiceImpl::AudioServiceImpl() : m_StopRequested(false)
{
	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
	{
		std::cout << "SDL_mixer could not initialize! SDL_mixer Error: " << Mix_GetError() << std::endl;
	}

	//Create thread to play audio.
	m_AudioThread = std::jthread(&AudioServiceImpl::PlayAudioAsync, this);
}

AudioServiceImpl::~AudioServiceImpl()
{
	for (const auto& pair : m_Sounds)
	{
		Mix_FreeChunk(pair.second);
	}

	// Request stop and wait for the audio thread to finish
	std::unique_lock lock(m_AudioMutex);
	m_StopRequested = true;
	m_ConditionVariable.notify_one();
}

void AudioServiceImpl::Play(int id)
{
	if (m_Muted) return; //If the audio is muted, don't play it.)
	if (isAudioInQueue(id)) return; //If the audio is already in the queue, don't add it again. (This prevents the same audio from playing multiple times at the same time. -> that will just make it louder)

	std::unique_lock lock(m_AudioMutex);



	if (m_Sounds.empty() || !m_Sounds.contains(id)) return;
	m_AudioQueue.push(id);
	m_ConditionVariable.notify_one();
}

void AudioServiceImpl::Stop(int id)
{
	std::unique_lock lock(m_AudioMutex);

	if (m_Sounds.empty() || !m_Sounds.contains(id))
		return;

	// Stop the sound on all channels
	for (int channel = 0; channel < MIX_CHANNELS; ++channel)
	{
		Mix_Chunk* chunk = Mix_GetChunk(channel);
		if (chunk != nullptr && chunk == m_Sounds.find(id)->second)
		{
			Mix_HaltChannel(channel);
		}
	}

	// Remove any pending instances of the specified sound ID from the audio queue
	while (!m_AudioQueue.empty() && m_AudioQueue.front() == id)
	{
		m_AudioQueue.pop();
	}
}

void AudioServiceImpl::ToggleMute()
{
	m_Muted = !m_Muted;
}



Mix_Chunk* AudioServiceImpl::AddSound(const int id, const std::string& file)
{
	const auto pathdir = ServiceLocator::GetInstance().ResourceManager.GetService().GetDataPath() + file;

	Mix_Chunk* wave = Mix_LoadWAV(pathdir.c_str());

	if (wave == nullptr) return nullptr;


	if (m_Sounds.contains(id) || id < 0)
	{
		Mix_FreeChunk(wave);
		return nullptr;
	}

	m_Sounds.insert(std::make_pair(id, wave));
	return wave;
}

int AudioServiceImpl::GetLastId() const
{
	int largestValue{};

	for (const auto& pair : m_Sounds)
	{
		if (pair.first > largestValue)
		{
			largestValue = pair.first;
		}
	}

	return largestValue;
}

bool AudioServiceImpl::isAudioInQueue(int id)
{
	std::queue<int> tempQueue{};

	// Create a copy of the original queue
	{
		m_AudioMutex.lock();
		tempQueue = m_AudioQueue;
		m_AudioMutex.unlock();
	}



	// Iterate through the queue
	while (!tempQueue.empty()) {
		// Check if the front element of the queue matches the target number
		if (tempQueue.front() == id)
		{
			return true;  // Number found in the queue
		}

		// Remove the front element and move to the next one
		tempQueue.pop();
	}

	return false;  // Number not found in the queue
}

void AudioServiceImpl::PlayAudioAsync()
{
	while (true)
	{
		int audioData;

		// Wait until there is audio data in the queue or stop is requested
		{
			std::unique_lock lock(m_AudioMutex);

			m_ConditionVariable.wait(lock, [this]() { return !m_AudioQueue.empty() || m_StopRequested; });

			if (m_StopRequested) return;

			audioData = m_AudioQueue.front();
			m_AudioQueue.pop();
		}

		// Play the audio using the audio service
		Mix_PlayChannel(-1, m_Sounds.find(audioData)->second, 0);
	}
}
