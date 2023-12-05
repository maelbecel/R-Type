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

            void OnUpdate(Timestep ts) override;
            void OnImGUIRender()       override;
            void OnEvent(Event &event) override;

        ////////////////
        // Attributes //
        ////////////////
        private:
            OrthographicCameraController _CameraController;
            glm::vec4                    _SquareColor;
    };
};

#endif // __DEFAULT_LAYER_HPP__
