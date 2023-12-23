/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** Render
*/

#ifndef RENDER_HPP_
#define RENDER_HPP_

/////////////////////////////////////////////////
// Main include file for Exodia Render         //
// Include this file to use Render             //
// It will allow you to render your game       //
/////////////////////////////////////////////////

// -- Renderer -------------------------------------------------------------

#include "Exodia/Renderer/Renderer/RenderCommand.hpp"
#include "Exodia/Renderer/Renderer/Renderer.hpp"
#include "Exodia/Renderer/Renderer/Renderer2D.hpp"
#include "Exodia/Renderer/Renderer/RendererAPI.hpp"

// -- Texture --------------------------------------------------------------

#include "Exodia/Renderer/Texture/SubTexture2D.hpp"
#include "Exodia/Renderer/Texture/Texture.hpp"

// -- Sound ----------------------------------------------------------------

#include "Exodia/Renderer/Sound/Sound.hpp"

// -- Camera ---------------------------------------------------------------

#include "Exodia/Renderer/Camera/Camera.hpp"
#include "Exodia/Renderer/Camera/EditorCamera.hpp"
#include "Exodia/Renderer/Camera/OrthographicCamera.hpp"
#include "Exodia/Renderer/Camera/OrthographicCameraController.hpp"

// -- Buffer ---------------------------------------------------------------

#include "Exodia/Renderer/Buffer/Buffers.hpp"
#include "Exodia/Renderer/Buffer/Framebuffer.hpp"
#include "Exodia/Renderer/Buffer/UniformBuffer.hpp"

// -- Context --------------------------------------------------------------

#include "Exodia/Renderer/Context/GraphicsContext.hpp"

// -- Vertex ---------------------------------------------------------------

#include "Exodia/Renderer/Vertex/VertexArray.hpp"

// -- Shader ---------------------------------------------------------------

#include "Exodia/Renderer/Shader/Shader.hpp"

#endif /* !RENDER_HPP_ */
