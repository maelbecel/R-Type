/*
** EPITECH PROJECT, 2023
** ExodiaGameEngine
** File description:
** OpenGLUniformBuffer
*/

#ifndef OPENGLUNIFORMBUFFER_HPP_
    #define OPENGLUNIFORMBUFFER_HPP_

    // Exodia Renderer includes
    #include "Renderer/Buffer/UniformBuffer.hpp"

namespace Exodia {

    class OpenGLUniformBuffer : public UniformBuffer {

        //////////////////////////////
        // Constructor & Destructor //
        //////////////////////////////
        public:

            OpenGLUniformBuffer(uint32_t size, uint32_t binding);
            ~OpenGLUniformBuffer();

        ///////////////////////
        // Setters & Getters //
        ///////////////////////
        public:

            virtual void SetData(const void *data, uint32_t size, uint32_t offset = 0) override;

        ////////////////
        // Attributes //
        ////////////////
        private:
            uint32_t _RendererID; /*!< The OpenGL uniform buffer ID */
    };
};

#endif /* !OPENGLUNIFORMBUFFER_HPP_ */
