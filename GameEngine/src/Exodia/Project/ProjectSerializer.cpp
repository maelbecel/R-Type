/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** ProjectSerializer
*/

// Exodia Project includes
#include "ProjectSerializer.hpp"

// Exodia Debug includes
#include "Debug/Logs.hpp"

// External includes
#include <fstream>
#include <yaml-cpp/yaml.h>

namespace Exodia {

    //////////////////////////////
    // Constructor & Destructor //
    //////////////////////////////

    ProjectSerializer::ProjectSerializer(Ref<Project> project) : _Project(project){};

    /////////////
    // Methods //
    /////////////

    bool ProjectSerializer::Serialize(const std::filesystem::path &path) {
        const auto &config = _Project->GetConfig();

        YAML::Emitter out;
        {
            out << YAML::BeginMap;
            out << YAML::Key << "Project" << YAML::Value;
            {
                out << YAML::BeginMap;
                out << YAML::Key << "Name" << YAML::Value << config.Name;
                out << YAML::Key << "StartScene" << YAML::Value << (uint64_t)config.StartScene;
                out << YAML::Key << "AssetsDirectory" << YAML::Value << config.AssetsDirectory.string();
                out << YAML::Key << "AssetRegistryPath" << YAML::Value << config.AssetRegistryPath.string();
                out << YAML::Key << "ScriptsDirectory" << YAML::Value << config.ScriptsDirectory.string();
                out << YAML::EndMap;
            }
            out << YAML::EndMap;
        }

        std::ofstream file(path);

        file << out.c_str();

        return true;
    }

    bool ProjectSerializer::Deserialize(const std::filesystem::path &path) {
        auto &config = _Project->GetConfig();

        YAML::Node data;

        try {
            data = YAML::LoadFile(path.string());
        } catch (const YAML::ParserException &e) {
            EXODIA_CORE_ERROR("Failed to parse project file `{0}`:\n\t{1}", path.string(), e.what());

            return false;
        }

        auto project = data["Project"];

        if (!project)
            return false;
        if (!project["Name"] || !project["StartScene"] || !project["AssetsDirectory"] ||
            !project["AssetRegistryPath"] || !project["ScriptsDirectory"])
            return false;

        try {
            config.Name = project["Name"].as<std::string>();
            config.StartScene = project["StartScene"].as<std::uint64_t>();
            config.AssetsDirectory = project["AssetsDirectory"].as<std::string>();
            config.AssetRegistryPath = project["AssetRegistryPath"].as<std::string>();
            config.ScriptsDirectory = project["ScriptsDirectory"].as<std::string>();
        } catch (const YAML::BadConversion &e) {
            EXODIA_CORE_ERROR("Failed to parse project file `{0}`:\n\t{1}", path.string(), e.what());

            return false;
        }
        return true;
    }
}; // namespace Exodia
