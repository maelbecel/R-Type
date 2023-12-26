/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** Create background
*/

#ifndef CREATEBACKGROUND_HPP_
#define CREATEBACKGROUND_HPP_

#include "Exodia.hpp"
#include "SceneType.hpp"

namespace Exodia {

    /**
     * @brief Create the background
     *
     * @param _World
     */
    void CreateBackground(std::map<SceneType, std::shared_ptr<Exodia::Scene>> _World);
}; // namespace Exodia

#endif /* !CREATEBACKGROUND_HPP_ */
