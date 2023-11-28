# Entity-Component-System

## Your first components

Components in ECS can be any data type, but generally they'll be a struct containing some plain old data. For now, let's define two components:
```cpp
struct Transform {
    glm::vec3 Translation;
    glm::vec3 Rotation;
    glm::vec3 Scale;

    Transform(const Transform &) = default;
    Transform(const glm::vec3 &translation = glm::vec3(0.0f)) : Translation(translation), Rotation(glm::vec3(0.0f)), Scale(glm::vec3(1.0f)) {};
};

struct Health {
    int CurrentHealth;
    int MaxHealth;

    Health(const Health &) = default;
    Health(int maxHealth = 100) : CurrentHealth(maxHealth), MaxHealth(maxHealth) {};
};
```

Note that we don't have to do anything special for these structs to act as components, though there is the requirement for at least a default constructor.

## Create a system

Now we need some logic to act on that data. Let's make a simple gravity system:

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
                transform->Translation.y += _GravityAmount * ts;
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
	    transform->Translation.y += _GravityAmount * ts;
	});
}
```

Alternatively, you may retrieve a single component at a time with `Entity::GetComponent()`, though this will return an invalid component handle
(see ComponentHandle<Component>::IsValid and ComponentHandle<Component>::operator bool()) if there isn't a component of that type attached:

```cpp
ComponentHandle<Transform> transform = entity->GetComponent<Transform>();

transform->Translation.y += _GravityAmount * ts; // this will crash if there is no position component on the entity
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

## Create the world

Next, inside a function somewhere, you can add the following code to create the world, setup the system, and create an entity:

```cpp
World *world = World::CreateWorld();

world->RegisterSystem(new GravitySystem(-6.9f));

Entity *entity = world->CreateEntity();

entity->AddComponent<Transform>();
entity->AddComponent<Health>();
```

Note `AddComponent()` can take any arguments that the component's constructor takes, so you can do this instead:

```cpp
entity->AddComponent<Transform>(glm::vec3(0.0f, 5.0f, 0.0f));
entity->AddComponent<Health>(175);
```cpp

Now you can call the `Update()` function on the world in order to update all systems that have been registered with the world:    

```cpp
world->Update(Timestep(1.0f / 60.0f));
```

Once you are done with the world, make sure to destroy it (this will also deallocate the world).

```cpp
world->DestroyWorld();
```

## Working with components

You may retrieve a component handle (for example, to print out the position of your entity) with `GetComponents()`:
```cpp
ComponentHandle<Transform> transform = entity->GetComponent<Transform>();

std::cout << "My position is " << transform->Translation.x << ", " << transform->Translation.y << std::endl;
```

If an entity doesn't have a component and you try to retrieve that type from it, `GetComponents()` will return an invalid component handle:
```cpp
ComponentHandle<Transform> transform = entity->GetComponent<Transform>();

// ComponentHandle::operator bool() will return false if the handle is invalid
if (transform /* or transform.IsValid() */)
    std::cout << "My position is " << transform->Translation.x << ", " << transform->Translation.y << std::endl;
else
    std::cout << "I don't have a Transform component !" << std::endl;
```

## Events

For communication between systems (and with other objects outside of ECS) there is an event system. Events can be any type of object, and you can subscribe to specific types of events by subclassing EventSubscriber and calling subscribe on the world:

```cpp
struct TakeDamageEvent {
    int Damage;
};

class TakeDamageSubscriber : public EventSubscriber<TakeDamageEvent> {
    public:
        // Constructor && Destructor
        TakeDamageSubscriber() = default;
        virtual ~TakeDamageSubscriber() {};

    public:
        // Methods
        virtual void Receive(World *world, const TakeDamageEvent &event) override
        {
            world->ForEach<Health>([&](UNUSED Entity *entity, ComponentHandle<Health> health) {
                std::cout << "I took " << event.Damage << " damage !" << std::endl;

                health->CurrentHealth -= event.Damage;
            });
        }
};

// ...

TakeDamageSubscriber *subscriber = new TakeDamageSubscriber();

world->Subscribe<TakeDamageEvent>(subscriber);

// ...
```

Then, to emit an event:

```cpp
world->Emit<TakeDamageEvent>(TakeDamageEvent{ 25 });
```

Note you can use initializer syntax if you want, this sets Damage to 25
Note make sure you call `Unsubscribe()` or `UnsubscribeAll()` on your subscriber before deleting it, or else emitting the event may cause a crash or other undesired behavior.

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
                health->CurrentHealth -= _DamagePerSecond * ts;
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

# Running the example

To run the example, you can use the following commands:

```bash
./bin_examples/ecs
```
