/*
** EPITECH PROJECT, 2023
** ExodiaGameEngine
** File description:
** Camera
*/

#include "Camera.hpp"

namespace Exodia {

    //////////////////////////////
    // Constructor & Destructor //
    //////////////////////////////

    Camera::Camera(const glm::mat4 &projection) : _Projection(projection){};

    ///////////////////////
    // Getters & Setters //
    ///////////////////////

    const glm::mat4 &Camera::GetProjection() const { return _Projection; }
}; // namespace Exodia
