/*
** EPITECH PROJECT, 2023
** ExodiaGameEngine
** File description:
** Layer
*/

// Exodia Core
#include "Core/Layer/Layer.hpp"

// Exodia Utils
#include "Utils/Memory.hpp"

namespace Exodia {

    //////////////////////////////
    // Constructor & Destructor //
    //////////////////////////////

    Layer::Layer(const std::string &name) : _DebugName(name) {};

    Layer::~Layer() {};

    /////////////
    // Methods //
    /////////////

    void Layer::OnAttach()
    {
        return;
    }

    void Layer::OnDetach()
    {
        return;
    }

    void Layer::OnUpdate(UNUSED Timestep ts)
    {
        return;
    }

    void Layer::OnImGUIRender()
    {
        return;
    }

    void Layer::OnEvent(UNUSED Event &event)
    {
        return;
    }
};
