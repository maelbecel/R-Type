/*
** EPITECH PROJECT, 2023
** ExodiaGameEngine
** File description:
** Layer
*/

// Exodia Core
#include "Layer.hpp"
#include "Core/Time/Timestep.hpp"

// External include
#include <sstream>

namespace Exodia {

    //////////////////////////////
    // Constructor & Destructor //
    //////////////////////////////

    Layer::Layer(const std::string &name) : _DebugName(name) {};

    /////////////
    // Methods //
    /////////////

    void Layer::OnAttach() {};

    void Layer::OnDetach() {};

    void Layer::OnUpdate(Timestep ts)
    {
        (void)ts;
    }

    void Layer::OnImGUIRender() {};

    void Layer::OnEvent(Event &event)
    {
        (void)event;
    }
};
