/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** GravitySystem
*/

// Exodia ECS System includes
#include "GravitySystem.hpp"

// Exodia Debug includes
#include "Debug/Profiling.hpp"

namespace Exodia
{

    /////////////////
    // Constructor //
    /////////////////

    GravitySystem::GravitySystem( float gravity ) : _Gravity( gravity ){};

    /////////////
    // Methods //
    /////////////

    void GravitySystem::Update( World *world, Timestep ts )
    {
        EXODIA_PROFILE_FUNCTION();

        world->ForEach<RigidBody2DComponent>( [ & ]( Entity *entity, ComponentHandle<RigidBody2DComponent> rigidBody ) {
            if ( rigidBody.Get().Type == RigidBody2DComponent::BodyType::Static )
                return;
            ApplyGravity( rigidBody, ts );
        } );
    }

    void GravitySystem::ApplyGravity( ComponentHandle<RigidBody2DComponent> rigidBody, Timestep ts )
    {
        auto &body = rigidBody.Get();

        // Calculate gravitational force based on gravity scale and mass
        glm::vec2 gravityForce = glm::vec2( 0.0f, -_Gravity * body.Mass * body.GravityScale );

        // Update velocity with gravity force considering the timestep
        body.Velocity += gravityForce * (float) ts;
    }
}; // namespace Exodia
