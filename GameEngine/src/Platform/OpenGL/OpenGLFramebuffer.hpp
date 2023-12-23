/*
** EPITECH PROJECT, 2023
** ExodiaGameEngine
** File description:
** OpenGLFramebuffer
*/

#ifndef OPENGLFRAMEBUFFER_HPP_
#define OPENGLFRAMEBUFFER_HPP_

// Exodia Renderer
#include "Renderer/Buffer/Framebuffer.hpp"

namespace Exodia
{

    /**
     * @brief Implementation of the Framebuffer class using OpenGL.
     * This class represents a framebuffer using OpenGL.
     */
    class OpenGLFramebuffer : public Framebuffer
    {

        //////////////////////////////
        // Constructor & Destructor //
        //////////////////////////////
      public:
        /**
         * @brief Construct a new OpenGLFramebuffer object
         * Call this constructor if you want to create a OpenGLFramebuffer from different specification
         * @param spec (Type: const FramebufferSpecification &) The different specification of the framebuffer
         */
        OpenGLFramebuffer( const FramebufferSpecification &spec );

        virtual ~OpenGLFramebuffer();

        /////////////
        // Methods //
        /////////////
      public:
        /**
         * @brief Bind the OpenGLFramebuffer for rendering.
         */
        virtual void Bind() override;

        /**
         * @brief Unbind the OpenGLFramebuffer for rendering.
         */
        virtual void Unbind() override;

        /**
         * @brief Resize the OpenGLFramebuffer.
         * This function resizes the OpenGLFramebuffer to the specified width and height.
         *
         * @param width  (Type: uint32_t) The new width of the OpenGLFramebuffer.
         * @param height (Type: uint32_t) The new height of the OpenGLFramebuffer.
         */
        virtual void Resize( uint32_t width, uint32_t height ) override;

        virtual int  ReadPixel( uint32_t attachmentIndex, int x, int y ) override;
        virtual void ClearAttachment( uint32_t attachmentIndex, int value ) override;

      private:
        /**
         * @brief Invalidate the framebuffer, recreating its internal attachments and updating their specifications.
         * This function creates or recreates the color and depth attachments of the OpenGL framebuffer, based on the
         * specifications provided during framebuffer creation. It ensures that the framebuffer is complete and ready
         * for rendering.
         *
         * @note This function should be called whenever the framebuffer specifications change.
         *
         * @throws An assertion error if the framebuffer is incomplete after the attachments are created.
         */
        void Invalidate();

        ///////////////////////
        // Getters & Setters //
        ///////////////////////
      public:
        /**
         * @brief Get the specification of the framebuffer.
         *
         * @return (Type: const FramebufferSpecification &) The specification of the framebuffer.
         */
        virtual const FramebufferSpecification &GetSpecification() const override;

        /**
         * @brief Get the color attachment of the framebuffer.
         *
         * @param index (Type: uint32_t) The index of the color attachment
         * @return      (Type: uint32_t) The color attachment of the framebuffer
         */
        virtual uint32_t GetColorAttachmentRendererID( uint32_t index = 0 ) const override;

        ////////////////
        // Attributes //
        ////////////////
      private:
        uint32_t                 _RendererID;    /* !< The ID of the framebuffer. */
        FramebufferSpecification _Specification; /* !< The specification of the framebuffer. */
        std::vector<FramebufferTextureSpecification>
            _ColorAttachmentSpecifications; /* !< The specifications of the color attachment of the framebuffer. */
        FramebufferTextureSpecification
            _DepthAttachmentSpecification;       /* !< The specification of the depth attachment of the framebuffer. */
        std::vector<uint32_t> _ColorAttachments; /* !< The color attachments of the framebuffer. */
        uint32_t              _DepthAttachment;  /* !< The depth attachment of the framebuffer. */
    };
}; // namespace Exodia

#endif /* !OPENGLFRAMEBUFFER_HPP_ */
