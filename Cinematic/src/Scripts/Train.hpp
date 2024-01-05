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
            EXODIA_INFO("Train OnCreate");
            HandleEntity->AddComponent<SpriteRendererComponent>();
            HandleEntity->AddComponent<BoxCollider2DComponent>();
            auto &transform = HandleEntity->AddComponent<TransformComponent>().Get();

            HandleEntity->AddComponent<SpriteRendererComponent>();

            auto sprite = HandleEntity->GetComponent<SpriteRendererComponent>();

            Ref<Texture2D> texture = TextureImporter::LoadTexture2D("Assets/Textures/Shell.png");

            sprite->Texture =
                SubTexture2D::CreateFromCoords(texture->Handle, {0.0f, 2.0f}, {33.0f, 33.0f}, {1.0f, 1.0f});

            transform.Scale = {0.5f, 0.5f, 0.5f};

            _Pos = {0, 0};
        }

        void OnUpdate(UNUSED(Timestep ts)) {
            auto &transform = HandleEntity->GetComponent<TransformComponent>().Get();
            clock += ts;

            if (clock > 0.01f) {
                _Pos.x += 0.01f;
                clock = 0;
                transform.Translation.x = _Pos.x;
                transform.Translation.y = _Pos.y;
            }
        }

      private:
        glm::vec2 _Pos;
        float clock;
    };
}; // namespace Cinematic

#endif /* !Train_HPP_ */
