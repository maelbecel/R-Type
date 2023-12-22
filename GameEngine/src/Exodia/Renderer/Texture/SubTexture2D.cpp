/*
** EPITECH PROJECT, 2023
** ExodiaGameEngine
** File description:
** SubTexture2D
*/

// Exodia Renderer
#include "SubTexture2D.hpp"

// Exodia Asset includes
#include "Asset/Manager/AssetManager.hpp"

namespace Exodia {

    /////////////
    // Factory //
    /////////////

    Ref<SubTexture2D> SubTexture2D::CreateFromCoords(const AssetHandle &assetHandle, const glm::vec2 &coords, const glm::vec2 &cellSize, const glm::vec2 &spriteSize)
    {
        return (CreateRef<SubTexture2D>(assetHandle, coords, cellSize, spriteSize));
    }

    /////////////////
    // Constructor //
    /////////////////

    SubTexture2D::SubTexture2D(const AssetHandle &assetHandle) : _AssetHandle(assetHandle), _Coords({ 0, 0 }), _SpriteSize({ 1, 1 })
    {
        Ref<Texture2D> texture = AssetManager::GetAsset<Texture2D>(_AssetHandle);

        if (texture != nullptr)
            _CellSize = glm::vec2(texture->GetWidth(), texture->GetHeight());
        else
            _CellSize = glm::vec2(1, 1);
    }

    SubTexture2D::SubTexture2D(const AssetHandle &assetHandle, const glm::vec2 &coords, const glm::vec2 &cellSize, const glm::vec2 &spriteSize) : _AssetHandle(assetHandle), _Coords(coords), _CellSize(cellSize), _SpriteSize(spriteSize)
    {
        calculateTextureCoords();
    }

    /////////////
    // Methods //
    /////////////

    void SubTexture2D::calculateTextureCoords()
    {
        Ref<Texture2D> texture = AssetManager::GetAsset<Texture2D>(_AssetHandle);

        if (texture == nullptr)
            return;

        glm::vec2 min = { (_Coords.x * _CellSize.x ) / texture->GetWidth(), (_Coords.y * _CellSize.y) / texture->GetHeight() };
        glm::vec2 max = { ((_Coords.x + _SpriteSize.x) * _CellSize.x) / texture->GetWidth(), ((_Coords.y + _SpriteSize.y) * _CellSize.y) / texture->GetHeight() };

        _TextureCoords[0] = { min.x, min.y };
        _TextureCoords[1] = { max.x, min.y };
        _TextureCoords[2] = { max.x, max.y };
        _TextureCoords[3] = { min.x, max.y };
    }

    /////////////
    // Getters //
    /////////////

    Ref<Texture2D> SubTexture2D::GetTexture()
    {
        Ref<Texture2D> texture = AssetManager::GetAsset<Texture2D>(_AssetHandle);

        return texture;
    }

    const glm::vec2 *SubTexture2D::GetTextureCoords() const
    {
        return _TextureCoords;
    }

    const glm::vec2 &SubTexture2D::GetCoords()
    {
        return _Coords;
    }

    const glm::vec2 &SubTexture2D::GetTextureCellSize()
    {
        return _CellSize;
    }

    const glm::vec2 &SubTexture2D::GetTextureSpriteSize()
    {
        return _SpriteSize;
    }

    AssetHandle SubTexture2D::GetAssetHandle() const
    {
        return _AssetHandle;
    }

    void SubTexture2D::SetCoords(const glm::vec2 &coords)
    {
        _Coords = coords;

        calculateTextureCoords();
    }

    void SubTexture2D::SetTextureCellSize(const glm::vec2 &cellSize)
    {
        _CellSize = cellSize;

        calculateTextureCoords();
    }

    void SubTexture2D::SetTextureSpriteSize(const glm::vec2 &spriteSize)
    {
        _SpriteSize = spriteSize;

        calculateTextureCoords();
    }

    void SubTexture2D::SetTexture(const AssetHandle &handle)
    {
        Ref<Texture2D> texture = AssetManager::GetAsset<Texture2D>(handle);

        _AssetHandle = handle;

        // Reset the texture coordinates
        _Coords = { 0, 0 };
        if (texture != nullptr)
            _CellSize = glm::vec2(texture->GetWidth(), texture->GetHeight());
        else
            _CellSize = { 1, 1 };
        _SpriteSize = { 1, 1 };

        calculateTextureCoords();
    }
};
