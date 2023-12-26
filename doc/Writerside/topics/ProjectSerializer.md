# ProjectSerializer

The ProjectSerializer part of the Project. It contains the classes that will be used to serialize a project.

## Constructor

```c++
ProjectSerializer(Ref<Project> project);
```

It initializes a new Serializer.

It takes the following parameters:

| Name     | Type           | Description |
|----------|----------------|-------------|
| project | Ref\<Project\> | The project |

It can be used like this:

```c++
Ref<Project> project = Project::New();
ProjectSerializer* projectSerializer = new ProjectSerializer(project);
```

## Serialize

```c++
bool Serialize(const std::filesystem::path &path);
```

It serializes the project.

It takes the following parameters:

| Name | Type | Description |
|------|------|-------------|
| path | const std::filesystem::path& | The path |

It can be used like this:

```c++
Ref<Project> project = Project::New();
ProjectSerializer* projectSerializer = new ProjectSerializer(project);
projectSerializer->Serialize("Project");
```

## Deserialize

```c++
bool Deserialize(const std::filesystem::path &path);
```

It deserializes the project.

It takes the following parameters:

| Name | Type | Description |
|------|------|-------------|
| path | const std::filesystem::path& | The path |

It can be used like this:

```c++
Ref<Project> project = Project::New();
ProjectSerializer* projectSerializer = new ProjectSerializer(project);
projectSerializer->Deserialize("Project");
```