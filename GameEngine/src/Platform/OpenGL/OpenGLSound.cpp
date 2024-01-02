/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** OpenGLSound
*/

#include "OpenGLSound.hpp"

// OpenAL-Soft include
#include <AL/alut.h>
#include <vorbis/vorbisfile.h>

namespace Exodia {

    ///////////////////////////////
    // Constructors & Destructor //
    ///////////////////////////////

    OpenGLSound::OpenGLSound(const std::filesystem::path &path) {
        if (path.extension() == ".wav")
            _buffer = alutCreateBufferFromFile(path.string().c_str());
        else if (path.extension() == ".ogg") {
            FILE *oggFile = fopen(path.string().c_str(), "rb");

            if (!oggFile) {
                EXODIA_CORE_ERROR("Failed to load sound: {0}", path.string());

                return;
            }

            OggVorbis_File oggStream;

            if (ov_open(oggFile, &oggStream, NULL, 0) < 0) {
                EXODIA_CORE_ERROR("Failed to load sound: {0}", path.string());

                fclose(oggFile);

                return;
            }

            vorbis_info *pInfo = ov_info(&oggStream, -1);

            ALsizei dataSize = 0;
            ALenum format = AL_FORMAT_MONO16;
            ALsizei freq = pInfo->rate;

            long totalSize = 0;
            int bitStream = 0;

            while (true) {
                char data[4096];
                long bytesRead = ov_read(&oggStream, data, sizeof(data), 0, 2, 1, &bitStream);

                if (bytesRead <= 0)
                    break;
                totalSize += bytesRead;
            }

            rewind(oggFile);

            char *bufferData = new char[totalSize];
            long bytesRead = 0;
            while (true) {
                long result = ov_read(&oggStream, bufferData + bytesRead, totalSize - bytesRead, 0, 2, 1, &bitStream);

                if (result <= 0)
                    break;
                bytesRead += result;
            }

            fclose(oggFile);

            alGenBuffers(1, &_buffer);
            alBufferData(_buffer, format, bufferData, totalSize, freq);

            delete[] bufferData;
        }

        if (_buffer == AL_NONE) {
            EXODIA_CORE_ERROR("Failed to load sound: {0}", path.string());

            return;
        }

        // -- Create a source --
        alGenSources(1, &_source);

        // -- Configure the source --
        alSourcei(_source, AL_BUFFER, _buffer);          // Attach the buffer to the source
        alSourcei(_source, AL_LOOPING, AL_FALSE);        // Set the source to loop
        alSourcef(_source, AL_GAIN, 0.5f);               // Set the source to 50% volume
        alSourcei(_source, AL_SOURCE_RELATIVE, AL_TRUE); // Set the source to 2D
    }

    OpenGLSound::~OpenGLSound() {
        // -- Delete the source --
        alDeleteSources(1, &_source);

        // -- Delete the buffer --
        alDeleteBuffers(1, &_buffer);
    }

    /////////////
    // Methods //
    /////////////

    void OpenGLSound::Play() {
        if (IsPlaying())
            return;
        alSourcePlay(_source);
    }

    void OpenGLSound::Pause() { alSourcePause(_source); }

    void OpenGLSound::Stop() { alSourceStop(_source); }

    ///////////////////////
    // Getters & Setters //
    ///////////////////////

    void OpenGLSound::SetVolume(float volume) { alSourcef(_source, AL_GAIN, volume); }

    void OpenGLSound::SetLoop(bool loop) { alSourcei(_source, AL_LOOPING, loop); }

    bool OpenGLSound::IsPlaying() const {
        ALint state;

        alGetSourcei(_source, AL_SOURCE_STATE, &state);

        return state == AL_PLAYING;
    }

    bool OpenGLSound::IsPaused() const {
        ALint state;

        alGetSourcei(_source, AL_SOURCE_STATE, &state);

        return state == AL_PAUSED;
    }

    bool OpenGLSound::IsStopped() const {
        ALint state;

        alGetSourcei(_source, AL_SOURCE_STATE, &state);

        return state == AL_STOPPED;
    }
}; // namespace Exodia
