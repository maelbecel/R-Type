/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** SceneImporter
*/

#ifndef SCENEIMPORTER_HPP_
#define SCENEIMPORTER_HPP_

// Exodia Asset includes
#include "Asset/Utils/AssetType.hpp"

// Exodia Scene includes
#include "Scene/Scene/Scene.hpp"

// External includes
#include <filesystem>

namespace Exodia
{

    class Scene;

    class SceneImporter
    {

        /////////////
        // Methods //
        /////////////
      public:
        static Ref<Scene> ImportScene( AssetHandle handle, const AssetSpecification &spec );
        static Ref<Scene> LoadScene( const std::filesystem::path &path );

        static void SaveScene( Ref<Scene> scene, const std::filesystem::path &path );
    };
}; // namespace Exodia

#endif /* !SCENEIMPORTER_HPP_ */
