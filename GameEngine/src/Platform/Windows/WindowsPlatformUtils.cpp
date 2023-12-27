/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** WindowsPlatformUtils
*/

// Exodia Utils includes
#include "Utils/PlatformUtils.hpp"

// GLFW includes
#include <GLFW/glfw3.h>

namespace Exodia {

    ///////////////////////
    // Getters & Setters //
    ///////////////////////

    float Time::GetTime() { return (float)glfwGetTime(); }
}; // namespace Exodia
