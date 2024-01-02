cmake_minimum_required(VERSION 3.12)

project(R-Type LANGUAGES CXX VERSION 1.0.1)

set(CMAKE_CXX_STANDARD 17)

# Set compiler flags
if (WIN32)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
else()
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fPIC")
endif()

set(GLAD_INCLUDE_DIRS ${CMAKE_BINARY_DIR}/GLAD/include CACHE STRING "GLAD Include directories")
set(GAME_ENGINE_DIR  ${CMAKE_SOURCE_DIR}/GameEngine)

# Set the source files for the Game Engine Library
set(SOURCES_GAME_ENGINE

    # R-Type source files

        # -- System source files

        src/System/AnimationSystem.cpp

        # -- Script source files

    src/Scripts/Player/Player.cpp
    src/Scripts/Player/Animations.cpp
    src/Scripts/Pata-pata/Pata-pata.cpp
    src/Scripts/BulletPlayer/BulletPlayer.cpp
    src/Scripts/BulletEnnemy/BulletEnnemy.cpp
    src/Scripts/Star/Star.cpp

        # -- Events source files

    src/Event/EntityEventSubscriber.cpp

        # -- Entity source files

    src/Entity/CreateBackground.cpp

        # -- Component source files
)

# Set the include directories for the Game Engine Library
set(INCLUDE_DIRS_GAME_ENGINE
    src/

    src/Entity/

    # GameEngine include directories
    ${GAME_ENGINE_DIR}/src
    ${GAME_ENGINE_DIR}/src/Exodia
    ${GAME_ENGINE_DIR}/src/Exodia/ECS/
    ${GAME_ENGINE_DIR}/src/Platform
)

# Create the Game Engine Static Library
add_library(R-Type STATIC ${SOURCES_GAME_ENGINE})

target_link_libraries(R-Type PRIVATE
    GameEngine
    asio::asio
    glm::glm
    glfw
    glad::glad
    imgui
    OpenAL::OpenAL
    spdlog::spdlog
    Catch2::Catch2 Catch2::Catch2WithMain
    sol2
    unofficial::nativefiledialog::nfd
    yaml-cpp::yaml-cpp
    imguizmo::imguizmo
)

target_include_directories(R-Type PRIVATE ${INCLUDE_DIRS_GAME_ENGINE})
target_include_directories(R-Type PRIVATE ${Stb_INCLUDE_DIR})
target_include_directories(R-Type PRIVATE ${CMAKE_BINARY_DIR}/_deps/imgui-src)
