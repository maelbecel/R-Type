/*
** EPITECH PROJECT, 2023
** ExodiaGameEngine
** File description:
** OpenGLTexture
*/

#ifndef OPENGLTEXTURE_HPP_
    #define OPENGLTEXTURE_HPP_

    // Exodia Renderer
    #include "Renderer/Texture/Texture.hpp"

    // External includes
    #include <glad/glad.h>

namespace Exodia {

    /**
     * @brief Implementation of the Texture2D class using OpenGL.
     * This class represents a 2D texture using OpenGL and provides methods for binding and setting texture data.
     */
    class OpenGLTexture : public Texture2D {

        //////////////////////////////
        // Constructor & Destructor //
        //////////////////////////////
        public:

            /**
             * @brief Construct a new OpenGLTexture object with specified dimensions.
             *
             * @param spec (Type: const TextureSpecification&) The specification of the texture.
             * @param data (Type: Buffer)                       The data of the texture.
             */
            OpenGLTexture(const TextureSpecification &spec, Buffer data);

            /**
             * @brief Destroy the OpenGLTexture object.
             * This destructor releases the resources associated with the OpenGL texture.
             */
            virtual ~OpenGLTexture();

        /////////////
        // Methods //
        /////////////
        public:

            /**
             * @brief Bind the OpenGLTexture to a texture slot.
             *
             * @param slot (Type: uint32_t) The texture slot to bind to (default is 0).
             */
            virtual void Bind(uint32_t slot = 0) const override;

        ////////////////
        // Comparator //
        ////////////////
        public:

            /**
             * @brief Compare this texture with another texture for equality.
             *
             * @param other (Type: const Texture&) The other texture to compare with.
             * @return      (Type: bool)           True if the textures are equal, false otherwise.
             */
            virtual bool operator==(const Texture &other) const override;

        ///////////////////////
        // Getters & Setters //
        ///////////////////////
        public:

            /**
             * @brief Get the width of the texture.
             *
             * @return (Type: uint32_t) The width of the texture.
             */
            virtual uint32_t GetWidth() const override;

            /**
             * @brief Get the height of the texture.
             *
             * @return (Type: uint32_t) The height of the texture.
             */
            virtual uint32_t GetHeight() const override;

            /**
             * @brief Get the RendererID of the texture.
             *
             * @return (Type: uint32_t) The OpenGL texture ID.
             */
            virtual uint32_t GetRendererID() const override;

            virtual void SetData(Buffer data) override;

            virtual bool IsLoaded() const override;

            virtual const TextureSpecification &GetSpecification() const override;

        ////////////////
        // Attributes //
        ////////////////
        private:
            TextureSpecification _Specification; /*!< The specification of the texture */
            uint32_t    _Width;                  /*!< Width of the texture */
            uint32_t    _Height;                 /*!< Height of the texture */
            uint32_t    _RendererID;             /*!< OpenGL texture ID */
            GLenum      _InternalFormat;         /*!< Internal format of the texture */
            GLenum      _DataFormat;             /*!< Data format of the texture */
            bool        _IsLoaded;               /*!< Whether the texture is loaded or not */
    };
};

#endif /* !OPENGLTEXTURE_HPP_ */
