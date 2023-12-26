# GravitySystem

## Description

The GravitySystem is a system that handles gravity. It contains the gravity's data.

## Methods

### Update
```c++
void Update(World *world, Timestep ts)
```

It takes the following parameters:

- `World *world` : A pointer to the world.
- `Timestep ts` : The timestep.

The Update method is called every frame. It updates the gravity's data.

### ApplyGravity
```c++
    void ApplyGravity(ComponentHandle<RigidBody2DComponent> rigidBody, Timestep ts);
```

It takes the following parameters:

- `ComponentHandle<RigidBody2DComponent> rigidBody` : The rigidbody.
- `Timestep ts` : The timestep.

This method is used to apply gravity to an entity.

## Usage

### Create a GravitySystem

To create a GravitySystem, you can use the following code:

```c++
World->RegisterSystem(new GravitySystem());
```

### Create a GravitySystem with a custom gravity

To create a GravitySystem with a custom gravity, you can use the following code:

```c++
World->RegisterSystem(new GravitySystem(-3.Of));
```