# SceneSerializer

The SceneSerializer part of the Scene. It contains the classes that will be used to create scenes serializers.

It defines the class SceneSerializer with the following methods:

## Constructor

```c++
SceneSerializer(const Ref<Scene> scene);
```

It constructs the SceneSerializer.

It takes the following parameters:

| Name  | Type         | Description |
|-------|--------------|-------------|
| scene | const Ref<Scene> | The scene   |

It can be used like this:

```c++
SceneSerializer sceneSerializer(scene);
```

## Serialize

```c++
void Serialize(const std::filesystem::path &path);
```

It serializes the scene.

It takes the following parameters:

| Name | Type | Description |
|------|------|-------------|
| path | const std::filesystem::path& | The path    |

It can be used like this:

```c++
sceneSerializer.Serialize(path);
```

## Deserialize

```c++
void Deserialize(const std::filesystem::path &path);
```

It deserializes the scene.

It takes the following parameters:

| Name | Type | Description |
|------|------|-------------|
| path | const std::filesystem::path& | The path    |

It can be used like this:

```c++
sceneSerializer.Deserialize(path);
```



