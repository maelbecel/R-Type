# ChildrenComponent

## Description

The `ChildrenComponent` struct represents a children component. It is used to store the IDs of the entity's children.

## Properties

| Name     | Type                | Description                                                                 |
|----------|---------------------|-----------------------------------------------------------------------------|
| Children | std::vector\<UUID\> | A vector of UUIDs that represent the IDs of the entity's children.          |

## Methods

- ```c++
  void AddChild(UUID &childID);
  ```
    The `AddChild()` function adds a child to the entity. ```Children.push_back(childID);```
  
- ```c++
    void RemoveChild(UUID &childID);
    ```
    The `RemoveChild()` function removes a child from the entity.```Children.erase(std::remove(Children.begin(), Children.end(), childID), Children.end());```

- ```c++
  bool HasChild(UUID &childID);
  ```
  The `HasChild()` function checks whether the entity has a child with the specified ID.```return std::find(Children.begin(), Children.end(), childID) != Children.end();```


## Usage

### Creating a children component

To create a children component, you can use the following code:

```c++
Entity *entity = _World->CreateEntity("Entity");
entity->AddComponent<ChildrenComponent>();
```

### Adding a child to an entity

To add a child to an entity, you can use the following code:

```c++
ChildrenComponent *childrenComponent = entity->GetComponent<ChildrenComponent>().Get();
childrenComponent->AddChild(childID);
```

### Removing a child from an entity

To remove a child from an entity, you can use the following code:

```c++
ChildrenComponent *childrenComponent = entity->GetComponent<ChildrenComponent>().Get();
childrenComponent->RemoveChild(childID);
```

### Checking whether an entity has a child

To check whether an entity has a child, you can use the following code:

```c++
ChildrenComponent *childrenComponent = entity->GetComponent<ChildrenComponent>().Get();
bool hasChild = childrenComponent->HasChild(childID);
```
