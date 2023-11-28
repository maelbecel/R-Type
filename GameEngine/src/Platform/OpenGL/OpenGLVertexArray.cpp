/*
** EPITECH PROJECT, 2023
** ExodiaGameEngine
** File description:
** OpenGLVertexArray
*/

// OpenGL
#include "OpenGLVertexArray.hpp"
#include <glad/glad.h>

// Exodia Utils
#include "Utils/Assert.hpp"

// Exodia Debug
#include "Debug/Profiling.hpp"

namespace Exodia {

    //////////////////////
    // Statics Function //
    //////////////////////

    /**
     * @brief Convert ShaderDataType to the corresponding OpenGL base data type.
     *
     * This static function maps the ShaderDataType enum values to their corresponding OpenGL base data types.
     * It is used for translating Exodia's shader data types to OpenGL data types when working with shader attributes and buffers.
     *
     * @param type (Type: ShaderDataType) The ShaderDataType to be converted.
     * @return     (Type: GLenum)         The corresponding OpenGL base data type.
     *
     * @note If the provided ShaderDataType is not recognized, an assertion error will be raised.
     */
    static GLenum ShaderDataTypeToOpenGLBaseType(ShaderDataType type)
    {
        switch (type) {
            case ShaderDataType::Float:
                return GL_FLOAT;
            case ShaderDataType::Float2:
                return GL_FLOAT;
            case ShaderDataType::Float3:
                return GL_FLOAT;
            case ShaderDataType::Float4:
                return GL_FLOAT;
            case ShaderDataType::Mat3:
                return GL_FLOAT;
            case ShaderDataType::Mat4:
                return GL_FLOAT;
            case ShaderDataType::Int:
                return GL_INT;
            case ShaderDataType::Int2:
                return GL_INT;
            case ShaderDataType::Int3:
                return GL_INT;
            case ShaderDataType::Int4:
                return GL_INT;
            case ShaderDataType::Bool:
                return GL_BOOL;
            default:
                break;
        }

        EXODIA_CORE_ASSERT(false, "Unknown ShaderDataType!");
        return 0;
    }

    //////////////////////////////
    // Constructor & Destructor //
    //////////////////////////////

    OpenGLVertexArray::OpenGLVertexArray() : _VertexBufferIndex(0)
    {
        EXODIA_PROFILE_FUNCTION(); // Performance instrumentation profiling for the function

        glCreateVertexArrays(1, &_RendererID); // Create an OpenGL vertex array object (VAO)
    }

    OpenGLVertexArray::~OpenGLVertexArray()
    {
        EXODIA_PROFILE_FUNCTION(); // Performance instrumentation profiling for the function

        glDeleteVertexArrays(1, &_RendererID); // Delete the OpenGL vertex array object (VAO)
    }

    /////////////
    // Methods //
    /////////////

    void OpenGLVertexArray::Bind() const
    {
        EXODIA_PROFILE_FUNCTION(); // Performance instrumentation profiling for the function

        glBindVertexArray(_RendererID); // Bind the OpenGL vertex array object (VAO)
    }

    void OpenGLVertexArray::Unbind() const
    {
        EXODIA_PROFILE_FUNCTION(); // Performance instrumentation profiling for the function

        glBindVertexArray(0); // Unbind the currently bound OpenGL vertex array object (VAO)
    }

    ///////////////////////
    // Getters & Setters //
    ///////////////////////

    void OpenGLVertexArray::AddVertexBuffer(const Ref<VertexBuffer> &vertexBuffer)
    {
        EXODIA_PROFILE_FUNCTION(); // Performance instrumentation profiling for the function

        // Check if the vertex buffer has a layout
        // if not raise an assertion error
        EXODIA_CORE_ASSERT(vertexBuffer->GetLayout().GetElements().size(), "Vertex Buffer has no layout !");

        // Bind the OpenGL vertex array object (VAO)
        glBindVertexArray(_RendererID);
        vertexBuffer->Bind();

        // Get the vertex buffer layout
        const auto &layout = vertexBuffer->GetLayout();

        for (const auto &element : layout) {
            switch(element.Type) {
                case ShaderDataType::Float:
                case ShaderDataType::Float2:
                case ShaderDataType::Float3:
                case ShaderDataType::Float4: {
                    glEnableVertexAttribArray(_VertexBufferIndex);
                    glVertexAttribPointer(
                        _VertexBufferIndex,
                        element.GetComponentCount(),
                        ShaderDataTypeToOpenGLBaseType(element.Type),
                        element.Normalized ? GL_TRUE : GL_FALSE,
                        layout.GetStride(),
                        reinterpret_cast<const void *>(static_cast<uintptr_t>(element.Offset))
                    );
                    _VertexBufferIndex++;
                    break;
                }
                case ShaderDataType::Int:
                case ShaderDataType::Int2:
                case ShaderDataType::Int3:
                case ShaderDataType::Int4:
                case ShaderDataType::Bool: {
                    glEnableVertexAttribArray(_VertexBufferIndex);
                    glVertexAttribIPointer(
                        _VertexBufferIndex,
                        element.GetComponentCount(),
                        ShaderDataTypeToOpenGLBaseType(element.Type),
                        layout.GetStride(),
                        reinterpret_cast<const void *>(static_cast<uintptr_t>(element.Offset))
                    );
                    _VertexBufferIndex++;
                    break;
                }
                case ShaderDataType::Mat3:
                case ShaderDataType::Mat4: {
                    uint8_t count = element.GetComponentCount();

                    for (uint8_t i = 0; i < count; i++) {
                        glEnableVertexAttribArray(_VertexBufferIndex);
                        glVertexAttribPointer(
                            _VertexBufferIndex,
                            count,
                            ShaderDataTypeToOpenGLBaseType(element.Type),
                            element.Normalized ? GL_TRUE : GL_FALSE,
                            layout.GetStride(),
                            reinterpret_cast<const void *>(static_cast<uintptr_t>(element.Offset + sizeof(float) * count * i))
                        );
                        glVertexAttribDivisor(_VertexBufferIndex, 1);
                        _VertexBufferIndex++;
                    }
                    break;
                }
                default:
                    EXODIA_CORE_ASSERT(false, "Unknown ShaderDataType !");
                    break;
            }
        }

        // Store the vertex buffer in the OpenGL vertex array object (VAO)
        _VertexBuffers.push_back(vertexBuffer);
    }

    void OpenGLVertexArray::SetIndexBuffer(const Ref<IndexBuffer> &indexBuffer)
    {
        EXODIA_PROFILE_FUNCTION(); // Performance instrumentation profiling for the function

        // Bind the OpenGL vertex array object (VAO)
        glBindVertexArray(_RendererID);
        indexBuffer->Bind();

        // Store the index buffer in the OpenGL vertex array object (VAO)
        _IndexBuffers = indexBuffer; 
    }

    const std::vector<Ref<VertexBuffer>> &OpenGLVertexArray::GetVertexBuffers() const
    {
        return _VertexBuffers;
    }

    const Ref<IndexBuffer> &OpenGLVertexArray::GetIndexBuffer() const
    {
        return _IndexBuffers;
    }
};
