/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** OpenGLFont
*/

#ifndef OPENGLFONT_HPP_
#define OPENGLFONT_HPP_

// Exodia Renderer includes
#include "Renderer/Font/Font.hpp"
#include "Renderer/Texture/Texture.hpp"

namespace Exodia {

    class OpenGLFont : public Font {

        //////////////////////////////
        // Constructor & Destructor //
        //////////////////////////////
      public:
        OpenGLFont(const std::string &path);
        ~OpenGLFont() override = default;

        /////////////
        // Methods //
        /////////////
      private:
        bool GenerateGlyphs(const std::string &path);
        void GenerateOffsets();
        void GenerateCoords();

        ///////////////////////
        // Getters & Setters //
        ///////////////////////
      public:
        const FontData &GetData() const override;

        Ref<Texture2D> GetTexture() const override;

        ////////////////
        // Attributes //
        ////////////////
      private:
        Scope<FontData> _Data;
        Ref<Texture2D> _Texture;
    };
}; // namespace Exodia

#endif /* !OPENGLFONT_HPP_ */
