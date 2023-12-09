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

// Exodia Utils
#include "Utils/Assert.hpp"
#include "Utils/Memory.hpp"

// External includes
#include <map>

namespace Exodia {

    ///////////////////////
    // Statics variables //
    ///////////////////////

    static std::map<AssetType, AssetImportFunction> AssetImportFunctions = {
        {AssetType::Texture2D, TextureImporter::ImportTexture2D}
    };

    /////////////
    // Methods //
    /////////////

    Ref<Asset> AssetImporter::ImportAsset(AssetHandle handle, const AssetSpecification &spec)
    {
        EXODIA_CORE_ASSERT(AssetImportFunctions.find(spec.Type) != AssetImportFunctions.end(), "No importer available for this asset type");

        return AssetImportFunctions[spec.Type](handle, spec);
    }
};
