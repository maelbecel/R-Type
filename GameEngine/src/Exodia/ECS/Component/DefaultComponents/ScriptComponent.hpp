/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** ScriptComponent
*/

#ifndef SCRIPTCOMPONENT_HPP_
    #define SCRIPTCOMPONENT_HPP_

    // Exodia Script includes
    #include "Script/Interface/ScriptableEntity.hpp"
    #include "Script/Engine/ScriptEngine.hpp"

    #include "Utils/LibrairyLoader.hpp"

    // Exodia Debug includes
    #include "Debug/Logs.hpp"

    // Exodia ECS includes
    #include "ECS/Interface/Component.hpp"

    // Exodia Project includes
    #include "Project/Project.hpp"

    // External includes
    #include <string>
    #include <functional>

namespace Exodia {

    struct ScriptComponent : public Component {
        std::string Name;

        ScriptableEntity *Instance = nullptr;

        std::function<ScriptableEntity *(std::string)>    InstantiateScript;
        std::function<void(ScriptComponent *)> DestroyScript;

        void Bind(std::string name)
        {
            Name = name;

            InstantiateScript = [](std::string name) -> ScriptableEntity * {
                auto factory = Project::GetActive()->GetScriptFactory(name);

                if (factory == nullptr) {
                    EXODIA_CORE_ERROR("No script factory found for script '{0}'", name);

                    return nullptr;
                }
                return factory();
            };

            DestroyScript = [](ScriptComponent *script) {
                if (script != nullptr && script->Instance != nullptr) {
                    delete script->Instance;

                    script->Instance = nullptr;
                }
            };
        }

        virtual void Serialize(YAML::Emitter &out)
        {
            out << YAML::Key << "ScriptComponent";
            out << YAML::BeginMap;
            {
                out << YAML::Key << "Name" << YAML::Value << Name;
            }
            out << YAML::EndMap;
        }

        virtual void Deserialize(const YAML::Node &node)
        {
            try {
                auto script = node["ScriptComponent"];

                Name = script["Name"].as<std::string>();

                Bind(Name);
            } catch (YAML::BadConversion &e) {
                EXODIA_CORE_WARN("ScriptComponent deserialization failed:\n\t{0}", e.what());
            }
        }

        virtual Buffer SerializeData() override
        {
            try {
                if (Name.empty())
                    return Buffer();
                Buffer buffer(sizeof(Name));

                std::memcpy(buffer.Data, Name.c_str(), sizeof(Name));

                return buffer;
            } catch (std::exception &error) {
                EXODIA_CORE_WARN("ScriptComponent serialization failed:\n\t{0}", error.what());
            }
            return Buffer();
        }

        virtual void DeserializeData(Buffer data) override
        {
            try {
                if (data.Size == 0)
                    return;
                Memcopy(&Name, data.Data, sizeof(Name));

                Bind(Name);
            } catch (std::exception &error) {
                EXODIA_CORE_WARN("ScriptComponent deserialization failed:\n\t{0}", error.what());
            }
        }
    };
};

#endif /* !SCRIPTCOMPONENT_HPP_ */
