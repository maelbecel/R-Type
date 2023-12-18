/*
** EPITECH PROJECT, 2023
** ExodiaGameEngine
** File description:
** RTypeLayer
*/

#ifndef GAMEENGINE_HPP_
    #define GAMEENGINE_HPP_

    #include "Exodia.hpp"

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

        ////////////////
        // Attributes //
        ////////////////
        private:
        Exodia::World *world = Exodia::World::CreateWorld();
            Exodia::Network::IOContextManager ioContextManager;

        // Define a local endpoint to listen on
        // asio::ip::udp::endpoint localEndpoint(asio::ip::address::from_string("127.0.0.1"), 8082);
        Exodia::Network::Network network;
            Exodia::OrthographicCameraController _CameraController;
            glm::vec4 _SquareColor = { 0.2f, 0.3f, 0.8f, 1.0f };
    };
};

#endif /* !GAMEENGINE_HPP_ */
