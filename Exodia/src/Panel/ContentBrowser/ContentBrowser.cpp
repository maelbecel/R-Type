/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** ContentBrowser
*/

// Panel includes
#include "ContentBrowser.hpp"

// ImGui includes
#include <imgui.h>
#include <misc/cpp/imgui_stdlib.h>

namespace Exodia
{

    //////////////////////////////
    // Constructor & Destructor //
    //////////////////////////////

    ContentBrowser::ContentBrowser( Ref<Project> project )
        : _Project( project ), _ThumbnailCache( CreateRef<ThumbnailCache>( project ) ),
          _BaseDirectory( project->GetAssetDirectory() ), _CurrentDirectory( _BaseDirectory ),
          _LastDirectory( _BaseDirectory )
    {
        _TreeNodes.push_back( TreeNode( ".", 0 ) );

        _DirectoryIcon = TextureImporter::LoadTexture2D( "./Assets/Icons/ContentBrowser/DirectoryIcon.png" );
        _FileIcon      = TextureImporter::LoadTexture2D( "./Assets/Icons/ContentBrowser/FileIcon.png" );
        _GoBack        = TextureImporter::LoadTexture2D( "./Assets/Icons/ContentBrowser/GoBack.png" );
        _GoForward     = TextureImporter::LoadTexture2D( "./Assets/Icons/ContentBrowser/GoForward.png" );

        RefreshTreeAsset();
    }

    /////////////
    // Methods //
    /////////////

    void ContentBrowser::OnImGuiRender()
    {
        ImGui::Begin( "Content Browser" );

        DrawHeaders();

        static float padding       = 45.0f;
        static float thumbnailSize = 150.0f;

        float cellSize   = thumbnailSize + padding;
        float panelWidth = ImGui::GetContentRegionAvail().x;

        int columnCount = (int) ( panelWidth / cellSize );

        if ( columnCount < 1 )
            columnCount = 1;

        ImGui::Columns( columnCount, 0, false );

        DrawFile( thumbnailSize );

        ImGui::Columns( 1 );
        ImGui::End();
    }

    void ContentBrowser::DrawHeaders()
    {
        if ( _CurrentDirectory != std::filesystem::path( _BaseDirectory ) )
        {
            ImGui::SameLine();

            if ( ImGui::ImageButton( reinterpret_cast<ImTextureID>( _GoBack->GetRendererID() ), { 15, 15 }, { 0, 1 },
                                     { 1, 0 } ) )
            {
                _LastDirectory    = _CurrentDirectory;
                _CurrentDirectory = _CurrentDirectory.parent_path();
            }
        }

        if ( _LastDirectory != _CurrentDirectory )
        {
            ImGui::SameLine();

            if ( ImGui::ImageButton( reinterpret_cast<ImTextureID>( _GoForward->GetRendererID() ), { 15, 15 }, { 0, 1 },
                                     { 1, 0 } ) )
                _CurrentDirectory = _LastDirectory;
        }

        ImGui::SameLine();
        ImGui::PushID( "SearchBar" );
        ImGui::SetNextItemWidth( 200 );
        ImGui::InputTextWithHint( "##Search", "Search...", &_SearchFilter );
        ImGui::PopID();
        ImGui::Separator();
    }

    void ContentBrowser::DrawFile( float thumbnailSize )
    {
        for ( auto &directoryEntry : std::filesystem::directory_iterator( _CurrentDirectory ) )
        {
            const auto    &path        = directoryEntry.path();
            std::string    filename    = path.filename().string();
            Ref<Texture2D> thumbnail   = _DirectoryIcon;
            bool           isDirectory = directoryEntry.is_directory();

            if ( _SearchFilter.length() > 0 && filename.find( _SearchFilter ) == std::string::npos )
                continue;

            ImGui::PushID( filename.c_str() );

            auto relativePath = std::filesystem::relative( path, Project::GetActiveAssetDirectory() );

            if ( !isDirectory )
            {
                thumbnail = _ThumbnailCache->GetOrCreateThumbnail( relativePath );

                if ( !thumbnail )
                    thumbnail = _FileIcon;
            }

            ImGui::PushStyleColor( ImGuiCol_Button, ImVec4( 0, 0, 0, 0 ) );
            ImGui::ImageButton( reinterpret_cast<ImTextureID>( thumbnail->GetRendererID() ),
                                { thumbnailSize, thumbnailSize }, { 0, 1 }, { 1, 0 } );

            if ( !isDirectory && ImGui::BeginPopupContextItem() )
            {
                if ( ImGui::MenuItem( "Import" ) )
                {
                    Project::GetActive()->GetEditorAssetManager()->ImportAsset( relativePath );

                    RefreshTreeAsset();
                }
                ImGui::EndPopup();
            }

            if ( ImGui::BeginDragDropSource() )
            {
                AssetHandle handle = GetAssetFromPathInTree( relativePath );

                ImGui::SetDragDropPayload( "CONTENT_BROWSER_ITEM", &handle, sizeof( AssetHandle ) );
                ImGui::EndDragDropSource();
            }

            ImGui::PopStyleColor();

            if ( ImGui::IsItemHovered() && ImGui::IsMouseDoubleClicked( ImGuiMouseButton_Left ) )
            {
                if ( directoryEntry.is_directory() )
                {
                    _LastDirectory = _CurrentDirectory;
                    _CurrentDirectory /= filename;
                }
            }

            ImGui::TextWrapped( "%s", filename.c_str() );
            ImGui::NextColumn();
            ImGui::PopID();
        }
    }

    void ContentBrowser::RefreshTreeAsset()
    {
        const auto &assetRegistry = _Project->GetEditorAssetManager()->GetAssetRegistry();

        for ( const auto &[ handle, spec ] : assetRegistry )
        {
            uint32_t currentNodeIndex = 0;

            for ( const auto &path : spec.Path )
            {
                auto it = _TreeNodes[ currentNodeIndex ].Children.find( path.generic_string() );

                if ( it != _TreeNodes[ currentNodeIndex ].Children.end() )
                {
                    currentNodeIndex = it->second;
                }
                else
                {
                    TreeNode node( path, handle );

                    node.Parent = currentNodeIndex;

                    _TreeNodes.push_back( node );
                    _TreeNodes[ currentNodeIndex ].Children[ path ] = _TreeNodes.size() - 1;

                    currentNodeIndex = _TreeNodes.size() - 1;
                }
            }
        }
    }

    ///////////////////////
    // Getters & Setters //
    ///////////////////////

    AssetHandle ContentBrowser::GetAssetFromPathInTree( const std::filesystem::path &path )
    {
        const auto &assetRegistry = _Project->GetEditorAssetManager()->GetAssetRegistry();

        for ( const auto &[ handle, spec ] : assetRegistry )
        {
            if ( spec.Path == path )
                return handle;
        }

        EXODIA_CORE_ASSERT( false, "Asset not found !" );
        return 0;
    }
}; // namespace Exodia
