/*
** EPITECH PROJECT, 2023
** $
** File description:
** Player
*/

#ifndef BULLETPLAYER_HPP_
#define BULLETPLAYER_HPP_

// Exodia includes
#include "Component/Animation.hpp"

#include <cmath>

using namespace Exodia;

namespace RType {

    class BulletPlayer : public ScriptableEntity {

        /////////////
        // Methods //
        /////////////
        public:
            void OnCreate() override;
            void OnUpdate(UNUSED(Timestep ts)) override;

        ////////////////
        // Attributes //
        ////////////////
        private:
            float _Speed;
    };
}; // namespace RT

#endif /* !BULLETPLAYER_HPP_ */
