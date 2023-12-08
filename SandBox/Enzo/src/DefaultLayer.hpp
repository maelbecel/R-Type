/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** DefaultLayer
*/

#ifndef __DEFAULT_LAYER_HPP__
    #define __DEFAULT_LAYER_HPP__

    #include "Exodia.hpp"

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

        ////////////////
        // Attributes //
        ////////////////
        private:
            OrthographicCameraController _CameraController;
            World                       *_World;
    };
};

#endif // __DEFAULT_LAYER_HPP__
