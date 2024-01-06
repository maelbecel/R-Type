/*
** EPITECH PROJECT, 2023
** ExodiaGameEngine
** File description:
** GameLayer
*/

#ifndef RTYPELAYER_HPP_
#define RTYPELAYER_HPP_

#include "Exodia.hpp"
#include "R-Type.hpp"

using namespace Exodia;

namespace FlappyBird {

    enum class GameState { Play, Menu, GameOver };

    class GameLayer : public Exodia::Layer {

        //////////////////////////////
        // Constructor & Destructor //
        //////////////////////////////
      public:
        GameLayer();
        ~GameLayer() = default;

        /////////////
        // Methods //
        /////////////
      public:
        void OnAttach() override;
        void OnDetach() override;
        void OnUpdate(Timestep ts) override;
        void OnImGUIRender() override;
        void OnEvent(Event &event) override;

      private:
        bool OnKeyReleasedEvent(KeyReleasedEvent &event);
        bool OnKeyPressedEvent(KeyPressedEvent &event);
        bool OnWindowResizeEvent(WindowResizeEvent &event);

        ////////////////
        // Attributes //
        ////////////////
      public:
        inline static std::map<GameState, Ref<Scene>> Scenes;
        inline static GameState CurrentScene;
    };
}; // namespace FlappyBird

#endif /* !RTYPELAYER_HPP_ */
