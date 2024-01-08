/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** Project
*/

// Exodia Project includes
#include "Project.hpp"
#include "Project/ProjectSerializer.hpp"

// Exodia ECS includes
#include "Scene/SceneHeaders.hpp"
#include "Exodia-ECS.hpp"

// Exodia Script includes
#include "Script/Interface/ScriptableEntity.hpp"

// Exodia Utils includes
#include "Exodia-Debug.hpp"

namespace Exodia {

    //////////////////////////////
    // Constructor & Destructor //
    //////////////////////////////

    Project::Project() {
        // -- Registering the component factories -- //
        RegisterComponent("IDComponent", [](Buffer data) -> IComponentContainer * {
            return new ComponentContainer<IDComponent>(data);
        });

        RegisterComponent("TagComponent", [](Buffer data) -> IComponentContainer * {
            return new ComponentContainer<TagComponent>(data);
        });

        RegisterComponent("TransformComponent", [](Buffer data) -> IComponentContainer * {
            return new ComponentContainer<TransformComponent>(data);
        });

        RegisterComponent("CameraComponent", [](Buffer data) -> IComponentContainer * {
            return new ComponentContainer<CameraComponent>(data);
        });

        RegisterComponent("RigidBody2DComponent", [](Buffer data) -> IComponentContainer * {
            return new ComponentContainer<RigidBody2DComponent>(data);
        });

        RegisterComponent("BoxCollider2DComponent", [](Buffer data) -> IComponentContainer * {
            return new ComponentContainer<BoxCollider2DComponent>(data);
        });

        RegisterComponent("CircleCollider2DComponent", [](Buffer data) -> IComponentContainer * {
            return new ComponentContainer<CircleCollider2DComponent>(data);
        });

        RegisterComponent("ChildrenComponent", [](Buffer data) -> IComponentContainer * {
            return new ComponentContainer<ChildrenComponent>(data);
        });

        RegisterComponent("ParentComponent", [](Buffer data) -> IComponentContainer * {
            return new ComponentContainer<ParentComponent>(data);
        });

        RegisterComponent("SpriteRendererComponent", [](Buffer data) -> IComponentContainer * {
            return new ComponentContainer<SpriteRendererComponent>(data);
        });

        RegisterComponent("CircleRendererComponent", [](Buffer data) -> IComponentContainer * {
            return new ComponentContainer<CircleRendererComponent>(data);
        });

        RegisterComponent("TextRendererComponent", [](Buffer data) -> IComponentContainer * {
            return new ComponentContainer<TextRendererComponent>(data);
        });

        RegisterComponent("ScriptComponent", [](Buffer data) -> IComponentContainer * {
            return new ComponentContainer<ScriptComponent>(data);
        });

        RegisterComponent("SoundComponent", [](Buffer data) -> IComponentContainer * {
            return new ComponentContainer<SoundComponent>(data);
        });

        RegisterComponent("MusicComponent", [](Buffer data) -> IComponentContainer * {
            return new ComponentContainer<MusicComponent>(data);
        });

        RegisterComponent("ParticleComponent", [](Buffer data) -> IComponentContainer * {
            return new ComponentContainer<ParticleComponent>(data);
        });

        // -- Registering the script factories -- //

        // ...

        // -- Registering the system factories -- //

        RegisterSystem("CollisionSystem", []() -> EntitySystem * { return new CollisionSystem(); });

        RegisterSystem("ScriptSystem", []() -> EntitySystem * { return new ScriptSystem(); });

        RegisterSystem("GravitySystem", []() -> EntitySystem * { return new GravitySystem(); });

        RegisterSystem("MovingSystem", []() -> EntitySystem * { return new MovingSystem(); });
    }

    /////////////
    // Methods //
    /////////////

    Ref<Project> Project::New() {
        _ActiveProject = CreateRef<Project>();

        return _ActiveProject;
    }

    Ref<Project> Project::Load(const std::filesystem::path &path) {
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

    bool Project::SaveActive(const std::filesystem::path &path) {
        ProjectSerializer serializer(_ActiveProject);

        if (!serializer.Serialize(path))
            return false;
        _ActiveProject->_ProjectDirectory = path.parent_path();
        return true;
    }

    ///////////////////////
    // Getters & Setters //
    ///////////////////////

    const std::filesystem::path &Project::GetProjectDirectory() { return _ProjectDirectory; }

    std::filesystem::path Project::GetAssetDirectory() {
        EXODIA_CORE_ASSERT(_ActiveProject, "Project::GetAssetDirectory() - No active project !");

        return GetProjectDirectory() / _ActiveProject->_Config.AssetsDirectory;
    }

    std::filesystem::path Project::GetAssetFilePath(const std::filesystem::path &path) {
        return GetAssetDirectory() / path;
    }

    std::filesystem::path Project::GetAssetRegistryPath() {
        EXODIA_CORE_ASSERT(_ActiveProject, "Project::GetAssetRegistryPath() - No active project !");

        return GetAssetDirectory() / _ActiveProject->_Config.AssetRegistryPath;
    }

    std::filesystem::path Project::GetAssetAbsolutePath(const std::filesystem::path &path) {
        return GetAssetDirectory() / path;
    }

    std::filesystem::path Project::GetScriptPath() {
        return GetAssetDirectory() / _ActiveProject->_Config.ScriptsDirectory;
    }

    const std::filesystem::path &Project::GetActiveProjectDirectory() {
        EXODIA_CORE_ASSERT(_ActiveProject, "Project::GetActiveProjectDirectory() - No active project !");

        return _ActiveProject->GetProjectDirectory();
    }

    std::filesystem::path Project::GetActiveAssetDirectory() {
        EXODIA_CORE_ASSERT(_ActiveProject, "Project::GetAssetDirectory() - No active project !");

        return _ActiveProject->GetAssetDirectory();
    }

    std::filesystem::path Project::GetActiveAssetFilePath(const std::filesystem::path &path) {
        EXODIA_CORE_ASSERT(_ActiveProject, "Project::GetAssetFilePath() - No active project !");

        return _ActiveProject->GetAssetFilePath(path);
    }

    std::filesystem::path Project::GetActiveAssetRegistryPath() {
        EXODIA_CORE_ASSERT(_ActiveProject, "Project::GetAssetRegistryPath() - No active project !");

        return _ActiveProject->GetAssetRegistryPath();
    }

    std::filesystem::path Project::GetActiveScriptPath() {
        EXODIA_CORE_ASSERT(_ActiveProject, "Project::GetScriptPath() - No active project !");

        return _ActiveProject->GetScriptPath();
    }

    Ref<Project> Project::GetActive() { return _ActiveProject; }

    Ref<IAssetManager> Project::GetAssetManager() const { return _AssetManager; }

    Ref<EditorAssetManager> Project::GetEditorAssetManager() const {
        return std::static_pointer_cast<EditorAssetManager>(_AssetManager);
    }

    ProjectConfig &Project::GetConfig() { return _Config; }

    void Project::RegisterComponent(std::string component, std::function<IComponentContainer *(Buffer)> factory) {
        if (_ComponentFactory.find(component) != _ComponentFactory.end()) {
            EXODIA_CORE_WARN("Project::RegisterComponent() - Component factory already exists !");

            return;
        }

        _ComponentFactory[component] = factory;
    }

    std::function<IComponentContainer *(Buffer)> Project::GetComponentFactory(std::string component) {
        auto it = _ComponentFactory.find(component);

        if (it == _ComponentFactory.end())
            return nullptr;
        return it->second;
    }

    void Project::RegisterScript(std::string script, std::function<ScriptableEntity *()> factory) {
        if (_ScriptFactory.find(script) != _ScriptFactory.end()) {
            EXODIA_CORE_WARN("Project::RegisterScript() - Script factory already exists !");

            return;
        }

        _ScriptFactory[script] = factory;
    }

    std::function<ScriptableEntity *()> Project::GetScriptFactory(std::string script) {
        auto it = _ScriptFactory.find(script);

        if (it == _ScriptFactory.end())
            return nullptr;
        return it->second;
    }

    void Project::RegisterSystem(std::string system, std::function<EntitySystem *()> factory) {
        if (_SystemFactory.find(system) != _SystemFactory.end()) {
            EXODIA_CORE_WARN("Project::RegisterSystem() - System factory already exists !");

            return;
        }

        _SystemFactory[system] = factory;
    }

    std::function<EntitySystem *()> Project::GetSystemFactory(std::string system) {
        auto it = _SystemFactory.find(system);

        if (it == _SystemFactory.end())
            return nullptr;
        return it->second;
    }
}; // namespace Exodia
