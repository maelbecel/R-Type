/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** IDComponent
*/

#ifndef IDCOMPONENT_HPP_
#define IDCOMPONENT_HPP_

// Exodia UUID includes
#include "Exodia-Utils.hpp"

// Exodia ECS includes
#include "Scene/Components/Component.hpp"

namespace Exodia {

    struct IDComponent : public Component {
        UUID ID;

        IDComponent(const IDComponent &) = default;
        IDComponent(const UUID &uuid = UUID()) : ID(uuid){};
    };
}; // namespace Exodia

#endif /* !IDCOMPONENT_HPP_ */
