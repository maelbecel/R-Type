/*
** EPITECH PROJECT, 2023
** ExodiaGameEngine
** File description:
** Buffers
*/

#ifndef BUFFERS_HPP_
#define BUFFERS_HPP_

// Exodia Utils
#include "Utils/Assert.hpp"

// External includes
#include <cstdint>
#include <vector>

namespace Exodia {

    /**
     * @brief This enumeration represents different types of shader data.
     */
    enum class ShaderDataType {
        None,
        // Float : Floating-point data types with 1 to 4 components.
        Float,
        Float2,
        Float3,
        Float4,
        // Matrices : Matrix data types with 3x3 and 4x4 components respectively.
        Mat3,
        Mat4,
        // Integers : Integer data types with 1 to 4 components.
        Int,
        Int2,
        Int3,
        Int4,
        // Bool : Boolean data type.
        Bool
    };

    /**
     * @brief Get the size in bytes for a specific shader data type.
     *
     * @param type (Type: ShaderDataType) The shader data type.
     * @return     (Type: uint32_t)       The size in bytes.
     *
     * @note If the shader data type is unknown, the function will assert.
     */
    static uint32_t ShaderDataTypeSize(ShaderDataType type) {
        switch (type) {
        case ShaderDataType::Float:
            return 4;
        case ShaderDataType::Float2:
            return 4 * 2;
        case ShaderDataType::Float3:
            return 4 * 3;
        case ShaderDataType::Float4:
            return 4 * 4;
        case ShaderDataType::Mat3:
            return 4 * 3 * 3;
        case ShaderDataType::Mat4:
            return 4 * 4 * 4;
        case ShaderDataType::Int:
            return 4;
        case ShaderDataType::Int2:
            return 4 * 2;
        case ShaderDataType::Int3:
            return 4 * 3;
        case ShaderDataType::Int4:
            return 4 * 4;
        case ShaderDataType::Bool:
            return 1;
        default:
            break;
        }

        EXODIA_CORE_ASSERT(false, "Unknown ShaderDataType !");
        return 0;
    }

    /**
     * @brief This structure represents a buffer element with the shader data type, name, size, offset and normalized
     * value. These elements are used in BufferLayout to define the structure of vertex data within the buffer.
     */
    struct BufferElement {
        std::string Name;    /*!< The name of the buffer element */
        ShaderDataType Type; /*!< The type of the buffer element */
        uint32_t Size;       /*!< The size of the buffer element */
        uint32_t Offset;     /*!< The offset of the buffer element */
        bool Normalized;     /*!< The normalized value of the buffer element */

        BufferElement() : Name(""), Type(ShaderDataType::None), Size(0), Offset(0), Normalized(false){};
        BufferElement(ShaderDataType type, const std::string &name, bool normalize = false)
            : Name(name), Type(type), Size(ShaderDataTypeSize(type)), Offset(0), Normalized(normalize){};

        /**
         * @brief Get the number of components in the buffer element.
         *
         * @return (Type: uint32_t) The number of components.
         */
        uint32_t GetComponentCount() const {
            switch (Type) {
            case ShaderDataType::Float:
                return 1;
            case ShaderDataType::Float2:
                return 2;
            case ShaderDataType::Float3:
                return 3;
            case ShaderDataType::Float4:
                return 4;
            case ShaderDataType::Mat3:
                return 3 * 3;
            case ShaderDataType::Mat4:
                return 4 * 4;
            case ShaderDataType::Int:
                return 1;
            case ShaderDataType::Int2:
                return 2;
            case ShaderDataType::Int3:
                return 3;
            case ShaderDataType::Int4:
                return 4;
            case ShaderDataType::Bool:
                return 1;
            default:
                break;
            }

            EXODIA_CORE_ASSERT(false, "Unknown ShaderDataType !");
            return 0;
        }
    };

    /**
     * @brief Represents the layout of buffer elements used in vertex data.
     */
    class BufferLayout {

        //////////////////////////////
        // Constructor & Destructor //
        //////////////////////////////
      public:
        BufferLayout() = default;

        /**
         * @brief Construct a new BufferLayout object using the provided list of buffer elements.
         *
         * @param elements (Type: const std::initializer_list<BufferElement> &) List of buffer elements.
         */
        BufferLayout(const std::initializer_list<BufferElement> &elements);

        ~BufferLayout() = default;

        /////////////
        // Methods //
        /////////////
      public:
        /**
         * @brief Get an iterator pointing to the beginning of the buffer elements.
         */
        std::vector<BufferElement>::iterator begin();

        /**
         * @brief Get an iterator pointing to the end of the buffer elements.
         */
        std::vector<BufferElement>::iterator end();

        /**
         * @brief Get a constant iterator pointing to the beginning of the buffer elements.
         */
        std::vector<BufferElement>::const_iterator begin() const;

        /**
         * @brief Get a constant iterator pointing to the end of the buffer elements.
         */
        std::vector<BufferElement>::const_iterator end() const;

      private:
        /**
         * @brief Calculate the offsets and stride for the buffer layout.
         */
        void CalculateOffsetsAndStride();

        ///////////////////////
        // Getters & Setters //
        ///////////////////////
      public:
        /**
         * @brief Get the stride of the buffer layout.
         *
         * @return (Type: uint32_t) The stride of the buffer layout.
         */
        inline uint32_t GetStride() const { return _Stride; }

        /**
         * @brief Get the elements of the buffer layout.
         *
         * @return (Type: const std::vector<BufferElement>&) The elements of the buffer layout.
         */
        inline const std::vector<BufferElement> &GetElements() const { return _Elements; }

        ////////////////
        // Attributes //
        ////////////////
      private:
        std::vector<BufferElement> _Elements; /*!< The elements of the buffer layout */
        uint32_t _Stride;                     /*!< The stride of the buffer layout */
    };

    /**
     * @brief Represents a vertex buffer used for storing vertex data.
     */
    class VertexBuffer {

        /////////////
        // Factory //
        /////////////
      public:
        /**
         * @brief Create a vertex buffer with the specified size.
         *
         * @param size (Type: uint32_t)          The size of the vertex buffer in bytes.
         * @return     (Type: Ref<VertexBuffer>) A reference to the created vertex buffer.
         */
        static Ref<VertexBuffer> Create(uint32_t size);

        /**
         * @brief Create a vertex buffer with the provided vertex data and size.
         *
         * @param vertices (Type: float *)           Pointer to the vertex data.
         * @param size     (Type: uint32_t)          The size of the vertex buffer in bytes.
         * @return         (Type: Ref<VertexBuffer>) A reference to the created vertex buffer.
         */
        static Ref<VertexBuffer> Create(float *vertices, uint32_t size);

        //////////////////////////////
        // Constructor & Destructor //
        //////////////////////////////
      public:
        /**
         * @brief Virtual destructor for the VertexBuffer class.
         */
        virtual ~VertexBuffer() = default;

        /////////////
        // Methods //
        /////////////
      public:
        /**
         * @brief Bind the Vertex buffer.
         */
        virtual void Bind() const = 0;

        /**
         * @brief Unbind the Vertex buffer.
         */
        virtual void Unbind() const = 0;

        ///////////////////////
        // Setters & Getters //
        ///////////////////////
      public:
        /**
         * @brief Set the layout of the vertex buffer.
         *
         * @param layout (Type: const BufferLayout &) The layout to set.
         */
        virtual void SetLayout(const BufferLayout &layout) = 0;

        /**
         * @brief Get the layout of the vertex buffer.
         *
         * @return (Type: const BufferLayout &) The layout of the vertex buffer.
         */
        virtual const BufferLayout &GetLayout() = 0;

        /**
         * @brief Set the data of the vertex buffer.
         *
         * @param data (Type: const void *) Pointer to the data.
         * @param size (Type: uint32_t)     The size of the data in bytes.
         */
        virtual void SetData(const void *data, uint32_t size) = 0;
    };

    /**
     * @brief Represents an index buffer used for storing indices for indexed rendering.
     *
     * TODO: Add support for more than 32-bit index buffers
     */
    class IndexBuffer {

        /////////////
        // Factory //
        /////////////
      public:
        /**
         * @brief Create an index buffer with the provided indices and count.
         *
         * @param indices (Type: uint32_t *)       Pointer to the indices data.
         * @param count   (Type: uint32_t)         The number of indices.
         * @return        (Type: Ref<IndexBuffer>) A reference to the created index buffer.
         */
        static Ref<IndexBuffer> Create(uint32_t *indices, uint32_t count);

        //////////////////////////////
        // Constructor & Destructor //
        //////////////////////////////
      public:
        /**
         * @brief Virtual destructor for the IndexBuffer class.
         */
        virtual ~IndexBuffer() = default;

        /////////////
        // Methods //
        /////////////
      public:
        /**
         * @brief Bind the Index buffer.
         */
        virtual void Bind() const = 0;

        /**
         * @brief Unbind the Index buffer.
         */
        virtual void Unbind() const = 0;

        ///////////////////////
        // Getters & Setters //
        ///////////////////////
      public:
        /**
         * @brief Get the count of the index buffer.
         *
         * @return (Type: uint32_t) The count of the index buffer.
         */
        virtual uint32_t GetCount() const = 0;
    };
}; // namespace Exodia

#endif /* !BUFFERS_HPP_ */
