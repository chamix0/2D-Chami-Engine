#include "AudioBuffer.h"

AudioBuffer::AudioBuffer(ALuint buffer): m_bufferId(buffer)
{
}

AudioBuffer::~AudioBuffer()
{
    alDeleteBuffers(1, &m_bufferId);
}

const unsigned AudioBuffer::GetBufferId() const
{
    return m_bufferId;
}
