/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** MovingSystem
*/

#ifndef MOVINGSYSTEM_HPP_
#define MOVINGSYSTEM_HPP_

// Exodia ECS Interface includes
#include "Interface/EntitySystem.hpp"

// Exodia ECS Component includes
#include "Scene/Components/Components.hpp"
#include "Component/ComponentHandle.hpp"

namespace Exodia {

    struct TransformComponent;
    struct RigidBody2DComponent;

    class MovingSystem : public EntitySystem {

        //////////////////////////////
        // Constructor & Destructor //
        //////////////////////////////
      public:
        MovingSystem(float gravity = 9.81f);
        ~MovingSystem() override = default;

        /////////////
        // Methods //
        /////////////
      public:
        virtual void Update(World *world, Timestep ts) override;

      private:
        void ApplyVelocity(ComponentHandle<RigidBody2DComponent> rigidBody,
                           ComponentHandle<TransformComponent> transform, Timestep ts);

        ////////////////
        // Attributes //
        ////////////////
      private:
        float _Gravity;
    };
}; // namespace Exodia

#endif /* !MOVINGSYSTEM_HPP_ */
