/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** SceneSerializer
*/

// Exodia Scene includes
#include "SceneSerializer.hpp"

// Exodia ECS includes
//#include "ECS/Component/Components.hpp"

#include "ECS/Component/DefaultComponents/IDComponent.hpp"

// Exodia Utils includes
//#include "Utils/Yaml-cpp.hpp"

// External includes
#include <fstream>

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

    void SceneSerializer::Deserialize(UNUSED const std::filesystem::path &path) {};

    void SceneSerializer::SerializeEntity(YAML::Emitter &out, Entity *entity)
    {
        out << YAML::BeginMap;
        out << YAML::Key << "Entity" << YAML::Value << entity->GetComponent<IDComponent>().Get().ID;
        {
            for (auto &component : entity->GetAllComponents()) {
                if (component)
                    component->Serialize(out);
                //std::cout << "Serializing entity: " << entity->GetComponent<TagComponent>().Get().Tag << std::endl;
            }
        }
        out << YAML::EndMap;
    }
};
