/*
** EPITECH PROJECT, 2023
** $
** File description:
** Player
*/

#ifndef PLAYER_HPP_
#define PLAYER_HPP_

// Exodia includes
#include "Exodia.hpp"

namespace Exodia {

    class Player : public ScriptableEntity {

        /////////////
        // Methods //
        /////////////
      public:
        void OnCreate() override { _Speed = 5.0f; }

        void OnUpdate(Timestep ts) override {
            auto transform = GetComponent<TransformComponent>();

            if (transform) {
                if (Input::IsKeyPressed(Key::A))
                    transform->Translation.x -= _Speed * ts;
                if (Input::IsKeyPressed(Key::D))
                    transform->Translation.x += _Speed * ts;
                if (Input::IsKeyPressed(Key::W))
                    transform->Translation.y += _Speed * ts;
                if (Input::IsKeyPressed(Key::S))
                    transform->Translation.y -= _Speed * ts;
            }
        }

        void OnCollisionEnter(Entity *entity) override {
            EXODIA_INFO("Collision with {0}", entity->GetComponent<TagComponent>().Get().Tag);

            auto body = GetComponent<RigidBody2DComponent>();

            if (body) {
                auto &bodyC = body.Get();

                if (bodyC.Type == RigidBody2DComponent::BodyType::Dynamic)
                    bodyC.Velocity = glm::vec2{0.0f, 0.0f};
                bodyC.GravityScale = 0.0f;
            }
        }

        ////////////////
        // Attributes //
        ////////////////
      private:
        float _Speed;
    };
}; // namespace Exodia

#endif /* !PLAYER_HPP_ */
