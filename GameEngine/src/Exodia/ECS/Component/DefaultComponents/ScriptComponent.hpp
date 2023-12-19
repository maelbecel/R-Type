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
        ScriptableEntity *Instance = nullptr;

        std::function<ScriptableEntity *()>    InstantiateScript;
        std::function<void(ScriptComponent *)> DestroyScript;

        template<typename T>
        void Bind()
        {
            InstantiateScript = []() -> ScriptableEntity * {
                return static_cast<ScriptableEntity *>(new T());
            };

            DestroyScript = [](ScriptComponent *script) {
                if (script != nullptr && script->Instance != nullptr) {
                    delete static_cast<T *>(script->Instance);
                    script->Instance = nullptr;
                }
            };
        }
    };
};

#endif /* !SCRIPTCOMPONENT_HPP_ */
