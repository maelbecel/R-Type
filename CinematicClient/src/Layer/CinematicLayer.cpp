/*
** EPITECH PROJECT, 2023
** ExodiaGameEngine
** File description:
** Cinematic
*/

#include "CinematicLayer.hpp"

using namespace Exodia;

namespace Cinematic {

    CinematicLayer::CinematicLayer() : Layer("Cinematic"), _World(Exodia::World::CreateWorld()) {}

    void CinematicLayer::OnAttach() {
        EXODIA_PROFILE_FUNCTION();

        EXODIA_INFO("Layer::OnAttach");

        _World->RegisterSystem(new MovingSystem(1.5f));

        Entity *cameraEntity = _World->CreateEntity("Camera");

        CameraComponent &camera = cameraEntity->AddComponent<CameraComponent>().Get();
        cameraEntity->GetComponent<TransformComponent>().Get().Translation = {0.0f, 0.0f, 15.0f};
        camera.Camera.SetProjectionType(SceneCamera::ProjectionType::Perspective);
        camera.Camera.SetViewportSize(Application::Get().GetWindow().GetWidth(),
                                      Application::Get().GetWindow().GetHeight());

        Entity *train = _World->CreateEntity("Train");
        train->AddComponent<ScriptComponent>().Get().Bind("Train");

        EXODIA_INFO("Add Train");
    }


    void CinematicLayer::OnUpdate(Timestep ts) {
        {
            EXODIA_PROFILE_SCOPE("Renderer Prep");

            Exodia::RenderCommand::SetClearColor({0.1f, 0.1f, 0.3f, 1});
            Exodia::RenderCommand::Clear();
        }

        // Update the world
        _World->Update(ts);

    }

    void CinematicLayer::OnDetach() {EXODIA_PROFILE_FUNCTION();}

    void CinematicLayer::OnImGUIRender() {EXODIA_PROFILE_FUNCTION();}

    void CinematicLayer::OnEvent(UNUSED(Event &event)) {EXODIA_PROFILE_FUNCTION();}



}