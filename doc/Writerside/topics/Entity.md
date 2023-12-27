# Entity

The Entity part of the ECS. It contains the classes that will be used to manage entities.

It defines the following classes:
- [**Entity**](#entity) : The Entity class is used to manage entities.
- [**EntityComponentIterator**](#entitycomponentiterator) : The EntityComponentIterator class is used to manage entity component iterators.
- [**EntityIterator**](#entityiterator) : The EntityIterator class is used to manage entity iterators.
- [**EntityView**](#entityview) : The EntityView class is used to manage entity views.
- [**EntityViewIterator**](#entityviewiterator) : The EntityViewIterator class is used to manage entity view iterators.


## Entity

The `Entity` class is used to manage entities.

### Constructor

```c++
Entity();
Entity(World *world, uint64_t id = UUID());
```

This creates a new `Entity`.

It takes the following parameters:

| Name  | Type     | Description  |
|-------|----------|--------------|
| world | World *  | The world    |
| id    | uint64_t | The id       |


Here is an example of how to use it :

```c++
Entity entity;
```

```c++
World *world;
uint64_t id;
Entity entity(world, id);
```

### AddComponent

```c++
template<typename Component, typename ...Args>
ComponentHandle<Component> Entity::AddComponent(Args && ...args)
```

This adds a component to the entity, and returns a handle to it.

It takes the following parameters:

| Name      | Type        | Description   |
|-----------|-------------|---------------|
| Component | typename    | The component |
| Args      | typename ...| The arguments |

Here is an example of how to use it :

```c++
Entity entity;
Component component;
ComponentHandle<Component> handle = entity.AddComponent(component);
```

### RemoveComponent

```c++
template<typename Component>
bool RemoveComponent()

bool RemoveComponent(IComponentContainer *component);
```

This removes a component from the entity.

It takes the following parameters:

| Name      | Type        | Description |
|-----------|-------------|-------------|
| Component | typename    | The component |

Here is an example of how to use it :

```c++
Entity entity;
bool result = entity.RemoveComponent<Component>();
```

```c++
Entity entity;
IComponentContainer *component;
bool result = entity.RemoveComponent(component);
```

### RemoveAllComponents

```c++
void RemoveAllComponents()
```

This removes all components from the entity.

Here is an example of how to use it :

```c++
Entity entity;
entity.RemoveAllComponents();
```

### CallFunctionWithComponents

```c++
template<typename ...Components>
bool CallFunctionWithComponents(typename std::common_type<std::function<void(ComponentHandle<Components>...)>>::type view) 
```

This calls a function with the components.

It takes the following parameters:

| Name       | Type                                                                                         | Description    |
|------------|----------------------------------------------------------------------------------------------|----------------|
| Components | typename ...                                                                                 | The components |
| view       | typename std::common_type\<std::function\<void\(ComponentHandle\<Components\>...\)\>\>::type | The view       |


Here is an example of how to use it :

```c++
Entity entity;
bool result = entity.CallFunctionWithComponents<Component>(view);
```

### Duplicate

```c++
Entity *Duplicate(World *world, UUID uuid, const std::string &name);
```

This duplicates the entity.

It takes the following parameters:

| Name   | Type                | Description  |
|--------|---------------------|--------------|
| world  | World *             | The world    |
| uuid   | UUID                | The uuid     |
| name   | const std::string & | The name     |

### GetWorld

```c++
World *GetWorld() const
```

This gets the world.

Here is an example of how to use it :

```c++
Entity entity;
World *world = entity.GetWorld();
```

### SetWorld

```c++
void SetWorld(World *world)
```

This sets the world.

It takes the following parameters:

| Name  | Type    | Description  |
|-------|---------|--------------|
| world | World * | The world    |

Here is an example of how to use it :

```c++
Entity entity;
World *world;
entity.SetWorld(world);
```

### HasComponent

```c++
template<typename Component>
bool HasComponent() const

template<typename Required, typename Additional, typename... Remaining>
bool HasComponent() const
```

This checks if the entity has a component.

It takes the following parameters:

| Name       | Type     | Description |
|------------|----------|-------------|
| Component  | typename | The component |
| Required   | typename | The required |
| Additional | typename | The additional |
| Remaining  | typename | The remaining |

Here is an example of how to use it :

```c++
Entity entity;
bool result = entity.HasComponent<Component>();
```

```c++
Entity entity;
bool result = entity.HasComponent<Required, Additional, Remaining>();
```

### GetComponent

```c++
template<typename Component>
ComponentHandle<Component> GetComponent() const
```

This gets a component.

It takes the following parameters:

| Name      | Type     | Description |
|-----------|----------|-------------|
| Component | typename | The component |

Here is an example of how to use it :

```c++
Entity entity;
ComponentHandle<Component> handle = entity.GetComponent<Component>();
```

### GetAllComponents

```c++
IComponentContainer *GetComponent(const std::string &index);
```

This gets all components.

It takes the following parameters:

| Name  | Type                | Description |
|-------|---------------------|-------------|
| index | const std::string & | The index   |

Here is an example of how to use it :

```c++
Entity entity;
std::string index;
IComponentContainer *component = entity.GetComponent(index);
```

### GetEntityID

```c++
uint64_t GetEntityID() const
```

This gets the entity id.

Here is an example of how to use it :

```c++
Entity entity;
uint64_t id = entity.GetEntityID();
```

### IsPendingDestroy

```c++
bool IsPendingDestroy() const
```

This checks if the entity is pending destroy.

Here is an example of how to use it :

```c++
Entity entity;
if (entity.IsPendingDestroy()) {
    // ...
}
```

### SetPendingDestroy

```c++
void SetPendingDestroy(bool pendingDestroy)
```

This sets the pending destroy.

It takes the following parameters:

| Name           | Type | Description     |
|----------------|------|-----------------|
| pendingDestroy | bool | The pending     |

Here is an example of how to use it :

```c++
Entity entity;
bool pendingDestroy;
entity.SetPendingDestroy(pendingDestroy);
```

## EntityComponentIterator

The `EntityComponentIterator` class is used to manage entity component iterators.

It's defined in the following template:
```c++
template<typename ...Components>
class EntityComponentIterator
```

### Constructor {id=constructor1}

```c++
EntityComponentIterator(World *world, size_t index, bool isEnd, bool includePendingDestroy)
```

This creates an entity component iterator.

It takes the following parameters:

| Name                  | Type    | Description                        |
|-----------------------|---------|------------------------------------|
| world                 | World * | The world                          |
| index                 | size_t  | The index                          |
| isEnd                 | bool    | If it is the end                   |
| includePendingDestroy | bool    | If it includes the pending destroy |

Here is an example of how to use it:

```c++
World *world;
size_t index;
bool isEnd;
bool includePendingDestroy;

EntityComponentIterator<Components...> iterator(world, index, isEnd, includePendingDestroy);
```

## GetIndex

```c++
size_t GetIndex() const
```

This gets the index.

Here is an example of how to use it:

```c++
EntityComponentIterator<Components...> iterator;
size_t index = iterator.GetIndex();
```

## IsEnd

```c++
bool IsEnd() const
```

This checks if it is the end.

Here is an example of how to use it:

```c++
EntityComponentIterator<Components...> iterator;

if (iterator.IsEnd()) {
    // ...
}
```

## IncludePendingDestroy

```c++
bool IncludePendingDestroy() const
```

This checks if it includes the pending destroy.

Here is an example of how to use it:

```c++
EntityComponentIterator<Components...> iterator;

if (iterator.IncludePendingDestroy()) {
    // ...
}
```

## GetWorld {id=getworld1}

```c++
World *GetWorld() const
```

This gets the world.

Here is an example of how to use it:

```c++
EntityComponentIterator<Components...> iterator;
World *world = iterator.GetWorld();
```

## Get

```c++
Entity *Get() const
```

This gets the entity.

Here is an example of how to use it:

```c++
EntityComponentIterator<Components...> iterator;
Entity *entity = iterator.Get();
```


## EntityIterator

The `EntityIterator` class is used to manage entity iterators.

His methods are the same as the `EntityComponentIterator` class.

## EntityView

The `EntityView` class is used to manage entity views.

## EntityViewIterator

The `EntityViewIterator` class is used to manage entity view iterators.

### Constructor {id=constructor2}

```c++
EntityView(const EntityIterator &first, const EntityIterator &last);
```

This creates an entity view.

It takes the following parameters:

| Name  | Type              | Description |
|-------|-------------------|-------------|
| first | const EntityIterator & | The first   |
| last  | const EntityIterator & | The last    |

Here is an example of how to use it:

```c++
EntityIterator first;
EntityIterator last;

EntityView view(first, last);
```

### begin

```c++
EntityViewIterator begin() const
```

This gets the beginning of the view.

Here is an example of how to use it:

```c++
EntityView view;
EntityViewIterator iterator = view.begin();
```

### end

```c++
EntityViewIterator end() const
```

This gets the end of the view.

Here is an example of how to use it:

```c++
EntityView view;
EntityViewIterator iterator = view.end();
```



