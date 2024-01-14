/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** OpenGLSound
*/

#ifndef OPENGLSOUND_HPP_
#define OPENGLSOUND_HPP_

// Exodia Renderer
#include "Renderer/Sound/Sound.hpp"

// OpenAL-Soft include
#include <AL/al.h>
#include <AL/alc.h>

namespace Exodia {

    class OpenGLSound : public Sound2D {

        ///////////////////////////////
        // Constructors & Destructor //
        ///////////////////////////////
      public:
        OpenGLSound(const std::filesystem::path &path);
        ~OpenGLSound() override;

        /////////////
        // Methods //
        /////////////
      public:
        void Play() override;
        void Pause() override;
        void Stop() override;

        ///////////////////////
        // Getters & Setters //
        ///////////////////////
      public:
        void SetVolume(float volume) override;
        void SetLoop(bool loop) override;

        bool IsPlaying() const override;
        bool IsPaused() const override;
        bool IsStopped() const override;

        ////////////////
        // Attributes //
        ////////////////
      private:
        ALuint _source;
        ALuint _buffer;
    };
}; // namespace Exodia

#endif /* !OPENGLSOUND_HPP_ */
