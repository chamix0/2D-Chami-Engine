#pragma once
#include <fstream>
#include <map>
#include <vector>

#include "../Utils/Vec2.h"
#include "../Utils/Audio/AudioBuffer.h"
#include "../../openal/AL/alc.h"


class Vec2;


class AudioManager
{
private:
    //singleton
    static AudioManager* audioInstance; //singleton instance

    //audio context and device
    ALCdevice* Device = nullptr;
    ALCcontext* Context = nullptr;

    //audio map
    std::map<std::string, AudioBuffer*> audioBuffers;
    std::vector<AudioSource*> audioSources;

public:
    static AudioManager* GetInstanceAudioManager();

    void Init();
    void ShutDown();
    ALCcontext* GetContext() const;
    ALCdevice* GetDevice() const;
    void PlayInstantSound(std::string audio, float pitch = 1, float gain = 1,
                          Vec2 position = Vec2());
    AudioBuffer* LoadAudio(std::string path);
    AudioSource* CreateAudioSource(float pitch = 1, float gain = 1, bool loop = true,
                                   Vec2 position = Vec2(),
                                   Vec2 velocity = Vec2());

private:
    int getFileSize(FILE* inFile);
    char* loadWAV(std::string fn, int& chan, int& samplerate, int& bps, int& size);
    bool isBigEndian();
    int convertToInt(char* buffer, int len);

};
