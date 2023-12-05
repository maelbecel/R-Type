/*
** EPITECH PROJECT, 2023
** $
** File description:
** CollisionStop
*/

#ifndef COLLISIONSTOP_HPP_
    #define COLLISIONSTOP_HPP_

    #include "Exodia.hpp"

namespace Exodia {

    class CollisionStop : public EventSubscriber<Events::OnCollisionEntered> {

        //////////////////////////////
        // Constructor & Destructor //
        //////////////////////////////
        public:
            CollisionStop() = default;
            ~CollisionStop() = default;

        /////////////
        // Methods //
        /////////////
        public:
        
            virtual void Receive(UNUSED World *world, const Events::OnCollisionEntered &event) override
            {
                auto &bodyA = event.EntityA->GetComponent<RigidBody2DComponent>().Get();
                auto &bodyB = event.EntityB->GetComponent<RigidBody2DComponent>().Get();

                if (bodyA.Type == RigidBody2DComponent::BodyType::Dynamic && bodyB.Type == RigidBody2DComponent::BodyType::Static)
                    bodyA.Velocity = glm::vec2{ 0.0f, 0.0f };
                else if (bodyA.Type == RigidBody2DComponent::BodyType::Static && bodyB.Type == RigidBody2DComponent::BodyType::Dynamic)
                    bodyB.Velocity = glm::vec2{ 0.0f, 0.0f };

                bodyA.GravityScale = 0.0f;
                bodyB.GravityScale = 0.0f;
            }
    };
};

#endif /* !COLLISIONSTOP_HPP_ */
