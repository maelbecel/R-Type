/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** Create player
*/

#ifndef CREATEPLAYER_HPP_
    #define CREATEPLAYER_HPP_

    #include "Component/Animation.hpp"
    #include "Component/Health.hpp"
    #include "Scripts/Player/Player.hpp"

namespace Exodia {

    /**
     * @brief Create a Player object
     *
     * @param _World
     */
    void CreatePlayer(World *_World);
};

#endif /* !CREATEPLAYER_HPP_ */
