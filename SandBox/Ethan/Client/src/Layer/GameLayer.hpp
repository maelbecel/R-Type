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

    class GameLayer : public Exodia::Layer {

        //////////////////////////////
        // Constructor & Destructor //
        //////////////////////////////
        public:

            GameLayer();
            ~GameLayer() = default;
    };
};

#endif /* !GAMELAYER_HPP_ */
