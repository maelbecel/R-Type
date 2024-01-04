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
#include "Exodia-Utils.hpp"

// External includes
#include <filesystem>
#include <yaml-cpp/yaml.h>

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

      private:
        void SerializeEntity(YAML::Emitter &out, Entity *entity);
        void DeserializeComponent(const std::string &componentType, const YAML::Node &componentNode, GameObject gameobject);

        ////////////////
        // Attributes //
        ////////////////
      private:
        Ref<Scene> _Scene;
    };
}; // namespace Exodia

#endif /* !SCENESERIALIZER_HPP_ */
