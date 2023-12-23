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

namespace Exodia
{

    using AssetRegistry = std::map<AssetHandle, AssetSpecification>;

    class EditorAssetManager : public IAssetManager
    {

        //////////////////////////////
        // Constructor & Destructor //
        //////////////////////////////
      public:
        EditorAssetManager()  = default;
        ~EditorAssetManager() = default;

        /////////////
        // Methods //
        /////////////
      public:
        void ImportAsset( const std::filesystem::path &path );

        void SerializeAssetRegistry();
        bool DeserializeAssetRegistry();

        ///////////////////////
        // Getters & Setters //
        ///////////////////////
      public:
        virtual Ref<Asset> GetAsset( AssetHandle handle ) override;
        virtual AssetType  GetAssetType( AssetHandle handle ) const override;
        virtual bool       IsAssetHandleValid( AssetHandle handle ) const override;
        virtual bool       IsAssetLoaded( AssetHandle handle ) const override;

        const AssetSpecification &GetAssetSpecification( AssetHandle handle ) const;
        const AssetRegistry      &GetAssetRegistry() const;

        const std::filesystem::path &GetFilePath( AssetHandle handle ) const;

        ////////////////
        // Attributes //
        ////////////////
      private:
        AssetRegistry _AssetRegistry;
        AssetMap      _LoadedAssets;
    };
}; // namespace Exodia

#endif /* !EDITORASSETMANAGER_HPP_ */
