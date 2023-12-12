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
        private:
            OrthographicCameraController _CameraController;
            World                       *_World;
            // std::unordered_map<std::string, IComponentContainer *()> _ComponentFactory;
    };
};

#endif // __DEFAULT_LAYER_HPP__
