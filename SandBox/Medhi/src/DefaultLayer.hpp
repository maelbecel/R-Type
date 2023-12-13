/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** DefaultLayer
*/

#ifndef __DEFAULT_LAYER_HPP__
    #define __DEFAULT_LAYER_HPP__

    #include "Exodia.hpp"
    #include <unordered_map>

namespace Exodia {

    enum SceneType {
        GAME,
        MENU
    };

    class DefaultLayer : public Layer {
        //////////////////////////////
        // Constructor & Destructor //
        //////////////////////////////
        public:

            DefaultLayer();
            ~DefaultLayer() = default;

        /////////////
        // Methods //
        /////////////
        public:

            void OnAttach() override;
            void OnDetach() override;
            void OnUpdate(Timestep ts) override;
            void OnEvent(Event &event) override;

        public:
            void CreatePlayer();
            void RegisterComponent(std::string name, std::function<IComponentContainer *(Buffer)> factory);

        ////////////////
        // Attributes //
        ////////////////
        public:
            inline static SceneType _currentScene;
            inline static std::map<SceneType, std::shared_ptr<Exodia::Scene>> _World;
        private:
            OrthographicCameraController                        _CameraController;
            std::unordered_map<std::string, std::function<IComponentContainer *(Buffer)>> _ComponentFactory;
    };
};

#endif // __DEFAULT_LAYER_HPP__
