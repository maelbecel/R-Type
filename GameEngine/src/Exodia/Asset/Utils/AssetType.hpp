/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** AssetType
*/

#ifndef ASSETTYPE_HPP_
    #define ASSETTYPE_HPP_

    // Exodia Core ID includes
    #include "Core/ID/UUID.hpp"

    // Exodia Utils
    #include "Utils/Assert.hpp"

    // External includes
    #include <filesystem>

namespace Exodia {

    using AssetHandle = UUID;

    enum class AssetType : uint16_t {
        None      = 0,
        Scene     = 1,
        Texture2D = 2,
        Sound2D   = 3
        // TODO: Add more asset types
    };

    struct AssetSpecification {
        AssetType             Type = AssetType::None;
        std::filesystem::path Path;

        operator bool() const
        {
            return Type != AssetType::None;
        }
    };

    namespace Utils {

        inline static std::string_view AssetTypeToString(AssetType type)
        {
            switch (type) {
                case AssetType::None:
                    return "AssetType::None";
                case AssetType::Scene:
                    return "AssetType::Scene";
                case AssetType::Texture2D:
                    return "AssetType::Texture2D";
                case AssetType::Sound2D:
                    return "AssetType::Sound2D";
                // TODO: Add more asset types
                default:
                    break;
            }

            EXODIA_CORE_ASSERT(false, "Unknown asset type !");
            return "AssetType::None";
        }

        inline static AssetType StringToAssetType(std::string_view type)
        {
            if (type == "AssetType::None")
                return AssetType::None;
            if (type == "AssetType::Scene")
                return AssetType::Scene;
            if (type == "AssetType::Texture2D")
                return AssetType::Texture2D;
            if (type == "AssetType::Sound2D")
                return AssetType::Sound2D;
            // TODO: Add more asset types

            EXODIA_CORE_ASSERT(false, "Unknown asset type !");
            return AssetType::None;
        }
    };

    class Asset {

        ///////////////////////
        // Getters & Setters //
        ///////////////////////
        public:

            virtual AssetType GetType() const = 0;

        ////////////////
        // Attributes //
        ////////////////
        public:
            AssetHandle Handle; /*!< The asset handle */
    };
};

#endif /* !ASSETTYPE_HPP_ */
