/*
** EPITECH PROJECT, 2023
** $
** File description:
** Player
*/

#ifndef BULLETPLAYER_HPP_
#define BULLETPLAYER_HPP_

// Exodia includes
#include "Exodia.hpp"

namespace RType {

    class BulletPlayer : public Exodia::ScriptableEntity {

        /////////////
        // Methods //
        /////////////
      public:
        void OnUpdate(Exodia::Timestep ts) override;
        void OnCollisionEnter(Exodia::Entity *entity) override;

      private:
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

#endif /* !BULLETPLAYER_HPP_ */
