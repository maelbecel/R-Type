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

    // External includes
    #include <filesystem>

namespace Exodia {

    using AssetHandle = UUID;

    enum class AssetType : uint16_t {
        None      = 0,
        Scene     = 1,
        Texture2D = 2
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
