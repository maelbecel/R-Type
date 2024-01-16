cmake_minimum_required(VERSION 3.12)

project(R-TypeSolo LANGUAGES CXX VERSION 1.0.1)

set(CMAKE_CXX_STANDARD 17)

# Set compiler flags
if (WIN32)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
else()
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fPIC")
endif()

set(GLAD_INCLUDE_DIRS ${CMAKE_BINARY_DIR}/GLAD/include CACHE STRING "GLAD Include directories")
set(GAME_ENGINE_DIR  ${CMAKE_SOURCE_DIR}/SandBox/GameEngine)

# Set the source files for the Game Engine Library
set(SOURCES_GAME_ENGINE

    # R-TypeSolo source files

        # -- System source files

        src/System/AnimationSystem.cpp
        src/System/FadeSystem.cpp

        # -- Script source files

        src/Scripts/Player/PlayerController.cpp
        src/Scripts/Player/Module.cpp
        src/Scripts/Player/PowerUp.cpp
        src/Scripts/Player/BulletPlayer.cpp
        src/Scripts/Player/SuperBullet.cpp
        src/Scripts/Player/Player.cpp
        src/Scripts/Enemies/PataPata/Pata-pata.cpp
        src/Scripts/Enemies/BulletEnemy.cpp
        src/Scripts/Star/Star.cpp
        src/Scripts/Tabrok/Tabrok.cpp
        src/Scripts/Mid/Mid.cpp
        src/Scripts/Bug/Bug.cpp

        src/Scripts/Menu/Intro.cpp

        # -- Entity source files

        src/Entity/CreateBackground.cpp

        # -- Event source files

        src/Event/Transition.cpp
)

# Set the include directories for the Game Engine Library
set(INCLUDE_DIRS_GAME_ENGINE
    src/

    src/Entity/

    # GameEngine include directories
    ${GAME_ENGINE_DIR}/src
    ${GAME_ENGINE_DIR}/src/Exodia
    ${GAME_ENGINE_DIR}/src/Platform
)

# Create the Game Engine Static Library
add_library(R-TypeSolo STATIC ${SOURCES_GAME_ENGINE})

target_link_libraries(R-TypeSolo PRIVATE
    Exodia-Tools
    Exodia-Debug
    Exodia-ECS

    SandBoxGE

    glm::glm
    glfw
    glad::glad
    imgui
    OpenAL::OpenAL
    spdlog::spdlog
    unofficial::nativefiledialog::nfd
    yaml-cpp::yaml-cpp
)

target_include_directories(R-TypeSolo PRIVATE
    ${CMAKE_BINARY_DIR}/../SandBox/Library/Debug/src/
    ${CMAKE_BINARY_DIR}/../SandBox/Library/Tools/src/
    ${CMAKE_BINARY_DIR}/../SandBox/Library/Entity-Component-System/src/
)

target_include_directories(R-TypeSolo PRIVATE ${INCLUDE_DIRS_GAME_ENGINE})
target_include_directories(R-TypeSolo PRIVATE ${Stb_INCLUDE_DIR})
target_include_directories(R-TypeSolo PRIVATE ${CMAKE_BINARY_DIR}/_deps/imgui-src)
