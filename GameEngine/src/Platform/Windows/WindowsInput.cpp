/*
** EPITECH PROJECT, 2023
** ExodiaGameEngine
** File description:
** WindowsInput
*/

// Platform includes
#include "WindowsWindow.hpp"

// Exodia Core
#include "Core/Application/Application.hpp"
#include "Core/Key/Input.hpp"

// External includes
#include <GLFW/glfw3.h>

namespace Exodia {

    ///////////////////////
    // Getters & Setters //
    ///////////////////////

    bool Input::IsKeyPressed(int keycode)
    {
        GLFWwindow *window = static_cast<GLFWwindow *>(Application::Get().GetWindow().GetNativeWindow());

        int state = glfwGetKey(window, keycode);

        return state == GLFW_PRESS;
    }

    bool Input::IsMouseButtonPressed(int button)
    {
        GLFWwindow *window = static_cast<GLFWwindow *>(Application::Get().GetWindow().GetNativeWindow());

        int state = glfwGetMouseButton(window, button);

        return state == GLFW_PRESS;
    }

    glm::vec2 Input::GetMousePosition()
    {
        GLFWwindow *window = static_cast<GLFWwindow *>(Application::Get().GetWindow().GetNativeWindow());
        double xpos;
        double ypos;

        glfwGetCursorPos(window, &xpos, &ypos);

        return {
            (float)xpos,
            (float)ypos
        };
    }

    float Input::GetMouseX()
    {
        return GetMousePosition().x;
    }

    float Input::GetMouseY()
    {
        return GetMousePosition().y;
    }
};
