/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** TextureImporter
*/

#ifndef TEXTUREIMPORTER_HPP_
    #define TEXTUREIMPORTER_HPP_

    // Exodia Asset includes
    #include "Asset/Utils/AssetType.hpp"

    // Exodia Texture includes
    #include "Renderer/Texture/Texture.hpp"

namespace Exodia {

    class Texture2D;

    class TextureImporter {

        /////////////
        // Methods //
        /////////////
        public:

            static Ref<Texture2D> ImportTexture2D(AssetHandle handle, const AssetSpecification &spec);
    };
};

#endif /* !TEXTUREIMPORTER_HPP_ */
