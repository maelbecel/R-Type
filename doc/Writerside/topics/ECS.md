# ECS

The ECS part is used to manage the ECS.
An ECS is a system that manages entities, components and systems.
It is used to manage the game objects.

It contains the following parts:

- [**Component**](Component.md) : The Component part of the ECS. It contains the classes that will be used to manage components.
- [**Entity**]() : The Entity part of the ECS. It contains the classes that will be used to manage entities.
- [**System**]() : The System part of the ECS. It contains the classes that will be used to manage systems.
- [**Events**]() : The Event part of the ECS. It contains the classes that will be used to manage events.
- [**EventSubscriber**]() : The EventSubscriber part of the ECS. It contains the classes that will be used to manage event subscribers.
- [**Interface**]() : The Interface part of the ECS. It contains the classes that will be used to manage interfaces.
- [**World**]() : The World part of the ECS. It contains the classes that will be used to manage worlds.


It also has a [**Utils**]() part that contains the classes that will be used to manage utils.


## AddComponent

```c++
template<typename Component, typename ...Args>
ComponentHandle<Component> Entity::AddComponent(Args && ...args)
```

It adds a component to the entity, and returns a handle to it.

The method takes the following parameters:

| Name | Type | Description |
|------|------|-------------|
| Component | typename | The component |
| Args | typename ... | The arguments |

Here is an example of how to use it:

```c++
Entity entity;
Component component;
ComponentHandle<Component> handle = entity.AddComponent(component);
```

## GetComponent

```c++
template<typename Component>
ComponentHandle<Component> Entity::GetComponent()
```

It gets a component from the entity.

The method takes the following parameters:

| Name | Type | Description |
|------|------|-------------|
| Component | typename | The component |

Here is an example of how to use it:

```c++
Entity entity;
ComponentHandle<Component> handle = entity.GetComponent<Component>();
```

## EntityComponentIterator

```c++
template<typename ...Components>
EntityComponentIterator<Components...>::EntityComponentIterator(World *world, size_t index, bool isEnd, bool includePendingDestroy)
```

It creates an entity component iterator.

The constructor takes the following parameters:

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

## IsEnd

```c++
template<typename ...Components>
bool EntityComponentIterator<Components...>::IsEnd() const
```

It checks if it is the end.

Here is an example of how to use it:

```c++
EntityComponentIterator<Components...> iterator;

bool isEnd = iterator.IsEnd();
```

## Get

```c++
template<typename ...Components>
Entity EntityComponentIterator<Components...>::Get() const
```

It gets the entity.

Here is an example of how to use it:

```c++
EntityComponentIterator<Components...> iterator;

Entity entity = iterator.Get();
```

## operator++

```c++
template<typename ...Components>
EntityComponentIterator<Components...> &EntityComponentIterator<Components...>::operator++()
```

It increments the iterator.

Here is an example of how to use it:

```c++
EntityComponentIterator<Components...> iterator;

++iterator;
```
