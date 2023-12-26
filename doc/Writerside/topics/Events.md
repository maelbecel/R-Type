# Events

The Events part of the ECS. It contains the classes that will be used to manage events.

It defines the namespace Events that contains the classes that will be used to manage events :

- [**OnEntityCreated**](#onentitycreated) : The OnEntityCreated struct of the Events. It contains the classes that will be used to manage the OnEntityCreated event.
- [**OnEntityDestroyed**](#onentitydestroyed) : The OnEntityDestroyed struct of the Events. It contains the classes that will be used to manage the OnEntityDestroyed event.
- [**OnComponentAdded**](#oncomponentadded) : The OnComponentAdded struct of the Events. It contains the classes that will be used to manage the OnComponentAdded event.
- [**OnComponentAddedNoTemplate**](#oncomponentaddednotemplate) : The OnComponentAddedNoTemplate struct of the Events. It contains the classes that will be used to manage the OnComponentAddedNoTemplate event.
- [**OnComponentRemoved**](#oncomponentremoved) : The OnComponentRemoved struct of the Events. It contains the classes that will be used to manage the OnComponentRemoved event.
- [**OnComponentRemovedNoTemplate**](#oncomponentremovednotemplate) : The OnComponentRemovedNoTemplate struct of the Events. It contains the classes that will be used to manage the OnComponentRemovedNoTemplate event.
- [**OnCollisionEntered**](#oncollisionentered) : The OnCollisionEntered struct of the Events. It contains the classes that will be used to manage the OnCollisionEntered event.
- [**OnHoveredEnter**](#onhoveredenter) : The OnHoveredEnter struct of the Events. It contains the classes that will be used to manage the OnHoveredEnter event.
- [**OnHoveredExit**](#onhoveredexit) : The OnHoveredExit struct of the Events. It contains the classes that will be used to manage the OnHoveredExit event.
- [**OnClick**](#onclick) : The OnClicked struct of the Events. It contains the classes that will be used to manage the OnClick event.


## OnEntityCreated

The OnEntityCreated struct of the Events. It contains the classes that will be used to manage the OnEntityCreated event.

It contains the following elements:

| Name   | Type   | Description                 |
|--------|--------|-----------------------------|
| entity | Entity | The entity that was created |

Here is an example of how to use it:

```c++
Entity entity;
Events::OnEntityCreated event(entity);
```

## OnEntityDestroyed

The OnEntityDestroyed struct of the Events. It contains the classes that will be used to manage the OnEntityDestroyed event.

It contains the following elements:

| Name   | Type   | Description                   |
|--------|--------|-------------------------------|
| entity | Entity | The entity that was destroyed |

Here is an example of how to use it:

```c++
Entity entity;
Events::OnEntityDestroyed event(entity);
```

## OnComponentAdded

The OnComponentAdded struct of the Events. It contains the classes that will be used to manage the OnComponentAdded event.
It is in the following template:

```c++
template<typename Component>
struct OnComponentAdded
```

It contains the following elements:

| Name      | Type                         | Description                   |
|-----------|------------------------------|-------------------------------|
| entity    | Entity                       | The entity                    |
| component | ComponentHandle\<Component\> | The component that was added  |

Here is an example of how to use it:

```c++
Entity entity;
Component component;
Events::OnComponentAdded<Component> event(entity, component);
```

## OnComponentAddedNoTemplate

The OnComponentAddedNoTemplate struct of the Events. It contains the classes that will be used to manage the OnComponentAddedNoTemplate event.

It contains the following elements:

| Name          | Type        | Description                       |
|---------------|-------------|-----------------------------------|
| entity        | Entity      | The entity                        |
| componentType | std::string | The component type that was added |

Here is an example of how to use it:

```c++
Entity entity;
std::string componentType;
Events::OnComponentAddedNoTemplate event(entity, componentType);
```

## OnComponentRemoved

The OnComponentRemoved struct of the Events. It contains the classes that will be used to manage the OnComponentRemoved event.
It is in the following template:

```c++
template<typename Component>
struct OnComponentRemoved
```

It contains the following elements:

| Name      | Type                         | Description                      |
|-----------|------------------------------|----------------------------------|
| entity    | Entity                       | The entity                       |
| component | ComponentHandle\<Component\> | The component that was removed   |

Here is an example of how to use it:

```c++
Entity entity;
Component component;
Events::OnComponentRemoved<Component> event(entity, component);
```

## OnComponentRemovedNoTemplate

The OnComponentRemovedNoTemplate struct of the Events. It contains the classes that will be used to manage the OnComponentRemovedNoTemplate event.

It contains the following elements:

| Name          | Type        | Description                         |
|---------------|-------------|-------------------------------------|
| entity        | Entity      | The entity                          |
| componentType | std::string | The component type that was removed |

Here is an example of how to use it:

```c++
Entity entity;
std::string componentType;
Events::OnComponentRemovedNoTemplate event(entity, componentType);
```

## OnCollisionEntered

The OnCollisionEntered struct of the Events. It contains the classes that will be used to manage the OnCollisionEntered event.

It contains the following elements:

| Name    | Type   | Description        |
|---------|--------|--------------------|
| entityA | Entity | The first entity   |
| entityB | Entity | The second entity  |

Here is an example of how to use it:

```c++
Entity entityA;
Entity entityB;

Events::OnCollisionEntered event(entityA, entityB);
```

## OnHoveredEnter

The OnHoveredEnter struct of the Events. It contains the classes that will be used to manage the OnHoveredEnter event.

It contains the following elements:

| Name   | Type   | Description        |
|--------|--------|--------------------|
| entity | Entity | The entity         |

Here is an example of how to use it:

```c++
Entity entity;

Events::OnHoveredEnter event(entity);
```

## OnHoveredExit

The OnHoveredExit struct of the Events. It contains the classes that will be used to manage the OnHoveredExit event.

It contains the following elements:

| Name   | Type   | Description        |
|--------|--------|--------------------|
| entity | Entity | The entity         |

Here is an example of how to use it:

```c++
Entity entity;

Events::OnHoveredExit event(entity);
```

## OnClick

The OnClick struct of the Events. It contains the classes that will be used to manage the OnClick event.

It contains the following elements:

| Name   | Type   | Description        |
|--------|--------|--------------------|
| entity | Entity | The entity         |

Here is an example of how to use it:

```c++
Entity entity;

Events::OnClick event(entity);
```



