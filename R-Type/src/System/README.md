# System

## Your first system

We need some logic to act on that component. Let's make a simple gravity system:

```cpp
class GravitySystem : public EntitySystem {
    public:
        // Constructor && Destructor
        GravitySystem(float amount) : _GravityAmount(amount) {};
    
        virtual ~GravitySystem() {};
 
    public:
        // Methods
        virtual void Update(World *world, Timestep ts) override
        {
            world->ForEach<Transform>([&](Entity *entity, ComponentHandle<Transform> transform) {
                transform.Get().Translation.y += _GravityAmount * ts;
            });
        }

    private:
        // Attributes
        float _GravityAmount;
};
```

This is a pretty standard class definition.
We subclass EntitySystem and implement the `Update()` method.
The world provides the `ForEach()` method, which takes a list of component types and runs a given function (in this case a lambda) on every entity that has those components.
Note that the lambda is passed a ComponentHandle, and not the component itself.

### Alternate iteration methods

In addition to the lambda-based each, there's also an iterator-based each, made to be used with the range based for loop.
Lambda-based each isn't a true loop, and as such you can't break from it. Instead, you can use a range based for loop.
The downside is that it will not directly expose components as arguments, but you can combine it with `Entity::CallFunctionWithComponents()` for a similar result:

```cpp
for (Entity *entity : world->ForEach<Transform>()) {
    entity->CallFunctionWithComponents<Transform>([&](ComponentHandle<Transform> transform) {
	    transform.Get().Translation.y += _GravityAmount * ts;
	});
}
```

Alternatively, you may retrieve a single component at a time with `Entity::GetComponent()`, though this will return an invalid component handle
(see ComponentHandle<Component>::IsValid and ComponentHandle<Component>::operator bool()) if there isn't a component of that type attached:

```cpp
ComponentHandle<Transform> transform = entity->GetComponent<Transform>();

transform.Get().Translation.y += _GravityAmount * ts; // this will crash if there is no position component on the entity
```

`CallFunctionWithComponents<Components>()` only runs the given function if the entity has the listed components.
It also returns true if all components were found, or false if not all components were on the entity.

Finally, if you want to run a function on all entities, regardless of components, then use the all function in the same way as each:

```cpp
world->ForAll([](Entity *entity) {
    // do something with entity
    // ...
});
```

You may also use `ForAll()` in a range based for loop in a similar fashion to `ForEach()`.
Note that `ForAll()` will not run on entities that have been marked for deletion.

## Systems and events

Often, your event subscribers will also be systems.
Systems have `Configure()` and `Unconfigure()` functions that are called when they are added to/removed from the world and which you may use to subscribe and unsubscribe from events:

```cpp
class FortniteZone : public EntitySystem, public EventSubscriber<TakeDamageEvent> {
    public:
        // Constructor && Destructor
        FortniteZone(float damagePerSecond) : _DamagePerSecond(damagePerSecond) {};
    
        virtual ~FortniteZone() {};

    public:
        // Methods
        virtual void Update(World *world, Timestep ts) override
        {
            world->ForEach<Health>([&](Entity *entity, ComponentHandle<Health> health) {
                health.Get().CurrentHealth -= _DamagePerSecond * ts;
            });
        }

        virtual void Configure(World *world) override
        {
            world->Subscribe<TakeDamageEvent>(this);
        }
    
        virtual void Unconfigure(World *world) override
        {
            // world->Unsubscribe<TakeDamageEvent>(this);
            world->UnsubscribeAll(this);

            // You may also unsubscribe from specific events with world->Unsubscribe<TakeDamageEvent>(this), but
            // when unconfigure is called you usually want to unsubscribe from all events.
        }

    private:
        // Attributes
        float _DamagePerSecond;
};
```

## Built-in events

There are a handful of built-in events. Here is the list:

- OnEntityCreated    - called when an entity has been created.
- OnEntityDestroyed  - called when an entity is being destroyed (including when a world is beind deleted).
- OnComponentAdded   - called when a component is added to an entity. This might mean the component is new to the entity, or there's just a new assignment of the component to that entity overwriting an old one.
- OnComponentRemoved - called when a component is removed from an entity. This happens upon manual removal `Entity::RemoveComponent()` and `Entity::RemoveAllComponents()` or upon entity destruction (which can also happen as a result of the world being destroyed).
