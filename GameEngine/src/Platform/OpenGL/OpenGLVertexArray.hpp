/*
** EPITECH PROJECT, 2023
** ExodiaGameEngine
** File description:
** OpenGLVertexArray
*/

#ifndef OPENGLVERTEXARRAY_HPP_
    #define OPENGLVERTEXARRAY_HPP_

    // Exodia Renderer
    #include "Renderer/Vertex/VertexArray.hpp"

namespace Exodia {

    /**
     * @brief Implementation of the VertexArray class using OpenGL.
     * This class represents an OpenGL vertex array object (VAO) used for rendering.
     */
    class OpenGLVertexArray : public VertexArray {

        //////////////////////////////
        // Constructor & Destructor //
        //////////////////////////////
        public:

            /**
             * @brief Construct a new OpenGLVertexArray object.
             * This constructor initializes an OpenGL vertex array object (VAO).
             */
            OpenGLVertexArray();

            /**
             * @brief Destroy the OpenGLVertexArray object.
             * This destructor releases the resources associated with the OpenGL vertex array object (VAO).
             */
            virtual ~OpenGLVertexArray();

        /////////////
        // Methods //
        /////////////
        public:

            /**
             * @brief Bind the OpenGLVertexArray.
             * This method binds the OpenGL vertex array object (VAO) for rendering.
             */
            virtual void Bind() const override;

            /**
             * @brief Unbind the OpenGLVertexArray.
             * This method unbinds the currently bound OpenGL vertex array object (VAO).
             */
            virtual void Unbind() const override;

        ///////////////////////
        // Getters & Setters //
        ///////////////////////
        public:

            /**
             * @brief Add a vertex buffer to the OpenGLVertexArray.
             * This method adds a vertex buffer to the OpenGL vertex array object (VAO).
             *
             * @param vertexBuffer (Type: const Ref<VertexBuffer> &) The vertex buffer to add.
             * 
             * @note If the provided vertexBuffer have no layout, the method will throw an exception.
             */
            virtual void AddVertexBuffer(const Ref<VertexBuffer> &vertexBuffer) override;

            /**
             * @brief Set the index buffer for the OpenGLVertexArray.
             * This method sets the index buffer for the OpenGL vertex array object (VAO).
             *
             * @param indexBuffer (Type: const Ref<IndexBuffer> &) The index buffer to set.
             */
            virtual void SetIndexBuffer(const Ref<IndexBuffer> &indexBuffer) override;

            /**
             * @brief Get the list of vertex buffers in the OpenGLVertexArray.
             * This method retrieves the list of vertex buffers associated with the OpenGL vertex array object (VAO).
             *
             * @return (Type: const std::vector<Ref<VertexBuffer>> &) The list of vertex buffers.
             */
            virtual const std::vector<Ref<VertexBuffer>> &GetVertexBuffers() const override;

            /**
             * @brief Get the index buffer of the OpenGLVertexArray.
             * This method retrieves the index buffer associated with the OpenGL vertex array object (VAO).
             *
             * @return (Type: const Ref<IndexBuffer>&) The index buffer.
             */
            virtual const Ref<IndexBuffer> &GetIndexBuffer() const override;

        ////////////////
        // Attributes //
        ////////////////
        private:
            uint32_t                       _RendererID;        /*!< OpenGL vertex array object (VAO) ID */
            uint32_t                       _VertexBufferIndex; /*!< Vertex buffer index */
            std::vector<Ref<VertexBuffer>> _VertexBuffers;     /*!< Vertex buffers */
            Ref<IndexBuffer>               _IndexBuffers;      /*!< Index buffer */
    };
};

#endif /* !OPENGLVERTEXARRAY_HPP_ */
