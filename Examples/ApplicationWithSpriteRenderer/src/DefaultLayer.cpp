/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** DefaultPlayer
*/

#include "DefaultLayer.hpp"
#include <imgui.h>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace Exodia {

    static void createSpaceShip(World *world, glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f))
    {
        Entity *entity = world->CreateEntity();

        entity->AddComponent<IDComponent>();
        entity->AddComponent<TransformComponent>(position);
        entity->AddComponent<SpriteRendererComponent>();

        auto sprite = entity->GetComponent<SpriteRendererComponent>();

        Ref<Texture2D> texture = Texture2D::Create("Assets/Textures/Shell.png");

        sprite->Texture = SubTexture2D::CreateFromCoords(texture, { 0.0f, 2.0f }, { 33.0f, 33.0f }, { 1.0f, 1.0f });
    }

    // -- Layer ----------------------------------------------------------------

    //////////////////////////////
    // Constructor & Destructor //
    //////////////////////////////

    DefaultLayer::DefaultLayer() : Layer("DefaultLayer"), _CameraController(1600.0f / 900.0f) {};

    /////////////
    // Methods //
    /////////////

    void DefaultLayer::OnAttach()
    {
        EXODIA_PROFILE_FUNCTION();

        _World = World::CreateWorld();

        createSpaceShip(_World);
        createSpaceShip(_World, glm::vec3(1.0f, 0.0f, 0.0f));
        createSpaceShip(_World, glm::vec3(-1.0f, 0.0f, 0.0f));
    }

    void DefaultLayer::OnDetach()
    {
        EXODIA_PROFILE_FUNCTION();

        _World->DestroyWorld();
    }

    void DefaultLayer::OnUpdate(Timestep ts)
    {
        // Update
        _CameraController.OnUpdate(ts);

        // Renderer Prep
        RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
        RenderCommand::Clear();

        // Renderer Draw
        _World->Update(ts);

        Renderer2D::BeginScene(_CameraController.GetCamera());

        _World->ForEach<SpriteRendererComponent>([&](Entity *entity, ComponentHandle<SpriteRendererComponent> sprite) {
            auto transform = entity->GetComponent<TransformComponent>();
            auto id = entity->GetComponent<IDComponent>();

            if (transform && id) {
                Renderer2D::DrawSprite(
                    transform.Get().GetTransform(), // Transform
                    sprite.Get(),                   // SpriteRendererComponent
                    (int)id.Get().ID                // Entity ID
                );
            }
        });

        Renderer2D::EndScene();
    }

    void DefaultLayer::OnEvent(Exodia::Event &event)
    {
        _CameraController.OnEvent(event);
    }
};
