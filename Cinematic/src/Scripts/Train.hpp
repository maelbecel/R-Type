/*
** EPITECH PROJECT, 2023
** $
** File description:
** Player
*/

#ifndef TRAIN_HPP_
#define TRAIN_HPP_

// Exodia includes
#include "Exodia.hpp"

using namespace Exodia;

namespace Cinematic {

    class Train : public ScriptableEntity {

        /////////////
        // Methods //
        /////////////
      public:
        void OnCreate() {
            HandleEntity->AddComponent<SpriteRendererComponent>();
            HandleEntity->AddComponent<CircleCollider2DComponent>();
            auto &transform = HandleEntity->AddComponent<TransformComponent>().Get();
            auto &circle = HandleEntity->AddComponent<CircleRendererComponent>().Get();

            circle.Color = {1, 0, 0, 1};

            transform.Scale = {0.5f, 0.5f, 0.5f};


            _Pos = {0, 0};
        }

        void OnUpdate(UNUSED(Timestep ts)) {
            EXODIA_INFO("Train OnUpdate");
            auto &transform = HandleEntity->GetComponent<TransformComponent>().Get();

            transform.Translation.x = _Pos.x;
            transform.Translation.y = _Pos.y;
        }

        private:
            glm::vec2 _Pos;

    };
};

#endif /* !Train_HPP_ */
