/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** Create pata-pata
*/

#ifndef CREATEPATAPATA_HPP_
#define CREATEPATAPATA_HPP_

#include "Component/Animation.hpp"
#include "Component/Clock.hpp"
#include "Component/Health.hpp"
#include "Scripts/Pata-pata.hpp"
#include "SceneType.hpp"

namespace Exodia {

    /**
     * @brief Create a PataPata object
     *
     * @param _World
     */
    void CreatePataPata(std::map<SceneType, std::shared_ptr<Exodia::Scene>> _World);
}; // namespace Exodia

#endif /* !CREATEPATAPATA_HPP_ */
