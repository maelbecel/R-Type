/*
** EPITECH PROJECT, 2023
** ExodiaGameEngine
** File description:
** Framebuffer
*/

#ifndef FRAMEBUFFER_HPP_
#define FRAMEBUFFER_HPP_

// Exodia Utils
#include "Utils/Memory.hpp"

// External includes
#include <vector>

namespace Exodia {

    enum class FramebufferTextureFormat {
        // Nothing
        None,

        // Color
        RGBA8,
        RED_INTEGER,

        // Depth / Stencil
        DEPTH24STENCIL8,

        // Defaults
        Depth = DEPTH24STENCIL8
    };

    struct FramebufferTextureSpecification {
        FramebufferTextureFormat TextureFormat;

        FramebufferTextureSpecification(FramebufferTextureFormat format = FramebufferTextureFormat::None)
            : TextureFormat(format){};

        // TODO: Filtering / Wrap
    };

    struct FramebufferAttachmentSpecification {
        std::vector<FramebufferTextureSpecification> Attachments;

        FramebufferAttachmentSpecification() = default;
        FramebufferAttachmentSpecification(std::initializer_list<FramebufferTextureSpecification> attachments)
            : Attachments(attachments){};
    };

    /**
     * @brief This structure represents the specification of a framebuffer.
     */
    struct FramebufferSpecification {
        uint32_t Width;                                 /* !< The width in pixels of the Framebuffer. */
        uint32_t Height;                                /* !< The height in pixels of the Framebuffer. */
        FramebufferAttachmentSpecification Attachments; /* !< The attachments of the framebuffer. */
        uint32_t Samples = 1;         /* !< The number of samples to use for multisampling. (default = 1) */
        bool SwapChainTarget = false; /* !< Whether or not the framebuffer is the swapchain target. (default = false) */
    };

    /**
     * @brief The Framebuffer class defines an abstract interface for creating framebuffers.
     * It provides methods to create framebuffer instances.
     */
    class Framebuffer {

        /////////////
        // Factory //
        /////////////
      public:
        /**
         * @brief Create a framebuffer instance from a framebuffer specification.
         *
         * @param spec (Type: const FramebufferSpecification &) The specification of the framebuffer.
         * @return     (Type: Ref<Framebuffer>)                 A reference to the created framebuffer.
         */
        static Ref<Framebuffer> Create(const FramebufferSpecification &spec);

        //////////////////////////////
        // Constructor & Destructor //
        //////////////////////////////
      public:
        virtual ~Framebuffer() = default;

        /////////////
        // Methods //
        /////////////
      public:
        /**
         * @brief Bind the framebuffer for rendering.
         */
        virtual void Bind() = 0;

        /**
         * @brief Unbind the framebuffer for rendering.
         */
        virtual void Unbind() = 0;

        /**
         * @brief Resize the framebuffer.
         *
         * @param width  (Type: uint32_t) The new width of the framebuffer.
         * @param height (Type: uint32_t) The new height of the framebuffer.
         */
        virtual void Resize(uint32_t width, uint32_t height) = 0;

        virtual int ReadPixel(uint32_t attachmentIndex, int x, int y) = 0;
        virtual void ClearAttachment(uint32_t attachmentIndex, int value) = 0;

        ///////////////////////
        // Getters & Setters //
        ///////////////////////
      public:
        /**
         * @brief Get the specification of the framebuffer.
         *
         * @return (Type: const FramebufferSpecification &) The specification of the framebuffer.
         */
        virtual const FramebufferSpecification &GetSpecification() const = 0;

        /**
         * @brief Get the color attachment of the framebuffer.
         *
         * @param index (Type: uint32_t) The index of the color attachment
         * @return      (Type: uint32_t) The color attachment of the framebuffer
         */
        virtual uint32_t GetColorAttachmentRendererID(uint32_t index = 0) const = 0;
    };
}; // namespace Exodia

#endif /* !FRAMEBUFFER_HPP_ */
