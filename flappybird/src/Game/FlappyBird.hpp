/*
** EPITECH PROJECT, 2023
** FlappyBird
** File description:
** FlappyBird
*/

#ifndef FLAPPYBIRD_HPP_
#define FLAPPYBIRD_HPP_

///////////////////////////////////////////////////
// Main include file for FlappyBird              //
// Include this file to use the FlappyBird logic //
// And create your own FlappyBird game           //
///////////////////////////////////////////////////

#include "Exodia.hpp"

#include "Scripts/Player.hpp"

namespace FlappyBird {

    inline static void Init() {
        // -- Init the FlappyBird project ------------------------------------------
        Ref<Exodia::Project> project = Exodia::Project::Load("./Assets/FlappyBird.proj");

        // -- Register FlappyBird components ---------------------------------------

        // -- Register FlappyBird scripts ------------------------------------------
        project->RegisterScript("Player", []() -> Exodia::ScriptableEntity * {
            return new FlappyBird::Player;
        });

        // -- Register FlappyBird systems ------------------------------------------
    }
}; // namespace FlappyBird

#endif /* !FLAPPYBIRD_HPP_ */
