/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** PrefabsImporter
*/

#include "PrefabsImporter.hpp"
#include "Scene/Scene/Scene.hpp"

// Exodia Debug includes
#include "Exodia-Debug.hpp"

namespace Exodia {

    /////////////
    // Methods //
    /////////////

    Ref<GameObject> PrefabsImporter::ImportPrefabs(UNUSED(AssetHandle handle), UNUSED(const AssetSpecification &spec)) {
        EXODIA_PROFILE_FUNCTION();

        return CreateRef<GameObject>();
    }

    GameObject PrefabsImporter::LoadPrefabs(const std::filesystem::path &path, Ref<Scene> scene) {
        EXODIA_PROFILE_FUNCTION();

        GameObject prefabs = scene->LoadPrefabs(path.string(), true);

        return prefabs;
    }
}; // namespace Exodia
