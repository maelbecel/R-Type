/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** FontImporter
*/

#include "FontImporter.hpp"

// Exodia Utils
#include "Utils/Memory.hpp"

// Exodia Project
#include "Project/Project.hpp"

// Exodia Renderer
#include "Renderer/Font/Font.hpp"

// Exodia Debug
#include "Debug/Profiling.hpp"

namespace Exodia {

    /////////////
    // Methods //
    /////////////

    Ref<Font> FontImporter::ImportFont(UNUSED(AssetHandle handle), const AssetSpecification &spec)
    {
        EXODIA_PROFILE_FUNCTION();

        return LoadFont(Project::GetActiveAssetDirectory() / spec.Path);
    }

    Ref<Font> FontImporter::LoadFont(const std::filesystem::path &path)
    {
        EXODIA_PROFILE_FUNCTION();

        Ref<Font> sound = Font::Create(path.string());

        return sound;
    }
};
