/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** AnimationSystem
*/

#ifndef ANIMATIONSYSTEM_HPP_
#define ANIMATIONSYSTEM_HPP_

#include "Exodia.hpp"
#include "Component/Animation.hpp"
#include "Scripts/Player/Player.hpp"
#include "Scripts/Pata-pata/Pata-pata.hpp"

using namespace Exodia;

namespace RType {

    class AnimationSystem : public EntitySystem {
      public:
        // Constructor && Destructor
        AnimationSystem(){};

        virtual ~AnimationSystem(){};

      public:
        // Methods
        virtual void Update(World *world, Timestep ts) override;

      private:
        template <typename T, typename F>
        void UpdateAnimation(Entity *entity, F &&func);
        void UpdatePlayer(Entity *entity, Exodia::ComponentHandle<SpriteRendererComponent> &sprite, Exodia::ComponentHandle<Animation> &animation, Timestep ts);
        void UpdatePataPata(Exodia::ComponentHandle<SpriteRendererComponent> &sprite, Exodia::ComponentHandle<Animation> &animation, Timestep ts);
        void UpdateBullet(Exodia::ComponentHandle<SpriteRendererComponent> &sprite, Exodia::ComponentHandle<Animation> &animation, Timestep ts);
    };
}; // namespace Exodia

#endif /* !ANIMATIONSYSTEM_HPP_ */
