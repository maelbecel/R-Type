/*
** EPITECH PROJECT, 2023
** ExodiaGameEngine
** File description:
** ExodiaEngine
*/

#include "GameLayer.hpp"
#include "R-Type.hpp"
#include "GameScene/LoadingScene.hpp"

namespace RType {

    using namespace Exodia;

    //////////////////////////////
    // Constructor & Destructor //
    //////////////////////////////

    GameLayer::GameLayer() : Layer("R-Type Layer"), _CurrentScene(LOADING)
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
        // -- Init the different scenes -- //
        _Scenes.emplace(LOADING, CreateRef<LoadingScene>());

        // -- Create the first scene -- //
        _Scenes[LOADING]->OnCreate();
    }

    void GameLayer::OnUpdate(Timestep ts)
    {
        RenderCommand::SetClearColor({ 0.0f, 0.0f, 0.0f, 1.0f });
        RenderCommand::Clear();

        _Scenes[_CurrentScene]->OnUpdate(ts);
    }

    void GameLayer::OnEvent(Event& event)
    {
        _Scenes[_CurrentScene]->OnEvent(event);
    }
};
