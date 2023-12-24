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
            void OnImGUIRender()       override;
            void OnEvent(Event &event) override;

        private:
            bool OnKeyReleasedEvent(KeyReleasedEvent &event);
            bool OnKeyPressedEvent(KeyPressedEvent &event);
            bool OnWindowResizeEvent(WindowResizeEvent &event);

        ////////////////
        // Attributes //
        ////////////////
        public:
            inline static std::map<SceneType, Ref<Scene>> Scenes;
            inline static SceneType CurrentScene;

        private:
            // TODO: WARNING: This is a temporary solution
            World *_WorldNetwork;

            Network::IOContextManager _IOContextManager;
            Scope<Network::Network>   _Network;
    };
};

#endif /* !RTYPELAYER_HPP_ */
