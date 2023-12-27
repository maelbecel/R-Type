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

    // -- Layer ----------------------------------------------------------------

    //////////////////////////////
    // Constructor & Destructor //
    //////////////////////////////

    DefaultLayer::DefaultLayer()
        : Layer("DefaultLayer"), _World(World::CreateWorld()), _Network(_World, _ioContextManager, 7071),
          _CameraController(1600.0f / 900.0f){};

    /////////////
    // Methods //
    /////////////

    void DefaultLayer::OnAttach() {
        Project::Load("./Client/R-Type.proj");

        _Network.Loop();

        _Network.SendAskConnect("0.0.0.0", 7070);

        Entity *entity = _World->CreateEntity("Player");

        entity->AddComponent<TransformComponent>(glm::vec3(1.0f, 0.0f, 0.0f));
        entity->AddComponent<SpriteRendererComponent>(glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));
    }

    void DefaultLayer::OnUpdate(Exodia::Timestep ts) {
        // Update
        _CameraController.OnUpdate(ts);
        _World->Update(ts);

        // Renderer Prep
        Exodia::RenderCommand::SetClearColor({0.1f, 0.1f, 0.1f, 1});
        Exodia::RenderCommand::Clear();

        // Renderer Draw
        Exodia::Renderer2D::BeginScene(_CameraController.GetCamera());

        _World->ForEach<SpriteRendererComponent, TransformComponent, IDComponent>(
            [&](UNUSED(Entity * entity), auto sprite, auto transform, auto id) {
                Renderer2D::DrawSprite(transform.Get().GetTransform(), sprite.Get(), id.Get().ID);
            });

        Exodia::Renderer2D::EndScene();
    }

    void DefaultLayer::OnEvent(Exodia::Event &event) { _CameraController.OnEvent(event); }
}; // namespace Exodia
