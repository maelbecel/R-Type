/*
** EPITECH PROJECT, 2023
** ECS
** File description:
** EntitySystem
*/

#ifndef ENTITYSYSTEM_HPP_
#define ENTITYSYSTEM_HPP_

// Exodia Core includes
#include "Exodia/Core/Time/Timestep.hpp"

// Exodia Utils includes
#include "Utils/CrossPlatform.hpp"

namespace Exodia {

    class World;

    class EntitySystem {
        ////////////////
        // Destructor //
        ////////////////
      public:
        virtual ~EntitySystem() = default;

        /////////////
        // Methods //
        /////////////
      public:
        virtual void Configure(World *world) { (void)world; }

        virtual void Unconfigure(World *world) { (void)world; }

        virtual void Update(World *world, Timestep ts) {
            (void)world;
            (void)ts;
        }
    };
}; // namespace Exodia

#endif /* !ENTITYSYSTEM_HPP_ */
