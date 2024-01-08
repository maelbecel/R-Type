cmake_minimum_required(VERSION 3.12)
project(SandBoxGames LANGUAGES CXX VERSION 1.0.1)

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

set(GAME_ENGINE_DIR  ${CMAKE_SOURCE_DIR}/GameEngine)


# Set source files for the SandBoxGames
set(SOURCES
    src/Main.cpp

    src/Layer/GameLayer.cpp

    src/ECS/Scripts/Player.cpp
)

# Set include directories for the SandBoxGames
set(INCLUDE_DIRS
    # SandBox include directories
    ${CMAKE_SOURCE_DIR}
    ${CMAKE_SOURCE_DIR}/src

    # GameEngine include directories
    ${GAME_ENGINE_DIR}/Tools
    ${GAME_ENGINE_DIR}/src
    ${GAME_ENGINE_DIR}/src/Exodia

    # Vendor include directories
    ${GLAD_SOURCE_DIR}
    ${IMGUI_SOURCE_DIR}
)


# Include directories
include_directories(${INCLUDE_DIRS})

# Add an executable for the r-type_client
add_executable(SandBoxGames ${SOURCES})

target_link_libraries(SandBoxGames PRIVATE
    Exodia-Tools
    Exodia-Debug
    Exodia-ECS

    GameEngine
    R-Type
    glad::glad
    glfw
    imgui
    glm::glm
    asio::asio
    OpenAL::OpenAL
    spdlog::spdlog
    Catch2::Catch2 Catch2::Catch2WithMain
    sol2
    unofficial::nativefiledialog::nfd
    yaml-cpp::yaml-cpp
    imguizmo::imguizmo
    FreeALUT::alut
    Vorbis::vorbisfile
)

target_include_directories(SandBoxGames PRIVATE
    ${CMAKE_BINARY_DIR}/../Library/Tools/src/
    ${CMAKE_BINARY_DIR}/../Library/Debug/src/
    ${CMAKE_BINARY_DIR}/../Library/Entity-Component-System/src
)

target_include_directories(SandBoxGames PRIVATE ${Stb_INCLUDE_DIR})
target_include_directories(SandBoxGames PRIVATE ${CMAKE_BINARY_DIR}/_deps/imgui-src)

set_target_properties(SandBoxGames PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/../
)

