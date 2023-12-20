# IDComponent

## Description

The `IDComponent` struct represents an ID component. It is used to identify entities in a scene.

## Properties

| Name | Type | Description      |
|------|------|------------------|
| ID   | UUID | The entity's ID. |

## Methods

The `IDComponent` struct does not contain any methods.

## Usage

### Creating an ID component

To create an ID component, you can use the following code:

```c++
Entity *entity = _World->CreateEntity("Entity");
entity->AddComponent<IDComponent>();
```

### Getting an entity's ID

To get an entity's ID, you can use the following code:

```c++
IDComponent *idComponent = entity->GetComponent<IDComponent>().Get();
UUID id = idComponent->ID;
```