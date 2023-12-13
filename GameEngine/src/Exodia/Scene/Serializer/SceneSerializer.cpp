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
        try {
            YAML::Node data = YAML::LoadFile(path);

            if (!data["Scene"]) {
                EXODIA_CORE_ERROR("Scene file '{0}' is invalid !", path.string());
                return;
            }

            std::string sceneName = data["Scene"].as<std::string>();

            EXODIA_CORE_INFO("Deserializing scene '{0}'...", sceneName);

            _Scene->SetName(sceneName);

            if (!data["Entities"])
                return;

            auto entities = data["Entities"];

            if (entities) {
                for (YAML::detail::iterator_value entity : entities) {
                    Entity *newEntity = _Scene->CreateEntityWithUUID(entity["Entity"].as<uint64_t>());

                    if (!newEntity)
                        return;

                    for (YAML::detail::iterator_value component : entity) {
                        std::string componentType = component.first.as<std::string>();

                        if (componentType == "Entity" || componentType == "IDComponent")
                            continue;

                        DeserializeComponent(componentType, entity, newEntity);
                    }
                }
            }
        } catch (const YAML::BadConversion& e) {
            EXODIA_CORE_ERROR("Failed to deserialize scene file '{0}':\n\t{1}", path.string(), e.what());
        } catch (const YAML::Exception& e) {
            EXODIA_CORE_ERROR("Failed to deserialize scene file '{0}':\n\t{1}", path.string(), e.what());
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

    void SceneSerializer::DeserializeComponent(const std::string &componentType, const YAML::Node &componentNode, Entity *entity)
    {
        try {
            std::function<IComponentContainer *(Buffer)> func = Project::GetActive()->GetComponentFactory(componentType);

            if (!func) {
                EXODIA_CORE_WARN("Component '{0}' is not registered !", componentType);

                return;
            }

            IComponentContainer *container = func(Buffer());

            container->Deserialize(componentNode);
            entity->AddComponent(container);
        } catch (const YAML::BadConversion &e) {
            EXODIA_CORE_ERROR("Error deserializing component '{0}': {1}", componentType, e.what());
        }
    }
};
