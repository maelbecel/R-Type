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
#include "Utils/Memory.hpp"

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
        virtual void Configure(UNUSED(World *world)) {};

        virtual void Unconfigure(UNUSED(World *world)) {};

        virtual void Update(UNUSED(World *world), UNUSED(Timestep ts)) {};
    };
}; // namespace Exodia

#endif /* !ENTITYSYSTEM_HPP_ */
