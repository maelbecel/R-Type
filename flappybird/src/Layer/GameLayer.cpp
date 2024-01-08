/*
** EPITECH PROJECT, 2023
** ExodiaGameEngine
** File description:
** ExodiaEngine
*/

#include "GameLayer.hpp"
#include "Tools/Random.hpp"

#include <imgui.h>
#include <string>

using namespace Exodia;

namespace FlappyBird {

    //////////////////////////////
    // Constructor & Destructor //
    //////////////////////////////

    GameLayer::GameLayer() : Layer("Flappy Bird"), _State(GameState::Menu), _Blink(false), _Time(0.0f) {
        FlappyBird::Init();
        Random::Init();
    }

    /////////////
    // Methods //
    /////////////

    void GameLayer::OnAttach() {
        EXODIA_PROFILE_FUNCTION();

        _Level.Init();
    }

    void GameLayer::OnUpdate(Timestep ts) {
        EXODIA_PROFILE_FUNCTION();

        // Renderer Prep
        {
            EXODIA_PROFILE_SCOPE("Renderer Prep");

            Renderer2D::ResetStats();
            RenderCommand::SetClearColor({0.1f, 0.1f, 0.1f, 1});
            RenderCommand::Clear();
        }

        // Game Update
        {
            EXODIA_PROFILE_SCOPE("Game Update");

            _Time += ts;

            if ((int)(_Time * 10.0f) % 8 > 4)
                _Blink = !_Blink;
            if (_Level.IsGameOver())
                _State = GameState::GameOver;
        }

        // Scene Update
        {
            EXODIA_PROFILE_SCOPE("Scene Update");

            switch (_State) {
            case GameState::Play:
                _Level.OnUpdate(ts);
                break;
            default:
                _Level.OnRender(ts);
                break;
            }
        }
    }

    void GameLayer::OnImGUIRender() {
        // -- ImGui Render -----------------------------------------------------

        switch (_State) {
        case GameState::Play: {
            std::string score = std::string("Score : "); // + std::to_string(_Level.GetPlayer().GetScore());

            ImGui::GetForegroundDrawList()->AddText(ImGui::GetFont(), 48.0f, ImGui::GetWindowPos(), IM_COL32_WHITE,
                                                    score.c_str());

            break;
        }
        case GameState::Menu: {
            ImVec2 pos = ImGui::GetWindowPos();

            uint32_t width = Exodia::Application::Get().GetWindow().GetWidth();

            pos.x += width / 2.0f - 300.0f;
            pos.y += 50.0f;

            if (_Blink)
                ImGui::GetForegroundDrawList()->AddText(ImGui::GetFont(), 120.0f, pos, IM_COL32_WHITE,
                                                        "Click to play !");
            break;
        }
        case GameState::GameOver: {
            ImVec2 pos = ImGui::GetWindowPos();

            uint32_t width = Exodia::Application::Get().GetWindow().GetWidth();

            pos.x += width / 2.0f - 300.0f;
            pos.y += 50.0f;

            if (_Blink)
                ImGui::GetForegroundDrawList()->AddText(ImGui::GetFont(), 120.0f, pos, IM_COL32_WHITE,
                                                        "Click to play !");

            pos.x += 200.0f;
            pos.y += 150.0f;

            std::string score = std::string("Score : "); // + std::to_string(_Level.GetPlayer().GetScore());

            ImGui::GetForegroundDrawList()->AddText(ImGui::GetFont(), 120.0f, pos, IM_COL32_WHITE, score.c_str());
            break;
        }
        }

        // -- Debug Stats ------------------------------------------------------

#ifdef EXODIA_DEBUG
        ImGui::Begin("R-Type Statistics");
        ImGui::Text("FPS: %.1f", Application::Get().GetStatistics().FPS);
        ImGui::Text("Frame Time: %.3f ms", Application::Get().GetStatistics().FrameTime);
        ImGui::Text("Memory Usage: %ld KB", Application::Get().GetStatistics().MemoryUsage / 1024);
        ImGui::Separator();
        ImGui::Text("Renderer Statistics:");
        ImGui::Text("Draw Calls: %d", Renderer2D::GetStats().DrawCalls);
        ImGui::Text("Quad Count: %d", Renderer2D::GetStats().QuadCount);
        ImGui::Text("Vertex Count: %d", Renderer2D::GetStats().GetTotalVertexCount());
        ImGui::Text("Index Count: %d", Renderer2D::GetStats().GetTotalIndexCount());
        ImGui::Separator();
        ImGui::End();
#endif
    }

    void GameLayer::OnEvent(Event &event) {
        EventDispatcher dispatcher(event);

        dispatcher.Dispatch<KeyPressedEvent>(BIND_EVENT_FN(GameLayer::OnKeyPressedEvent));
        dispatcher.Dispatch<MouseButtonPressedEvent>(BIND_EVENT_FN(GameLayer::OnMouseButtonPressedEvent));
    }

    bool GameLayer::OnKeyPressedEvent(KeyPressedEvent &event) {
        _Level.OnKeyPressed(event.GetKeyCode());
        return true;
    }

    bool GameLayer::OnMouseButtonPressedEvent(UNUSED(MouseButtonPressedEvent &event)) {
        if (_State == GameState::GameOver)
            _Level.Reset();

        _State = GameState::Play;
        _Level.Play();
        return true;
    }
}; // namespace FlappyBird
