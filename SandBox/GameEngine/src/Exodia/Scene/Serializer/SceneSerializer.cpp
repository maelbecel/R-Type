/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** SceneSerializer
*/

// Exodia Scene includes
#include "SceneSerializer.hpp"

// Exodia ECS includes
#include "Scene/Components/Components.hpp"

// External includes
#include <yaml-cpp/yaml.h>
#include <fstream>
#include <string>

namespace Exodia {

    //////////////////////////////
    // Constructor & Destructor //
    //////////////////////////////

    SceneSerializer::SceneSerializer(Ref<Scene> scene) : _Scene(scene){};

    /////////////
    // Methods //
    /////////////

    void SceneSerializer::Serialize(const std::filesystem::path &path) {
        YAML::Emitter out;

        out << YAML::BeginMap;
        out << YAML::Key << "Scene" << YAML::Value << _Scene->GetName();

        out << YAML::Key << "Entities" << YAML::Value << YAML::BeginSeq;
        {
            _Scene->GetWorld().ForEach<IDComponent>(
                [&](Entity *entity, auto id) {
                    out << YAML::BeginMap;
                    out << YAML::Key << "Entity" << YAML::Value << id.Get().ID;
                    { SerializeEntity(out, entity); }
                    out << YAML::EndMap;
                },
                false);
        }
        out << YAML::EndSeq;

        out << YAML::Key << "Systems" << YAML::Value << YAML::BeginSeq;
        {
            for (auto &system : _Scene->_Systems) {
                out << YAML::BeginMap;
                out << YAML::Key << "System" << YAML::Value << system.first;
                out << YAML::EndMap;
            }
        }
        out << YAML::EndSeq;
        out << YAML::EndMap;

        std::ofstream fout(path);

        fout << out.c_str();
    }

    void SceneSerializer::Deserialize(const std::filesystem::path &path) {
        std::string filepath = path.string();

        try {
            YAML::Node data = YAML::LoadFile(filepath);

            if (!data["Scene"]) {
                EXODIA_CORE_ERROR("Scene file '{0}' is invalid !", filepath);
                return;
            }

            std::string sceneName = data["Scene"].as<std::string>();

            EXODIA_CORE_INFO("Deserializing scene '{0}'...", sceneName);

            _Scene->SetName(sceneName);

            if (data["Entities"]) {
                auto entities = data["Entities"];

                for (YAML::detail::iterator_value entity : entities) {
                    GameObject newGameObject = _Scene->CreateEntityWithUUID(entity["Entity"].as<uint64_t>());

                    for (YAML::detail::iterator_value component : entity) {
                        std::string componentType = component.first.as<std::string>();

                        if (componentType == "Entity" || componentType == "IDComponent")
                            continue;

                        SceneSerializer::DeserializeComponent(componentType, entity, newGameObject);
                    }
                }
            }

            if (data["Systems"]) {
                auto systems = data["Systems"];

                for (YAML::detail::iterator_value system : systems) {
                    std::string systemType = system["System"].as<std::string>();

                    std::function<Exodia::EntitySystem *()> func = Project::GetActive()->GetSystemFactory(systemType);

                    if (!func) {
                        EXODIA_CORE_WARN("System '{0}' is not registered !", systemType);

                        continue;
                    }
                    _Scene->RegisterSystem(func());
                }
            }
        } catch (const YAML::BadConversion &e) {
            EXODIA_CORE_ERROR("Failed to deserialize scene file '{0}':\n\t{1}", filepath, e.what());
        } catch (const YAML::Exception &e) {
            EXODIA_CORE_ERROR("Failed to deserialize scene file '{0}':\n\t{1}", filepath, e.what());
        }
    }

    void SceneSerializer::SerializeEntity(YAML::Emitter &out, Entity *entity) {
        for (auto &component : entity->GetAllComponents()) {
            if (component)
                component->Serialize(out);
        }
    }

    void SceneSerializer::DeserializeComponent(const std::string &componentType, const YAML::Node &componentNode,
                                               GameObject gameObject) {
        try {
            std::function<IComponentContainer *(Buffer)> func =
                Project::GetActive()->GetComponentFactory(componentType);

            if (!func) {
                EXODIA_CORE_WARN("Component '{0}' is not registered !", componentType);

                return;
            }

            IComponentContainer *container = func(Buffer());

            container->Deserialize(componentNode);
            gameObject.AddComponent(container);
        } catch (const YAML::BadConversion &e) {
            EXODIA_CORE_ERROR("Error deserializing component '{0}': {1}", componentType, e.what());
        }
    }
}; // namespace Exodia
