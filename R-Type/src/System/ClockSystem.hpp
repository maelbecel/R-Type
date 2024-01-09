/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** AnimationSystem
*/

#ifndef CLOCKSYSTEM_HPP_
#define CLOCKSYSTEM_HPP_

// R-Type Events includes
#include "Event/AnimationEvent.hpp"

namespace RType {

    class ClockSystem : public Exodia::EntitySystem {

        //////////////////////////////
        // Constructor & Destructor //
        //////////////////////////////
      public:
        ClockSystem() = default;
        ~ClockSystem() = default;

        /////////////
        // Methods //
        /////////////
      public:
        void Update(Exodia::World *world, Exodia::Timestep ts) override;
    };
}; // namespace RType

#endif /* !CLOCKSYSTEM_HPP_ */