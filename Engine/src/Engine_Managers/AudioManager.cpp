#include "AudioManager.h"

#include "LogicManager.h"


AudioManager* AudioManager::audioInstance = nullptr;

AudioManager* AudioManager::GetInstanceAudioManager()
{
    if (audioInstance == nullptr)
    {
        audioInstance = new AudioManager();
    }
    return audioInstance;
}

void AudioManager::Init()
{
    //get the default device
    Device = alcOpenDevice(NULL);
    if (Device)
    {
        //create context
        Context = alcCreateContext(Device, NULL);

        //set current context
        alcMakeContextCurrent(Context);
    }
}

void AudioManager::ShutDown()
{
    alcMakeContextCurrent(NULL);

    if (Device != nullptr)
    {
        alcCloseDevice(Device);
        Device = nullptr;
    }

    if (Context)
    {
        alcDestroyContext(Context);
        Context = nullptr;
    }

    for (const auto& tex : audioBuffers)
    {
        delete tex.second;
    }

    for (int i = 0; i < audioSources.size(); ++i)
    {
        delete audioSources[i];
    }
}

ALCcontext* AudioManager::GetContext() const
{
    return Context;
}

ALCdevice* AudioManager::GetDevice() const
{
    return Device;
}

void AudioManager::PlayInstantSound(std::string audio, float pitch, float gain, Vec2 position)
{
    AudioSource* audio_source = CreateAudioSource(pitch, gain, false, position);
    audio_source->PlayClip(audio);
}


AudioBuffer* AudioManager::LoadAudio(std::string path)
{
    if (audioBuffers.find(path) == audioBuffers.end())
    {
        int channel, sampleRate, bps, size;
        //load the data
        char* data = loadWAV(path, channel, sampleRate, bps, size);

        unsigned int bufferid, format;
        alGenBuffers(1, &bufferid);
        if (channel == 1)
        {
            if (bps == 8)
            {
                format = AL_FORMAT_MONO8;
            }
            else
            {
                format = AL_FORMAT_MONO16;
            }
        }
        else
        {
            if (bps == 8)
            {
                format = AL_FORMAT_STEREO8;
            }
            else
            {
                format = AL_FORMAT_STEREO16;
            }
        }
        alBufferData(bufferid, format, data, size, sampleRate);
        audioBuffers[path] = new AudioBuffer(bufferid);
        return audioBuffers[path];
    }
    return audioBuffers[path];
}


AudioSource* AudioManager::CreateAudioSource(float pitch, float gain, bool loop, Vec2 position,
                                             Vec2 velocity)
{
    for (int i = 0; i < audioSources.size(); ++i)
    {
        if (!audioSources[i]->isPlaying())
        {
            audioSources[i]->SetPitch(pitch);
            audioSources[i]->SetGain(gain);
            audioSources[i]->SetLooping(loop);
            audioSources[i]->SetPosition(position);
            audioSources[i]->SetVelocity(velocity);
            return audioSources[i];
        }
    }

    //create audio source
    AudioSource* source = new AudioSource(pitch, gain, loop, position, velocity);
    //add to the list
    audioSources.push_back(source);
    return source;
}



int AudioManager::getFileSize(FILE* inFile)
{
    int fileSize = 0;
    fseek(inFile, 0, SEEK_END);

    fileSize = ftell(inFile);

    fseek(inFile, 0, SEEK_SET);
    return fileSize;
}

char* AudioManager::loadWAV(std::string fn, int& chan, int& samplerate, int& bps, int& size)
{
    //read buffer
    char buffer[4];
    //init the stream
    std::ifstream in(fn, std::ios::binary);
    //read the chunk ID "RIFF"
    in.read(buffer, 4);
    if (strncmp(buffer, "RIFF", 4) != 0)
    {
        return nullptr;
    }

    in.read(buffer, 4); //RiffChunkSize
    in.read(buffer, 4); //Format(“wave”) 
    in.read(buffer, 4); //SubChunkID (“fmt”)  
    in.read(buffer, 4); //FmtChunkSize 16
    int FmtChunkSize = convertToInt(buffer, 4);
    in.read(buffer, 2); //AudioFormat
    in.read(buffer, 2); //Channels
    chan = convertToInt(buffer, 2);
    in.read(buffer, 4); //SampleRate
    samplerate = convertToInt(buffer, 4);
    in.read(buffer, 4); //ByteRate
    in.read(buffer, 2); //BlockAlign
    in.read(buffer, 2); //BitsPerSample
    bps = convertToInt(buffer, 2);
    if (FmtChunkSize > 16)
    {
        in.read(buffer, 2); //ExtraParamsSize
        int numBytesToSkip = convertToInt(buffer, 2);
        in.read(buffer, numBytesToSkip); //ExtraParams
    }

    while (strncmp(buffer, "data", 4) != 0)
    {
        in.read(buffer, 4);
    }
    in.read(buffer, 4);
    size = convertToInt(buffer, 4);
    char* data = new char[size];
    in.read(data, size);
    return data;
}

bool AudioManager::isBigEndian()
{
    int a = 1;
    return !((char*)&a)[0];
}

int AudioManager::convertToInt(char* buffer, int len)
{
    int a = 0;
    if (!isBigEndian())
        for (int i = 0; i < len; i++)
            ((char*)&a)[i] = buffer[i];
    else
        for (int i = 0; i < len; i++)
            ((char*)&a)[3 - i] = buffer[i];
    return a;
}
