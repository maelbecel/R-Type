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

// Exodia Debug includes
#include "Debug/Logs.hpp"

// External includes
#include <map>
#include <yaml-cpp/yaml.h>

namespace Exodia {

    /////////////////////////////////
    // Yaml-cpp operator overloads //
    /////////////////////////////////

    YAML::Emitter &operator<<(YAML::Emitter &out, const std::string_view &str)
    {
        out << std::string(str.data(), str.size());

        return out;
    }

    //////////////////////////////////
    // Static variables & Functions //
    //////////////////////////////////

    static std::map<std::filesystem::path, AssetType> AssetExtensionMap = {
        { ".exodia", AssetType::Scene },
        { ".png", AssetType::Texture2D },
        { ".jpg", AssetType::Texture2D },
        { ".jpeg", AssetType::Texture2D }
    };

    static AssetType GetAssetTypeFromFileExtension(const std::filesystem::path &extension)
    {
        auto it = AssetExtensionMap.find(extension);

        if (it == AssetExtensionMap.end()) {
            EXODIA_CORE_WARN("Asset type not found for extension `{}`", extension.string());

            return AssetType::None;
        }
        return it->second;
    }

    /////////////
    // Methods //
    /////////////

    void EditorAssetManager::ImportAsset(const std::filesystem::path &path)
    {
        AssetHandle        handle;
        AssetSpecification spec;

        spec.Path = path;
        spec.Type = GetAssetTypeFromFileExtension(path.extension());

        if (spec.Type == AssetType::None)
            return;

        for (const auto &[handle, spec] : _AssetRegistry) {
            if (spec.Path.filename() == path.filename()) {
                EXODIA_CORE_INFO("The asset `{}` is already imported !", path.string());

                return;
            }
        }

        Ref<Asset> asset = AssetImporter::ImportAsset(handle, spec);

        if (asset) {
            asset->Handle = handle;

            _LoadedAssets[handle]  = asset;
            _AssetRegistry[handle] = spec;

            SerializeAssetRegistry();
        }
    }

    void EditorAssetManager::SerializeAssetRegistry()
    {
        auto path = Project::GetActiveAssetRegistryPath();

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
        auto path = Project::GetActiveAssetRegistryPath();

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

            try {
                AssetHandle handle = node["Handle"].as<uint64_t>();

                auto &spec = _AssetRegistry[handle];

                spec.Path = node["Path"].as<std::string>();
                spec.Type = Utils::StringToAssetType(node["Type"].as<std::string>());
            } catch (const YAML::Exception &e) {
                EXODIA_CORE_ERROR("Failed to deserialize asset registry `{}`:\n\t{}", path.string(), e.what());

                continue;
            }
        }
        return true;
    }

    ///////////////////////
    // Getters & Setters //
    ///////////////////////

    Ref<Asset> EditorAssetManager::GetAsset(AssetHandle handle)
    {
        if (!IsAssetHandleValid(handle))
            return nullptr;
        Ref<Asset> asset = nullptr;

        if (IsAssetLoaded(handle))
            asset = _LoadedAssets.at(handle);
        else {
            const AssetSpecification &spec = GetAssetSpecification(handle);

            asset = AssetImporter::ImportAsset(handle, spec);

            if (asset == nullptr) {
                EXODIA_CORE_WARN("Import asset '{0}' failed !", (uint64_t)handle);

                return nullptr;
            }

            _LoadedAssets[handle] = asset;
        }

        return asset;
    }

    AssetType EditorAssetManager::GetAssetType(AssetHandle handle) const
    {
        if (!IsAssetHandleValid(handle))
            return AssetType::None;
        return _AssetRegistry.at(handle).Type;
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

    const std::filesystem::path &EditorAssetManager::GetFilePath(AssetHandle handle) const
    {
        return GetAssetSpecification(handle).Path;
    }
};
