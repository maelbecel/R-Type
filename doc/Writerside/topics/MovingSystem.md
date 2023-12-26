# MovingSystem

## Description

The MovingSystem is a system that handles the movement of entities. It contains the movement's data.

## Methods

### Update
```c++
void Update(World *world, Timestep ts)
```

It takes the following parameters:

- `World *world` : A pointer to the world.
- `Timestep ts` : The timestep.

The Update method is called every frame. It updates the movement's data.

### ApplyVelocity
```c++
   void ApplyVelocity(ComponentHandle<RigidBody2DComponent> rigidBody, ComponentHandle<TransformComponent> transform, Timestep ts);
```

It takes the following parameters:

- `ComponentHandle<RigidBody2DComponent> rigidBody` : The rigidbody.
- `ComponentHandle<TransformComponent> transform` : The transform.
- `Timestep ts` : The timestep.

This method is used to apply velocity to an entity, based on its rigidbody and transform.

## Usage

### Create a MovingSystem

To create a MovingSystem, you can use the following code:

```c++
World->RegisterSystem(new MovingSystem());
```

### Create a MovingSystem with a custom gravity

To create a MovingSystem with a custom gravity, you can use the following code:

```c++
World->RegisterSystem(new MovingSystem(3.Of));
```