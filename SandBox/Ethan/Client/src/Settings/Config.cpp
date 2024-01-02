/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** Config
*/

#include "Exodia.hpp"
#include "Config.hpp"

// External includes
#include <filesystem>
#include <fstream>
#include <yaml-cpp/yaml.h>

namespace RType {

    /////////////
    // Methods //
    /////////////

    void Config::Init()
    {
        if (!std::filesystem::exists(".rtype"))
            std::filesystem::create_directory(".rtype");
    }

    bool Config::Read()
    {
        if (!std::filesystem::exists(".rtype/config.cfg"))
            return false;
        YAML::Node config;

        try {
            config = YAML::LoadFile(".rtype/config.cfg");

            if (!config)
                return false;
        } catch (const YAML::ParserException &error) {
            EXODIA_CORE_ERROR("Failed to parse config file:\n\t{0}", error.what());

            return false;
        }

        auto window = config["[Window Configuration]"];

        if (!window)
            return false;
        
        try {
            if (window["Width"]) {
                uint32_t width = window["Width"].as<uint32_t>();
                uint32_t height = Exodia::Application::Get().GetWindow().GetHeight();

                Exodia::Application::Get().GetWindow().Resize(width, height);
                Exodia::Renderer::OnWindowResize(width, height);
            } if (window["Height"]) {
                uint32_t width = Exodia::Application::Get().GetWindow().GetWidth();
                uint32_t height = window["Height"].as<uint32_t>();

                Exodia::Application::Get().GetWindow().Resize(width, height);
                Exodia::Renderer::OnWindowResize(width, height);
            }

            EXODIA_CORE_INFO("Resizing window to ({0}, {1})", Exodia::Application::Get().GetWindow().GetWidth(), Exodia::Application::Get().GetWindow().GetHeight());
        } catch (const YAML::BadConversion &error) {
            EXODIA_CORE_ERROR("Failed to parse config file:\n\t{0}", error.what());

            return false;
        }

        return true;
    }

    bool Config::Write()
    {
        if (!std::filesystem::exists(".rtype/config.cfg"))
            std::filesystem::create_directory(".rtype");
        std::ofstream file(".rtype/config.cfg");

        if (!file.is_open())
            return false;

        YAML::Emitter out;
        {
            out << YAML::BeginMap;
            out << YAML::Key << "[Window Configuration]" << YAML::Value;
            {
                out << YAML::BeginMap;
                out << YAML::Key << "Width" << YAML::Value << Exodia::Application::Get().GetWindow().GetWidth();
                out << YAML::Key << "Height" << YAML::Value << Exodia::Application::Get().GetWindow().GetHeight();
                out << YAML::EndMap;
            }
            out << YAML::EndMap;
        }

        file << out.c_str();
        return true;
    }
};
