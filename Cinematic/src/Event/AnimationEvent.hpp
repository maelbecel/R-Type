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

namespace Cinematic::Events {

    struct AnimationEndingEvent {
        Exodia::Entity *Entity;
    };
}; // namespace Cinematic::Events

#endif /* !ANIMATIONEVENT_HPP_ */