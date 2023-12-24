/*
** EPITECH PROJECT, 2023
** ExodiaGameEngine
** File description:
** OpenGLContext
*/

#ifndef OPENGLCONTEXT_HPP_
#define OPENGLCONTEXT_HPP_

// Exodia Renderer
#include "Renderer/Context/GraphicsContext.hpp"

struct GLFWwindow;

namespace Exodia {

    /**
     * @brief Implementation of the OpenGL context for rendering.
     *
     * This class represents the OpenGL context used for rendering. It provides methods for initializing
     * the context and swapping the render buffers.
     */
    class OpenGLContext : public GraphicsContext {

        /////////////////////////////
        // Contructor & Destructor //
        /////////////////////////////
      public:
        /**
         * @brief Construct a new OpenGLContext object.
         *
         * @param windowHandle (Type: GLFWwindow *) The window handle associated with the context.
         */
        OpenGLContext(GLFWwindow *windowHandle);

        /**
         * @brief Destroy the OpenGLContext object.
         * The destructor for the OpenGL context.
         */
        virtual ~OpenGLContext() override;

        /////////////
        // Methods //
        /////////////
      public:
        /**
         * @brief Initialize the OpenGL context.
         *
         * This method initializes the OpenGL context by setting it as the current context, loading the
         * OpenGL function pointers using glad, and logging the renderer information.
         */
        virtual void Init() override;

        /**
         * @brief Swap the render buffers.
         *
         * This method swaps the render buffers to display the rendered content. It is equivalent to
         * glfwSwapBuffers.
         */
        virtual void SwapBuffers() override;

        ////////////////
        // Attributes //
        ////////////////
      private:
        GLFWwindow *_WindowHandle; /*!< The window handle associated with the context. */
    };
}; // namespace Exodia

#endif /* !OPENGLCONTEXT_HPP_ */
