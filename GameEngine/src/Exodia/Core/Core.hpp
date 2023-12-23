/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** Core
*/

#ifndef CORE_HPP_
#define CORE_HPP_

/////////////////////////////////////////////////////
// Main include file for Exodia Core               //
// Include this file to use the core of the engine //
// And create your own application                 //
/////////////////////////////////////////////////////

// -- Application ----------------------------------------------------------

#include "Exodia/Core/Application/Application.hpp"
#include "Exodia/Core/Application/Window.hpp"

// -- KeyCodes -------------------------------------------------------------

#include "Exodia/Core/Key/Input.hpp"
#include "Exodia/Core/Key/KeyCodes.hpp"
#include "Exodia/Core/Key/MouseButtonCodes.hpp"

// -- Layer ----------------------------------------------------------------
#include "Exodia/Core/Layer/Layer.hpp"
#include "Exodia/Core/Layer/LayerStack.hpp"

// -- Time -----------------------------------------------------------------
#include "Exodia/Core/Time/Timer.hpp"
#include "Exodia/Core/Time/Timestep.hpp"

// -- ID -------------------------------------------------------------------
#include "Exodia/Core/ID/UUID.hpp"

// -- Buffer ---------------------------------------------------------------

#include "Exodia/Core/Buffer/Buffer.hpp"

#endif /* !CORE_HPP_ */
