#include "AudioSource.h"

#include "AudioBuffer.h"
#include "../../Engine_Managers/AudioManager.h"

AudioSource::AudioSource(float pitch, float gain, bool loop, Vec2 position, Vec2 velocity): m_clip(nullptr),
    m_pitch(pitch), m_loop(loop), m_position(position), m_velocity(velocity)

{
    //create the source 
    alGenSources(1, &m_sourceid);

    /*set float values*/
    //pitch
    alSourcef(m_sourceid,AL_PITCH, pitch);
    //gain (volume)
    alSourcef(m_sourceid,AL_GAIN, gain);
    //out of cone volume
    alSourcef(m_sourceid,AL_ROLLOFF_FACTOR, 0.75f);
    alSourcef(m_sourceid,AL_REFERENCE_DISTANCE, 10.f);


    /*set int values*/
    //loop
    alSourcei(m_sourceid,AL_LOOPING, loop);

    /*set vec3 values*/
    //position
    alSource3f(m_sourceid, AL_POSITION, m_position.x * PIXEL_TO_CM, m_position.y * PIXEL_TO_CM,
               m_position.z * PIXEL_TO_CM);
    //verlocity
    alSource3f(m_sourceid, AL_VELOCITY, m_velocity.x * PIXEL_TO_CM, m_velocity.y * PIXEL_TO_CM,
               m_velocity.z * PIXEL_TO_CM);
}

AudioSource::~AudioSource()
{
    //delete the source
    alDeleteSources(1, &m_sourceid);
}

void AudioSource::SetPitch(float pitch)
{
    m_pitch = pitch;
    alSourcef(m_sourceid,AL_PITCH, m_pitch);
}

void AudioSource::SetGain(float gain)
{
    m_gain = gain;
    alSourcef(m_sourceid,AL_GAIN, gain);
}

void AudioSource::SetLooping(bool loop)

{
    m_loop = loop;
    alSourcei(m_sourceid,AL_LOOPING, loop);
}

void AudioSource::SetPosition(Vec2 pos)
{
    m_position = Vec2(pos.x, pos.y, pos.z, m_position.a);
    alSource3f(m_sourceid, AL_POSITION, -m_position.x, m_position.y, m_position.z);
}

void AudioSource::SetVelocity(Vec2 vel)
{
    m_velocity = vel;
    alSource3f(m_sourceid, AL_VELOCITY, -m_velocity.x, m_velocity.y, 0);
}

void AudioSource::SetClip(AudioBuffer* buffer)
{
    m_clip = buffer;
    alSourcei(m_sourceid,AL_BUFFER,NULL);
    alSourcei(m_sourceid, AL_BUFFER, buffer->GetBufferId());
}

ALuint* AudioSource::GetAudioSourceId()
{
    return &m_sourceid;
}

void AudioSource::PlayClip(std::string clip)
{
    SetClip(AudioManager::GetInstanceAudioManager()->LoadAudio(clip));
    play();
}

void AudioSource::play()
{
    alSourcePlay(m_sourceid);
}

void AudioSource::stop()
{
    alSourceStop(m_sourceid);
}

void AudioSource::pause()
{
    alSourcePause(m_sourceid);
}

bool AudioSource::isPlaying() const
{
    ALint value;

    alGetSourcei(m_sourceid, AL_SOURCE_STATE, &value);


    if (value == AL_PLAYING)
    {
        return true;
    }
    if (value == AL_STOPPED)
    {
        return false;
    }
    if (value == AL_PAUSED)
    {
        return false;
    }
    return false;
}
