#pragma once

class AudioService
{
public:
	AudioService() = default;
	~AudioService() = default;

	AudioService(const AudioService& other) = delete;
	AudioService(AudioService&& other) = delete;
	AudioService& operator=(const AudioService& other) = delete;
	AudioService& operator=(AudioService&& other) = delete;

	void play(int id);
};

class null_AudioService final : public AudioService
{

};
