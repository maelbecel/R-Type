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

        public:
            void RegisterComponent(std::string name, std::function<IComponentContainer *(Buffer)> factory);

        ////////////////
        // Attributes //
        ////////////////
        public:
            inline static SceneType _currentScene;
            inline static std::map<SceneType, std::shared_ptr<Exodia::Scene>> _World;

        private:
            // WARNING: This is a temporary solution
            Exodia::World *_worldNetwork = Exodia::World::CreateWorld();

            std::unordered_map<std::string, std::function<IComponentContainer *(Buffer)>> _ComponentFactory;
            Exodia::Network::IOContextManager ioContextManager;

            Ref<Framebuffer>             _Framebuffer;

            Entity _LastEntityHovered;

            std::unique_ptr<Exodia::Network::Network> network = nullptr;
            Exodia::OrthographicCameraController _CameraController;
    };
};

#endif /* !RTYPELAYER_HPP_ */
