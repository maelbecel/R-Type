/*
** EPITECH PROJECT, 2023
** ExodiaGameEngine
** File description:
** VertexArray
*/

#ifndef VERTEXARRAY_HPP_
#define VERTEXARRAY_HPP_

// Exodia Renderer
#include "Renderer/Buffer/Buffers.hpp"

// Exodia Utils
#include "Utils/Memory.hpp"

namespace Exodia
{

    /**
     * @brief The VertexArray class defines an abstract interface for creating and managing vertex arrays.
     * It provides methods for creating vertex arrays, binding and unbinding them, as well as managing associated vertex
     * and index buffers.
     */
    class VertexArray
    {

        /////////////
        // Factory //
        /////////////
      public:
        /**
         * @brief Create a new vertex array.
         *
         * @return (Type: Ref<VertexArray>) A reference to the created vertex array.
         */
        static Ref<VertexArray> Create();

        //////////////////////////////
        // Constructor & Destructor //
        //////////////////////////////
      public:
        virtual ~VertexArray() = default;

        /////////////
        // Methods //
        /////////////
      public:
        /**
         * @brief Bind the vertex array for rendering.
         * This function makes the vertex array active for rendering.
         */
        virtual void Bind() const = 0;

        /**
         * @brief Unbind the vertex array.
         * This function makes the vertex array inactive for rendering.
         */
        virtual void Unbind() const = 0;

        ///////////////////////
        // Getters & Setters //
        ///////////////////////
      public:
        /**
         * @brief Add a vertex buffer to the vertex array.
         *
         * @param vertexBuffer (Type: const Ref<VertexBuffer> &) A reference to the vertex buffer to add.
         */
        virtual void AddVertexBuffer( const Ref<VertexBuffer> &vertexBuffer ) = 0;

        /**
         * @brief Set the index buffer for the vertex array.
         *
         * @param indexBuffer (Type: const Ref<IndexBuffer> &) A reference to the index buffer to set.
         */
        virtual void SetIndexBuffer( const Ref<IndexBuffer> &indexBuffer ) = 0;

        /**
         * @brief Get a vector of references to the vertex buffers associated with the vertex array.
         *
         * @return (Type: const std::vector<Ref<VertexBuffer>> &) A constant reference to the vector of vertex buffer
         * references.
         */
        virtual const std::vector<Ref<VertexBuffer>> &GetVertexBuffers() const = 0;

        /**
         * @brief Get a reference to the index buffer associated with the vertex array.
         *
         * @return (Type: const Ref<IndexBuffer> &) A constant reference to the index buffer reference.
         */
        virtual const Ref<IndexBuffer> &GetIndexBuffer() const = 0;
    };
}; // namespace Exodia

#endif /* !VERTEXARRAY_HPP_ */
