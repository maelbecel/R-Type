/*
** EPITECH PROJECT, 2023
** ExodiaGameEngine
** File description:
** GameLayer
*/

#ifndef GAMELAYER_HPP_
    #define GAMELAYER_HPP_

    #include "Game/FlappyBird.hpp"

    using namespace Exodia;

namespace FlappyBird {

    enum class GameState {
        Play,
        Menu,
        GameOver
    };

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

#endif /* !GAMELAYER_HPP_ */
