/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** Settings
*/

// R-Type Game includes
#include "R-Type.hpp"

// R-Type Client includes
#include "Settings.hpp"
#include "Events/GameEvents.hpp"

// External includes
#include <fstream>
#include <filesystem>
#include <yaml-cpp/yaml.h>

namespace RType {

    /////////////
    // Methods //
    /////////////

    bool Settings::Read()
    {
        if (!std::filesystem::exists(".rtype/keybind.cfg"))
            return false;
        YAML::Node config;

        try {
            config = YAML::LoadFile(".rtype/keybind.cfg");

            if (!config)
                return false;
        } catch (const YAML::ParserException &error) {
            EXODIA_CORE_ERROR("Failed to parse keybind file:\n\t{0}", error.what());

            return false;
        }

        auto keys = config["[KeyBinds Configuration]"];

        if (!keys)
            return false;
        
        try {
            if (keys["UP"] && keys["UP"].IsSequence() && keys["UP"].size() == 2)
                KeyBinds[UP]      = std::make_pair(keys["UP"][0].as<int>(), keys["UP"][1].as<int>());
            if (keys["DOWN"] && keys["DOWN"].IsSequence() && keys["DOWN"].size() == 2)
                KeyBinds[DOWN]    = std::make_pair(keys["DOWN"][0].as<int>(), keys["DOWN"][1].as<int>());
            if (keys["LEFT"] && keys["LEFT"].IsSequence() && keys["LEFT"].size() == 2)
                KeyBinds[LEFT]    = std::make_pair(keys["LEFT"][0].as<int>(), keys["LEFT"][1].as<int>());
            if (keys["RIGHT"] && keys["RIGHT"].IsSequence() && keys["RIGHT"].size() == 2)
                KeyBinds[RIGHT]   = std::make_pair(keys["RIGHT"][0].as<int>(), keys["RIGHT"][1].as<int>());
            if (keys["ATTACK1"] && keys["ATTACK1"].IsSequence() && keys["ATTACK1"].size() == 2)
                KeyBinds[ATTACK1] = std::make_pair(keys["ATTACK1"][0].as<int>(), keys["ATTACK1"][1].as<int>());
            if (keys["ATTACK2"] && keys["ATTACK2"].IsSequence() && keys["ATTACK2"].size() == 2)
                KeyBinds[ATTACK2] = std::make_pair(keys["ATTACK2"][0].as<int>(), keys["ATTACK2"][1].as<int>());
        } catch (const YAML::BadConversion &error) {
            EXODIA_CORE_ERROR("Failed to convert keybind file:\n\t{0}", error.what());

            return false;
        }
        return true;
    }

    bool Settings::Write()
    {
        if (!std::filesystem::exists(".rtype/keybind.cfg"))
            std::filesystem::create_directory(".rtype");
        std::ofstream file(".rtype/keybind.cfg");

        if (!file.is_open())
            return false;

        YAML::Emitter out;
        {
            out << YAML::BeginMap;
            out << YAML::Key << "[KeyBinds Configuration]" << YAML::Value;
            {
                out << YAML::BeginMap;

                for (auto &keyBind : KeyBinds) {
                    out << YAML::Key << PlayerEventToString(keyBind.first) << YAML::Value << YAML::Flow;
                    {
                        out << YAML::BeginSeq << keyBind.second.first << keyBind.second.second << YAML::EndSeq;
                    }
                }

                out << YAML::EndMap;
            }
            out << YAML::EndMap;
        }

        file << out.c_str();
        return true;
    }
};
