/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** SceneSerializer
*/

// Exodia Scene includes
#include "SceneSerializer.hpp"

// Exodia ECS includes
#include "ECS/Component/DefaultComponents/IDComponent.hpp"

// External includes
#include <yaml-cpp/yaml.h>
#include <fstream>
#include <string>

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
                std::string componentType;

                try {
                    componentType = component.first.as<std::string>();
                } catch (YAML::BadConversion &e) {
                    EXODIA_CORE_ERROR("Component has no type !");

                    continue;
                }
                if (componentType == "Entity")
                    continue;

                DeserializeComponent(newEntity, componentType, component.second);
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
