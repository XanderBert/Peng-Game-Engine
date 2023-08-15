#pragma once
#include "AudioService.h"

class AudioServiceDebug final : public null_AudioService
{
public:
	AudioServiceDebug();
	virtual ~AudioServiceDebug() override;

	AudioServiceDebug(const AudioServiceDebug& other) = delete;
	AudioServiceDebug(AudioServiceDebug&& other) = delete;
	AudioServiceDebug& operator=(const AudioServiceDebug& other) = delete;
	AudioServiceDebug& operator=(AudioServiceDebug&& other) = delete;

	void Play(int id) override;
	void Stop(int id) override;
	void AddSound(const int id, const std::string& file) override;
	void ToggleMute() override {}
	int GetLastId()const override;

private:
	null_AudioService* m_pAudioService;
};
