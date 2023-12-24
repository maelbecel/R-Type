# World

The World class of the ECS. It contains the classes that will be used to manage the world.

It defines multiple shortcuts to manage the world :

| using                   | type                                                                                                                                                 |
|-------------------------|------------------------------------------------------------------------------------------------------------------------------------------------------|
| WorldAllocator          | std::allocator_traits\<Allocator\>::template rebind_alloc\<World\>                                                                                   |
| SystemAllocator         | std::allocator_traits\<Allocator\>::template rebind_alloc\<EntitySystem\>                                                                            |
| SystemPtrAllocator      | std::allocator_traits\<Allocator\>::template rebind_alloc\<EntitySystem *\>                                                                          |
| EntityAllocator         | std::allocator_traits\<Allocator\>::template rebind_alloc\<Entity\>                                                                                  |
| EntityPtrAllocator      | std::allocator_traits\<Allocator\>::template rebind_alloc\<Entity *\>                                                                                |
| SubscriberPtrAllocator  | std::allocator_traits\<Allocator\>::template rebind_alloc\<IEventSubscriber *\>                                                                      |
| SubscriberPairAllocator | std::allocator_traits\<Allocator\>::template rebind_alloc\<std::pair\<const TypeIndex, std::vector\<IEventSubscriber *, SubscriberPtrAllocator\>\>\> |

## Constructor

```c++
World(Allocator allocator = Allocator());
```

It init a world;

It takes the following parameters:

| Name      | Type      | Description |
|-----------|-----------|-------------|
| allocator | Allocator | The allocator |


## CreateWorld

```c++
static World *CreateWorld(Allocator allocator = Allocator());
```

It creates a world.

It takes the following parameters:

| Name      | Type      | Description |
|-----------|-----------|-------------|
| allocator | Allocator | The allocator |

It returns a pointer to the world.

Here is an example of how to use it:

```c++
Allocator allocator;
World *world = World::CreateWorld(allocator);
```

## DestroyWorld

```c++
void DestroyWorld();
```

It destroys the world.

Here is an example of how to use it:

```c++
world->DestroyWorld();
```

## CreateEntity

```c++
Entity *CreateEntity(const std::string &name = std::string());
Entity *CreateEntity(const UUID &uuid, const std::string &name = std::string());
```

It creates an entity.

It takes the following parameters:

| Name | Type | Description |
|------|------|-------------|
| name | std::string & | The name |
| uuid | UUID & | The uuid |

It returns a pointer to the entity.

Here is an example of how to use it:

```c++
std::string name;
UUID uuid;
Entity *entity = world->CreateEntity(name);
```

## CreateNewEntity

```c++
Entity *CreateNewEntity(const std::string &name = std::string());
Entity *CreateNewEntity(const UUID &uuid, const std::string &name = std::string());
```

It creates a new entity.

It takes the following parameters:

| Name | Type | Description |
|------|------|-------------|
| name | std::string & | The name |
| uuid | UUID & | The uuid |

It returns a pointer to the entity.

Here is an example of how to use it:

```c++
std::string name;
UUID uuid;
Entity *entity = world->CreateNewEntity(name);
```

## DestroyEntity

```c++
void DestroyEntity(Entity *entity, bool immediate = false);
```

It destroys an entity.

It takes the following parameters:

| Name      | Type    | Description |
|-----------|---------|-------------|
| entity    | Entity * | The entity  |
| immediate | bool    | The immediate |

Here is an example of how to use it:

```c++
Entity *entity;
bool immediate;
world->DestroyEntity(entity, immediate);
```

## CleanUp

```c++
bool CleanUp();
```

It cleans up the world.

It returns a bool.

Here is an example of how to use it:

```c++
world->CleanUp();
```

## Reset

```c++
void Reset();
```

It resets the world.

Here is an example of how to use it:

```c++
world->Reset();
```

## RegisterSystem

```c++
EntitySystem *RegisterSystem(EntitySystem *system);
```

It registers a system.

It takes the following parameters:

| Name   | Type          | Description |
|--------|---------------|-------------|
| system | EntitySystem * | The system  |

It returns a pointer to the system.

Here is an example of how to use it:

```c++
EntitySystem *system;
world->RegisterSystem(system);
```

## UnregisterSystem

```c++
void UnregisterSystem(EntitySystem *system);
```

It unregisters a system.

It takes the following parameters:

| Name   | Type          | Description |
|--------|---------------|-------------|
| system | EntitySystem * | The system  |

Here is an example of how to use it:

```c++
EntitySystem *system;
world->UnregisterSystem(system);
```

## EnableSystem

```c++
void EnableSystem(EntitySystem *system);
```

It enables a system.

It takes the following parameters:

| Name   | Type          | Description |
|--------|---------------|-------------|
| system | EntitySystem * | The system  |

Here is an example of how to use it:

```c++
EntitySystem *system;
world->EnableSystem(system);
```

## DisableSystem

```c++
void DisableSystem(EntitySystem *system);
```

It disables a system.

It takes the following parameters:

| Name   | Type          | Description |
|--------|---------------|-------------|
| system | EntitySystem * | The system  |

Here is an example of how to use it:

```c++
EntitySystem *system;
world->DisableSystem(system);
```

## Subscribe

```c++
template<typename Event>
void Subscribe(EventSubscriber<Event> *subscriber)
```

It subscribes to an event.

It takes the following parameters:

| Name       | Type                       | Description |
|------------|----------------------------|-------------|
| subscriber | EventSubscriber\<Event\> * | The subscriber |

Here is an example of how to use it:

```c++
EventSubscriber<Event> *subscriber;

world->Subscribe(subscriber);
```

## Unsubscribe

```c++
template<typename Event>
void Unsubscribe(EventSubscriber<Event> *subscriber)
```

It unsubscribes to an event.

It takes the following parameters:
    
| Name       | Type                       | Description |
|------------|----------------------------|-------------|
| subscriber | EventSubscriber\<Event\> * | The subscriber |

Here is an example of how to use it:

```c++
EventSubscriber<Event> *subscriber;

world->Unsubscribe(subscriber);
```

## UnsubscribeAll

```c++
void UnsubscribeAll(void *subscriber);
```

It unsubscribes all the events.

It takes the following parameters:

| Name       | Type | Description |
|------------|------|-------------|
| subscriber | void * | The subscriber |

Here is an example of how to use it:

```c++
void *subscriber;

world->UnsubscribeAll(subscriber);
```

## Emit

```c++
template<typename Event>
void Emit(const Event &event)
```

It emits an event.

It takes the following parameters:

| Name  | Type | Description |
|-------|------|-------------|
| event | Event & | The event |

Here is an example of how to use it:

```c++
Event event;

world->Emit(event);
```

## ForEach

```c++
template<typename ...Entities>
void ForEach(typename std::common_type<std::function<void(Entity *, ComponentHandle<Entities>...)>>::type function, bool includePendingDestroy = false)
```

It iterates over entities.

It takes the following parameters:

| Name                  | Type                                                              | Description                 |
|-----------------------|-------------------------------------------------------------------|-----------------------------|
| function              | std::function\<void(Entity *, ComponentHandle\<Entities\>...)\> & | The function                |
| includePendingDestroy | bool                                                              | The include pending destroy |

Here is an example of how to use it:

```c++
World *world;

world->ForEach<Components...>({[](Entity *entity, ComponentHandle<Components>... components) {
    // ...
}});
```

## ForAll

```c++
void ForAll(std::function<void(Entity *)> function, bool includePendingDestroy = false);
```

It iterates over all entities.

It takes the following parameters:

| Name                  | Type                          | Description                 |
|-----------------------|-------------------------------|-----------------------------|
| function              | std::function<void(Entity *)> & | The function                |
| includePendingDestroy | bool                          | The include pending destroy |

Here is an example of how to use it:

```c++
World *world;

world->ForAll({[](Entity *entity) {
    // ...
}});
```

## AllEntities

```c++
EntityView AllEntities(bool includePendingDestroy = false);
```

It gets all the entities.

It takes the following parameters:

| Name                  | Type | Description                 |
|-----------------------|------|-----------------------------|
| includePendingDestroy | bool | The include pending destroy |

It returns an entity view.

Here is an example of how to use it:

```c++
World *world;

EntityView entityView = world->AllEntities();
```

## Update

```c++
void Update(Timestep ts);
```

It updates the world.

It takes the following parameters:

| Name | Type | Description |
|------|------|-------------|
| ts | Timestep | The timestep |

Here is an example of how to use it:

```c++
Timestep ts;

world->Update(ts);
```

## GetCount

```c++
uint64_t GetCount() const;
```

It gets the count.

It returns a uint64_t.

Here is an example of how to use it:

```c++
uint64_t count = world->GetCount();
```

## GetEntityByIndex

```c++
Entity *GetEntityByIndex(uint64_t index) const;
```

It gets an entity by index.

It takes the following parameters:

| Name  | Type | Description |
|-------|------|-------------|
| index | uint64_t | The index |

It returns a pointer to the entity.

Here is an example of how to use it:

```c++
uint64_t index;

Entity *entity = world->GetEntityByIndex(index);
```

## GetEntityByID

```c++
Entity *GetEntityByID(uint64_t id) const;
```

It gets an entity by id.

It takes the following parameters:  

| Name | Type | Description |
|------|------|-------------|
| id | uint64_t | The id |

It returns a pointer to the entity.

Here is an example of how to use it:

```c++
uint64_t id;

Entity *entity = world->GetEntityByID(id);
```

## GetEntityByTag

```c++
Entity *GetEntityByTag(const std::string &tag) const;
```

It gets an entity by tag.

It takes the following parameters:

| Name | Type | Description |
|------|------|-------------|
| tag | std::string & | The tag |

It returns a pointer to the entity.

Here is an example of how to use it:

```c++
std::string tag;

Entity *entity = world->GetEntityByTag(tag);
```

## GetPrimaryAllocator

```c++
EntityAllocator &GetPrimaryAllocator();
```

It gets the primary allocator.

It returns an entity allocator.

Here is an example of how to use it:

```c++
EntityAllocator &entityAllocator = world->GetPrimaryAllocator();
```




