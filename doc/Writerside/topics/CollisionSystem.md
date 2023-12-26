# CollisionSystem

## Description

The CollisionSystem is a system that handles collisions between entities. It contains the collision's data.

## Methods

### Update
```c++
void Update(World *world, Timestep ts)
```

It takes the following parameters:

- `World *world` : A pointer to the world.
- `Timestep ts` : The timestep.


This method is called every frame. It updates the collision's data.

### Recieve
```c++
void Receive(World *world, const Events::OnCollisionEntered &event)
```

It takes the following parameters:

- `World *world` : A pointer to the world.
- `const Events::OnCollisionEntered &event` : The event.

This method is called when a collision between two entities is detected. It updates the collision's data.

### CheckCollision
```c++
    bool CheckCollision(ComponentHandle<BoxCollider2DComponent> collider1, ComponentHandle<TransformComponent> transform1, ComponentHandle<BoxCollider2DComponent> collider2, ComponentHandle<TransformComponent> transform2);
    bool CheckCollision(ComponentHandle<BoxCollider2DComponent> collider1, ComponentHandle<TransformComponent> transform1, ComponentHandle<CircleCollider2DComponent> collider2, ComponentHandle<TransformComponent> transform2);
    bool CheckCollision(ComponentHandle<CircleCollider2DComponent> collider1, ComponentHandle<TransformComponent> transform1, ComponentHandle<CircleCollider2DComponent> collider2, ComponentHandle<TransformComponent> transform2);
    bool CheckCollision(ComponentHandle<CircleCollider2DComponent> collider1, ComponentHandle<TransformComponent> transform1, ComponentHandle<BoxCollider2DComponent> collider2, ComponentHandle<TransformComponent> transform2);
```

It takes the following parameters:
- `ComponentHandle<BoxCollider2DComponent> collider1` : The first collider.
- `ComponentHandle<TransformComponent> transform1` : The first transform.
- `ComponentHandle<BoxCollider2DComponent> collider2` : The second collider.
- `ComponentHandle<TransformComponent> transform2` : The second transform.
- `ComponentHandle<CircleCollider2DComponent> collider1` : The first collider.
- `ComponentHandle<TransformComponent> transform1` : The first transform.
- `ComponentHandle<CircleCollider2DComponent> collider2` : The second collider.
- `ComponentHandle<TransformComponent> transform2` : The second transform.
- `ComponentHandle<CircleCollider2DComponent> collider1` : The first collider.

These methods are used to check if two entities are colliding. They return true if they are colliding, false otherwise.


### CalculateTransformedBoundingBox

```c++
    BoundingBox CalculateTransformedBoundingBox(const BoxCollider2DComponent &collider, const TransformComponent &transform);
```

It takes the following parameters:
- `const BoxCollider2DComponent &collider` : The collider.
- `const TransformComponent &transform` : The transform.

This method is used to calculate the bounding box of an entity. It returns the bounding box.

### IntersectBoundingBoxes

```c++
    bool IntersectBoundingBoxes(const BoundingBox &box1, const BoundingBox &box2);
```

It takes the following parameters:
- `const BoundingBox &box1` : The first bounding box.
- `const BoundingBox &box2` : The second bounding box.

This method is used to check if two bounding boxes are intersecting. It returns true if they are intersecting, false otherwise.

### EmitOnCollisionEnterEvent

```c++
    void EmitOnCollisionEnterEvent(Entity *entityA, Entity *entityB);
```

It takes the following parameters:
- `Entity *entityA` : The first entity.
- `Entity *entityB` : The second entity.

This method is used to emit an OnCollisionEnter event. It emits the event.

### Compare Collisions

```c++
    void CompareCollisions(const std::vector<std::pair<Entity *, Entity *>> &collisions);
```

It takes the following parameters:
- `const std::vector<std::pair<Entity *, Entity *>> &collisions` : The collisions.

This method is used to compare collisions. It updates the collision's data.


## Usage

### Create a CollisionSystem

To create a CollisionSystem, you can use the following code:

```c++
    CollisionSystem *collisionSystem = new CollisionSystem();
    World->RegisterSystem(collisionSystem);
```

