/*
** EPITECH PROJECT, 2023
** $
** File description:
** Player
*/

#ifndef FOLLOWINGCAMERA_HPP_
#define FOLLOWINGCAMERA_HPP_

// Exodia includes
#include "Exodia.hpp"

using namespace Exodia;

namespace Cinematic {

    class FollowingCamera : public ScriptableEntity {

        /////////////
        // Methods //
        /////////////
      public:
        void OnCreate() {
            EXODIA_INFO("FollowingCamera OnCreate");
            HandleEntity.AddComponent<BoxCollider2DComponent>();
            auto &transform = HandleEntity.GetComponent<TransformComponent>();

            transform.Scale = {0.5f, 0.5f, 0.5f};

            _Pos = {0, 0};
        }

        void OnUpdate(UNUSED(Timestep ts)) {
            auto &transform = HandleEntity.GetComponent<TransformComponent>();
            clock += ts;

            if (clock > 0.01f) {
                _Pos.x += 0.005f;
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

#endif /* !FOLLOWINGCAMERA_HPP_ */
