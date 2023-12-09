/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** SceneImporter
*/

// Exodia Asset includes
#include "SceneImporter.hpp"

// Exodia Debug includes
#include "Debug/Profiling.hpp"

// Exodia Project includes
#include "Project/Project.hpp"

// Exodia Scene includes
#include "Scene/Serializer/SceneSerializer.hpp"

namespace Exodia {

    /////////////
    // Methods //
    /////////////

    Ref<Scene> SceneImporter::ImportScene(UNUSED AssetHandle handle, const AssetSpecification &spec)
    {
        EXODIA_PROFILE_FUNCTION();

        return LoadScene(Project::GetActiveAssetDirectory() / spec.Path);
    }

    Ref<Scene> SceneImporter::LoadScene(const std::filesystem::path &path)
    {
        EXODIA_PROFILE_FUNCTION();

        Ref<Scene> scene = CreateRef<Scene>();

        SceneSerializer serializer(scene);

        serializer.Deserialize(path);
        return scene;
    }

    void SceneImporter::SaveScene(Ref<Scene> scene, const std::filesystem::path &path)
    {
        EXODIA_PROFILE_FUNCTION();

        SceneSerializer serializer(scene);

        serializer.Serialize(Project::GetActiveAssetDirectory() / path);
    }
};
