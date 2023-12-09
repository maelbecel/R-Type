/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** EditorAssetManager
*/

// Exodia Assets includes
#include "EditorAssetManager.hpp"
#include "Asset/Importer/AssetImporter.hpp"

// Exodia Utils includes
#include "Utils/Assert.hpp"

namespace Exodia {

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
};
