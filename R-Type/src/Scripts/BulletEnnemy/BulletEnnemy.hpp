/*
** EPITECH PROJECT, 2023
** $
** File description:
** Player
*/

#ifndef BULLETENNEMY_HPP_
#define BULLETENNEMY_HPP_

// Exodia includes
#include "Exodia.hpp"
#include "Component/Animation.hpp"

#include <cmath>

using namespace Exodia;

namespace RType {

    class BulletEnnemy : public ScriptableEntity {

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
    };
}; // namespace Exodia

#endif /* !BULLETENNEMY_HPP_ */
