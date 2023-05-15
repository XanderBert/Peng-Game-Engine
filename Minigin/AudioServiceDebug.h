#pragma once
#include "AudioService.h"

class AudioServiceDebug final :public AudioService
{
public:
    AudioServiceDebug();
    ~AudioServiceDebug();

    AudioServiceDebug(const AudioServiceDebug& other) = delete;
    AudioServiceDebug(AudioServiceDebug&& other) = delete;
    AudioServiceDebug& operator=(const AudioServiceDebug& other) = delete;
    AudioServiceDebug& operator=(AudioServiceDebug&& other) = delete;

    void Play(int id) override;
    void AddSound(const int id, const std::string& file) override;
    int GetLastId()const override;

private:
    AudioServiceImpl* m_Impl;
};
