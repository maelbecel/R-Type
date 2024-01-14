/*
** EPITECH PROJECT, 2023
** $
** File description:
** Player
*/

#ifndef SUPERBULLET_HPP_
#define SUPERBULLET_HPP_

// Exodia includes
#include "Exodia.hpp"

namespace RType {

    class SuperBullet : public Exodia::ScriptableEntity {

        /////////////
        // Methods //
        /////////////
      public:
        void OnUpdate(Exodia::Timestep ts) override;
        void OnCollisionEnter(Exodia::Entity *entity) override;
        void UpdateAnimations();

        ////////////////
        // Attributes //
        ////////////////
      private:
        bool _NeedUpdate = true;
        float _Speed = 10.0f;
        // TODO: Damage stats of the bullet
    };
}; // namespace RType

#endif /* !SUPERBULLET_HPP_ */