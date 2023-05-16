#pragma once
#include "AudioService.h"

class AudioServiceDebug final : public AudioService
{
public:
    AudioServiceDebug();
    ~AudioServiceDebug();

    AudioServiceDebug(const AudioServiceDebug& other) = delete;
    AudioServiceDebug(AudioServiceDebug&& other) = delete;
    AudioServiceDebug& operator=(const AudioServiceDebug& other) = delete;
    AudioServiceDebug& operator=(AudioServiceDebug&& other) = delete;

    void Play(int id);
    void AddSound(const int id, const std::string& file);
    int GetLastId()const override;

};
