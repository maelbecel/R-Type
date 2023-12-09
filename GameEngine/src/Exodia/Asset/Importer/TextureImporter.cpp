/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** TextureImporter
*/

// Exodia Asset includes
#include "TextureImporter.hpp"

// Exodia Buffer includes
#include "Core/Buffer/Buffer.hpp"

// Exodia Utils
#include "Utils/Assert.hpp"

// Exodia Debug includes
#include "Debug/Profiling.hpp"

// Stb includes
#define STB_IMAGE_IMPLEMENTATION
    #include "stb_image.h"

namespace Exodia {

    /////////////
    // Methods //
    /////////////

    Ref<Texture2D> TextureImporter::ImportTexture2D(AssetHandle handle, const AssetSpecification &spec)
    {
        EXODIA_PROFILE_FUNCTION();

        std::string path = spec.Path.string();

        Buffer data;
        int width    = 0;
        int height   = 0;
        int channels = 0;

        stbi_set_flip_vertically_on_load(1);
        {
            EXODIA_PROFILE_SCOPE("stbi_load - TextureImporter::ImportTexture2D");

            data.Data = stbi_load(path.c_str(), &width, &height, &channels, 0);
        }

        EXODIA_CORE_ASSERT(data.Data, "Failed to load image !");

        data.Size = width * height * channels;

        TextureSpecification textureSpec;

        textureSpec.Width  = width;
        textureSpec.Height = height;

        switch (channels) {
            case 3:
                textureSpec.Format = ImageFormat::RGB8;
                break;
            case 4:
                textureSpec.Format = ImageFormat::RGBA8;
                break;
            default:
                EXODIA_CORE_ASSERT(false, "Unsupported image format !");
                break;
        }

        Ref<Texture2D> texture = Texture2D::Create(textureSpec);

        data.Release();
        return texture;
    }
};
