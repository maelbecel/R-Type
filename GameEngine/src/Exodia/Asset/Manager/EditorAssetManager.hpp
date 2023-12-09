/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** EditorAssetManager
*/

#ifndef EDITORASSETMANAGER_HPP_
    #define EDITORASSETMANAGER_HPP_

    // Exodia Asset includes
    #include "Asset/Manager/IAssetManager.hpp"

    // External includes
    #include <map>

namespace Exodia {

    using AssetRegistry = std::map<AssetHandle, AssetSpecification>;

    class EditorAssetManager : public IAssetManager {

        ///////////////////////
        // Getters & Setters //
        ///////////////////////
        public:

            virtual Ref<Asset> GetAsset(AssetHandle handle)           const override;
            virtual bool       IsAssetHandleValid(AssetHandle handle) const override;
            virtual bool       IsAssetLoaded(AssetHandle handle)      const override;

            const AssetSpecification &GetAssetSpecification(AssetHandle handle) const;
        
        ////////////////
        // Attributes //
        ////////////////
        private:

            AssetRegistry _AssetRegistry;
            AssetMap      _LoadedAssets;
    };
};

#endif /* !EDITORASSETMANAGER_HPP_ */
