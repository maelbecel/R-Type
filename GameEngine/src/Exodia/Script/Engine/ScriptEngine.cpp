/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** ScriptEngine
*/

// Exodia Script
#include "ScriptEngine.hpp"

// Exodia Project
#include "Project/Project.hpp"

// Exodia Utils
#include "Utils/LibrairyLoader.hpp"

namespace Exodia
{

    ///////////////////////
    // Static Attributes //
    ///////////////////////

    ScriptEngineData *ScriptEngine::Data = nullptr;

    /////////////
    // Methods //
    /////////////

    void ScriptEngine::Init()
    {
        std::filesystem::path scriptModulePath = Project::GetActiveScriptPath();

        Data = new ScriptEngineData();

        if ( std::filesystem::exists( scriptModulePath ) )
        {
            for ( auto &file : std::filesystem::directory_iterator( scriptModulePath ) )
            {
                auto path = file.path();

#ifdef _WIN32
                if ( path.extension() != ".dll" )
                    continue;
#else
                if ( path.extension() != ".so" )
                    continue;
#endif
                void *handle = LibraryLoader::Load( path.string() );

                if ( handle != nullptr )
                    continue;
                auto getScriptableEntity =
                    ( ScriptableEntity * (*) (void) ) LibraryLoader::GetFunction( handle, "CreateScript" );

                if ( !getScriptableEntity )
                {
                    LibraryLoader::Close( handle );

                    continue;
                }

                Data->ScriptableEntities.push_back( path.stem().string() );
            }
        }
    }

    void ScriptEngine::Shutdown()
    {
        if ( Data )
        {
            delete Data;
            Data = nullptr;
        }
    }

    ///////////////////////
    // Getters & Setters //
    ///////////////////////

    ScriptableEntity *ScriptEngine::InstantiateScript( const std::string &name )
    {
#ifdef _WIN32
        void *handle = LibraryLoader::Load( ( Project::GetActiveScriptPath() / ( name + ".dll" ) ).string() );
#else
        void *handle = LibraryLoader::Load( ( Project::GetActiveScriptPath() / ( name + ".so" ) ).string() );
#endif

        auto getScriptableEntity =
            ( ScriptableEntity * (*) (void) ) LibraryLoader::GetFunction( handle, "CreateScript" );

        if ( !getScriptableEntity )
        {
            EXODIA_CORE_WARN( "ScriptEngine::InstantiateScript: Failed to load script {0}", name );

            LibraryLoader::Close( handle );
            return nullptr;
        }

        return getScriptableEntity();
    }

    std::vector<std::string> ScriptEngine::GetScriptableEntities() { return Data->ScriptableEntities; }
}; // namespace Exodia
