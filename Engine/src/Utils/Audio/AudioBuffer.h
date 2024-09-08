#pragma once
#include <cstdint>
#include <string>

#include "AudioSource.h"
const float PIXEL_TO_CM = 1;

class AudioBuffer
{
private:
    ALuint m_bufferId;

public:
    AudioBuffer(unsigned int buffer);
    ~AudioBuffer();
    const unsigned GetBufferId() const;
};
