/*
** EPITECH PROJECT, 2023
** ExodiaGameEngine
** File description:
** GraphicsContext
*/

#ifndef GRAPHICSCONTEXT_HPP_
    #define GRAPHICSCONTEXT_HPP_

    // Exodia Tools
    #include "Utils/Memory.hpp"

namespace Exodia {

    /**
     * @brief This class represents an Interface of a Graphics Context for rendering.
     * 
     */
    class GraphicsContext {

        /////////////
        // Factory //
        /////////////
        public:

            /**
             * @brief Create a graphics context instance.
             * Static function to create a graphics context instance based on the current renderer API.
             *
             * @param window (Type: void *)                 A pointer to the window associated with the context.
             * @return       (Type: Scope<GraphicsContext>) A smart pointer to the created graphics context.
             */
            static Scope<GraphicsContext> Create(void *window);

        //////////////////////////////
        // Constructor & Destructor //
        //////////////////////////////
        public:

            virtual ~GraphicsContext() = default;

        /////////////
        // Methods //
        /////////////
        public:

            /**
             * @brief Initialize the graphics context.
             * Call this method to initialize the graphics context.
             */
            virtual void Init() = 0;

            /**
             * @brief Swap the front and back buffers.
             * Call this method to swap the front and back buffers, displaying the rendered content.
             * (For OpenGL, this is equivalent to glfwSwapBuffers.)
             */
            virtual void SwapBuffers() = 0;
    };
};

#endif /* !GRAPHICSCONTEXT_HPP_ */
