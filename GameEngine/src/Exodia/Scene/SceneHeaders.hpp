/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** SceneHeaders
*/

#ifndef SCENEHEADERS_HPP_
#define SCENEHEADERS_HPP_

///////////////////////////////////////////////////////////////////////
// Main include file for Exodia Scene                                //
// Include this file to use different features for your game's scene //
// It will allow you manipulate the scene.                           //
///////////////////////////////////////////////////////////////////////

// -- Camera ---------------------------------------------------------------

#include "Exodia/Scene/Camera/SceneCamera.hpp"

// -- Components -----------------------------------------------------------

#include "Exodia/Scene/Components/Component.hpp"
#include "Exodia/Scene/Components/Components.hpp"

// -- Systems --------------------------------------------------------------

#include "Exodia/Scene/System/Collision/CollisionSystem.hpp"
#include "Exodia/Scene/System/Script/ScriptSystem.hpp"
#include "Exodia/Scene/System/Physics/GravitySystem.hpp"
#include "Exodia/Scene/System/Physics/MovingSystem.hpp"

// -- Event Subscribers ----------------------------------------------------

#include "Exodia/Scene/EventSubscriber/EventHover.hpp"

// -- Prefabs --------------------------------------------------------------

#include "Exodia/Scene/Prefabs/Prefabs.hpp"

// -- Scene ----------------------------------------------------------------

#include "Exodia/Scene/Scene/Scene.hpp"

// -- GameObject -----------------------------------------------------------

#include "Exodia/Scene/GameObject/GameObject.hpp"

// -- Serializer -----------------------------------------------------------

#include "Exodia/Scene/Serializer/SceneSerializer.hpp"

#endif /* !SCENEHEADERS_HPP_ */
