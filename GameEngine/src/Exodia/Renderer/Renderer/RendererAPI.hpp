/*
** EPITECH PROJECT, 2023
** ExodiaGameEngine
** File description:
** RendererAPI
*/

#ifndef RENDERERAPI_HPP_
    #define RENDERERAPI_HPP_

    // Exodia Renderer
    #include "Renderer/Vertex/VertexArray.hpp"

    // External include
    #include <glm/glm.hpp>

namespace Exodia {

    /**
     * @brief The RendererAPI class defines an abstract interface for interacting with different rendering APIs.
     * It provides methods for initializing, clearing, and drawing graphics using a specific rendering API.
     */
    class RendererAPI {

        //////////////////
        // Enumerations //
        //////////////////
        public:

            /**
             * @brief An enumeration of supported rendering APIs.
             */
            enum class API {
                None,
                OpenGL,
                SFML
                //TODO: Implement other rendering APIs (DirectX, Vulkan, Metal, etc.)
            };

        /////////////
        // Methods //
        /////////////
        public:

            /**
             * @brief Initialize the rendering API. This function sets up the necessary resources and environment for rendering.
             */
            virtual void Init() = 0;

            /**
             * @brief Clear the rendering buffer. This function clears the rendering buffer to the previously set clear color.
             */
            virtual void Clear() = 0;

            /**
             * @brief Draw indexed geometry. This function renders the specified vertex array with indices.
             *
             * @param vertexArray (Type: Ref<VertexArray>) The vertex array containing vertex and index data.
             * @param indexCount  (Type: uint32_t)         The number of indices to render (default is 0 to render all).
             */
            virtual void DrawIndexed(const Ref<VertexArray> &vertexArray, uint32_t indexCount = 0) = 0;

            virtual void DrawLines(const Ref<VertexArray> &vertexArray, uint32_t indexCount) = 0;

            virtual void SetLineWidth(float width) = 0;

        ///////////////////////
        // Getters & Setters //
        ///////////////////////
        public:

            /**
             * @brief Set the clear color for the rendering buffer.
             *
             * @param color (Type: glm::vec4) The color to set as the clear color.
             */
            virtual void SetClearColor(const glm::vec4 &color) = 0;

            /**
             * @brief Set the viewport dimensions.
             *
             * @param x      (Type: uint32_t) The x-coordinate of the viewport's lower-left corner.
             * @param y      (Type: uint32_t) The y-coordinate of the viewport's lower-left corner.
             * @param width  (Type: uint32_t) The width of the viewport.
             * @param height (Type: uint32_t) The height of the viewport.
             */
            virtual void SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height) = 0;

            /**
             * @brief Get the currently active rendering API.
             *
             * @return (Type: API) The currently active rendering API.
             */
            inline static API GetAPI()
            {
                return _API;
            }

            inline static void SetAPI(API api)
            {
                _API = api;
            }

        ////////////////
        // Attributes //
        ////////////////
        private:
            static API _API; /*!< The API of the Renderer */
    };
};

#endif /* !RENDERERAPI_HPP_ */
