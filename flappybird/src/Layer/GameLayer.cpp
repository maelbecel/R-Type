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

    /**
     * The GameLayer constructor initializes the Flappy Bird game and sets the initial state, blink
     * status, and time.
     */
    GameLayer::GameLayer() : Layer("Flappy Bird"), _State(GameState::Menu), _Blink(false), _Time(0.0f) {
        FlappyBird::Init();
        Random::Init();
    }

    /////////////
    // Methods //
    /////////////

    /**
     * The function initializes the game level.
     */
    void GameLayer::OnAttach() {
        EXODIA_PROFILE_FUNCTION();

        _Level.Init();
    }

    /**
     * The function `OnUpdate` updates the game state, prepares the renderer, and updates the scene
     * based on the current game state.
     *
     * @param ts Timestep is a class that represents the time elapsed since the last frame. It is used
     * to control the speed of the game and ensure consistent gameplay across different hardware. In
     * this code, it is passed as a parameter to the OnUpdate function to update the game logic and
     * scene based on the elapsed time
     */
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

    /**
     * The function `OnImGUIRender()` is responsible for rendering the user interface elements in the
     * game, including the score, menu, game over screen, and debug statistics.
     */
    void GameLayer::OnImGUIRender() {
        // -- ImGui Render -----------------------------------------------------

        switch (_State) {
        case GameState::Play: {
            std::string score = std::string("Score : " + std::to_string(_Level.GetScore()));

            ImGui::GetForegroundDrawList()->AddText(ImGui::GetFont(), 48.0f, ImGui::GetWindowPos(), IM_COL32_WHITE,
                                                    score.c_str());

            break;
        }
        case GameState::Menu: {
            ImVec2 pos = ImGui::GetWindowPos();

            uint32_t width = Exodia::Application::Get().GetWindow().GetWidth();

            pos.x += width / 2.0f - 400.0f;
            pos.y += 100.0f;

            if (_Blink)
                ImGui::GetForegroundDrawList()->AddText(ImGui::GetFont(), 120.0f, pos, IM_COL32_WHITE,
                                                        "Click to play !");
            break;
        }
        case GameState::GameOver: {
            ImVec2 pos = ImGui::GetWindowPos();

            uint32_t width = Exodia::Application::Get().GetWindow().GetWidth();

            pos.x += width / 2.0f - 400.0f;
            pos.y += 100.0f;

            if (_Blink)
                ImGui::GetForegroundDrawList()->AddText(ImGui::GetFont(), 120.0f, pos, IM_COL32_WHITE,
                                                        "Click to play !");

            pos.x += 200.0f;
            pos.y += 150.0f;

            std::string score = std::string("Score : " + std::to_string(_Level.GetScore()));

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

    /**
     * The function `OnEvent` in the `GameLayer` class dispatches events to their corresponding event
     * handlers.
     * 
     * @param event The "event" parameter is a reference to an Event object. It is passed to the
     * OnEvent function to handle different types of events.
     */
    void GameLayer::OnEvent(Event &event) {
        EventDispatcher dispatcher(event);

        dispatcher.Dispatch<KeyPressedEvent>(BIND_EVENT_FN(GameLayer::OnKeyPressedEvent));
        dispatcher.Dispatch<MouseButtonPressedEvent>(BIND_EVENT_FN(GameLayer::OnMouseButtonPressedEvent));
    }

    /**
     * The function `OnKeyPressedEvent` in the `GameLayer` class handles key pressed events by passing the
     * key code to the `_Level` object and returns true.
     *
     * @param event The event parameter is an object of type KeyPressedEvent. It represents the event that
     * occurred when a key was pressed.
     *
     * @return a boolean value of true.
     */
        bool GameLayer::OnKeyPressedEvent(KeyPressedEvent &event) {
        _Level.OnKeyPressed(event.GetKeyCode());
        return true;
    }

    /**
     * The function checks if the game state is "GameOver" and if so, resets the level and changes the
     * state to "Play", then starts playing the level.
     *
     * @param event The parameter "event" is of type MouseButtonPressedEvent, which is an event that is
     * triggered when a mouse button is pressed.
     *
     * @return a boolean value of true.
     */
    bool GameLayer::OnMouseButtonPressedEvent(UNUSED(MouseButtonPressedEvent &event)) {
        if (_State == GameState::GameOver)
            _Level.Reset();

        _State = GameState::Play;
        _Level.Play();
        return true;
    }
}; // namespace FlappyBird
