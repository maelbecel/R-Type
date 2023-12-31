/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** FontImporter
*/

#ifndef FONTIMPORTER_HPP_
#define FONTIMPORTER_HPP_

// Exodia Asset includes
#include "Asset/Utils/AssetType.hpp"

// Exodia Renderer includes
#include "Renderer/Font/Font.hpp"

// External includes
#include <filesystem>

namespace Exodia {

    class Font;

    class FontImporter {

        /////////////
        // Methods //
        /////////////
      public:
        static Ref<Font> ImportFont(AssetHandle handle, const AssetSpecification &spec);
        static Ref<Font> LoadFont(const std::filesystem::path &path);
    };
}; // namespace Exodia

#endif /* !FONTIMPORTER_HPP_ */
