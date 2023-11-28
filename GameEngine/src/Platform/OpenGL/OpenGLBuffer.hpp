/*
** EPITECH PROJECT, 2023
** ExodiaGameEngine
** File description:
** OpenGLBuffer
*/

#ifndef OPENGLBUFFER_HPP_
    #define OPENGLBUFFER_HPP_

    // Exodia Renderer
    #include "Renderer/Buffer/Buffer.hpp"

namespace Exodia {

    /**
     * @brief Implementation of the OpenGL vertex buffer.
     *
     * This class represents a vertex buffer in OpenGL, which stores vertex data for rendering.
     */
    class OpenGLVertexBuffer : public VertexBuffer {

        //////////////////////////////
        // Constructor & Destructor //
        //////////////////////////////
        public:

            /**
             * @brief Construct a new OpenGLVertexBuffer object with the given size.
             *
             * @param size (Type: uint32_t) The size of the buffer in bytes.
             */
            OpenGLVertexBuffer(uint32_t size);

            /**
             * @brief Construct a new OpenGLVertexBuffer object with the given vertices and size.
             *
             * @param vertices (Type: float *)  Pointer to the vertex data.
             * @param size     (Type: uint32_t) The size of the buffer in bytes.
             */
            OpenGLVertexBuffer(float *vertices, uint32_t size);

            /**
             * @brief Destroy the OpenGLVertexBuffer object.
             * The destructor releases the resources associated with the vertex buffer.
             */
            virtual ~OpenGLVertexBuffer();

        /////////////
        // Methods //
        /////////////
        public:

            /**
             * @brief Bind the vertex buffer.
             * This method binds the vertex buffer for rendering.
             */
            virtual void Bind() const override;

            /**
             * @brief Unbind the vertex buffer.
             * This method unbinds the vertex buffer.
             */
            virtual void Unbind() const override;

        ///////////////////////
        // Setters & Getters //
        ///////////////////////
        public:

            /**
             * @brief Set the layout of the buffer.
             *
             * @param layout (Type: const BufferLayout&) The layout to set.
             */
            virtual void SetLayout(const BufferLayout &layout) override;

            /**
             * @brief Get the layout of the buffer.
             *
             * @return (Type: const BufferLayout&) The layout of the buffer.
             */
            virtual const BufferLayout &GetLayout() override;

            /**
             * @brief Set data for the buffer.
             *
             * @param data (Type: const void *) Pointer to the data.
             * @param size (Type: uint32_t)     The size of the data in bytes.
             */
            virtual void SetData(const void *data, uint32_t size) override;

        ////////////////
        // Attributes //
        ////////////////
        private:
            uint32_t     _RendererID; /*!< The ID of the buffer */
            BufferLayout _Layout; /*!< The layout of the buffer */
    };

    /**
     * @brief Implementation of the OpenGL index buffer.
     *
     * This class represents an index buffer in OpenGL, which stores indices for indexed rendering.
     */
    class OpenGLIndexBuffer : public IndexBuffer {

        //////////////////////////////
        // Constructor & Destructor //
        //////////////////////////////
        public:

            /**
             * @brief Construct a new OpenGLIndexBuffer object with the given indices and count.
             *
             * @param indices (Type: uint32_t *) Pointer to the indices data.
             * @param count   (Type: uint32_t)   The number of indices.
             */
            OpenGLIndexBuffer(uint32_t *indices, uint32_t count);

            /**
             * @brief Destroy the OpenGLIndexBuffer object.
             * The destructor releases the resources associated with the index buffer.
             */
            virtual ~OpenGLIndexBuffer();

        /////////////
        // Methods //
        /////////////
        public:

            /**
             * @brief Bind the index buffer.
             * This method binds the index buffer for rendering.
             */
            virtual void Bind() const override;

            /**
             * @brief Unbind the index buffer.
             * This method unbinds the index buffer.
             */
            virtual void Unbind() const override;

        ///////////////////////
        // Getters & Setters //
        ///////////////////////
        public:

            /**
             * @brief Get the count of indices.
             *
             * @return (Type: uint32_t) The number of indices.
             */
            virtual uint32_t GetCount() const override;

        ////////////////
        // Attributes //
        ////////////////
        private:
            uint32_t _RendererID; /*!< The ID of the buffer */
            uint32_t _Count;      /*!< The number of indices */
    };
};

#endif /* !OPENGLBUFFER_HPP_ */
