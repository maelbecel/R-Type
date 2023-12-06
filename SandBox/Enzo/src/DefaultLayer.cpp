/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** DefaultPlayer
*/

#include "DefaultLayer.hpp"
#include "Script/Player.hpp"
#include "Script/Pata-pata.hpp"
#include "Script/Star.hpp"
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
        entity->AddComponent<SpriteRendererComponent>();
        entity->AddComponent<Health>(185);
        entity->AddComponent<ScriptComponent>().Get().Bind<Player>();
        entity->AddComponent<Animation>(1.0f, 2.0f, 1.0f);
        entity->GetComponent<TransformComponent>().Get().Scale.y = 0.5f;

        // Set entity sprite
        auto sprite = entity->GetComponent<SpriteRendererComponent>();
        Ref<Texture2D> texture = Texture2D::Create("Assets/Textures/Player.png");
        sprite.Get().Texture = SubTexture2D::CreateFromCoords(texture, { 2.0f, 4.0f }, { 33.2f, 17.2f }, { 1.0f, 1.0f });

        Entity *patata = _World->CreateEntity("Pata-pata");

        patata->AddComponent<IDComponent>();
        patata->AddComponent<SpriteRendererComponent>();
        patata->AddComponent<Health>(185);
        patata->AddComponent<ScriptComponent>().Get().Bind<PataPata>();
        patata->AddComponent<Animation>(1.0f, 8.0f, 1.0f);
        patata->AddComponent<Clock>();

        Entity *background = _World->CreateEntity("Background");

        background->AddComponent<IDComponent>();
        background->AddComponent<CircleRendererComponent>(glm::vec4{ 0.0f, 0.0f, 0.005f, 1.0f });
        background->GetComponent<TransformComponent>().Get().Scale.y = 100.0f;
        background->GetComponent<TransformComponent>().Get().Scale.x = 100.0f;
        background->GetComponent<TransformComponent>().Get().Translation.z = -0.5f;

        std::cout << background->GetComponent<TransformComponent>().Get().Translation.z << std::endl;

        // Set entity sprite
        auto sprite2 = patata->GetComponent<SpriteRendererComponent>();
        Ref<Texture2D> texture2 = Texture2D::Create("Assets/Textures/Pata-Pata.png");
        sprite2.Get().Texture = SubTexture2D::CreateFromCoords(texture2, { 0.0f, 0.0f }, { 33.3125f, 36.0f }, { 1.0f, 1.0f });


		for(int i = 0; i < 60; i++) {
            Entity *star = _World->CreateEntity("Star" + std::to_string(i));

            star->AddComponent<IDComponent>();
            star->AddComponent<ScriptComponent>().Get().Bind<Star>();
            star->GetComponent<TransformComponent>().Get().Scale.y = 0.1f;
            star->GetComponent<TransformComponent>().Get().Scale.x = 0.1f;
            star->AddComponent<Clock>();
			star->AddComponent<CircleRendererComponent>(glm::vec4{ 0.9f, 0.9f, 0.9f + static_cast<float>(random() % 100) / 10000.0f, 0.9f });
        }
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

		_World->ForEach<CircleRendererComponent>([&](Entity *entity, ComponentHandle<CircleRendererComponent> circle) {
            auto transform = entity->GetComponent<TransformComponent>();
            auto id = entity->GetComponent<IDComponent>();

            if (transform && id) {
                Renderer2D::DrawCircle(
                    transform.Get().GetTransform(), // Transform
					circle.Get().Color, // CircleRendererComponent
                    circle.Get().Thickness, // CircleRendererComponent
                    circle.Get().Fade, // CircleRendererComponent
                    (int)id.Get().ID                // Entity ID
                );
            }
        });

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
