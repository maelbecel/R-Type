/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** AssetManager
*/

#ifndef ASSETMANAGER_HPP_
    #define ASSETMANAGER_HPP_

    // Exodia Asset includes
    #include "Asset/Utils/AssetType.hpp"

    // Exodia Project includes
    #include "Project/Project.hpp"

    // Exodia Utils includes
    #include "Utils/Memory.hpp"

namespace Exodia {

    class AssetManager {

        ///////////////////////
        // Getters & Setters //
        ///////////////////////
        public:
            
            template<typename T>
            static Ref<T> GetAsset(AssetHandle handle)
            {
                Ref<Asset> asset = Project::GetActive()->GetAssetManager()->GetAsset(handle);

                return std::static_pointer_cast<T>(asset);
            }
    };
};

#endif /* !ASSETMANAGER_HPP_ */
