/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** ContentBrowser
*/

#ifndef CONTENTBROWSER_HPP_
#define CONTENTBROWSER_HPP_

// Exodia includes
#include "Exodia.hpp"

// Thumbnail
#include "Thumbnail/ThumbnailCache.hpp"

namespace Exodia
{

    class ContentBrowser
    {

        //////////////////////
        // Structure & Enum //
        //////////////////////
      private:
        struct TreeNode
        {
            std::filesystem::path Path;
            AssetHandle           Handle;

            uint32_t                                  Parent = 0;
            std::map<std::filesystem::path, uint32_t> Children;

            TreeNode( const std::filesystem::path &path, AssetHandle handle ) : Path( path ), Handle( handle ){};
        };

        //////////////////////////////
        // Constructor & Destructor //
        //////////////////////////////
      public:
        ContentBrowser( Ref<Project> project );
        ~ContentBrowser() = default;

        /////////////
        // Methods //
        /////////////
      public:
        void OnImGuiRender();

      private:
        void DrawHeaders();
        void DrawAssets( float thumbnailSize );
        void DrawFile( float thumbnailSize );

        void RefreshTreeAsset();

        ///////////////////////
        // Getters & Setters //
        ///////////////////////
      private:
        AssetHandle GetAssetFromPathInTree( const std::filesystem::path &path );

        ////////////////
        // Attributes //
        ////////////////
      private:
        Ref<Project>        _Project;
        Ref<ThumbnailCache> _ThumbnailCache;

        std::filesystem::path _BaseDirectory;
        std::filesystem::path _CurrentDirectory;
        std::filesystem::path _LastDirectory;

        std::string _SearchFilter;

        Ref<Texture2D> _DirectoryIcon;
        Ref<Texture2D> _FileIcon;
        Ref<Texture2D> _GoBack;
        Ref<Texture2D> _GoForward;

        std::vector<TreeNode>                                               _TreeNodes;
        std::map<std::filesystem::path, std::vector<std::filesystem::path>> _AssetTree;
    };
}; // namespace Exodia

#endif /* !CONTENTBROWSER_HPP_ */
