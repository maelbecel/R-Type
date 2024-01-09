/*
** EPITECH PROJECT, 2023
** ExodiaGameEngine
** File description:
** Texture
*/

#ifndef TEXTURE_HPP_
#define TEXTURE_HPP_

// Exodia Asset includes
#include "Asset/Asset.hpp"

// Exodia Utils
#include "Exodia-Utils.hpp"

// External includes
#include <cstdint>
#include <string>

namespace Exodia {

    enum class ImageFormat { None = 0, R8 = 1, RGB8 = 2, RGBA8 = 3, RGBA32F = 4 };

    struct TextureSpecification {
        uint32_t Width = 1;
        uint32_t Height = 1;

        ImageFormat Format = ImageFormat::RGBA8;

        bool GenerateMips = true;
    };

    /**
     * @brief The Texture class defines an abstract interface for working with textures in the rendering pipeline.
     * It provides methods for binding textures, setting data, and retrieving texture properties.
     */
    class Texture : public Asset {

        //////////////////////////////
        // Constructor & Destructor //
        //////////////////////////////
      public:
        virtual ~Texture() = default;

        /////////////
        // Methods //
        /////////////
      public:
        /**
         * @brief Bind the texture to a specific texture slot for rendering.
         *
         * @param slot (Type: uint32_t) The texture slot index (default is 0).
         */
        virtual void Bind(uint32_t slot = 0) const = 0;

        ////////////////
        // Comparator //
        ////////////////
      public:
        /**
         * @brief Compare two textures for equality.
         *
         * @param other (Type: const Texture &) The texture to compare with.
         * @return      (Type: bool)            True if the textures are equal, otherwise false.
         */
        virtual bool operator==(const Texture &other) const = 0;

        ///////////////////////
        // Getters & Setters //
        ///////////////////////
      public:
        /**
         * @brief Get the width of the texture.
         *
         * @return (Type: uint32_t) The width of the texture.
         */
        virtual uint32_t GetWidth() const = 0;

        /**
         * @brief Get the height of the texture.
         *
         * @return (Type: uint32_t) The height of the texture.
         */
        virtual uint32_t GetHeight() const = 0;

        /**
         * @brief Get the RendererID of the texture.
         *
         * @return (Type: uint32_t) The RendererID of the texture.
         */
        virtual uint32_t GetRendererID() const = 0;

        /**
         * @brief Set data for the texture.
         *
         * @param data (Type: Buffer) The data to set.
         */
        virtual void SetData(Buffer data) = 0;
        virtual Buffer GetData() const = 0;

        virtual bool IsLoaded() const = 0;

        virtual const TextureSpecification &GetSpecification() const = 0;
    };

    /**
     * @brief The Texture2D class provides an abstract interface for creating and managing 2D textures.
     * It defines methods for creating textures and selecting them for rendering.
     */
    class Texture2D : public Texture {

        /////////////
        // Factory //
        /////////////
      public:
        /**
         * @brief Create a 2D texture with a specified texture specification.
         *
         * @param spec   (Type: const TextureSpecification &) The texture specification (default is
         * TextureSpecification())
         * @param data   (Type: Buffer)                       The data to set (default is Buffer())
         * @return       (Type: Ref<Texture2D>)               A reference to the created texture.
         */
        static Ref<Texture2D> Create(const TextureSpecification &spec, Buffer data = Buffer());

        ///////////////////////
        // Getters & Setters //
        ///////////////////////
      public:
        static AssetType GetStaticType();
        virtual AssetType GetType() const;
    };
}; // namespace Exodia

#endif /* !TEXTURE_HPP_ */
