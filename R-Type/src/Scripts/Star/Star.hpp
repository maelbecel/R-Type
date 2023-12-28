/*
** EPITECH PROJECT, 2023
** $
** File description:
** Player
*/

#ifndef STAR_HPP_
#define STAR_HPP_

// Exodia includes
#include "Exodia.hpp"
#include "Component/Clock.hpp"
#include <random>

using namespace Exodia;


namespace RType {

    class Star : public ScriptableEntity {

        /////////////
        // Methods //
        /////////////
      public:
        enum class State {
            GROWING = 0,
            SHRINKING,
        };

        void OnCreate() override;

        void OnUpdate(Timestep ts) override;

        ////////////////
        // Attributes //
        ////////////////
      private:
        float _Intensity;
        State _State;
        float _Size;
    };
}; // namespace RType

#endif /* !STAR_HPP_ */
