/*
** EPITECH PROJECT, 2023
** $
** File description:
** Player
*/

#ifndef BUTTON_SCRIPT_HPP_
    #define BUTTON_SCRIPT_HPP_
    // Exodia includes
    #include "Exodia.hpp"
    #include "../DefaultLayer.hpp"
    #include <random>

namespace Exodia {

    class ButtonScript : public ScriptableEntity {

        /////////////
        // Methods //
        /////////////
        public:

            void OnCreate() override
            {
                EXODIA_INFO("Button Create : Click should be between X : {0} -> {1}, Y {2} -> {3}", GetComponent<TransformComponent>().Get().Translation.x, GetComponent<TransformComponent>().Get().Translation.x + GetComponent<TransformComponent>().Get().Scale.x, GetComponent<TransformComponent>().Get().Translation.y, GetComponent<TransformComponent>().Get().Translation.y + GetComponent<TransformComponent>().Get().Scale.y);
            }

            void OnUpdate(UNUSED Timestep ts) override
            {
                // Check if the button is clicked
                // If it is, change the scene
                // If it is not, do nothing

                auto transform = GetComponent<TransformComponent>();

                if (Input::IsMouseButtonPressed(Mouse::BUTTON0)) {
                    UNUSED auto pos = Input::GetMousePosition();
                    UNUSED auto &tc = transform.Get();

                    EXODIA_INFO("Clicked at {0}:{1}", pos.x, pos.y);
                    DefaultLayer::_currentScene = SceneType::GAME;
                    DefaultLayer::_World[GAME]->OnRuntimeStart();
                }

            }

        ////////////////
        // Attributes //
        ////////////////
        private:

    };
};

#endif /* !BUTTON_SCRIPT_HPP_ */

