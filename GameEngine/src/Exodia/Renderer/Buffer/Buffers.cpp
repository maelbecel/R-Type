/*
** EPITECH PROJECT, 2023
** ExodiaGameEngine
** File description:
** Buffers
*/

// Exodia Renderer
#include "Buffers.hpp"
#include "Renderer/Renderer/RendererAPI.hpp"
#include "Renderer/Renderer/Renderer.hpp"

// Entry point
#include "OpenGL/OpenGLBuffer.hpp"

namespace Exodia {

    //////////////////////////////////////////
    ////////////// BufferLayout //////////////
    //////////////////////////////////////////

    //////////////////////////////
    // Constructor & Destructor //
    //////////////////////////////

    BufferLayout::BufferLayout(const std::initializer_list<BufferElement> &elements) : _Elements(elements) {
        CalculateOffsetsAndStride();
    }

    /////////////
    // Methods //
    /////////////

    std::vector<BufferElement>::iterator BufferLayout::begin() { return _Elements.begin(); }

    std::vector<BufferElement>::iterator BufferLayout::end() { return _Elements.end(); }

    std::vector<BufferElement>::const_iterator BufferLayout::begin() const { return _Elements.begin(); }

    std::vector<BufferElement>::const_iterator BufferLayout::end() const { return _Elements.end(); }

    void BufferLayout::CalculateOffsetsAndStride() {
        uint32_t offset = 0;

        _Stride = 0;

        // Calculate offsets
        for (auto &element : _Elements) {
            element.Offset = offset;
            offset += element.Size;
            _Stride += element.Size;
        }
    }

    /////////////////////////////////////////////////////
    ////////////// VertexBuffer || Factory //////////////
    /////////////////////////////////////////////////////

    Ref<VertexBuffer> VertexBuffer::Create(uint32_t size) {
        RendererAPI::API api = Renderer::GetAPI();

        switch (api) {
        case RendererAPI::API::None:
            EXODIA_CORE_ASSERT(false, "RendererAPI::API::None is currently not supported !");
            return nullptr;
        case RendererAPI::API::OpenGL:
            return CreateRef<OpenGLVertexBuffer>(size);
        }

        EXODIA_CORE_ASSERT(false, "Unknown RendererAPI !");
        return nullptr;
    }

    Ref<VertexBuffer> VertexBuffer::Create(float *vertices, uint32_t size) {
        RendererAPI::API api = Renderer::GetAPI();

        switch (api) {
        case RendererAPI::API::None:
            EXODIA_CORE_ASSERT(false, "RendererAPI::API::None is currently not supported !");
            return nullptr;
        case RendererAPI::API::OpenGL:
            return CreateRef<OpenGLVertexBuffer>(vertices, size);
        }

        EXODIA_CORE_ASSERT(false, "Unknown RendererAPI !");
        return nullptr;
    }

    /////////////////////////////////////////////////////
    ////////////// IndexBuffer || Factory ///////////////
    /////////////////////////////////////////////////////

    Ref<IndexBuffer> IndexBuffer::Create(uint32_t *indices, uint32_t count) {
        RendererAPI::API api = Renderer::GetAPI();

        switch (api) {
        case RendererAPI::API::None:
            EXODIA_CORE_ASSERT(false, "RendererAPI::API::None is currently not supported !");
            return nullptr;
        case RendererAPI::API::OpenGL:
            return CreateRef<OpenGLIndexBuffer>(indices, count);
        }

        EXODIA_CORE_ASSERT(false, "Unknown RendererAPI !");
        return nullptr;
    }
}; // namespace Exodia
