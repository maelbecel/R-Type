/*
** EPITECH PROJECT, 2023
** ExodiaGameEngine
** File description:
** SubTexture2D
*/

#ifndef SUBTEXTURE2D_HPP_
    #define SUBTEXTURE2D_HPP_

    // Exodia Renderer
    #include "Texture.hpp"

    // Exodia Asset includes
    #include "Asset/Utils/AssetType.hpp"

    // External includes
    #include <glm/glm.hpp>

namespace Exodia {

    /**
     * @brief The SubTexture2D class represents a portion of a 2D texture, defined by texture coordinates.
     * It allows creating and managing subtextures for rendering sprites or other texture-based graphics.
     */
    class SubTexture2D {

        /////////////
        // Factory //
        /////////////
        public:

            /**
             * @brief Create a SubTexture2D instance from texture coordinates.
             *
             * @param texture    (Type: const Ref<Texture2D> &) The parent texture.
             * @param coords     (Type: const glm::vec2      &) The starting coordinates of the subtexture within the texture.
             * @param cellSize   (Type: const glm::vec2      &) The size of each cell within the texture (for grid-based textures).
             * @param spriteSize (Type: const glm::vec2      &) The size of the sprite within the cell (default is {1, 1}).
             * @return           (Type: Ref<SubTexture2D>)      A reference to the created SubTexture2D.
             */
            static Ref<SubTexture2D> CreateFromCoords(const Ref<Texture2D> &texture, const glm::vec2 &coords, const glm::vec2 &cellSize, const glm::vec2 &spriteSize);

        //////////////////////////////
        // Constructor & Destructor //
        //////////////////////////////
        public:

            SubTexture2D(const Ref<Texture2D> &texture);
            SubTexture2D(const Ref<Texture2D> &texture, const glm::vec2 &coords, const glm::vec2 &cellSize, const glm::vec2 &spriteSize);
            SubTexture2D(const AssetHandle &assetHandle, const glm::vec2 &coords, const glm::vec2 &cellSize, const glm::vec2 &spriteSize);

            ~SubTexture2D() = default;

        /////////////
        // Methods //
        /////////////
        private:

            /**
             * @brief Calculate the texture coordinates of the subtexture.
             */
            void calculateTextureCoords();

        ///////////////////////
        // Getters & Setters //
        ///////////////////////
        public:

            /**
             * @brief Get the parent texture of the subtexture.
             *
             * @return (Type: Ref<Texture2D>) The parent texture.
             */
            Ref<Texture2D> GetTexture();

            /**
             * @brief Get the array of texture coordinates defining the subtexture's corners.
             *
             * @return (Type: const glm::vec2 *) Pointer to the array of texture coordinates.
             */
            const glm::vec2 *GetTextureCoords() const;

            const glm::vec2 &GetCoords();
            const glm::vec2 &GetTextureCellSize();
            const glm::vec2 &GetTextureSpriteSize();

            AssetHandle GetAssetHandle() const;

            void SetCoords(const glm::vec2 &coords);
            void SetTextureCellSize(const glm::vec2 &cellSize);
            void SetTextureSpriteSize(const glm::vec2 &spriteSize);
            void SetTexture(const AssetHandle &handle);
            void SetTexture(const Ref<Texture2D> &texture);

        ////////////////
        // Attributes //
        ////////////////
        private:
            Ref<Texture2D> _Texture;            /*!< The parent texture of the subtexture. */
            glm::vec2      _TextureCoords[4];   /*!< The texture coordinates defining the subtexture's corners. */
            glm::vec2      _Coords;             /*!< The starting coordinates of the subtexture within the texture. */
            glm::vec2      _CellSize;           /*!< The size of each cell within the texture (for grid-based textures). */
            glm::vec2      _SpriteSize;         /*!< The size of the sprite within the cell (default is {1, 1}). */
    };
};

#endif /* !SUBTEXTURE2D_HPP_ */
