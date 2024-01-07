/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** PrefabsImporter
*/

#include "PrefabsImporter.hpp"

// Exodia Debug includes
#include "Exodia-Debug.hpp"

// Exodia Project includes
#include "Project/Project.hpp"

// Exodia Scene includes
#include "Scene/Scene/Scene.hpp"
#include "Scene/Prefabs/Prefabs.hpp"

namespace Exodia {

    /////////////
    // Methods //
    /////////////

    Ref<Prefabs> PrefabsImporter::ImportPrefabs(UNUSED(AssetHandle handle), const AssetSpecification &spec) {
        EXODIA_PROFILE_FUNCTION();

        return LoadPrefabs(Project::GetActiveAssetDirectory() / spec.Path);
    }

    Ref<Prefabs> PrefabsImporter::LoadPrefabs(const std::filesystem::path &path, Ref<Scene> scene) {
        EXODIA_PROFILE_FUNCTION();

        Ref<Prefabs> prefabs = CreateRef<Prefabs>();

        prefabs->Load(path.string(), scene);

        return prefabs;
    }

    void PrefabsImporter::SavePrefabs(Ref<Prefabs> prefabs, const std::filesystem::path &path) {
        EXODIA_PROFILE_FUNCTION();

        prefabs->Save((Project::GetActiveAssetDirectory() / path).string());
    }
}; // namespace Exodia
