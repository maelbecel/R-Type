/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** AnimationEvent
*/

#ifndef ANIMATIONEVENT_HPP_
#define ANIMATIONEVENT_HPP_

// Exodia includes
#include "Exodia.hpp"

namespace Exodia::Events {

    struct AnimationEndingEvent {
        Exodia::Entity *Entity;
    };
}; // namespace Exodia::Events

#endif /* !ANIMATIONEVENT_HPP_ */