/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** SceneSerializer
*/

// Exodia Scene includes
#include "SceneSerializer.hpp"

// Exodia ECS includes
#include "ECS/Component/Components.hpp"

// External includes
#include <yaml-cpp/yaml.h>
#include <fstream>
#include <string>

namespace YAML {

    ///////////////
    // Structure //
    ///////////////

    template<>
    struct convert<glm::vec2> {
        static Node encode(const glm::vec2 &rhs)
        {
            Node node;

            node.push_back(rhs.x);
            node.push_back(rhs.y);
            node.SetStyle(EmitterStyle::Flow);
            return node;
        }

        static bool decode(const Node &node, glm::vec2 &rhs)
        {
            if (!node.IsSequence() || node.size() != 2)
                return false;

            rhs.x = node[0].as<float>();
            rhs.y = node[1].as<float>();
            return true;
        }
    };

    template<>
    struct convert<glm::vec3> {
        static Node encode(const glm::vec3 &rhs)
        {
            Node node;

            node.push_back(rhs.x);
            node.push_back(rhs.y);
            node.push_back(rhs.z);
            return node;
        }

        static bool decode(const Node &node, glm::vec3 &rhs)
        {
            if (!node.IsSequence() || node.size() != 3)
                return false;

            rhs.x = node[0].as<float>();
            rhs.y = node[1].as<float>();
            rhs.z = node[2].as<float>();
            return true;
        }
    };

    template<>
    struct convert<glm::vec4> {
        static Node encode(const glm::vec4 &rhs)
        {
            Node node;

            node.push_back(rhs.x);
            node.push_back(rhs.y);
            node.push_back(rhs.z);
            node.push_back(rhs.w);
            return node;
        }

        static bool decode(const Node &node, glm::vec4 &rhs)
        {
            if (!node.IsSequence() || node.size() != 4)
                return false;

            rhs.x = node[0].as<float>();
            rhs.y = node[1].as<float>();
            rhs.z = node[2].as<float>();
            rhs.w = node[3].as<float>();
            return true;
        }
    };
};

namespace Exodia {


    //////////////////////////////
    // Constructor & Destructor //
    //////////////////////////////

    SceneSerializer::SceneSerializer(Ref<Scene> scene) : _Scene(scene) {};

    /////////////
    // Methods //
    /////////////

    void SceneSerializer::Serialize(const std::filesystem::path &path)
    {
        YAML::Emitter out;

        out << YAML::BeginMap;
        out << YAML::Key << "Scene" << YAML::Value << _Scene->GetName();
        out << YAML::Key << "Entities" << YAML::Value << YAML::BeginSeq;
        {
            _Scene->GetWorld().ForAll([&](Entity *entity) {
                if (entity == nullptr || !entity->GetComponent<IDComponent>())
                    return;

                SerializeEntity(out, entity);
            });
        }
        out << YAML::EndSeq;
        out << YAML::EndMap;

        std::ofstream fout(path);

        fout << out.c_str();
    }

    void SceneSerializer::Deserialize(const std::filesystem::path &path)
    {
        YAML::Node data;

        try {
            data = YAML::LoadFile(path);
        } catch (YAML::ParserException &e) {
            EXODIA_CORE_ERROR("Failed to load scene file '{0}' !", path.string());

            return;
        }

        if (!data["Scene"]) {
            EXODIA_CORE_ERROR("Scene file '{0}' is invalid !", path.string());

            return;
        }
    
        try {
            std::string sceneName = data["Scene"].as<std::string>();

            EXODIA_CORE_INFO("Deserializing scene '{0}'...", sceneName);

            _Scene->SetName(sceneName);
        } catch (YAML::BadConversion &e) {
            EXODIA_CORE_ERROR("Scene file '{0}' is invalid !", path.string());

            return;
        }

        if (!data["Entities"])
            return;

        auto entities = data["Entities"];

        for (auto entity : entities) {
            if (!entity["Entity"])
                continue;
            uint64_t uuid = 0;

            try {
                uuid = entity["Entity"].as<uint64_t>();
            } catch (YAML::BadConversion &e) {
                EXODIA_CORE_ERROR("Entity has no ID !");

                continue;
            }

            Entity *newEntity = _Scene->CreateEntityWithUUID(uuid);

            if (!newEntity)
                return;

            for (auto component : entity) {
                if (component["IDComponent"])
                    continue;
                else if (component["TransformComponent"]) {
                    try {
                        auto transform = component["TransformComponent"];
                        auto &tc       = newEntity->GetComponent<TransformComponent>().Get();

                        tc.Translation = transform["Translation"].as<glm::vec3>();
                        tc.Rotation    = transform["Rotation"].as<glm::vec3>();
                        tc.Scale       = transform["Scale"].as<glm::vec3>();
                    } catch (YAML::BadConversion &e) {
                        EXODIA_CORE_ERROR("Transform component has invalid data !");

                        continue;
                    }
                }






                // -- TODO: Implement the user Factory for deserialization -- //
                /*std::string componentType;

                try {
                    componentType = component.first.as<std::string>();
                } catch (YAML::BadConversion &e) {
                    EXODIA_CORE_ERROR("Component has no type !");

                    continue;
                }
                if (componentType == "Entity")
                    continue;

                DeserializeComponent(newEntity, componentType, component.second);*/
            }
        }
    }

    void SceneSerializer::SerializeEntity(YAML::Emitter &out, Entity *entity)
    {
        out << YAML::BeginMap;
        out << YAML::Key << "Entity" << YAML::Value << entity->GetComponent<IDComponent>().Get().ID;
        {
            for (auto &component : entity->GetAllComponents()) {
                if (component)
                    component->Serialize(out);
            }
        }
        out << YAML::EndMap;
    }

    void SceneSerializer::DeserializeComponent(Entity *entity, std::string componentType, YAML::Node &componentData)
    {
        (void)entity;
        (void)componentType;
        (void)componentData;
        // TODO: Implement DeserializeComponent
    }
};
