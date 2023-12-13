/*
** EPITECH PROJECT, 2023
** $
** File description:
** Player
*/

#ifndef CAMERA_SCRIPT_HPP_
    #define CAMERA_SCRIPT_HPP_
    // Exodia includes
    #include "Exodia.hpp"
    #include <random>

namespace Exodia {

    class CameraScript : public ScriptableEntity {

        /////////////
        // Methods //
        /////////////
        public:

            void OnCreate() override
            {
                auto cam = GetComponent<CameraComponent>();
                cam.Get().Primary = true;
                cam.Get().FixedAspectRatio = true;
                cam.Get().Camera.SetProjectionType(SceneCamera::ProjectionType::Perspective);
            }

            void OnUpdate(UNUSED Timestep ts) override
            {
                auto velocity = GetComponent<RigidBody2DComponent>();
                auto transform = GetComponent<TransformComponent>();

                if (Input::IsKeyPressed(Key::J)) {
                    EXODIA_INFO("velocity: {0}", velocity.Get().Velocity.x);
                    EXODIA_INFO("transform: {0}", transform.Get().Translation.x);
                }
            }

        ////////////////
        // Attributes //
        ////////////////
        private:
            Camera _camera;
    };
};

#endif /* !CAMERA_SCRIPT_HPP_ */

