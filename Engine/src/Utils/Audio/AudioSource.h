#pragma once
#include <string>

#include "../Vec2.h"
#include "../../../openal/AL/al.h"

class AudioBuffer;

class AudioSource
{
private:
    AudioBuffer* m_clip;
    ALuint m_sourceid;
    float m_pitch = 1, m_gain = 1;
    bool m_loop = true;
    Vec2 m_position = Vec2();
    Vec2 m_velocity = Vec2();

public:
    AudioSource(float pitch = 1, float gain = 1, bool loop = true, Vec2 position = Vec2(), Vec2 velocity = Vec2());
    ~AudioSource();
    void SetPitch(float pitch);
    void SetGain(float gain);
    void SetLooping(bool loop);
    void SetPosition(Vec2 pos);
    void SetVelocity(Vec2 vel);
    void SetClip(AudioBuffer* buffer);
    //getter
    ALuint* GetAudioSourceId();
    //manage audio
    void PlayClip(std::string clip);

    void play();
    void stop();
    void pause();
    bool isPlaying() const;
};
