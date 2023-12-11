/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** IAssetManager
*/

#ifndef IASSETMANAGER_HPP_
    #define IASSETMANAGER_HPP_

    // Exodia Asset includes
    #include "Asset/Utils/AssetType.hpp"

    // Exodia Utils includes
    #include "Utils/Memory.hpp"

    // External includes
    #include <map>

namespace Exodia {

    using AssetMap = std::map<AssetHandle, Ref<Asset>>;

    class IAssetManager {

        ////////////////
        // Destructor //
        ////////////////
        public:
            
            virtual ~IAssetManager() = default;

        ///////////////////////
        // Getters & Setters //
        ///////////////////////
        public:

            virtual Ref<Asset> GetAsset(AssetHandle handle)                 = 0;
            virtual AssetType  GetAssetType(AssetHandle handle)       const = 0;
            virtual bool       IsAssetHandleValid(AssetHandle handle) const = 0;
            virtual bool       IsAssetLoaded(AssetHandle handle)      const = 0;
    };
};

#endif /* !IASSETMANAGER_HPP_ */
