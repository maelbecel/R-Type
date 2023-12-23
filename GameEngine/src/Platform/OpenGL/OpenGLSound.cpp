/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** OpenGLSound
*/

#include "OpenGLSound.hpp"

// OpenAL-Soft include
#include <AL/alut.h>

namespace Exodia {

    ///////////////////////////////
    // Constructors & Destructor //
    ///////////////////////////////

    OpenGLSound::OpenGLSound(const std::string &path)
    {
        // -- Load the sound -- !WARNING! {.mp3} only
        _buffer = alutCreateBufferFromFile(path.c_str());

        // -- Create a source --
        alGenSources(1, &_source);

        // -- Configure the source --
        alSourcei(_source, AL_BUFFER, _buffer);          // Attach the buffer to the source
        alSourcei(_source, AL_LOOPING, AL_FALSE);        // Set the source to loop
        alSourcef(_source, AL_GAIN, 0.5f);               // Set the source to 50% volume
        alSourcei(_source, AL_SOURCE_RELATIVE, AL_TRUE); // Set the source to 2D
    }

    OpenGLSound::~OpenGLSound()
    {
        // -- Delete the source --
        alDeleteSources(1, &_source);

        // -- Delete the buffer --
        alDeleteBuffers(1, &_buffer);
    }

    /////////////
    // Methods //
    /////////////

    void OpenGLSound::Play()
    {
        alSourcePlay(_source);
    }

    void OpenGLSound::Pause()
    {
        alSourcePause(_source);
    }

    void OpenGLSound::Stop()
    {
        alSourceStop(_source);
    }

    ///////////////////////
    // Getters & Setters //
    ///////////////////////

    void OpenGLSound::SetVolume(float volume)
    {
        alSourcef(_source, AL_GAIN, volume);
    }

    void OpenGLSound::SetLoop(bool loop)
    {
        alSourcei(_source, AL_LOOPING, loop);
    }

    bool OpenGLSound::IsPlaying() const
    {
        ALint state;

        alGetSourcei(_source, AL_SOURCE_STATE, &state);

        return state == AL_PLAYING;
    }

    bool OpenGLSound::IsPaused() const
    {
        ALint state;

        alGetSourcei(_source, AL_SOURCE_STATE, &state);

        return state == AL_PAUSED;
    }

    bool OpenGLSound::IsStopped() const
    {
        ALint state;

        alGetSourcei(_source, AL_SOURCE_STATE, &state);

        return state == AL_STOPPED;
    }
};
