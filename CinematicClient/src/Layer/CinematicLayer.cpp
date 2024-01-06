/*
** EPITECH PROJECT, 2023
** ExodiaGameEngine
** File description:
** Cinematic
*/

#include "CinematicLayer.hpp"

using namespace Exodia;

namespace Cinematic {

    CinematicLayer::CinematicLayer() : Layer("Cinematic"), _scene(new Scene()) {}

    void CinematicLayer::OnAttach() {
        EXODIA_PROFILE_FUNCTION();

        EXODIA_INFO("Layer::OnAttach");

        _scene->RegisterSystem(new MovingSystem(1.5f));
        _scene->RegisterSystem(new AnimationSystem());

        /// Create a Camera

        GameObject cameraEntity = _scene->CreateEntity("Camera");

        CameraComponent &camera = cameraEntity.AddComponent<CameraComponent>();
        cameraEntity->GetComponent<TransformComponent>().Get().Translation = {0.0f, 0.0f, 15.0f};
        camera.Camera.SetProjectionType(SceneCamera::ProjectionType::Perspective);
        camera.Camera.SetViewportSize(Application::Get().GetWindow().GetWidth(),
                                      Application::Get().GetWindow().GetHeight());
        cameraEntity->AddComponent<ScriptComponent>().Get().Bind("FollowingCamera");

        /// Create a Train

        GameObject train = _scene->CreateEntity("Train");
        train.AddComponent<ScriptComponent>().Bind("Train");

        _scene->OnRuntimeStart();

        EXODIA_INFO("Add Train");
    }

    void CinematicLayer::OnUpdate(Timestep ts) {
        {
            EXODIA_PROFILE_SCOPE("Renderer Prep");

            Exodia::RenderCommand::SetClearColor({0.1f, 0.1f, 0.3f, 1});
            Exodia::RenderCommand::Clear();
        }

        // Update the world
        _scene->OnUpdateRuntime(ts);
    }

    void CinematicLayer::OnDetach() { EXODIA_PROFILE_FUNCTION(); }

    void CinematicLayer::OnImGUIRender() { EXODIA_PROFILE_FUNCTION(); }

    void CinematicLayer::OnEvent(UNUSED(Event &event)) { EXODIA_PROFILE_FUNCTION(); }

} // namespace Cinematic