/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** ScriptSystem
*/

#ifndef SCRIPTSYSTEM_HPP_
#define SCRIPTSYSTEM_HPP_

// Exodia ECS Interface includes
#include "Interface/EntitySystem.hpp"

// Exodia ECS Components includes
#include "Component/Components.hpp"
#include "Component/ComponentHandle.hpp"

namespace Exodia {

    class ScriptSystem : public EntitySystem {

        ///////////////////////////////
        // Constructors & Destructor //
        ///////////////////////////////
      public:
        ScriptSystem() = default;
        virtual ~ScriptSystem() override = default;

        /////////////
        // Methods //
        /////////////
      public:
        virtual void Update(World *world, Timestep ts) override;
    };
}; // namespace Exodia

#endif /* !SCRIPTSYSTEM_HPP_ */
