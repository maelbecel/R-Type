# How to use the default system give by the game engine

## Introduction

If you do not know what is the Entity Component System, you can read the ECS guide.

## List of all default systems

    - `CollisionDetectionSystem` : Detect collision between entities
    - `GravitySystem` : Apply gravity to entities
    - `MovingSystem` : Move entities
    - `ScriptSystem` : Execute scripts

## How to use a system

Nothing hard you just need to register them to the world :

```cpp
_World->RegisterSystem(new ScriptSystem());
_World->RegisterSystem(new GravitySystem(1.5f));
_World->RegisterSystem(new MovingSystem(1.5f));
_World->RegisterSystem(new CollisionSystem());
```

And after you just need to call the `Update` method of the world :

```cpp
_World->Update(ts);
```

End all is done !

Now play with your entities and your systems !

Example of a little world :

```cpp
_World = World::CreateWorld();

Entity *entity = _World->CreateEntity("Player");

entity->AddComponent<SpriteRendererComponent>(glm::vec4{ 0.8f, 0.2f, 0.3f, 1.0f });
entity->AddComponent<ScriptComponent>().Get().Bind<Player>();
entity->AddComponent<BoxCollider2DComponent>();
entity->GetComponent<TransformComponent>().Get().Translation = glm::vec3{ 0.0f, 5.0f, 0.0f };

auto body = entity->AddComponent<RigidBody2DComponent>();

body.Get().Type = RigidBody2DComponent::BodyType::Dynamic;
body.Get().Mass = 1.0f;
body.Get().GravityScale = 1.0f;
body.Get().Velocity = glm::vec2{ 1.0f, 0.0f };

Entity *Obstacle = _World->CreateEntity("Obstacle");

Obstacle->AddComponent<SpriteRendererComponent>(glm::vec4{ 0.2f, 0.8f, 0.3f, 1.0f });
Obstacle->AddComponent<BoxCollider2DComponent>();
Obstacle->AddComponent<RigidBody2DComponent>().Get().Type = RigidBody2DComponent::BodyType::Static;
auto &transform = Obstacle->GetComponent<TransformComponent>().Get();

transform.Translation = glm::vec3{ 2.0f, -2.0f, 0.0f };
transform.Scale = glm::vec3{ 15.0f, 2.0f, 1.0f };

_World->RegisterSystem(new ScriptSystem());
_World->RegisterSystem(new GravitySystem(1.5f));
_World->RegisterSystem(new MovingSystem(1.5f));
_World->RegisterSystem(new CollisionSystem());

_World->Subscribe<Events::OnCollisionEntered>(new CollisionStop());
```

## Running the example

To run the example, use the following commands:

```bash
./bin_examples/defaultSystem
```
