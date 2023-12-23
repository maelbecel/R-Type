/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** ScriptComponent
*/

#ifndef SCRIPTCOMPONENT_HPP_
#define SCRIPTCOMPONENT_HPP_

// Exodia Script includes
#include "Script/Engine/ScriptEngine.hpp"
#include "Script/Interface/ScriptableEntity.hpp"

#include "Utils/LibrairyLoader.hpp"

// Exodia Debug includes
#include "Debug/Logs.hpp"

// Exodia ECS includes
#include "ECS/Interface/Component.hpp"

// External includes
#include <functional>
#include <string>

namespace Exodia
{

    struct ScriptComponent : public Component
    {
        ScriptableEntity *Instance = nullptr;

        std::function<ScriptableEntity *()>      InstantiateScript;
        std::function<void( ScriptComponent * )> DestroyScript;

        template <typename T> void Bind()
        {
            InstantiateScript = []() -> ScriptableEntity * { return static_cast<ScriptableEntity *>( new T() ); };

            DestroyScript = []( ScriptComponent *script ) {
                if ( script != nullptr && script->Instance != nullptr )
                {
                    delete static_cast<T *>( script->Instance );
                    script->Instance = nullptr;
                }
            };
        }
    };
}; // namespace Exodia

#endif /* !SCRIPTCOMPONENT_HPP_ */
