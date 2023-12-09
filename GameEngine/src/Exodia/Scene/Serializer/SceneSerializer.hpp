/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** SceneSerializer
*/

#ifndef SCENESERIALIZER_HPP_
    #define SCENESERIALIZER_HPP_

    // Exodia Scene includes
    #include "Scene/Scene/Scene.hpp"

    // Exodia Utils includes
    #include "Utils/Memory.hpp"

    // External includes
    #include <filesystem>

namespace Exodia {

    class SceneSerializer {

        //////////////////////////////
        // Constructor & Destructor //
        //////////////////////////////
        public:

            SceneSerializer(Ref<Scene> scene);
            ~SceneSerializer() = default;

        /////////////
        // Methods //
        /////////////
        public:

            void Serialize(const std::filesystem::path &path);
            void Deserialize(const std::filesystem::path &path);

        ////////////////
        // Attributes //
        ////////////////
        private:

            Ref<Scene> _Scene;
    };
};

#endif /* !SCENESERIALIZER_HPP_ */
