# TagComponent

## Description

The `TagComponent` struct represents a tag component. It is used to identify the entity's tag in a scene.

## Properties

| Name | Type        | Description       |
|------|-------------|-------------------|
| Tag  | std::string | The entity's tag. |

## Methods

The `TagComponent` struct does not contain any methods.

## Usage

### Creating a tag component

To create a tag component, you can use the following code:

```c++
Entity *entity = _World->CreateEntity("Entity");
entity->AddComponent<TagComponent>();
```

### Getting an entity's tag

To get an entity's tag, you can use the following code:

```c++
TagComponent *tagComponent = entity->GetComponent<TagComponent>().Get();
std::string tag = tagComponent->Tag;
```

