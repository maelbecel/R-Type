/*
** EPITECH PROJECT, 2023
** ExodiaGameEngine
** File description:
** OpenGLBuffer
*/

// OpenGL
#include "OpenGLBuffer.hpp"
#include <glad/glad.h>

// Exodia Debug
#include "Debug/Profiling.hpp"

namespace Exodia {

    //////////////////////////////////////////
    ////////////// VertexBuffer //////////////
    //////////////////////////////////////////

    //////////////////////////////
    // Constructor & Destructor //
    //////////////////////////////

    OpenGLVertexBuffer::OpenGLVertexBuffer(uint32_t size)
    {
        EXODIA_PROFILE_FUNCTION(); // Performance instrumentation profiling for the function

        glCreateBuffers(1, &_RendererID);                              // Create the buffer
        glBindBuffer(GL_ARRAY_BUFFER, _RendererID);                    // Bind the buffer
        glBufferData(GL_ARRAY_BUFFER, size, nullptr, GL_DYNAMIC_DRAW); // Allocate the buffer
    }

    OpenGLVertexBuffer::OpenGLVertexBuffer(float *vertices, uint32_t size)
    {
        EXODIA_PROFILE_FUNCTION(); // Performance instrumentation profiling for the function

        glCreateBuffers(1, &_RendererID);                              // Create the buffer
        glBindBuffer(GL_ARRAY_BUFFER, _RendererID);                    // Bind the buffer
        glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW); // Allocate the buffer
    }

    OpenGLVertexBuffer::~OpenGLVertexBuffer()
    {
        EXODIA_PROFILE_FUNCTION(); // Performance instrumentation profiling for the function

        glDeleteBuffers(1, &_RendererID); // Delete the buffer
    }

    /////////////
    // Methods //
    /////////////

    void OpenGLVertexBuffer::Bind() const
    {
        EXODIA_PROFILE_FUNCTION(); // Performance instrumentation profiling for the function

        glBindBuffer(GL_ARRAY_BUFFER, _RendererID); // Bind the buffer
    }

    void OpenGLVertexBuffer::Unbind() const
    {
        EXODIA_PROFILE_FUNCTION(); // Performance instrumentation profiling for the function

        glBindBuffer(GL_ARRAY_BUFFER, 0); // Unbind the buffer
    }

    ///////////////////////
    // Setters & Getters //
    ///////////////////////

    void OpenGLVertexBuffer::SetLayout(const BufferLayout &layout)
    {
        _Layout = layout;
    }

    const BufferLayout &OpenGLVertexBuffer::GetLayout()
    {
        return _Layout;
    }

    void OpenGLVertexBuffer::SetData(const void *data, uint32_t size)
    {
        glBindBuffer(GL_ARRAY_BUFFER, _RendererID);      // Bind the buffer
        glBufferSubData(GL_ARRAY_BUFFER, 0, size, data); // Set the data
    }

    //////////////////////////////////////////
    ////////////// IndexBuffer ///////////////
    //////////////////////////////////////////

    //////////////////////////////
    // Constructor & Destructor //
    //////////////////////////////

    OpenGLIndexBuffer::OpenGLIndexBuffer(uint32_t *indices, uint32_t count) : _Count(count)
    {
        EXODIA_PROFILE_FUNCTION(); // Performance instrumentation profiling for the function

        glCreateBuffers(1, &_RendererID);                                                         // Create the buffer
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _RendererID);                                       // Bind the buffer
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(uint32_t), indices, GL_STATIC_DRAW); // Allocate the buffer
    }

    OpenGLIndexBuffer::~OpenGLIndexBuffer()
    {
        EXODIA_PROFILE_FUNCTION(); // Performance instrumentation profiling for the function

        glDeleteBuffers(1, &_RendererID); // Delete the buffer
    }

    /////////////
    // Methods //
    /////////////

    void OpenGLIndexBuffer::Bind() const
    {
        EXODIA_PROFILE_FUNCTION(); // Performance instrumentation profiling for the function

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _RendererID); // Bind the buffer
    }

    void OpenGLIndexBuffer::Unbind() const
    {
        EXODIA_PROFILE_FUNCTION(); // Performance instrumentation profiling for the function

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0); // Unbind the buffer
    }

    /////////////
    // Getters //
    /////////////

    uint32_t OpenGLIndexBuffer::GetCount() const
    {
        return _Count;
    }
};
