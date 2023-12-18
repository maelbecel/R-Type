/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** ScriptEngine
*/

#ifndef SCRIPTENGINE_HPP_
    #define SCRIPTENGINE_HPP_

    // External includes
    #include <unordered_map>
    #include <string>
    #include <vector>

namespace Exodia {

    class ScriptableEntity;

    struct ScriptEngineData {
        std::vector<std::string> ScriptableEntities;
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

            static ScriptableEntity *InstantiateScript(const std::string &name);
            static std::vector<std::string> GetScriptableEntities();

        ////////////////
        // Attributes //
        ////////////////
        public:

            static ScriptEngineData *Data;
    };
};

#endif /* !SCRIPTENGINE_HPP_ */
