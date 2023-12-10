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

    // External includes
    #include <yaml-cpp/yaml.h>
    #include <string>

namespace Exodia {

    struct ScriptComponent {
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

        void Serialize(UNUSED YAML::Emitter &out)
        {
            //TODO: Script Serialization implementation
        }
    };
};

#endif /* !SCRIPTCOMPONENT_HPP_ */
