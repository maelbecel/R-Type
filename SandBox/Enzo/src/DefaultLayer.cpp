/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** DefaultPlayer
*/

#include "DefaultLayer.hpp"
#include "Script/Player.hpp"
#include "Script/ExampleScript.hpp"
#include "ComponentExample.hpp"

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

        _World = World::CreateWorld();

        Entity *entity = _World->CreateEntity("Player");

        entity->AddComponent<IDComponent>();
        entity->AddComponent<SpriteRendererComponent>(glm::vec4{ 0.8f, 0.2f, 0.3f, 1.0f });
        entity->AddComponent<Health>(185);
        entity->AddComponent<ScriptComponent>().Get().Bind<Player>();
        entity->AddComponent<SpriteRendererComponent>();

        auto sprite = entity->GetComponent<SpriteRendererComponent>();

        Ref<Texture2D> texture = Texture2D::Create("Assets/Textures/Player.png");

        sprite->Texture = SubTexture2D::CreateFromCoords(texture, { 2.0f, 4.0f }, { 33.2f, 17.2f }, { 1.0f, 1.0f });

        entity->GetComponent<TransformComponent>().Get().Scale.y = 0.5f;
    }

    void DefaultLayer::OnDetach()
    {
        EXODIA_PROFILE_FUNCTION();
    }

    void DefaultLayer::OnUpdate(Exodia::Timestep ts)
    {
        // Update
        _CameraController.OnUpdate(ts);

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
