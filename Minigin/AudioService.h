#pragma once
#include <string>
#include "AudioServiceImpl.h"

class null_AudioService
{
public:
    null_AudioService() = default;
    virtual ~null_AudioService() = default;

    null_AudioService(const null_AudioService& other) = delete;
    null_AudioService(null_AudioService&& other) = delete;
    null_AudioService& operator=(const null_AudioService& other) = delete;
    null_AudioService& operator=(null_AudioService&& other) = delete;

    virtual void Play(int id) = 0;
    virtual void AddSound(const int id, const std::string& file) = 0;
    virtual int GetLastId()const = 0;
};
 
class AudioService : public null_AudioService
{
public:
    AudioService();
    ~AudioService() override;

    AudioService(const AudioService& other) = delete;
    AudioService(AudioService&& other) = delete;
    AudioService& operator=(const AudioService& other) = delete;
    AudioService& operator=(AudioService&& other) = delete;

    virtual void Play(int id) override;
	virtual void AddSound(const int id, const std::string& file) override;
    virtual int GetLastId() const override;

private:
    AudioServiceImpl* m_Impl;
};


