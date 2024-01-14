/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** PrefabsImporter
*/

#ifndef PREFABSIMPORTER_HPP_
#define PREFABSIMPORTER_HPP_

// Exodia Asset includes
#include "Asset/Utils/AssetType.hpp"

// Exodia Tools
#include "Exodia-Utils.hpp"

// External includes
#include <filesystem>

namespace Exodia {

    class Scene;
    class GameObject;

    class PrefabsImporter {

        /////////////
        // Methods //
        /////////////
      public:
        static Ref<GameObject> ImportPrefabs(AssetHandle handle, const AssetSpecification &spec);

        static GameObject LoadPrefabs(const std::filesystem::path &path, Ref<Scene> scene);
    };
}; // namespace Exodia

#endif /* !PREFABSIMPORTER_HPP_ */
