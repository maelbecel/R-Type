# ScriptableEntity

The ScriptableEntity part of the Script. It contains the classes that will be used to create scriptable entities.

It defines the class ScriptableEntity with the following methods:

## OnCreate

```c++
virtual void OnCreate();
```

It is called when the scriptable entity is created.

It can be used like this:

```c++
void OnCreate() override;
```

## OnDestroy

```c++
virtual void OnDestroy();
```

It is called when the scriptable entity is destroyed.

It can be used like this:

```c++
void OnDestroy() override;
```

## OnUpdate

```c++
virtual void OnUpdate(Timestep ts);
```

It is called when the scriptable entity updates.

It takes the following parameters:

| Name | Type   | Description |
|------|--------|-------------|
| ts   | Timestep | The ts      |

It can be used like this:

```c++
void OnUpdate(Timestep ts) override;
```

## OnCollisionEnter

```c++
virtual void OnCollisionEnter(Entity *other);
```

It is called when the scriptable entity collides with another entity.

It takes the following parameters:

| Name  | Type   | Description |
|-------|--------|-------------|
| other | Entity* | The other   |


It can be used like this:

```c++
void OnCollisionEnter(Entity *other) override;
```

## OnHoveredEnter

```c++
virtual void OnHoveredEnter();
```

It is called when the scriptable entity is hovered.

It can be used like this:

```c++
void OnHoveredEnter() override;
```

## OnHoveredExit

```c++
virtual void OnHoveredExit();
```

It is called when the scriptable entity is not hovered.

It can be used like this:

```c++
void OnHoveredExit() override;
```

## OnKeyPressed

```c++
virtual void OnKeyPressed(int keycode);
```

It is called when a key is pressed.

It takes the following parameters:

| Name    | Type | Description |
|---------|------|-------------|
| keycode | int  | The keycode |

It can be used like this:

```c++
void OnKeyPressed(int keycode) override;
```

## OnKeyReleased

```c++
virtual void OnKeyReleased(int keycode);
```

It is called when a key is released.

It takes the following parameters:

| Name   | Type | Description |
|--------|------|-------------|
| keycode | int  | The keycode |

It can be used like this:

```c++
void OnKeyReleased(int keycode) override;
```

## OnClick

```c++
virtual void OnClick()
```

It is called when the scriptable entity is clicked.

It can be used like this:

```c++
void OnClick() override;
```

## GetComponent

```c++
template <typename Component>
ComponentHandle<Component> GetComponent()
```

It gets the component.

It takes the following parameters:

| Name | Type | Description |
|------|------|-------------|
| Component | typename Component | The component |

It returns a ComponentHandle\<Component\>.

It can be used like this:

```c++
ComponentHandle<Component> component = GetComponent<Component>();
```

