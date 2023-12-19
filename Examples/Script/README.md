# Scripting with Exodia Game Engine

## Introduction

In this guide we will learn how to use the Exodia Game Engine scripting API to create a simple player controller.

## Script Abstraction

Know that this abstraction can evolved in the future, it's currently a simple script abstraction.
If you want to upgrade it, ask to `PharaEthan` the owner of the game engine.

```cpp
class ScriptableEntity {
    public:
        virtual ~ScriptableEntity() = default; 

        /**
         * @brief Called when the scriptable entity is created.
         */
        virtual void OnCreate() {};

        /**
         * @brief Called when the scriptable entity is destroyed.
         */
        virtual void OnDestroy() {};

        /**
         * @brief Called when the scriptable entity is updated.
         *
         * @param ts The timestep.
         */
        virtual void OnUpdate(UNUSED Timestep ts) {};


        template<typename Component>
        ComponentHandle<Component> GetComponent()
        {
            return HandleEntity.GetComponent<Component>();
        }

        Entity HandleEntity; /* !< The entity that owns the scriptable entity. */
};
```

We can see that the scriptable entity is a simple class that can be inherited to create a script.

## Scripting

So let's create a simple script that will print a message when the scriptable entity is created and a player controller that will move the entity.

```cpp
class ExampleScript : public ScriptableEntity {
    public:
        void OnCreate() override
        {
            std::cout << "Hello World !" << std::endl;
        }
};

class Player : public ScriptableEntity {
    public:

        void OnCreate() override
        {
            _Speed = 5.0f;
        }

        void OnUpdate(Timestep ts) override
        {
            auto transform = GetComponent<TransformComponent>();

            if (transform) {
                if (Input::IsKeyPressed(Key::A))
                    transform->Translation.x -= _Speed * ts;
                if (Input::IsKeyPressed(Key::D))
                    transform->Translation.x += _Speed * ts;
                if (Input::IsKeyPressed(Key::W))
                    transform->Translation.y += _Speed * ts;
                if (Input::IsKeyPressed(Key::S))
                    transform->Translation.y -= _Speed * ts;
            }
        }

    private:
        float _Speed;
};
```

## Binding

How to bind it to the current world for use it ?
We have to use the `ScriptComponent` struct.

```cpp
// -- Example 1 --
Entity *entity = _World->CreateEntity("Player");

entity->AddComponent<SpriteRendererComponent>(glm::vec4{ 0.8f, 0.2f, 0.3f, 1.0f });

auto script = entity->AddComponent<ScriptComponent>();

script.Get().Bind<Player>();

// -- Example 2 --
Entity *hello = _World->CreateEntity();

hello->AddComponent<ScriptComponent>().Get().Bind<ExampleScript>();
```

Don't forget when you will update your system that run the script to initialize the scriptable entity.

```cpp
_World->ForEach<ScriptComponent>([&](Entity *entity, ComponentHandle<ScriptComponent> script)
{
    auto &sc = script.Get();

    if (!sc.Instance) {
        sc.Instance = sc.InstantiateScript();
        sc.Instance->HandleEntity = *entity;
        sc.Instance->OnCreate();
    }

    sc.Instance->OnUpdate(ts);
});
```

Note this code is a system that run the scriptable entity, you can create your own system.
Currently this system already exist in the game engine. It's the `ScriptSystem`.
If you want to use it, you have to add it to the world.

```cpp
_World->RegisterSystem(new ScriptSystem());

_World->Update(ts);
```

If you need more information about how Entity Component System work, you can read the ECS guide.

## Running the example

To run the example, use the following commands:

```bash
./bin_examples/script
```
