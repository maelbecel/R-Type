/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** GravitySystem
*/

#ifndef GRAVITYSYSTEM_HPP_
    #define GRAVITYSYSTEM_HPP_

    // Exodia ECS Interface includes
    #include "Interface/EntitySystem.hpp"

    // Exodia ECS Component includes
    #include "Component/Components.hpp"
    #include "Component/ComponentHandle.hpp"

namespace Exodia {

    struct RigidBody2DComponent;

    class GravitySystem : public EntitySystem {

        /////////////////
        // Constructor //
        /////////////////
        public:

            GravitySystem(float gravity = 9.81f);
            ~GravitySystem() override = default;

        /////////////
        // Methods //
        /////////////
        public:

            void Update(World *world, Timestep ts) override;

        private:
            void ApplyGravity(ComponentHandle<RigidBody2DComponent> rigidBody, Timestep ts);

        ///////////////
        // Atributes //
        ///////////////
        private:
            float _Gravity;
    };
};

#endif /* !GRAVITYSYSTEM_HPP_ */
