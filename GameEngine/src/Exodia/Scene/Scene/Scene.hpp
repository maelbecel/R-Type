/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** Scene
*/

#ifndef SCENE_HPP_
    #define SCENE_HPP_

    // Exodia Asset includes
    #include "Asset/Asset.hpp"

namespace Exodia {

    class Scene : public Asset {

        ///////////////////////
        // Getters & Setters //
        ///////////////////////
        public:

            virtual AssetType GetType() const override;
    };
};

#endif /* !SCENE_HPP_ */
