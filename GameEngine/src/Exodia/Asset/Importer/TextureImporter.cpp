/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** TextureImporter
*/

// Exodia Asset includes
#include "TextureImporter.hpp"

// Exodia Renderer includes
#include "Renderer/Renderer/RendererAPI.hpp"

// Exodia Buffer includes
#include "Core/Buffer/Buffer.hpp"

// Exodia Project includes
#include "Project/Project.hpp"

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

    Ref<Texture2D> TextureImporter::ImportTexture2D(UNUSED(AssetHandle handle), const AssetSpecification &spec) {
        EXODIA_PROFILE_FUNCTION();

        return LoadTexture2D(Project::GetActiveAssetDirectory() / spec.Path);
    }

    Ref<Texture2D> TextureImporter::LoadTexture2D(const std::filesystem::path &path) {
        EXODIA_PROFILE_FUNCTION();

        if (RendererAPI::GetAPI() == RendererAPI::API::None)
            return nullptr;
        Buffer data;
        int width = 0;
        int height = 0;
        int channels = 0;

        stbi_set_flip_vertically_on_load(1);
        {
            EXODIA_PROFILE_SCOPE("stbi_load - TextureImporter::LoadTexture2D");

            data.Data = stbi_load(path.string().c_str(), &width, &height, &channels, 4);

            channels = 4;
        }

        data.Size = width * height * channels;

        if (!data.Data) {
            EXODIA_CORE_ERROR("Failed to load image '{0}'", path.string());

            return nullptr;
        }

        TextureSpecification textureSpec;

        textureSpec.Width = width;
        textureSpec.Height = height;
        textureSpec.Format = ImageFormat::RGBA8;

        Ref<Texture2D> texture = Texture2D::Create(textureSpec, data);

        data.Release();
        return texture;
    }
}; // namespace Exodia
