cmake_minimum_required(VERSION 3.12)

project(Editor LANGUAGES CXX VERSION 1.0.1)

set(CMAKE_BUILD_TYPE Debug)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Set compiler flags
if (MSVC)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W4 /WX")
else()
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Werror")
endif()

set(GAME_ENGINE_DIR  ${CMAKE_SOURCE_DIR}/SandBox/GameEngine)
set(R_TYPE_DIR  ${CMAKE_SOURCE_DIR}/SandBox/R-Type/R-Type)

# Set source files for the Editor Game Engine Application
set(SOURCES

    src/Exodia-Editor.cpp

        # R-Type Layer sources files

    src/Layer/EditorLayer.cpp

        # ImGui Panels source files

    src/Panel/ContentBrowser/ContentBrowser.cpp
    src/Panel/SceneHierarchy/SceneHierarchy.cpp
    src/Panel/Statistics/Statistics.cpp
    src/Panel/Console/Console.cpp

        # Thumbnail sources files

    src/Thumbnail/ThumbnailCache.cpp
)

# Set include directories for the Editor Game Engine Application
set(INCLUDE_DIRS
    # Exodia-App include directories
    src/

    # R-Type include directories
    ${R_TYPE_DIR}

    # GameEngine include directories
    ${GAME_ENGINE_DIR}/src
    ${GAME_ENGINE_DIR}/src/Exodia
    ${GAME_ENGINE_DIR}/src/Exodia/ECS/
    ${GAME_ENGINE_DIR}/src/Platform
)

# Include directories
include_directories(${INCLUDE_DIRS})

# Add an executable for the exodia
add_executable(Editor ${SOURCES})

target_link_libraries(Editor PRIVATE
    Exodia-Tools
    Exodia-Debug
    Exodia-ECS
    
    SandBoxGE

    R-TypeSolo

    glad::glad
    glfw
    imgui
    glm::glm
    OpenAL::OpenAL
    spdlog::spdlog
    unofficial::nativefiledialog::nfd
    yaml-cpp::yaml-cpp
)

target_include_directories(Editor PRIVATE
    ${CMAKE_BINARY_DIR}/../SandBox/Library/Tools/src/
    ${CMAKE_BINARY_DIR}/../SandBox/Library/Debug/src/
    ${CMAKE_BINARY_DIR}/../SandBox/Library/Entity-Component-System/src/
    ${CMAKE_BINARY_DIR}/../SandBox/R-Type/R-Type/src/
    ${CMAKE_BINARY_DIR}/../SandBox/R-Type/R-Type
)
target_include_directories(Editor PRIVATE ${Stb_INCLUDE_DIR})
target_include_directories(Editor PRIVATE ${CMAKE_BINARY_DIR}/_deps/imgui-src)

set_target_properties(Editor PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/../Release/R-Type/
)
