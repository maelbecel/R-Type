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
            bool OnKeyReleasedEvent(KeyReleasedEvent &event);
            bool OnKeyPressedEvent(KeyPressedEvent &event);

        public:
            void RegisterComponent(std::string name, std::function<IComponentContainer *(Buffer)> factory);

        ////////////////
        // Attributes //
        ////////////////
        public:
            inline static SceneType _currentScene;
            inline static std::map<SceneType, std::shared_ptr<Exodia::Scene>> _World;

        private:
            std::unordered_map<std::string, std::function<IComponentContainer *(Buffer)>> _ComponentFactory;
            Exodia::World *_worldNetwork = Exodia::World::CreateWorld();
            Exodia::Network::IOContextManager ioContextManager;

            Ref<Framebuffer>             _Framebuffer;

            Entity _LastEntityHovered;
            // Define a local endpoint to listen on
            // asio::ip::udp::endpoint localEndpoint(asio::ip::address::from_string("127.0.0.1"), 8082);
            Exodia::Network::Network network;
            Exodia::OrthographicCameraController _CameraController;
    };
};

#endif /* !RTYPELAYER_HPP_ */
