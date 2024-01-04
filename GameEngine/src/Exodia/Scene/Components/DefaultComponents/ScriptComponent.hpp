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

// Exodia Debug includes
#include "Exodia-Debug.hpp"

// Exodia ECS includes
#include "Scene/Components/Component.hpp"

// Exodia Project includes
#include "Project/Project.hpp"

// External includes
#include <string>
#include <functional>

namespace Exodia {

    struct ScriptComponent : public Component {
        std::string Name;

        ScriptableEntity *Instance = nullptr;

        std::function<ScriptableEntity *(std::string)> InstantiateScript = nullptr;
        std::function<void(ScriptComponent *)> DestroyScript = nullptr;

        void Bind(std::string name) {
            if (name.empty())
                return;
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

        virtual void Serialize(YAML::Emitter &out) {
            out << YAML::Key << "ScriptComponent";
            out << YAML::BeginMap;
            { out << YAML::Key << "Name" << YAML::Value << Name; }
            out << YAML::EndMap;
        }

        virtual void Deserialize(const YAML::Node &node) {
            try {
                auto script = node["ScriptComponent"];

                Name = script["Name"].as<std::string>();

                Bind(Name);
            } catch (YAML::BadConversion &e) {
                EXODIA_CORE_WARN("ScriptComponent deserialization failed:\n\t{0}", e.what());
            }
        }

        virtual Buffer SerializeData() override {
            try {
                Buffer buffer(sizeof(char) * Name.size());

                std::memcpy(buffer.Data, Name.data(), sizeof(char) * Name.size());

                EXODIA_CORE_WARN("Serialized ScriptComponent '{0}': Data({1})", Name, buffer.Size);

                return buffer;
            } catch (std::exception &error) {
                EXODIA_CORE_WARN("ScriptComponent serialization failed:\n\t{0}", error.what());
            }
            return Buffer();
        }

        virtual void DeserializeData(Buffer data) override {
            if (!data || data.Size == 0)
                return;
            try {
                for (uint32_t i = 0; i < data.Size; i++)
                    Name.push_back((char)data.Data[i]);
                Bind(Name);
            } catch (std::exception &error) {
                EXODIA_CORE_WARN("ScriptComponent deserialization failed:\n\t{0}", error.what());
            }
        }
    };
}; // namespace Exodia

#endif /* !SCRIPTCOMPONENT_HPP_ */
