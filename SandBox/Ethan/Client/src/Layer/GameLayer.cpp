/*
** EPITECH PROJECT, 2023
** ExodiaGameEngine
** File description:
** ExodiaEngine
*/

#include "GameLayer.hpp"
#include "R-Type.hpp"

namespace RType {

    using namespace Exodia;

    //////////////////////////////
    // Constructor & Destructor //
    //////////////////////////////

    GameLayer::GameLayer() : Layer("R-Type Layer")
    {
        RType::EntryPoint();

        Config::Init();

        if (!Config::Read())
            Config::Write();
    }

    /////////////
    // Methods //
    /////////////

    void GameLayer::OnAttach()
    {
        _Scene = CreateRef<Scene>("Intro");

        SceneSerializer serializer(_Scene);

        serializer.Deserialize("./Assets/Scene/Loading.exodia");

        // -- Scene System -- //
        _Scene->RegisterSystem(new ClockSystem());
        _Scene->RegisterSystem(new AnimationSystem());
        _Scene->RegisterSystem(new FadeSystem());

        // -- Resizing the viewport -- //
        _Scene->OnViewportResize(Application::Get().GetWindow().GetWidth(), Application::Get().GetWindow().GetHeight());

        // -- Start the scene -- //
        _Scene->OnRuntimeStart();
    }

    void GameLayer::OnUpdate(Timestep ts)
    {
        RenderCommand::SetClearColor({ 0.0f, 0.0f, 0.0f, 1.0f });
        RenderCommand::Clear();

        _Scene->OnUpdateRuntime(ts);
    }
};
