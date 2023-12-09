/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** SceneSerializer
*/

#include "SceneSerializer.hpp"

namespace Exodia {

    //////////////////////////////
    // Constructor & Destructor //
    //////////////////////////////

    SceneSerializer::SceneSerializer(Ref<Scene> scene) : _Scene(scene) {};

    /////////////
    // Methods //
    /////////////

    void SceneSerializer::Serialize(UNUSED const std::filesystem::path &path) {};

    void SceneSerializer::Deserialize(UNUSED const std::filesystem::path &path) {};
};
