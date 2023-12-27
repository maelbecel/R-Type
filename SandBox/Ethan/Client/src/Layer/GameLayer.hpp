/*
** EPITECH PROJECT, 2023
** ExodiaGameEngine
** File description:
** GameLayer
*/

#ifndef GAMELAYER_HPP_
    #define GAMELAYER_HPP_

    // Exodia includes
    #include "Exodia.hpp"

    // R-Type Games includes
    #include "R-Type.hpp"

    // R-Type Client includes
    #include "GameScene/GameScene.hpp"

namespace RType {

    enum SceneType {
        LOADING,
        MENU,
        GAME,
        END
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
            void OnUpdate(Exodia::Timestep ts) override;

        ////////////////
        // Attributes //
        ////////////////
        private:

            std::map<SceneType, Ref<GameScene>> _Scenes;
            SceneType _CurrentScene;
    };
};

#endif /* !GAMELAYER_HPP_ */
