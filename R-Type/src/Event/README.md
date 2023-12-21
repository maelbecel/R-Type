# Event

## Your first event

Events are a way to communicate between systems and entities.

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
            world->ForEach<Health>([&](UNUSED(Entity *entity), ComponentHandle<Health> health) {
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

## Built-in events

There are a handful of built-in events. Here is the list:

- OnEntityCreated    - called when an entity has been created.
- OnEntityDestroyed  - called when an entity is being destroyed (including when a world is beind deleted).
- OnComponentAdded   - called when a component is added to an entity. This might mean the component is new to the entity, or there's just a new assignment of the component to that entity overwriting an old one.
- OnComponentRemoved - called when a component is removed from an entity. This happens upon manual removal `Entity::RemoveComponent()` and `Entity::RemoveAllComponents()` or upon entity destruction (which can also happen as a result of the world being destroyed).
