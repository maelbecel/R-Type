/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** EditorAssetManager
*/

// Exodia Assets includes
#include "EditorAssetManager.hpp"
#include "Asset/Utils/AssetType.hpp"
#include "Asset/Importer/AssetImporter.hpp"

// Exodia Project includes
#include "Project/Project.hpp"

// Exodia Utils includes
#include "Utils/Assert.hpp"

// YAML-CPP includes
#include <yaml-cpp/yaml.h>

namespace Exodia {

    ////////////////////////////////
    // YAML-CPP Operator Overload //
    ////////////////////////////////

    YAML::Emitter &operator<<(YAML::Emitter &out, const std::string_view &str)
    {
        out << std::string(str.data(), str.size());

        return out;
    }

    /////////////
    // Methods //
    /////////////

    void EditorAssetManager::ImportAsset(const std::filesystem::path &path)
    {
        AssetHandle        handle;
        AssetSpecification spec;

        spec.Path = path;
        spec.Type = AssetType::Texture2D;

        Ref<Asset> asset = AssetImporter::ImportAsset(handle, spec);

        asset->Handle = handle;

        if (asset) {
            _LoadedAssets[handle]  = asset;
            _AssetRegistry[handle] = spec;

            SerializeAssetRegistry();
        }
    }

    void EditorAssetManager::SerializeAssetRegistry()
    {
        auto path = Project::GetAssetRegistryPath();

        YAML::Emitter out;
        {
            out << YAML::BeginMap;
            out << YAML::Key << "AssetRegistry" << YAML::Value;
            out << YAML::BeginSeq;

            for (const auto &[handle, spec] : _AssetRegistry) {
                std::string filepath = spec.Path.generic_string();

                out << YAML::BeginMap;
                out << YAML::Key << "Handle" << YAML::Value << handle;
                out << YAML::Key << "Path"   << YAML::Value << filepath;
                out << YAML::Key << "Type"   << YAML::Value << Utils::AssetTypeToString(spec.Type);
                out << YAML::EndMap;
            }

            out << YAML::EndSeq;
            out << YAML::EndMap;
        }

        std::ofstream file(path);

        file << out.c_str();
    }

    bool EditorAssetManager::DeserializeAssetRegistry()
    {
        auto path = Project::GetAssetRegistryPath();

        YAML::Node data;

        try {
            data = YAML::LoadFile(path);
        } catch (const YAML::ParserException &e) {
            EXODIA_CORE_ERROR("Failed to deserialize asset registry `{}`:\n\t{}", path.string(), e.what());

            return false;
        }

        auto assetRegistry = data["AssetRegistry"];

        if (!assetRegistry)
            return false;
        for (const auto &node : assetRegistry) {
            if (!node["Handle"] || !node["Path"] || !node["Type"])
                continue;
            AssetHandle handle = node["Handle"].as<uint64_t>();

            auto &spec = _AssetRegistry[handle];

            spec.Path = node["Path"].as<std::string>();
            spec.Type = Utils::StringToAssetType(node["Type"].as<std::string>());
        }
        return true;
    }

    ///////////////////////
    // Getters & Setters //
    ///////////////////////

    Ref<Asset> EditorAssetManager::GetAsset(AssetHandle handle) const
    {
        if (!IsAssetHandleValid(handle))
            return nullptr;
        Ref<Asset> asset = nullptr;

        if (IsAssetLoaded(handle))
            asset = _LoadedAssets.at(handle);
        else {
            const AssetSpecification &spec = GetAssetSpecification(handle);

            asset = AssetImporter::ImportAsset(handle, spec);

            EXODIA_CORE_ASSERT(asset, "AssetImporter::ImportAsset() - Asset import failed !");
        }

        return asset;
    }

    bool EditorAssetManager::IsAssetHandleValid(AssetHandle handle) const
    {
        return handle != 0 && _AssetRegistry.find(handle) != _AssetRegistry.end();
    }

    bool EditorAssetManager::IsAssetLoaded(AssetHandle handle) const
    {
        return _LoadedAssets.find(handle) != _LoadedAssets.end();
    }

    const AssetSpecification &EditorAssetManager::GetAssetSpecification(AssetHandle handle) const
    {
        auto it = _AssetRegistry.find(handle);

        EXODIA_CORE_ASSERT(it != _AssetRegistry.end(), "EditorAssetManager::GetAssetSpecification() - Asset handle not found !");

        return it->second;
    }

    const AssetRegistry &EditorAssetManager::GetAssetRegistry() const
    {
        return _AssetRegistry;
    }
};
