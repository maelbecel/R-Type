/*
** EPITECH PROJECT, 2023
** ExodiaGameEngine
** File description:
** OpenGLUniformBuffer
*/

// OpenGL includes
#include "OpenGLUniformBuffer.hpp"

// External includes
#include <glad/glad.h>

namespace Exodia {

    //////////////////////////////
    // Constructor & Destructor //
    //////////////////////////////

    OpenGLUniformBuffer::OpenGLUniformBuffer(uint32_t size, uint32_t binding) {
        glCreateBuffers(1, &_RendererID);
        glNamedBufferData(_RendererID, size, nullptr, GL_DYNAMIC_DRAW);
        glBindBufferBase(GL_UNIFORM_BUFFER, binding, _RendererID);
    }

    OpenGLUniformBuffer::~OpenGLUniformBuffer() { glDeleteBuffers(1, &_RendererID); }

    ///////////////////////
    // Setters & Getters //
    ///////////////////////

    void OpenGLUniformBuffer::SetData(const void *data, uint32_t size, uint32_t offset) {
        glNamedBufferSubData(_RendererID, offset, size, data);
    }
}; // namespace Exodia
