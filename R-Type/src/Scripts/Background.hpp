/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** Background
*/

#ifndef BACKGROUND_HPP_
    #define BACKGROUND_HPP_

    // Exodia includes
    #include "Exodia.hpp"

    // R-Type includes
    #include "Scripts/Star.hpp"

namespace RType {

    class BackgroundScript : public Exodia::ScriptableEntity {

        //////////////////////////////
        // Constructor & Destructor //
        //////////////////////////////
        public:

            BackgroundScript() = default;
            ~BackgroundScript() override = default;

        /////////////
        // Methods //
        /////////////
        public:

            void OnCreate() override
            {
                // -- Generate background, only if we have a renderer ----------
                if (Exodia::Renderer::GetAPI() != Exodia::RendererAPI::API::None)
                    return;
                std::random_device rd;
                std::mt19937 gen(rd());

                std::uniform_real_distribution<float> colorDist(0.9f, 1.0f);
                std::uniform_int_distribution<int>   velocityDist(-8, -1);

                for(int i = 0; i < 60; i++) {
                    Exodia::Entity *star = HandleEntity->GetWorld()->CreateEntity("Star" + std::to_string(i));

                    if (!star)
                        return;
                    star->GetComponent<Exodia::TransformComponent>().Get().Scale = { 0.1f, 0.1f, 0.1f };

                    star->AddComponent<Exodia::ScriptComponent>().Get().Bind("Star");
                    star->AddComponent<Exodia::Clock>();
                    star->AddComponent<Exodia::CircleRendererComponent>(glm::vec4{ 0.9f, 0.9f, colorDist(gen), 0.9f });

                    auto body = star->AddComponent<Exodia::RigidBody2DComponent>();

                    body.Get().Type = Exodia::RigidBody2DComponent::BodyType::Dynamic;
                    body.Get().Mass = 0.0f;
                    body.Get().GravityScale = 0.0f;
                    body.Get().Velocity.x = (float)velocityDist(gen);
                }
            }
    };
};

#endif /* !BACKGROUND_HPP_ */
