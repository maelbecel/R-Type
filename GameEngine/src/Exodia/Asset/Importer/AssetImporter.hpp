/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** AssetImporter
*/

#ifndef ASSETIMPORTER_HPP_
    #define ASSETIMPORTER_HPP_

    // Exodia Asset includes
    #include "Asset/Utils/AssetType.hpp"

    // Exodia Utils
    #include "Utils/Memory.hpp"

    // External includes
    #include <functional>

namespace Exodia {

    using AssetImportFunction = std::function<Ref<Asset>(AssetHandle, const AssetSpecification &)>;

    class AssetImporter {

        /////////////
        // Methods //
        /////////////
        public:

            static Ref<Asset> ImportAsset(AssetHandle handle, const AssetSpecification &spec);
    };
};

#endif /* !ASSETIMPORTER_HPP_ */
