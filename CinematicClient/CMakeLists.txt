cmake_minimum_required(VERSION 3.12)

project(cinematic-client LANGUAGES CXX VERSION 1.0.1)

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
set(CINEMATIC_DIR  ${CMAKE_SOURCE_DIR}/Cinematic)

# Set source files for the Exodia Game Engine Application
set(SOURCES

    src/Cinematic.cpp

        # R-Type Layer sources files

    src/Layer/CinematicLayer.cpp
)

# Set include directories for the Exodia Game Engine Application
set(INCLUDE_DIRS
    # Exodia-App include directories
    src/

    # R-Type include directories
    ${CINEMATIC_DIR}
    ${CINEMATIC_DIR}/src

    # GameEngine include directories
    ${GAME_ENGINE_DIR}/src
    ${GAME_ENGINE_DIR}/src/Exodia
    ${GAME_ENGINE_DIR}/src/Exodia/ECS/
    ${GAME_ENGINE_DIR}/src/Platform
)

# Include directories
include_directories(${INCLUDE_DIRS})

# Add an executable for the r-type_client
add_executable(cinematic-client ${SOURCES})

target_link_libraries(cinematic-client PRIVATE

    Exodia-Tools
    Exodia-Debug
    Exodia-ECS

    GameEngine
    Cinematic
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

target_include_directories(cinematic-client PRIVATE
    ${CMAKE_BINARY_DIR}/../Library/Debug/src/
    ${CMAKE_BINARY_DIR}/../Library/Tools/src/
    ${CMAKE_BINARY_DIR}/../Library/Entity-Component-System/src
)

target_include_directories(cinematic-client PRIVATE ${Stb_INCLUDE_DIR})
target_include_directories(cinematic-client PRIVATE ${CMAKE_BINARY_DIR}/_deps/imgui-src)

set_target_properties(cinematic-client PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/../
)
