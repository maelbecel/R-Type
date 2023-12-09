/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** Project
*/

#ifndef PROJECT_HPP_
    #define PROJECT_HPP_

    // Exodia Asset includes
    #include "Asset/Manager/RuntimeAssetManager.hpp"
    #include "Asset/Manager/EditorAssetManager.hpp"

    // Exodia Utils includes
    #include "Utils/Memory.hpp"

    // External includes
    #include <filesystem>

namespace Exodia {

    struct ProjectConfig {
        std::string Name = "Untitled";

        std::filesystem::path StartScene;
        std::filesystem::path AssetsDirectory;
        std::filesystem::path AssetRegistryPath;
        std::filesystem::path ScriptsDirectory;
    };

    class Project {

        //////////////////////////////
        // Constructor & Destructor //
        //////////////////////////////
        public:

            Project() = default;
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

            static const std::filesystem::path &GetProjectDirectory();
            static std::filesystem::path        GetAssetDirectory();
            static std::filesystem::path        GetAssetFilePath(const std::filesystem::path &path);
            static std::filesystem::path        GetAssetRegistryPath();
            static Ref<Project>                 GetActive();

            Ref<IAssetManager>       GetAssetManager()        const;
            Ref<RuntimeAssetManager> GetRuntimeAssetManager() const;
            Ref<EditorAssetManager>  GetEditorAssetManager()  const;

            ProjectConfig &GetConfig();
        
        ////////////////
        // Attributes //
        ////////////////
        private:

            ProjectConfig         _Config;
            std::filesystem::path _ProjectDirectory;
            Ref<IAssetManager>    _AssetManager;

        ///////////////////
        // Singletons... //
        ///////////////////
        private:

            inline static Ref<Project> _ActiveProject;
    };
};

#endif /* !PROJECT_HPP_ */
