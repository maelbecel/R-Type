/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** DefaultPlayer
*/

#include "DefaultLayer.hpp"
#include "Script/Dobkeratops.hpp"

namespace Exodia {

    // -- Layer ----------------------------------------------------------------

    //////////////////////////////
    // Constructor & Destructor //
    //////////////////////////////

    DefaultLayer::DefaultLayer() : Layer("DefaultLayer"), _CameraController(1280.0f / 720.0f) {};

    /////////////
    // Methods //
    /////////////

    void DefaultLayer::OnAttach()
    {
        EXODIA_PROFILE_FUNCTION();

        Ref<Texture2D> dobkeratopsTexture = Texture2D::Create("Assets/Textures/Dobkeratops.png");

        _World = World::CreateWorld();

        Entity *entity = _World->CreateEntity("Dobkeratops");

        entity->AddComponent<ScriptComponent>().Get().Bind<DobkeratopsTails>();

        _World->RegisterSystem(new ScriptSystem());

        _CameraController.SetZoomLevel(5.0f);
    }

    void DefaultLayer::OnDetach()
    {
        EXODIA_PROFILE_FUNCTION();

        _World->DestroyWorld();
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

        /*_World->ForEach<SpriteRendererComponent, TransformComponent>([&](Entity *entity, auto sprite, auto transform) {
            Renderer2D::DrawSprite(
                transform.Get().GetTransform(), // Transform
                sprite.Get(),                   // SpriteRendererComponent
                (int)entity->GetEntityID()      // Entity ID
            );
        });*/

        /*_World->ForEach<ChildrenComponent>([&](Entity *entity, auto children) {
            auto &cc = children.Get();

            for (auto &child : cc.Children) {
                //Entity *childEntity = entity->GetWorld()->GetEntityByID(child);

                if (_World->GetEntityByID(child) != nullptr)
                    continue;
                _World->AddEntity(childEntity);

                if (childEntity) {
                    auto transform = childEntity->GetComponent<TransformComponent>();
                    auto id        = childEntity->GetComponent<IDComponent>();
                    auto sprite    = childEntity->GetComponent<SpriteRendererComponent>();

                    if (transform && id && sprite) {
                        Renderer2D::DrawSprite(
                            transform.Get().GetTransform(), // Transform
                            sprite.Get(),                   // SpriteRendererComponent
                            (int)id.Get().ID                // Entity ID
                        );
                    }
                }
            }
        });*/

        /*_World->ForEach<TransformComponent, SpriteRendererComponent>([&](Entity *entity, auto transform, auto sprite) {
            Renderer2D::DrawSprite(
                transform.Get().GetTransform(), // Transform
                sprite.Get(),                   // SpriteRendererComponent
                (int)entity->GetEntityID()      // Entity ID
            );
        });*/

        Renderer2D::EndScene();
    }

    void DefaultLayer::OnEvent(Event &event)
    {
        _CameraController.OnEvent(event);
    }
};
