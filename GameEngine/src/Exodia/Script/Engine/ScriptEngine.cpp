/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** ScriptEngine
*/

// Exodia Script
#include "ScriptEngine.hpp"

// Exodia Project
#include "Project/Project.hpp"

// Exodia Utils
#include "Utils/LibrairyLoader.hpp"

namespace Exodia {

    ///////////////////////
    // Static Attributes //
    ///////////////////////

    ScriptEngineData *ScriptEngine::Data = nullptr;

    /////////////
    // Methods //
    /////////////

    void ScriptEngine::Init()
    {
        std::filesystem::path scriptModulePath = Project::GetActiveScriptPath();

        Data = new ScriptEngineData();

        if (std::filesystem::exists(scriptModulePath)) {
            for (const auto &file : std::filesystem::directory_iterator(scriptModulePath)) {
                if (file.is_regular_file() && file.path().extension() == ".lua")
                    Data->LoadScript(file.path().string());
            }
        }
    }

    void ScriptEngine::Shutdown()
    {
        for (auto &script : Data->Scripts)
            script.second.abandon();
        Data->Scripts.clear();

        if (Data) {
            delete Data;
            Data = nullptr;
        }
    }

    ///////////////////////
    // Getters & Setters //
    ///////////////////////

    sol::optional<sol::table> ScriptEngine::GetScriptPublicVariables(const std::string &scriptName)
    {
        if (Data->Scripts.find(scriptName) != Data->Scripts.end()) {
            sol::table global = Data->Scripts[scriptName].lua_state();
            sol::optional<sol::table> publicTable = global["public"];

            if (!publicTable)
                return sol::nullopt;
            return *publicTable;
        }
        return sol::nullopt;
    }

    sol::protected_function ScriptEngine::GetScript(const std::string &name)
    {
        if (Data->Scripts.find(name) != Data->Scripts.end())
            return Data->Scripts[name];
        return nullptr;
    }

    std::vector<std::string> ScriptEngine::GetScriptableEntities()
    {
        std::vector<std::string> scriptableEntities;

        for (const auto &script : Data->Scripts)
            scriptableEntities.push_back(script.first);
        return scriptableEntities;
    }
};
