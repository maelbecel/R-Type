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

    #include "Scene/Prefabs/Prefabs.hpp"

    // External includes
    #include <filesystem>

namespace Exodia {

    class Prefabs;
    class Scene;

    class PrefabsImporter {

        /////////////
        // Methods //
        /////////////
        public:

            static Ref<Prefabs> ImportPrefabs(AssetHandle handle, const AssetSpecification &spec);
            static Ref<Prefabs> LoadPrefabs(const std::filesystem::path &path, Ref<Scene> scene = nullptr);

            static void SavePrefabs(Ref<Prefabs> prefabs, const std::filesystem::path &path);
    };
};

#endif /* !PREFABSIMPORTER_HPP_ */
