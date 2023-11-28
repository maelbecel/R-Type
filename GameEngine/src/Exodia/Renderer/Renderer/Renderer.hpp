/*
** EPITECH PROJECT, 2023
** ExodiaGameEngine
** File description:
** Renderer
*/

#ifndef RENDERER_HPP_
    #define RENDERER_HPP_

    // Exodia Renderer
    #include "Renderer/Camera/OrthographicCamera.hpp"
    #include "Renderer/Renderer/RenderCommand.hpp"
    #include "Renderer/Shader/Shader.hpp"

namespace Exodia {

    /**
     * @brief This structure holds scene-related data, primarily the view-projection matrix.
     */
    struct SceneData {
        glm::mat4 ViewProjectionMatrix; /*!< The view-projection matrix of the scene */
    };

    /**
     * @brief The central rendering class that manages rendering operations and scene data.
     * It provides methods for initializing the renderer, submitting renderable objects,
     * and managing scene data.
     */
    class Renderer {

        /////////////
        // Methods //
        /////////////
        public:
            
            /**
             * @brief Initialize the renderer and associated systems.
             * Call this method at the beginning to initialize rendering and setup systems.
             */
            static void Init();

            /**
             * @brief Shutdown the renderer and associated systems.
             * Call this method at the end to clean up and shut down the renderer.
             */
            static void Shutdown();

            /**
             * @brief Begin rendering a scene with a given orthographic camera.
             *
             * @param camera (Type: OrthographicCamera &) The orthographic camera for rendering the scene.
             */
            static void BeginScene(OrthographicCamera &camera);

            /**
             * @brief End rendering a scene.
             * Call this method after rendering the scene to finalize rendering operations.
             */
            static void EndScene();

            /**
             * @brief Submit a renderable object to be rendered.
             * Call this method to submit a renderable object, shader, and transformation for rendering.
             *
             * @param shader      (Type: const Ref<Shader> &)      The shader for rendering.
             * @param vertexArray (Type: const Ref<VertexArray> &) The vertex array containing the geometry.
             * @param transform   (Type: const glm::mat4 &)        The transformation matrix for the object (default = identity matrix).
             */
            static void Submit(const Ref<Shader> &shader, const Ref<VertexArray> &vertexArray, const glm::mat4 &transform = glm::mat4(1.0f));

            /**
             * @brief Handle window resize events.
             * Call this method to adjust the viewport when the window size changes.
             *
             * @param width  (Type: uint32_t) The new width of the window.
             * @param height (Type: uint32_t) The new height of the window.
             */
            static void OnWindowResize(uint32_t width, uint32_t height);

        ///////////////////////
        // Getters & Setters //
        ///////////////////////
        public:

            /**
             * @brief Get the underlying rendering API.
             *
             * @return (Type: RendererAPI::API) The current rendering API.
             */
            inline static RendererAPI::API GetAPI()
            {
                return RendererAPI::GetAPI();
            }

        ////////////////
        // Attributes //
        ////////////////
        private:
            static SceneData *_SceneData; /*!< Data of the scene */
    };
};

#endif /* !RENDERER_HPP_ */
