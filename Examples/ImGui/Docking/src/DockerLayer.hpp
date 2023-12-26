/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** DockerLayer
*/

#ifndef __DOCKER_LAYER_HPP__
#define __DOCKER_LAYER_HPP__

#include "Exodia.hpp"
#include "StatImGui.hpp"
#include "ViewportImGui.hpp"

namespace Exodia {

    class DockerLayer : public Layer {

        //////////////////////////////
        // Constructor & Destructor //
        //////////////////////////////
      public:
        DockerLayer();
        ~DockerLayer() = default;

        /////////////
        // Methods //
        /////////////
      public:
        void OnAttach() override;
        void OnUpdate(Timestep ts) override;
        void OnImGUIRender() override;
        void OnEvent(Event &event) override;

        ////////////////
        // Attributes //
        ////////////////
      private:
        OrthographicCameraController _CameraController;
        glm::vec4 _SquareColor;

        Ref<Framebuffer> _Framebuffer;
        Ref<StatImGui> _Stats;
        Ref<ViewportImGui> _Viewport;
    };
}; // namespace Exodia

#endif // __DOCKER_LAYER_HPP__
