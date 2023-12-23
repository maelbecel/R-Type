/*
** EPITECH PROJECT, 2023
** ExodiaGameEngine
** File description:
** RenderCommand
*/

// Exodia Renderer
#include "RenderCommand.hpp"

// Entry Point
#include "OpenGL/OpenGLRendererAPI.hpp"

namespace Exodia
{
    RendererAPI *RenderCommand::_RendererAPI = new OpenGLRendererAPI;
};
