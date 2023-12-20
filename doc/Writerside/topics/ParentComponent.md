# ParentComponent

## Description

The `ParentComponent` struct represents a parent component. It is used to identify the entity's parent in a scene.

## Properties

| Name   | Type | Description      |
|--------|------|------------------|
| Parent | UUID | The entity's ID. |

## Methods

The `ParentComponent` struct does not contain any methods.

## Usage

### Creating a parent component

To create a parent component, you can use the following code:

```c++
Entity *entity = _World->CreateEntity("Entity");
entity->AddComponent<ParentComponent>();
```

### Getting an entity's parent

To get an entity's parent, you can use the following code:

```c++
ParentComponent *parentComponent = entity->GetComponent<ParentComponent>().Get();
UUID parent = parentComponent->Parent;
```