# Entity

## Description

Here is the repository where you will create all entity for the R-Type project.

## Your first entity

Entity in ECS is a simple class that contains a list of components. For now, let's define a basic entity:
```cpp
class SpaceShip {

    public:
        // Constructor & Destructor
        SpaceShip() = default;
        ~SpaceShip() = default;

    public:
        // Methods
        static void CreateSpaceShip(World *world, glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f))
        {
            Entity *entity = world->CreateEntity();

            entity->AddComponent<IDComponent>();
            entity->AddComponent<TransformComponent>(position);
            entity->AddComponent<SpriteRendererComponent>();
            entity->AddComponent<BoxCollider2DComponent>();
            entity->AddComponent<Health>(125);

            auto sprite = entity->GetComponent<SpriteRendererComponent>();

            Ref<Texture2D> texture = Texture2D::Create("Assets/Textures/Shell.png");

            sprite->Texture = SubTexture2D::CreateFromCoords(texture, { 0.0f, 2.0f }, { 33.0f, 33.0f }, { 1.0f, 1.0f });
        }
};
```
