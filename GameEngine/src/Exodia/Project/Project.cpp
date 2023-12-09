/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** Project
*/

// Exodia Project includes
#include "Project.hpp"
#include "Project/ProjectSerializer.hpp"

// Exodia Utils includes
#include "Utils/Assert.hpp"

namespace Exodia {

    /////////////
    // Methods //
    /////////////

    Ref<Project> Project::New()
    {
        _ActiveProject = CreateRef<Project>();

        return _ActiveProject;
    }

    Ref<Project> Project::Load(const std::filesystem::path &path)
    {
        Ref<Project> project = CreateRef<Project>();

        ProjectSerializer serializer(project);

        if (!serializer.Deserialize(path))
            return nullptr;

        project->_ProjectDirectory = path.parent_path();

        _ActiveProject = project;

        Ref<EditorAssetManager> editorAssetManager = CreateRef<EditorAssetManager>();

        _ActiveProject->_AssetManager = editorAssetManager;

        editorAssetManager->DeserializeAssetRegistry();

        return project;
    }

    bool Project::SaveActive(const std::filesystem::path &path)
    {
        ProjectSerializer serializer(_ActiveProject);

        if (!serializer.Serialize(path))
            return false;
        _ActiveProject->_ProjectDirectory = path.parent_path();
        return true;
    }

    ///////////////////////
    // Getters & Setters //
    ///////////////////////

    const std::filesystem::path &Project::GetProjectDirectory()
    {
        return _ProjectDirectory;
    }

    std::filesystem::path Project::GetAssetDirectory()
    {
        EXODIA_CORE_ASSERT(_ActiveProject, "Project::GetAssetDirectory() - No active project !");

        return GetProjectDirectory() / _ActiveProject->_Config.AssetsDirectory;
    }

    std::filesystem::path Project::GetAssetFilePath(const std::filesystem::path &path)
    {
        return GetAssetDirectory() / path;
    }

    std::filesystem::path Project::GetAssetRegistryPath()
    {
        EXODIA_CORE_ASSERT(_ActiveProject, "Project::GetAssetRegistryPath() - No active project !");

        return GetAssetDirectory() / _ActiveProject->_Config.AssetRegistryPath;
    }

    std::filesystem::path Project::GetAssetAbsolutePath(const std::filesystem::path &path)
    {
        return GetAssetDirectory() / path;
    }

    const std::filesystem::path &Project::GetActiveProjectDirectory()
    {
        EXODIA_CORE_ASSERT(_ActiveProject, "Project::GetActiveProjectDirectory() - No active project !");

        return _ActiveProject->GetProjectDirectory();
    }

    std::filesystem::path Project::GetActiveAssetDirectory()
    {
        EXODIA_CORE_ASSERT(_ActiveProject, "Project::GetAssetDirectory() - No active project !");

        return _ActiveProject->GetAssetDirectory();
    }

    std::filesystem::path Project::GetActiveAssetFilePath(const std::filesystem::path &path)
    {
        EXODIA_CORE_ASSERT(_ActiveProject, "Project::GetAssetFilePath() - No active project !");

        return _ActiveProject->GetAssetFilePath(path);
    }

    std::filesystem::path Project::GetActiveAssetRegistryPath()
    {
        EXODIA_CORE_ASSERT(_ActiveProject, "Project::GetAssetRegistryPath() - No active project !");

        return _ActiveProject->GetAssetRegistryPath();
    }

    Ref<Project> Project::GetActive()
    {
        return _ActiveProject;
    }

    Ref<IAssetManager> Project::GetAssetManager() const
    {
        return _AssetManager;
    }

    Ref<RuntimeAssetManager> Project::GetRuntimeAssetManager() const
    {
        return std::static_pointer_cast<RuntimeAssetManager>(_AssetManager);
    }

    Ref<EditorAssetManager> Project::GetEditorAssetManager() const
    {
        return std::static_pointer_cast<EditorAssetManager>(_AssetManager);
    }

    ProjectConfig &Project::GetConfig()
    {
        return _Config;
    }
};
