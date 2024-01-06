/*
** EXODIA PROJECT, 2023
** TryAGame
** File description:
** GameLayer
*/

#ifndef GAMELAYER_HPP_
#define GAMELAYER_HPP_

#include "Exodia.hpp"
#include "imgui.h"

#include "Level/Level.hpp"

using namespace Exodia;

namespace FlappyBird {

    enum class GameState { Play, Menu, GameOver };

    class GameLayer : public Exodia::Layer {

        // Constructor & Destructor
      public:
        GameLayer();
        ~GameLayer();

        // Methods overrided from Exodia::Layer
      public:
        void OnAttach() override;
        void OnDetach() override;
        void OnUpdate(Timestep ts) override;
        void OnImGUIRender() override;
        void OnEvent(Event &event) override;

        // Methods
      private:
        bool OnKeyReleasedEvent(KeyReleasedEvent &event);
        bool OnKeyPressedEvent(KeyPressedEvent &event);
        bool OnWindowResizeEvent(WindowResizeEvent &event);

      public:
        inline static std::map<GameState, Ref<Scene>> Scenes;

      private:
        Level _Level;
        GameState _State;
        float _Time;
        bool _Blink;

        ImFont *_Font;
    };
} // namespace FlappyBird

#endif /* !GAMELAYER_HPP_ */
