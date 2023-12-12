/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** ThumbnailCache
*/

#ifndef THUMBNAILCACHE_HPP_
    #define THUMBNAILCACHE_HPP_

    // Exodia includes
    #include "Exodia.hpp"

namespace Exodia {

    struct ThumbnailImage {

        uint64_t Timestamp;

        Ref<Texture2D> Image;
    };

    class ThumbnailCache {

        //////////////////////////////
        // Constructor & Destructor //
        //////////////////////////////
        public:

            ThumbnailCache(Ref<Project> project);
            ~ThumbnailCache() = default;

        ///////////////////////
        // Getters & Setters //
        ///////////////////////
        public:

            /**
             * @brief Get the Or Create Thumbnail object
             * 
             * 1. Read the file's last modified time
             * 2. Compare is last modified time with the cached image's last modified time (in memory first, then from cache file)
             * 3. If equal, return associated thumbnail, otherwise load asset from disk and generate thumbnail
             * 4. If generated new thumbnail, store in cache
             *
             * @param path The path to the asset
             * @return Ref<Texture2D> The thumbnail
             */
            Ref<Texture2D> GetOrCreateThumbnail(const std::filesystem::path &path);

        ////////////////
        // Attributes //
        ////////////////
        private:

            Ref<Project>                                    _Project;
            std::map<std::filesystem::path, ThumbnailImage> _ImageCache;
            std::filesystem::path                           _CacheDirectory;
    };
};

#endif /* !THUMBNAILCACHE_HPP_ */

