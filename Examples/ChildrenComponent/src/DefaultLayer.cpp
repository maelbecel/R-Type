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

        _World->ForEach<SpriteRendererComponent, TransformComponent>([&](Entity *entity, auto sprite, auto transform) {
            Renderer2D::DrawSprite(
                transform.Get().GetTransform(), // Transform
                sprite.Get(),                   // SpriteRendererComponent
                (int)entity->GetEntityID()      // Entity ID
            );
        });

        Renderer2D::EndScene();
    }

    void DefaultLayer::OnEvent(Event &event)
    {
        _CameraController.OnEvent(event);
    }
};
