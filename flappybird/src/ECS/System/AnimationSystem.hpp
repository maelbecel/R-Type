/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** AnimationSystem
*/

#ifndef ANIMATIONSYSTEM_HPP_
#define ANIMATIONSYSTEM_HPP_

// R-Type Events includes
#include "../Event/AnimationEvent.hpp"

using namespace Exodia;

namespace FlappyBird {

    class AnimationSystem : public Exodia::EntitySystem, public Exodia::EventSubscriber<Events::AnimationEndingEvent> {

        //////////////////////////////
        // Constructor & Destructor //
        //////////////////////////////
      public:
        AnimationSystem() = default;
        ~AnimationSystem() = default;

        /////////////
        // Methods //
        /////////////
      public:
        void Update(Exodia::World *world, Exodia::Timestep ts) override;
        void Receive(Exodia::World *world, const Events::AnimationEndingEvent &event) override;
    };
}; // namespace FlappyBird

#endif /* !ANIMATIONSYSTEM_HPP_ */