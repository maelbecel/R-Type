/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** SoundImporter
*/

// Exodia Asset
#include "SoundImporter.hpp"

// Exodia Utils
#include "Utils/Memory.hpp"

// Exodia Project
#include "Project/Project.hpp"

// Exodia Renderer
#include "Renderer/Sound/Sound.hpp"

// Exodia Debug
#include "Exodia-Debug.hpp"

namespace Exodia {

    /////////////
    // Methods //
    /////////////

    Ref<Sound2D> SoundImporter::ImportSound2D(UNUSED(AssetHandle handle), const AssetSpecification &spec) {
        EXODIA_PROFILE_FUNCTION();

        return LoadSound2D(Project::GetActiveAssetDirectory() / spec.Path);
    }

    Ref<Sound2D> SoundImporter::LoadSound2D(const std::filesystem::path &path) {
        EXODIA_PROFILE_FUNCTION();

        Ref<Sound2D> sound = Sound2D::Create(path.string());

        return sound;
    }
}; // namespace Exodia
