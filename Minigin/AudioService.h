#pragma once
#include <string>
#include "AudioServiceImpl.h"

class AudioService
{
public:
    AudioService();
    virtual ~AudioService();

    AudioService(const AudioService& other) = delete;
    AudioService(AudioService&& other) = delete;
    AudioService& operator=(const AudioService& other) = delete;
    AudioService& operator=(AudioService&& other) = delete;

    virtual void Play(int id);
    virtual void AddSound(const int id, const std::string& file);
    virtual int GetLastId() const;

private:
    AudioServiceImpl* m_Impl;
};

class null_AudioService final : public AudioService
{
    void Play([[maybe_unused]]int id) override {}
    void AddSound([[maybe_unused]] const int id, [[maybe_unused]] const std::string& file) override{}
    int GetLastId()const override { return 0; }
};
