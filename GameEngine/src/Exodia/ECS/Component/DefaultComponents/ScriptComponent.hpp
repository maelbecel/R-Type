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

    // External includes
    #include <string>
    #include <functional>

namespace Exodia {

    struct ScriptComponent : public Component {
        std::string Name;

        ScriptableEntity *Instance = nullptr;

        std::function<ScriptableEntity *()>    InstantiateScript;
        std::function<void(ScriptComponent *)> DestroyScript;

        void Bind(const std::string &name)
        {
            Name = name;

            InstantiateScript = [this]() -> ScriptableEntity * {
                return ScriptEngine::InstantiateScript(Name);
            };

            DestroyScript = [](ScriptComponent *script) {
                if (script != nullptr && script->Instance != nullptr) {
                    delete script->Instance;
                    script->Instance = nullptr;
                }
            };
        }

        virtual void Serialize(YAML::Emitter &out) override
        {
            out << YAML::Key << "ScriptComponent";
            out << YAML::BeginMap;
            {
                out << YAML::Key << "Name" << YAML::Value << Name;
            }
            out << YAML::EndMap;
        }

        virtual void Deserialize(UNUSED const YAML::Node &node) override
        {
            try {
                auto script = node["ScriptComponent"];

                Bind(script["Name"].as<std::string>());
            } catch (YAML::BadConversion &e) {
                EXODIA_CORE_WARN("ScriptComponent deserialization failed: {0}", e.what());
            }
        }

        virtual void DrawComponent() override
        {
            if (Name.empty()) {
                if (ImGui::Button("Add Script"))
                    ImGui::OpenPopup("AddScript");

                if (ImGui::BeginPopup("AddScript")) {
                    const auto &scripts = ScriptEngine::GetScriptableEntities();

                    for (auto script : scripts) {
                        if (ImGui::MenuItem(script.c_str())) {
                            Bind(script);

                            ImGui::CloseCurrentPopup();
                        }
                    }

                    ImGui::EndPopup();
                }
            } else {
                ImGui::Text("Script: %s", Name.c_str());

                ImGui::SameLine();

                if (ImGui::Button("Remove Script")) {
                    Name = "";
                    Instance = nullptr;
                }
            }
        }
    };
};

#endif /* !SCRIPTCOMPONENT_HPP_ */
