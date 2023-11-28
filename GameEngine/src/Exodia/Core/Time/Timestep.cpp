/*
** EPITECH PROJECT, 2023
** ExodiaGameEngine
** File description:
** Timestep
*/

// Exodia Core
#include "Timestep.hpp"

namespace Exodia {

    ///////////////////////////////
    // Constructor & Desctructor //
    ///////////////////////////////

    Timestep::Timestep(float time) : _Time(time) {};

    ///////////////////////
    // Getters & Setters //
    ///////////////////////

    float Timestep::GetSeconds() const
    {
        return _Time;
    }

    float Timestep::GetMilliseconds() const
    {
        return _Time * 1000.0f;
    }
};
