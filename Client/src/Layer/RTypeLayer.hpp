/*
** EPITECH PROJECT, 2023
** ExodiaGameEngine
** File description:
** RTypeLayer
*/

#ifndef RTYPELAYER_HPP_
    #define RTYPELAYER_HPP_

    #include "Exodia.hpp"
    #include "R-Type.hpp"

namespace Exodia {

    class RTypeLayer : public Exodia::Layer {

        //////////////////////////////
        // Constructor & Destructor //
        //////////////////////////////
        public:

            RTypeLayer();
            ~RTypeLayer() = default;

        /////////////
        // Methods //
        /////////////
        public:

            void OnAttach()            override;
            void OnDetach()            override;
            void OnUpdate(Timestep ts) override;
            void OnEvent(Event &event) override;

        private:
            bool OnKeyReleasedEvent(KeyReleasedEvent &event);
            bool OnKeyPressedEvent(KeyPressedEvent &event);
            bool OnWindowResizeEvent(WindowResizeEvent &event);

        ////////////////
        // Attributes //
        ////////////////
        private:
            std::map<RType::SceneType, std::pair<RType::SceneState, Ref<Exodia::Scene>>> _Scenes;
            RType::SceneType _CurrentScene;

            EditorCamera _WaitingCamera;
    };
};

#endif /* !RTYPELAYER_HPP_ */
