/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** GameScene
*/

#ifndef GAMESCENE_HPP_
    #define GAMESCENE_HPP_

    // Exodia includes
    #include "Exodia.hpp"

namespace RType {

    class GameScene {

        //////////////////////////////
        // Constructor & Destructor //
        //////////////////////////////
        public:

            virtual ~GameScene() = default;

        /////////////
        // Methods //
        /////////////
        public:

            virtual void OnCreate() = 0;
            virtual void OnDestroy() = 0;

            virtual void OnUpdate(Exodia::Timestep ts) = 0;
            virtual void OnEvent(Exodia::Event &event) = 0;
    };
};

#endif /* !GAMESCENE_HPP_ */
