/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** ScriptComponent
*/

#ifndef SCRIPTCOMPONENT_HPP_
    #define SCRIPTCOMPONENT_HPP_

    // Exodia Script includes
    #include "Script/ScriptableEntity.hpp"

    // Exodia ECS includes
    #include "ECS/Interface/Component.hpp"

namespace Exodia {

    struct ScriptComponent : public Component {
        static std::string GetStaticName()
        {
            return "ScriptComponent";
        }

        std::string GetName() const override
        {
            return GetStaticName();
        }

        ScriptableEntity *Instance = nullptr;

        ScriptableEntity *(*InstantiateScript)();
        void              (*DestroyScript)(ScriptComponent *);

        template<typename ScriptClass>
        void Bind()
        {
            InstantiateScript = []() {
                return static_cast<ScriptableEntity *>(new ScriptClass());
            };

            DestroyScript = [](ScriptComponent *script) {
                if (script->Instance != nullptr) {
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
                // TODO: Serialize script
            }
            out << YAML::EndMap;
        }
    };
};

#endif /* !SCRIPTCOMPONENT_HPP_ */
