/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** Sound
*/

#ifndef SOUND_HPP_
#define SOUND_HPP_

// Exodia Asset includes
#include "Asset/Utils/AssetType.hpp"

// External includes
#include <string>

namespace Exodia {

    class Sound : public Asset {

        ///////////////////////////////
        // Constructors & Destructor //
        ///////////////////////////////
      public:
        virtual ~Sound() = default;

        /////////////
        // Methods //
        /////////////
      public:
        virtual void Play() = 0;
        virtual void Pause() = 0;
        virtual void Stop() = 0;

        ///////////////////////
        // Getters & Setters //
        ///////////////////////
      public:
        virtual void SetVolume(float volume) = 0;
        virtual void SetLoop(bool loop) = 0;

        virtual bool IsPlaying() const = 0;
        virtual bool IsPaused() const = 0;
        virtual bool IsStopped() const = 0;
    };

    class Sound2D : public Sound {

        /////////////
        // Factory //
        /////////////
      public:
        static Ref<Sound2D> Create(const std::string &path);

        ///////////////////////
        // Getters & Setters //
        ///////////////////////
      public:
        static AssetType GetStaticType();
        virtual AssetType GetType() const override;
    };
}; // namespace Exodia

#endif /* !SOUND_HPP_ */
