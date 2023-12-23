/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** ThumbnailCache
*/

#include "ThumbnailCache.hpp"

namespace Exodia
{

    //////////////////////////////
    // Constructor & Destructor //
    //////////////////////////////

    ThumbnailCache::ThumbnailCache( Ref<Project> project ) : _Project( project )
    {
        _CacheDirectory = _Project->GetAssetDirectory() / "Thumbnail.cache";
    }

    ///////////////////////
    // Getters & Setters //
    ///////////////////////

    Ref<Texture2D> ThumbnailCache::GetOrCreateThumbnail( const std::filesystem::path &path )
    {
        auto absolutePath = _Project->GetAssetAbsolutePath( path );

        std::filesystem::file_time_type lastModifiedTime = std::filesystem::last_write_time( absolutePath );

        uint64_t timestamp =
            std::chrono::duration_cast<std::chrono::milliseconds>( lastModifiedTime.time_since_epoch() ).count();

        if ( _ImageCache.find( path ) != _ImageCache.end() )
        {
            auto &thumbnail = _ImageCache[ path ];

            if ( thumbnail.Timestamp == timestamp )
                return thumbnail.Image;
        }

        if ( path.extension() != ".png" && path.extension() != ".jpg" && path.extension() != ".jpeg" )
            return nullptr;
        Ref<Texture2D> texture = TextureImporter::LoadTexture2D( absolutePath );

        if ( !texture )
            return nullptr;

        auto &thumbnail = _ImageCache[ path ];

        thumbnail.Timestamp = timestamp;
        thumbnail.Image     = texture;

        return texture;
    }
}; // namespace Exodia
