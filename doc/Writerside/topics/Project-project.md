# Project

The Project class is the class that will be used to create a project.

It contains the following methods and structures:

## Constructor

```c++
Project();
```

It creates the Project.

It can be used like this:

```c++
Project* project = new Project();
```

## ProjectConfig

The ProjectConfig structure of the Project. It contains the classes that will be used to configure a project.

It contains the following properties:

| Name              | Type                  | Description                            |
|-------------------|-----------------------|----------------------------------------|
| Name              | std::string           | The name of the project                |
| StartScene        | AssetHandle           | The start scene of the project         |
| AssetsDirectory   | std::filesystem::path | The assets directory of the project    |
| AssetRegistryPath | std::filesystem::path | The asset registry path of the project |
| ScriptsDirectory  | std::filesystem::path | The scripts directory of the project   |

It can be used like this:

```c++
Project::ProjectConfig config;
config.Name = "Project";
config.StartScene = AssetHandle("Scene", "Assets/Scenes/Scene.scene");
```

## New

```c++
static Ref<Project> New();
```

It creates a new Project.

It can be used like this:

```c++
Ref<Project> project = Project::New();
```

## Load

```c++
static Ref<Project> Load(const std::filesystem::path &path);
```

It loads a Project.

It takes the following parameters:

| Name | Type                  | Description |
|------|-----------------------|-------------|
| path | std::filesystem::path | The path    |

It can be used like this:

```c++
Ref<Project> project = Project::Load("Project");
```

## SaveActive

```c++
static bool SaveActive(std::filesystem::path &path);
```

It saves the active Project.

It takes the following parameters:

| Name | Type                  | Description |
|------|-----------------------|-------------|
| path | std::filesystem::path | The path    |

It can be used like this:

```c++
Project::SaveActive("Project");
```

## GetProjectDirectory

```c++
const std::filesystem::path &GetProjectDirectory();
```

It gets the project directory.

It can be used like this:

```c++
std::filesystem::path projectDirectory = Project.GetProjectDirectory();
```

## GetAssetDirectory

```c++
std::filesystem::path GetAssetDirectory();
```

It gets the asset directory.

It can be used like this:

```c++
std::filesystem::path assetDirectory = Project.GetAssetDirectory();
```

## GetAssetFilePath

```c++
std::filesystem::path GetAssetFilePath(const std::filesystem::path &path);
```

It gets the asset file path.

It takes the following parameters:

| Name | Type                  | Description |
|------|-----------------------|-------------|
| path | std::filesystem::path | The path    |

It can be used like this:

```c++
std::filesystem::path assetFilePath = Project.GetAssetFilePath("Assets/Scenes/Scene.scene");
```

## GetAssetRegistryPath

```c++
std::filesystem::path GetAssetRegistryPath();
```

It gets the asset registry path.

It can be used like this:

```c++
std::filesystem::path assetRegistryPath = Project.GetAssetRegistryPath();
```

## GetAssetAbsolutePath

```c++
std::filesystem::path GetAssetAbsolutePath(const std::filesystem::path &path);
```

It gets the asset absolute path.

It takes the following parameters:

| Name | Type                  | Description |
|------|-----------------------|-------------|
| path | std::filesystem::path | The path    |

It can be used like this:

```c++
std::filesystem::path assetAbsolutePath = Project.GetAssetAbsolutePath("Assets/Scenes/Scene.scene");
```

## GetScriptPath

```c++
std::filesystem::path GetScriptPath();
```

It gets the script path.

It can be used like this:

```c++
std::filesystem::path scriptPath = Project.GetScriptPath();
```

## GetActiveProjectDirectory

```c++
static const std::filesystem::path &GetActiveProjectDirectory();
```

It gets the active project directory.

It can be used like this:

```c++
std::filesystem::path activeProjectDirectory = Project::GetActiveProjectDirectory();
```

## GetActiveAssetDirectory

```c++
static std::filesystem::path GetActiveAssetDirectory();
```

It gets the active asset directory.

It can be used like this:

```c++
std::filesystem::path activeAssetDirectory = Project::GetActiveAssetDirectory();
```

## GetActiveAssetFilePath

```c++
static std::filesystem::path GetActiveAssetFilePath(const std::filesystem::path &path);
```

It gets the active asset file path.

It takes the following parameters:

| Name | Type                  | Description |
|------|-----------------------|-------------|
| path | std::filesystem::path | The path    |

It can be used like this:

```c++
std::filesystem::path activeAssetFilePath = Project::GetActiveAssetFilePath("Assets/Scenes/Scene.scene");
```

## GetActiveAssetRegistryPath

```c++
static std::filesystem::path GetActiveAssetRegistryPath();
```

It gets the active asset registry path.

It can be used like this:

```c++
std::filesystem::path activeAssetRegistryPath = Project::GetActiveAssetRegistryPath();
```

## GetActiveScriptPath

```c++
static std::filesystem::path GetActiveScriptPath();
```

It gets the active script path.

It can be used like this:

```c++
std::filesystem::path activeScriptPath = Project::GetActiveScriptPath();
```

## GetActive

```c++
static Ref<Project> GetActive();
```

It gets the active Project.

It can be used like this:

```c++
Ref<Project> project = Project::GetActive();
```

## GetAssetManager

```c++
static Ref<IAssetManager> GetAssetManager() const;
```

It gets the asset manager.

It can be used like this:

```c++
Ref<IAssetManager> assetManager = Project.GetAssetManager();
```

## GetEditorAssetManager

```c++
static Ref<EditorAssetManager> GetEditorAssetManager() const;
```

It gets the editor asset manager.

It can be used like this:

```c++
Ref<EditorAssetManager> editorAssetManager = Project.GetEditorAssetManager();
```

## RegisterComponent

```c++
void RegisterComponent(std::string component, std::function<IComponentContainer *(Buffer)> factory);
```

It registers a component.

It takes the following parameters:

| Name      | Type                                             | Description |
|-----------|--------------------------------------------------|-------------|
| component | std::string                                      | The component |
| factory   | std::function\<IComponentContainer *\(Buffer\)\> | The factory   |

It can be used like this:

```c++
Project.RegisterComponent("TagComponent", [](Buffer buffer)
{
    return new TagComponent(buffer);
});
```

## GetComponentFactory

```c++
std::function<IComponentContainer *(Buffer)> GetComponentFactory(std::string component);
```

It gets the component factory.

It takes the following parameters:

| Name      | Type       | Description |
|-----------|------------|-------------|
| component | std::string | The component |

It can be used like this:

```c++
std::function<IComponentContainer *(Buffer)> componentFactory = Project.GetComponentFactory("TagComponent");
```

## GetConfig

```c++
ProjectConfig &GetConfig();
```

It gets the config.

It can be used like this:

```c++
ProjectConfig config = Project.GetConfig();
```
