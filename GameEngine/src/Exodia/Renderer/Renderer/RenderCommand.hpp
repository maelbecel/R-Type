/*
** EPITECH PROJECT, 2023
** ExodiaGameEngine
** File description:
** RenderCommand
*/

#ifndef RENDERCOMMAND_HPP_
#define RENDERCOMMAND_HPP_

// Exodia Renderer
#include "Renderer/Renderer/RendererAPI.hpp"

namespace Exodia
{

    /**
     * @brief This class provides static methods to issue rendering commands to the underlying rendering API.
     * It acts as an interface to interact with the renderer and encapsulates rendering operations such as :
     *      - initialization
     *      - clearing the screen
     *      - drawing indexed vertices.
     */
    class RenderCommand
    {

        /////////////
        // Methods //
        /////////////
      public:
        /**
         * @brief Initialize the renderer
         * Call this method to initialize the rendering API
         */
        static void Init() { _RendererAPI->Init(); }

        /**
         * @brief Clear the screen
         * Call this method to clear the screen
         */
        static void Clear() { _RendererAPI->Clear(); }

        /**
         * @brief Draw indexed vertices
         * Call this method to draw indexed vertices using a vertex array
         *
         * @param vertexArray (Type: const Ref<VertexArray> &) The vertex array containing the vertices
         * @param indexCount  (Type: uint32_t)                 The number of indices to draw
         */
        static void DrawIndexed( const Ref<VertexArray> &vertexArray, uint32_t indexCount = 0 )
        {
            _RendererAPI->DrawIndexed( vertexArray, indexCount );
        }

        static void DrawLines( const Ref<VertexArray> &vertexArray, uint32_t indexCount )
        {
            _RendererAPI->DrawLines( vertexArray, indexCount );
        }

        static void SetLineWidth( float width ) { _RendererAPI->SetLineWidth( width ); }

        ///////////////////////
        // Setters & Getters //
        ///////////////////////
      public:
        /**
         * @brief Set the clear color of the screen
         * Call this method to set the color used for clearing the screen
         *
         * @param color (Type: const glm::vec4 &) The clear color (RGBA)
         */
        inline static void SetClearColor( const glm::vec4 &color ) { _RendererAPI->SetClearColor( color ); }

        /**
         * @brief Set the viewport
         * Call this method to set the viewport's position and size
         *
         * @param x      (Type: uint32_t) The x-coordinate of the viewport's lower-left corner
         * @param y      (Type: uint32_t) The y-coordinate of the viewport's lower-left corner
         * @param width  (Type: uint32_t) The width of the viewport
         * @param height (Type: uint32_t) The height of the viewport
         */
        inline static void SetViewport( uint32_t x, uint32_t y, uint32_t width, uint32_t height )
        {
            _RendererAPI->SetViewport( x, y, width, height );
        }

        ////////////////
        // Attributes //
        ////////////////
      private:
        static RendererAPI *_RendererAPI; /*!< The RendererAPI of the RenderCommand object */
    };
}; // namespace Exodia

#endif /* !RENDERCOMMAND_HPP_ */
