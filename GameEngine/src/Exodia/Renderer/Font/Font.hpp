/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** Font
*/

#ifndef FONT_HPP_
#define FONT_HPP_

// Exodia Assets
#include "Asset/Utils/AssetType.hpp"

// Exodia Utils
#include "Utils/Memory.hpp"

// External includes
#include <glm/glm.hpp>
#include <array>

namespace Exodia {

    class Texture2D;

    struct Glyph {
        glm::vec2 TextureCoord;
        int Width;
    };

    struct FontData {
        std::array<Glyph, 256> Glyphs;
    };

    class Font : public Asset {

        /////////////
        // Factory //
        /////////////
      public:
        static Ref<Font> Create(const std::string &path);

        ///////////////////////////////
        // Constructors & Destructor //
        ///////////////////////////////
      public:
        virtual ~Font() = default;

        ///////////////////////
        // Getters & Setters //
        ///////////////////////
      public:
        virtual const FontData &GetData() const = 0;

        virtual Ref<Texture2D> GetTexture() const = 0;

        static AssetType GetStaticType();
        virtual AssetType GetType() const;
    };
}; // namespace Exodia

#endif /* !FONT_HPP_ */
