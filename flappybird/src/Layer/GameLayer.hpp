/*
** EPITECH PROJECT, 2023
** ExodiaGameEngine
** File description:
** GameLayer
*/

#ifndef GAMELAYER_HPP_
#define GAMELAYER_HPP_

#include "Game/FlappyBird.hpp"
#include "Level/Level.hpp"

namespace FlappyBird {

    using namespace Exodia;

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
        void OnUpdate(Timestep ts) override;
        void OnImGUIRender() override;
        void OnEvent(Event &event) override;

      private:
        bool OnKeyPressedEvent(KeyPressedEvent &event);
        bool OnMouseButtonPressedEvent(MouseButtonPressedEvent &event);

        ////////////////
        // Attributes //
        ////////////////
      private:
        GameState _State;
        bool _Blink;
        float _Time;

        Level _Level;
    };
}; // namespace FlappyBird

#endif /* !GAMELAYER_HPP_ */
