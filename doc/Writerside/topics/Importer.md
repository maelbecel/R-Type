# Importer

The Importer is the part of the Asset that will be used to import all.

He is divided in the 3 following parts :

- [**AssetImporter**](#assetimporter) : The Importer part of the Importer. It contains the classes that will be used to import assets.
- [**SceneImporter**](#sceneimporter) : The Scene part of the Importer. It contains the classes that will be used to import scenes.
- [**TextureImporter**](#textureimporter) : The Texture part of the Importer. It contains the classes that will be used to import textures.


## AssetImporter

The AssetImporter class is used to import assets.

### ImportAsset

```c++
static Ref<Asset> ImportAsset(AssetHandle handle, const AssetSpecification &spec);
```

It imports an asset.

The method takes the following parameters:

| Name   | Type               | Description             |
|--------|--------------------|-------------------------|
| handle | AssetHandle        | The asset handle        |
| spec   | AssetSpecification | The asset specification |

Here is an example of how to use it:

```c++
AssetHandle handle;
AssetSpecification spec;
Ref<Asset> asset = AssetImporter::ImportAsset(handle, spec);
```

## SceneImporter

The SceneImporter class is used to import scenes.

### ImportScene

```c++
static Ref<Scene> ImportScene(AssetHandle handle, const AssetSpecification &spec);
```

It imports a scene.

The method takes the following parameters:

| Name   | Type               | Description             |
|--------|--------------------|-------------------------|
| handle | AssetHandle        | The asset handle        |
| spec   | AssetSpecification | The asset specification |

Here is an example of how to use it:

```c++
AssetHandle handle;
AssetSpecification spec;
Ref<Scene> scene = SceneImporter::ImportScene(handle, spec);
```

### LoadScene

```c++
static Ref<Scene> LoadScene(const std::filesystem::path &path);
```

It loads a scene from a file.

The method takes the following parameters:

| Name | Type                     | Description        |
|------|--------------------------|--------------------|
| path | std::filesystem::path    | The path           |

Here is an example of how to use it:

```c++
std::filesystem::path path;
Ref<Scene> scene = SceneImporter::LoadScene(path);
```

### SaveScene

```c++
static void SaveScene(const Ref<Scene> &scene, const std::filesystem::path &path);
```

It saves a scene to a file.

The method takes the following parameters:

| Name  | Type                  | Description        |
|-------|-----------------------|--------------------|
| scene | Ref\<Scene\>          | The scene          |
| path  | std::filesystem::path | The path           |

Here is an example of how to use it:

```c++
Ref<Scene> scene;
std::filesystem::path path;
SceneImporter::SaveScene(scene, path);
```

## TextureImporter

### ImportTexture2D

```c++
static Ref<Texture2D> ImportTexture2D(AssetHandle handle, const AssetSpecification &spec);
```

It imports a 2D texture.

The method takes the following parameters:

| Name   | Type               | Description             |
|--------|--------------------|-------------------------|
| handle | AssetHandle        | The asset handle        |
| spec   | AssetSpecification | The asset specification |

Here is an example of how to use it:

```c++
AssetHandle handle;
AssetSpecification spec;
Ref<Texture2D> texture = TextureImporter::ImportTexture2D(handle, spec);
```

### LoadTexture2D

```c++
static Ref<Texture2D> LoadTexture2D(const std::filesystem::path &path);
```

It loads a 2D texture from a file.

The method takes the following parameters:

| Name | Type                     | Description        |
|------|--------------------------|--------------------|
| path | std::filesystem::path    | The path           |

Here is an example of how to use it:

```c++
std::filesystem::path path;
Ref<Texture2D> texture = TextureImporter::LoadTexture2D(path);
```








