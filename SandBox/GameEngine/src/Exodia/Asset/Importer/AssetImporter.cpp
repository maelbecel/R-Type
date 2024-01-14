/*
** EPITECH PROJECT, 2023
** $
** File description:
** AssetImporter
*/

// Exodia Asset includes
#include "AssetImporter.hpp"
#include "Asset/Utils/AssetType.hpp"
#include "Asset/Importer/TextureImporter.hpp"
#include "Asset/Importer/SceneImporter.hpp"
#include "Asset/Importer/SoundImporter.hpp"
#include "Asset/Importer/PrefabsImporter.hpp"

// Exodia Utils
#include "Exodia-Debug.hpp"
#include "Exodia-Utils.hpp"

// External includes
#include <map>

namespace Exodia {

    ///////////////////////
    // Statics variables //
    ///////////////////////

    static std::map<AssetType, AssetImportFunction> AssetImportFunctions = {
        {AssetType::Scene, SceneImporter::ImportScene},
        {AssetType::Texture2D, TextureImporter::ImportTexture2D},
        {AssetType::Sound2D, SoundImporter::ImportSound2D},
        {AssetType::Font, FontImporter::ImportFont},
        {AssetType::Prefabs, PrefabsImporter::ImportPrefabs}};

    /////////////
    // Methods //
    /////////////

    Ref<Asset> AssetImporter::ImportAsset(AssetHandle handle, const AssetSpecification &spec) {
        if (AssetImportFunctions.find(spec.Type) == AssetImportFunctions.end()) {
            EXODIA_CORE_ERROR("No importer available for '{0}'", Utils::AssetTypeToString(spec.Type));

            return nullptr;
        }

        return AssetImportFunctions[spec.Type](handle, spec);
    }
}; // namespace Exodia
