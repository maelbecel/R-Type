# Scene

The Scene part of the Renderer. It contains the classes that will be used to create scenes.

The `Scene` class herits for the `Asset` class.

It defines the class `Scene`.

```mermaid
Graph TD;
    Asset --> Scene;
```

It contains the following  methods:

## Constructor

```c++
Scene(const std::string& name = "Scene");
```

It constructs the Scene.

It takes the following parameters:

| Name | Type | Description |
|------|------|-------------|
| name | const std::string& | The name    |

It can be used like this:

```c++
Scene scene;
```

## Copy

```c++
static Ref<Scene> Copy(const Ref<Scene> other);
```

It copies the scene.

It takes the following parameters:

| Name  | Type         | Description |
|-------|--------------|-------------|
| other | const Ref<Scene>& | The other  |

It returns a Ref<Scene>.

It can be used like this:

```c++
Ref<Scene> scene = Scene::Copy(other);
```

## CreateEntity

```c++
Entity *CreateEntity(const std::string &name = std::string());
```

It creates an entity.

It takes the following parameters:

| Name | Type               | Description |
|------|--------------------|-------------|
| name | const std::string& | The name    |

It returns a pointer to an Entity.

It can be used like this:

```c++
Entity *entity = scene->CreateEntity(name);
```

## CreateEntityWithUUID

```c++
Entity *CreateEntityWithUUID(UUID uuid, const std::string &name);
```

The CreateEntityWithUUID method is used to create an entity with a UUID.

It takes the following parameters:

| Name | Type  | Description |
|------|-------|-------------|
| uuid | UUID  | The uuid    |
| name | std::string & | name        |

It returns a pointer to an Entity.

It can be used like this:

```c++
Entity *entity = scene->CreateEntityWithUUID(uuid, name);
```

## DuplicateEntity

```c++
Entity *DuplicateEntity(Entity *entity);
```

It duplicates an entity.

It takes the following parameters:

| Name   | Type   | Description |
|--------|--------|-------------|
| entity | Entity* | The entity  |

It returns a pointer to an Entity.

It can be used like this:

```c++
Entity *entity = scene->DuplicateEntity(entity);
```

## DestroyEntity

```c++
void DestroyEntity(Entity *entity);
```

It destroys an entity.

It takes the following parameters:

| Name   | Type   | Description |
|--------|--------|-------------|
| entity | Entity* | The entity  |

It can be used like this:

```c++
scene->DestroyEntity(entity);
```

## OnRuntimeStart

```c++
void OnRuntimeStart();
```

It is called when the runtime starts.

It can be used like this:

```c++
scene->OnRuntimeStart();
```

## OnRuntimeStop

```c++
void OnRuntimeStop();
```

It is called when the runtime stops.

It can be used like this:

```c++
scene->OnRuntimeStop();
```

## OnUpdateRuntime

```c++
void OnUpdateRuntime(Timestep ts);
```

It is called when the runtime updates.

It takes the following parameters:

| Name | Type   | Description |
|------|--------|-------------|
| ts   | Timestep | The ts      |

It can be used like this:

```c++
scene->OnUpdateRuntime(ts);
```

## OnUpdateEditor

```c++
void OnUpdateEditor(Timestep ts, EditorCamera &camera);
```

It is called when the editor updates.

It takes the following parameters:

| Name   | Type         | Description |
|--------|--------------|-------------|
| ts     | Timestep     | The ts      |
| camera | EditorCamera | The camera  |

It can be used like this:

```c++
scene->OnUpdateEditor(ts, camera);
```

## OnViewportResize

```c++
void OnViewportResize(uint32_t width, uint32_t height);
```

It is called when the viewport resizes.

It takes the following parameters:

| Name   | Type     | Description |
|--------|----------|-------------|
| width  | uint32_t | The width   |
| height | uint32_t | The height  |

It can be used like this:

```c++
scene->OnViewportResize(width, height);
```

## ForEach

```c++
template <typename... Components>
void ForEach(typename std::common_type<std::function<void(Entity *, ComponentHandle<Components>...)>>::type function,
             bool includePendingDestroy = false)
```

It iterates through the entities.

It takes the following parameters:

| Name                   | Type                                                                 | Description |
|------------------------|----------------------------------------------------------------------|-------------|
| function               | typename std::common_type\<std::function\<void(Entity \*, ComponentHandle\<Components\>...)\>\>::type | The function |
| includePendingDestroy | bool                                                                 | The include pending destroy |

It can be used like this:

```c++
scene->ForEach<Components...>([](Entity *entity, ComponentHandle<Components>... components) {
    // ...
});
```

## RegisterSystem

```c++
void RegisterSystem(EntitySystem *system);
```

It registers a system.

It takes the following parameters:

| Name   | Type         | Description |
|--------|--------------|-------------|
| system | EntitySystem | The system  |

It can be used like this:

```c++
scene->RegisterSystem(system);
```

## Subscribe

```c++
template <typename Event>
void Subscribe(EventSubscriber<Event> *subscriber)
```

It subscribes to an event.

It takes the following parameters:

| Name       | Type                    | Description |
|------------|-------------------------|-------------|
| subscriber | EventSubscriber\<Event\> | The subscriber |

It can be used like this:

```c++
scene->Subscribe<event>(subscriber);
```

## GetName

```c++
const std::string &GetName() const;
```

It gets the name of the scene.

It returns a const std::string&.

It can be used like this:

```c++
std::string name = scene->GetName();
```

## SetName

```c++
void SetName(const std::string &name);
```

It sets the name of the scene.

It takes the following parameters:

| Name | Type               | Description |
|------|--------------------|-------------|
| name | const std::string& | The name    |

It can be used like this:

```c++
scene->SetName(name);
```

## GetWorld

```c++
World &GetWorld() const;
```

It gets the world of the scene.

It returns a World&.

It can be used like this:

```c++
World world = scene->GetWorld();
```

## GetWorldPtr

```c++
World *GetWorldPtr() const;
```

It gets the world pointer of the scene.

It returns a World*.

It can be used like this:

```c++
World *world = scene->GetWorldPtr();
```

## GetPrimaryCamera

```c++
Entity *GetPrimaryCamera() const;
```

It gets the primary camera of the scene.

It returns a pointer to an Entity.

It can be used like this:

```c++
Entity *entity = scene->GetPrimaryCamera();
```

## GetEntityByName

```c++
Entity *GetEntityByName(const std::string &name);
```

It gets an entity by its name.

It takes the following parameters:

| Name | Type               | Description |
|------|--------------------|-------------|
| name | const std::string& | The name    |

It returns a pointer to an Entity.

It can be used like this:

```c++
Entity *entity = scene->GetEntityByName(name);
```

## GetEntityByUUID

```c++
Entity *GetEntityByUUID(UUID uuid);
```

It gets an entity by its UUID.

It takes the following parameters:

| Name | Type | Description |
|------|------|-------------|
| uuid | UUID | The uuid    |

It returns a pointer to an Entity.

It can be used like this:

```c++
Entity *entity = scene->GetEntityByUUID(uuid);
```

## IsRunning

```c++
bool IsRunning() const;
```

It returns if the scene is running.

It returns a bool.

It can be used like this:

```c++
bool running = scene->IsRunning();
```

## IsPaused

```c++
bool IsPaused() const;
```

It returns if the scene is paused.

It returns a bool.

It can be used like this:

```c++
bool paused = scene->IsPaused();
```

## SetPaused

```c++
void SetPaused(bool paused);
```

It sets the paused of the scene.

It takes the following parameters:

| Name   | Type | Description |
|--------|------|-------------|
| paused | bool | The paused  |

It can be used like this:

```c++
scene->SetPaused(paused);
```

## GetType

```c++
virtual AssetType GetType() const override;
```

It gets the type of the scene.

It returns an AssetType.

It can be used like this:

```c++
AssetType assetType = scene->GetType();
```





