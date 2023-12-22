/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** DefaultPlayer
*/

#include "DefaultLayer.hpp"
#include "Script/Player.hpp"
#include "Script/Pata-pata.hpp"
#include "Script/ExampleScript.hpp"
#include "ComponentExample.hpp"
#include "AnimationSystem.hpp"

namespace Exodia {

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

        // Create world
        _World = World::CreateWorld();
        _World->RegisterSystem(new AnimationSystem());
        _World->RegisterSystem(new ScriptSystem());

        // Create entities
        Entity *entity = _World->CreateEntity("Player");

        entity->AddComponent<IDComponent>();
        entity->AddComponent<SpriteRendererComponent>(glm::vec4{ 0.8f, 0.2f, 0.3f, 1.0f });
        entity->AddComponent<Health>(185);
        entity->AddComponent<ScriptComponent>().Get().Bind("Player");
        entity->AddComponent<SpriteRendererComponent>();
        entity->AddComponent<Animation>();
        entity->GetComponent<TransformComponent>().Get().Scale.y = 0.5f;

        // Set entity sprite
        auto sprite = entity->GetComponent<SpriteRendererComponent>();
        Ref<Texture2D> texture = Texture2D::Create("Assets/Textures/Player.png");
        sprite.Get().Texture = SubTexture2D::CreateFromCoords(texture, { 2.0f, 4.0f }, { 33.2f, 17.2f }, { 1.0f, 1.0f });

        Entity *patata = _World->CreateEntity("Pata-pata");

        patata->AddComponent<IDComponent>();
        patata->AddComponent<SpriteRendererComponent>(glm::vec4{ 0.8f, 0.2f, 0.3f, 1.0f });
        patata->AddComponent<Health>(185);
        patata->AddComponent<ScriptComponent>().Get().Bind("PataPata");
        patata->AddComponent<SpriteRendererComponent>();
        patata->AddComponent<Animation>(1.0f, 8.0f, 1.0f);

        // Set entity sprite
        auto sprite2 = patata->GetComponent<SpriteRendererComponent>();
        Ref<Texture2D> texture2 = Texture2D::Create("Assets/Textures/Pata-Pata.png");
        sprite2.Get().Texture = SubTexture2D::CreateFromCoords(texture2, { 0.0f, 0.0f }, { 33.3125f, 36.0f }, { 1.0f, 1.0f });

        // Create camera
        _CameraController.SetZoomLevel(5.0f);
    }

    void DefaultLayer::OnDetach()
    {
        EXODIA_PROFILE_FUNCTION();
    }

    void DefaultLayer::OnUpdate(Exodia::Timestep ts)
    {
        // Update
        _CameraController.OnUpdate(ts);

        _World->Update(ts);

        // Renderer Prep
        Exodia::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
        Exodia::RenderCommand::Clear();

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
