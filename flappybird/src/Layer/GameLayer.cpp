/*
** EXODIA PROJECT, 2023
** TryAGame
** File description:
** GameLayer
*/

#include "GameLayer.hpp"

#include "Tools/Random.hpp"

using namespace Exodia;

namespace FlappyBird {

    //////////////////////////////
    // Constructor & Destructor //
    //////////////////////////////

    GameLayer::GameLayer() : Layer("GameLayer"), _State(GameState::Menu), _Time(0.0f), _Blink(false) {}

    GameLayer::~GameLayer() {}

    void GameLayer::OnAttach() {
        EXODIA_PROFILE_FUNCTION();
        _Level.Init();
        
    }

    void GameLayer::OnDetach(){};

    void GameLayer::OnUpdate(Exodia::Timestep ts) {
        // Update
        _Time += ts;

        if ((int)(_Time * 10.0f) % 8 > 4)
            _Blink = !_Blink;
        if (_Level.IsGameOver())
            _State = GameState::GameOver;

        const glm::vec2 &playerPos = _Level.GetPlayer().GetPosition();

        _Camera->SetPosition({playerPos.x, playerPos.y, 0.0f});

        switch (_State) {
        case GameState::Play:
            _Level.OnUpdate(ts);
            break;
        default:
            break;
        }

        // Render Prep
        Exodia::RenderCommand::SetClearColor({0.0f, 0.0f, 0.0f, 1});
        Exodia::RenderCommand::Clear();

        // Render Draw
        Exodia::Renderer2D::BeginScene(*_Camera);

        _Level.OnRender();

        Exodia::Renderer2D::EndScene();
    }

    void GameLayer::OnImGUIRender() {
        switch (_State) {
        case GameState::Play: {
            std::string score = std::string("Score : ") + std::to_string(_Level.GetPlayer().GetScore());
            ImGui::GetForegroundDrawList()->AddText(_Font, 48.0f, ImGui::GetWindowPos(), 0xffffffff, score.c_str());
            break;
        }
        case GameState::Menu: {
            ImVec2 pos = ImGui::GetWindowPos();

            unsigned int width = Exodia::Application::Get().GetWindow().GetWidth();

            pos.x += width / 2.0f - 300.0f;
            pos.y += 50.0f;

            if (_Blink)
                ImGui::GetForegroundDrawList()->AddText(_Font, 120.0f, pos, 0xffffffff, "Click to play !");
            break;
        }
        case GameState::GameOver: {
            ImVec2 pos = ImGui::GetWindowPos();

            unsigned int width = Exodia::Application::Get().GetWindow().GetWidth();

            pos.x += width / 2.0f - 300.0f;
            pos.y += 50.0f;

            if (_Blink)
                ImGui::GetForegroundDrawList()->AddText(_Font, 120.0f, pos, 0xffffffff, "Click to play !");

            pos.x += 200.0f;
            pos.y += 150.0f;

            std::string score = std::string("Score : ") + std::to_string(_Level.GetPlayer().GetScore());
            ImGui::GetForegroundDrawList()->AddText(_Font, 120.0f, pos, 0xffffffff, score.c_str());
            break;
        }
        }
    }

    void GameLayer::OnEvent(Exodia::Event &event) {
        Exodia::EventDispatcher dispatcher(event);

        dispatcher.Dispatch<Exodia::MouseButtonPressedEvent>(BIND_EVENT_FN(GameLayer::OnMouseButtonPressed));
        dispatcher.Dispatch<Exodia::WindowResizeEvent>(BIND_EVENT_FN(GameLayer::OnWindowResize));
    }

    bool GameLayer::OnMouseButtonPressed(Exodia::MouseButtonPressedEvent &event) {
        (void)event;

        if (_State == GameState::GameOver)
            _Level.Reset();

        _State = GameState::Play;
        return false;
    }

    bool GameLayer::OnWindowResize(Exodia::WindowResizeEvent &event) {
        CreateCamera(event.GetWidth(), event.GetHeight());

        return false;
    }

    void GameLayer::CreateCamera(uint32_t width, uint32_t height) {
        float aspectRatio = (float)width / (float)height;

        float cameraWidth = 8.0f;

        float bottom = -cameraWidth;
        float top = cameraWidth;
        float left = bottom * aspectRatio;
        float right = top * aspectRatio;

        _Camera = CreateScope<Exodia::OrthographicCamera>(left, right, bottom, top);
    }
} // namespace FlappyBird
