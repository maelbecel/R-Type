/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** ScriptEngine
*/

#ifndef SCRIPTENGINE_HPP_
    #define SCRIPTENGINE_HPP_

    // Exodia Debug
    #include "Debug/Logs.hpp"

    // Lua include
    #include <sol/sol.hpp>

    // External includes
    #include <unordered_map>
    #include <functional>
    #include <string>
    #include <vector>

namespace Exodia {

    class ScriptableEntity;

    struct ScriptEngineData {
        std::unordered_map<std::string, sol::protected_function> Scripts;

        void LoadScript(const std::string &path)
        {
            sol::state lua;
            
            try {
                sol::protected_function_result loadResult = lua.safe_script_file(path);

                if (!loadResult.valid()) {
                    sol::error err = loadResult;

                    EXODIA_CORE_ERROR("Error while loading script '{0}':\n\t{1}", path, err.what());
                } else {
                    sol::protected_function script = loadResult;

                    Scripts[path] = script;
                }
            } catch (const sol::error &e) {
                EXODIA_CORE_ERROR("Error while loading script '{0}':\n\t{1}", path, e.what());
            }
        }
    };

    class ScriptEngine {

        /////////////
        // Methods //
        /////////////
        public:

            static void Init();
            static void Shutdown();

        ///////////////////////
        // Getters & Setters //
        ///////////////////////
        public:

            static sol::optional<sol::table> GetScriptPublicVariables(const std::string &scriptName);

            static sol::protected_function GetScript(const std::string &name);
            static std::vector<std::string> GetScriptableEntities();

        ////////////////
        // Attributes //
        ////////////////
        public:

            static ScriptEngineData *Data;
    };
};

#endif /* !SCRIPTENGINE_HPP_ */
