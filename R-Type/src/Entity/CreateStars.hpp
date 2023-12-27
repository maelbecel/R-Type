/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** Create stars
*/

#ifndef CREATESTARS_HPP_
#define CREATESTARS_HPP_

#include "Component/Clock.hpp"
#include "Scripts/Star/Star.hpp"
#include "SceneType.hpp"

namespace Exodia {

    /**
     * @brief Create the stars
     *
     * @param _World
     */
    void CreateStars(std::map<SceneType, std::shared_ptr<Exodia::Scene>> _World);
}; // namespace Exodia

#endif /* !CREATESTARS_HPP_ */
