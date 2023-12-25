/*
** EPITECH PROJECT, 2023
** ExodiaGameEngine
** File description:
** ExodiaEngine
*/

#include "GameLayer.hpp"

namespace RType {

    //////////////////////////////
    // Constructor & Destructor //
    //////////////////////////////

    GameLayer::GameLayer() : Layer("R-Type Layer")
    {
        Config::Init();

        if (!Config::Read())
            Config::Write();
    }
};
