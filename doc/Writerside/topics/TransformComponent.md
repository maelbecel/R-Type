# TransformComponent

## Description

The `TransformComponent` struct represents a transform component. It is used to identify the entity's transform in a scene.

## Properties

| Name     | Type        | Description                                                                 |
|----------|-------------|-----------------------------------------------------------------------------|
| Translation | glm::vec3   | The entity's translation.                                                   |
| Rotation    | glm::vec3   | The entity's rotation.                                                      |
| Scale       | glm::vec3   | The entity's scale.                                                         |


## Methods

- ```c++
  glm::mat4 GetTransform() const
  ```
  The `GetTransform()` function returns the entity's transform.

## Usage

### Creating a transform component

To create a transform component, you can use the following code:

```c++
Entity *entity = _World->CreateEntity("Entity");
entity->AddComponent<TransformComponent>();
```

### Getting an entity's transform

To get an entity's transform, you can use the following code:

```c++
TransformComponent *transformComponent = entity->GetComponent<TransformComponent>().Get();
glm::mat4 transform = transformComponent->GetTransform();
```

### Setting an entity's transform

To set an entity's transform, you can use the following code:

```c++
TransformComponent *transformComponent = entity->GetComponent<TransformComponent>().Get();
transformComponent->Translation = glm::vec3(0.0f, 0.0f, 0.0f);
transformComponent->Rotation = glm::vec3(0.0f, 0.0f, 0.0f);
transformComponent->Scale = glm::vec3(1.0f, 1.0f, 1.0f);
```

