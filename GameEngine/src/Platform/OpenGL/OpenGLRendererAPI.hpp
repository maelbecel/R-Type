/*
** EPITECH PROJECT, 2023
** ExodiaGameEngine
** File description:
** OpenGLRendererAPI
*/

#ifndef OPENGLRENDERERAPI_HPP_
#define OPENGLRENDERERAPI_HPP_

// Exodia Renderer
#include "Renderer/Renderer/RendererAPI.hpp"

namespace Exodia
{

    /**
     * @brief OpenGL implementation of the RendererAPI interface.
     *
     * This class provides methods for initializing the renderer, clearing the render buffers, drawing
     * indexed vertex arrays, setting the clear color, and setting the viewport using OpenGL API calls.
     */
    class OpenGLRendererAPI : public RendererAPI
    {

        /////////////
        // Methods //
        /////////////
      public:
        /**
         * @brief Initialize the OpenGL renderer.
         *
         * This function initializes the OpenGL renderer by enabling blending and depth testing.
         */
        virtual void Init() override;

        /**
         * @brief Clear the render buffers.
         *
         * This function clears the color and depth buffers of the render target.
         */
        virtual void Clear() override;

        /**
         * @brief Draw a vertex array with indexed rendering.
         *
         * @param vertexArray (Type: const Ref<VertexArray>&) The vertex array to draw.
         * @param indexCount  (Type: uint32_t)                The number of indices to draw. If set to 0, the count from
         * the vertex array's index buffer is used.
         */
        virtual void DrawIndexed( const Ref<VertexArray> &vertexArray, uint32_t indexCount = 0 ) override;

        virtual void DrawLines( const Ref<VertexArray> &vertexArray, uint32_t indexCount ) override;

        virtual void SetLineWidth( float width ) override;

        ///////////////////////
        // Getters & Setters //
        ///////////////////////
      public:
        /**
         * @brief Set the clear color for the renderer.
         *
         * @param color (Type: const glm::vec4&) The color to set as the clear color.
         */
        virtual void SetClearColor( const glm::vec4 &color ) override;

        /**
         * @brief Set the viewport for rendering.
         *
         * @param x      (Type: uint32_t) The x-coordinate of the viewport's lower-left corner.
         * @param y      (Type: uint32_t) The y-coordinate of the viewport's lower-left corner.
         * @param width  (Type: uint32_t) The width of the viewport.
         * @param height (Type: uint32_t) The height of the viewport.
         */
        virtual void SetViewport( uint32_t x, uint32_t y, uint32_t width, uint32_t height ) override;
    };
}; // namespace Exodia

#endif /* !OPENGLRENDERERAPI_HPP_ */
