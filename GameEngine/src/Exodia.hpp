/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** Exodia
*/

#ifndef EXODIA_HPP_
    #define EXODIA_HPP_

    /////////////////////////////////////////
    // Main include file for Exodia        //
    // Include this file to use the engine //
    // And create your own application     //
    /////////////////////////////////////////

    // -- Core -----------------------------------------------------------------

    #include "Exodia/Core/Core.hpp"

    // -- Entity Component System ----------------------------------------------

    #include "Exodia/ECS/ECS.hpp"

    // -- Exodia Events --------------------------------------------------------

    #include "Exodia/Events/ApplicationEvent.hpp"
    #include "Exodia/Events/MouseEvent.hpp"
    #include "Exodia/Events/KeyEvent.hpp"
    #include "Exodia/Events/Event.hpp"

    // -- Exodia ImGui ---------------------------------------------------------

    #include "Exodia/ImGui/ImGuiLayer.hpp"

    // -- Exodia Renderer ------------------------------------------------------

    #include "Exodia/Renderer/Render.hpp"

    // -- Exodia Scene ---------------------------------------------------------

    #include "Exodia/Scene/Scene.hpp"

    // -- Exodia Debug ---------------------------------------------------------

    #include "Exodia/Debug/Profiling.hpp"
    #include "Exodia/Debug/Logs.hpp"

    // -- Exodia Utils ---------------------------------------------------------

    #include "Utils/CrossPlatform.hpp"
    #include "Utils/PlatformUtils.hpp"
    #include "Utils/Memory.hpp"
    #include "Utils/Assert.hpp"

#endif /* !EXODIA_HPP_ */
