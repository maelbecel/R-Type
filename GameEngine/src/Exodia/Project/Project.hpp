/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** Project
*/

#ifndef PROJECT_HPP_
#define PROJECT_HPP_

// Exodia Asset includes
#include "Asset/Manager/EditorAssetManager.hpp"

// Exodia ECS includes
#include "Exodia-ECS.hpp"

// Exodia Utils includes
#include "Exodia-Utils.hpp"

// External includes
#include <unordered_map>
#include <filesystem>
#include <functional>

namespace Exodia {

    class ScriptableEntity;

    struct ProjectConfig {
        std::string Name = "Untitled";

        AssetHandle StartScene;

        std::filesystem::path AssetsDirectory;
        std::filesystem::path AssetRegistryPath;
        std::filesystem::path ScriptsDirectory;
    };

    class Project {

        //////////////////////////////
        // Constructor & Destructor //
        //////////////////////////////
      public:
        Project();
        ~Project() = default;

        /////////////
        // Methods //
        /////////////
      public:
        static Ref<Project> New();
        static Ref<Project> Load(const std::filesystem::path &path);

        static bool SaveActive(const std::filesystem::path &path);

        ///////////////////////
        // Getters & Setters //
        ///////////////////////
      public:
        const std::filesystem::path &GetProjectDirectory();
        std::filesystem::path GetAssetDirectory();
        std::filesystem::path GetAssetFilePath(const std::filesystem::path &path);
        std::filesystem::path GetAssetRegistryPath();
        std::filesystem::path GetAssetAbsolutePath(const std::filesystem::path &path);
        std::filesystem::path GetScriptPath();

        static const std::filesystem::path &GetActiveProjectDirectory();
        static std::filesystem::path GetActiveAssetDirectory();
        static std::filesystem::path GetActiveAssetFilePath(const std::filesystem::path &path);
        static std::filesystem::path GetActiveAssetRegistryPath();
        static std::filesystem::path GetActiveScriptPath();

        static Ref<Project> GetActive();

        Ref<IAssetManager> GetAssetManager() const;
        Ref<EditorAssetManager> GetEditorAssetManager() const;

        void RegisterComponent(std::string component, std::function<IComponentContainer *(Buffer)> factory);
        std::function<IComponentContainer *(Buffer)> GetComponentFactory(std::string component);

        void RegisterScript(std::string script, std::function<ScriptableEntity *()> factory);
        std::function<ScriptableEntity *()> GetScriptFactory(std::string script);

        void RegisterSystem(std::string system, std::function<EntitySystem *()> factory);
        std::function<EntitySystem *()> GetSystemFactory(std::string system);

        ProjectConfig &GetConfig();

        ////////////////
        // Attributes //
        ////////////////
      private:
        ProjectConfig _Config;
        std::filesystem::path _ProjectDirectory;
        Ref<IAssetManager> _AssetManager;

        std::unordered_map<std::string, std::function<IComponentContainer *(Buffer)>> _ComponentFactory;
        std::unordered_map<std::string, std::function<ScriptableEntity *()>> _ScriptFactory;
        std::unordered_map<std::string, std::function<EntitySystem *()>> _SystemFactory;

        ///////////////////
        // Singletons... //
        ///////////////////
      private:
        inline static Ref<Project> _ActiveProject;
    };
}; // namespace Exodia

#endif /* !PROJECT_HPP_ */
