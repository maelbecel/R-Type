# ScriptComponent

## Description

The `ScriptComponent` struct represents a script component. It is used to identify the entity's script in a scene.

## Properties

| Name              | Type                                    | Description                                           |
|-------------------|-----------------------------------------|-------------------------------------------------------|
| Instance          | ScriptableEntity*                       | The scriptable entity instance.                       |
| InstantiateScript | std::function\<ScriptableEntity*()\>    | The function that instantiates the scriptable entity. |
| DestroyScript     | std::function\<void(ScriptComponent*)\> | The function that destroys the scriptable entity.     |

## Methods

- ```c++
  template<typename T>
  void Bind()
  ```
  The `Bind()` function binds the scriptable entity to the script component.
  ```c++
  InstantiateScript = []() { return static_cast<ScriptableEntity*>(new T()); };
  DestroyScript = [](ScriptComponent *scriptComponent) { delete scriptComponent->Instance; scriptComponent->Instance = nullptr; };
  ```

## Usage

### Creating a script component

To create a script component, you can use the following code:

```c++
Entity *entity = _World->CreateEntity("Entity");
entity->AddComponent<ScriptComponent>();
```

### Binding a scriptable entity to a script component

To bind a scriptable entity to a script component, you can use the following code:

```c++
ScriptComponent *scriptComponent = entity->GetComponent<ScriptComponent>().Get();
scriptComponent->Bind<ScriptableEntity>();
```
