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

    // R-Type includes
    #include "R-Type.hpp"

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

            Ref<Exodia::Scene> _Scene;        
    };
};

#endif /* !GAMELAYER_HPP_ */
