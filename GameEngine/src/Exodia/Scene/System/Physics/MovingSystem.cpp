/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** MovingSystem
*/

// Exodia ECS System includes
#include "MovingSystem.hpp"

// Exodia Debug includes
#include "Exodia-Debug.hpp"

namespace Exodia {

    /////////////////
    // Constructor //
    /////////////////

    MovingSystem::MovingSystem(float gravity) : _Gravity(gravity){};

    /////////////
    // Methods //
    /////////////

    void MovingSystem::Update(World *world, Timestep ts) {
        EXODIA_PROFILE_FUNCTION();

        world->LockMutex();
        world->ForEach<RigidBody2DComponent, TransformComponent>([&](Entity *entity,
                                                                     ComponentHandle<RigidBody2DComponent> rigidBody,
                                                                     ComponentHandle<TransformComponent> transform) {
            if (rigidBody.Get().Type == RigidBody2DComponent::BodyType::Static)
                return;
            ApplyVelocity(rigidBody, transform, ts);
        });
        world->UnlockMutex();
    }

    void MovingSystem::ApplyVelocity(ComponentHandle<RigidBody2DComponent> rigidBody,
                                     ComponentHandle<TransformComponent> transform, Timestep ts) {
        auto &rb = rigidBody.Get();
        auto &tc = transform.Get();
        float deltaTime = ts;

        // Calculate acceleration using force equation F = m * a (here, F = m * g, where g is gravity)
        glm::vec2 acceleration = glm::vec2(0.0f, -_Gravity) * rb.GravityScale;

        // Apply acceleration taking into account the object's mass
        glm::vec2 force = rb.Mass * acceleration;

        // Calculate displacement based on velocity, time, and mass
        glm::vec2 displacement = (rb.Velocity + 0.5f * force * deltaTime) * deltaTime;

        // Update the entity's position
        tc.Translation += glm::vec3(displacement, 0.0f);

        // Update the velocity based on the calculated force and time
        rb.Velocity += force * deltaTime;
    }
}; // namespace Exodia
