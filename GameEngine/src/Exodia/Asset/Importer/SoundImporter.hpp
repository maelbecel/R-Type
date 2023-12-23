/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** SoundImporter
*/

#ifndef SOUNDIMPORTER_HPP_
    #define SOUNDIMPORTER_HPP_

    // Exodia Asset includes
    #include "Asset/Utils/AssetType.hpp"

    // Exodia Renderer includes
    #include "Renderer/Sound/Sound.hpp"

    // External includes
    #include <filesystem>

namespace Exodia {

    class Sound2D;

    class SoundImporter {
        
        /////////////
        // Methods //
        /////////////
        public:

            static Ref<Sound2D> ImportSound2D(AssetHandle handle, const AssetSpecification &spec);
            static Ref<Sound2D> LoadSound2D(const std::filesystem::path &path);
    };
};

#endif /* !SOUNDIMPORTER_HPP_ */

