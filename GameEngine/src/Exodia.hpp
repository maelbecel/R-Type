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

#include "Exodia-ECS.hpp"

// -- Exodia Events --------------------------------------------------------

#include "Exodia/Events/ApplicationEvent.hpp"
#include "Exodia/Events/MouseEvent.hpp"
#include "Exodia/Events/KeyEvent.hpp"
#include "Exodia/Events/Event.hpp"

// -- Exodia Asset Manager -------------------------------------------------

#include "Exodia/Asset/Asset.hpp"

// -- Exodia ImGui ---------------------------------------------------------

#include "Exodia/ImGui/ImGuiLayer.hpp"
#include "Exodia/ImGui/ImGuiToolsUI.hpp"

// -- Exodia Renderer ------------------------------------------------------

#include "Exodia/Renderer/Render.hpp"

// -- Exodia Scene ---------------------------------------------------------

#include "Exodia/Scene/SceneHeaders.hpp"

// -- Exodia Project -------------------------------------------------------

#include "Exodia/Project/Project.hpp"
#include "Exodia/Project/ProjectSerializer.hpp"

// -- Exodia Script --------------------------------------------------------

#include "Exodia/Script/Script.hpp"

// -- Exodia Debug ---------------------------------------------------------

#include "Exodia-Debug.hpp"

// -- Exodia Math ----------------------------------------------------------

#include "Exodia/Math/Math.hpp"

// -- Exodia Network -------------------------------------------------------

#include "Network/Network.hpp"

// -- Exodia Utils ---------------------------------------------------------

#include "Exodia-Utils.hpp"
#include "Utils/PlatformUtils.hpp"

#endif /* !EXODIA_HPP_ */
