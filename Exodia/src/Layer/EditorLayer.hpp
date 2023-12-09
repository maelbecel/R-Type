/*
** EPITECH PROJECT, 2023
** ExodiaGameEngine
** File description:
** EditorLayer
*/

#ifndef GAMEENGINE_HPP_
    #define GAMEENGINE_HPP_

    #include "Exodia.hpp"

namespace Exodia {

    class EditorLayer : public Exodia::Layer {

        //////////////////////////////
        // Constructor & Destructor //
        //////////////////////////////
        public:

            EditorLayer();
            ~EditorLayer() = default;

        /////////////
        // Methods //
        /////////////
        public:

            void OnAttach()            override;
            void OnDetach()            override;
            void OnUpdate(Timestep ts) override;
            void OnImGUIRender()       override;
            void OnEvent(Event &event) override;

        ////////////////
        // Attributes //
        ////////////////
        private:

            Exodia::OrthographicCameraController _CameraController;
            glm::vec4 _SquareColor = { 0.2f, 0.3f, 0.8f, 1.0f };
    };
};

#endif /* !GAMEENGINE_HPP_ */
