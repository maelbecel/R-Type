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

namespace Exodia {

    class ContentBrowser {

        //////////////////////////////
        // Constructor & Destructor //
        //////////////////////////////
        public:

            ContentBrowser(Ref<Project> project);
            ~ContentBrowser() = default;

        /////////////
        // Methods //
        /////////////
        public:

            void OnImGuiRender();

        ////////////////
        // Attributes //
        ////////////////
        private:

            Ref<Project>        _Project;
            Ref<ThumbnailCache> _ThumbnailCache;
    };
};

#endif /* !CONTENTBROWSER_HPP_ */
