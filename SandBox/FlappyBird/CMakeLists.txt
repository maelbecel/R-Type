cmake_minimum_required(VERSION 3.12)
project(FlappyBird LANGUAGES CXX VERSION 1.0.1)

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


# Set source files for the FlappyBird
set(SOURCES
    src/FlappyBird.cpp

    src/Layer/GameLayer.cpp

    src/Level/Level.cpp

    src/Scripts/Player.cpp

    src/Tools/Random.cpp
)

# Set include directories for the FlappyBird
set(INCLUDE_DIRS

    # Flappy include directories
    src/

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
add_executable(FlappyBird ${SOURCES})

target_link_libraries(FlappyBird PRIVATE
    Exodia-Tools
    Exodia-Debug
    Exodia-ECS
    SandBoxGE

    glad::glad
    glfw
    imgui
    glm::glm
    OpenAL::OpenAL
    spdlog::spdlog
    unofficial::nativefiledialog::nfd
    yaml-cpp::yaml-cpp
    FreeALUT::alut
    Vorbis::vorbisfile
)

target_include_directories(FlappyBird PRIVATE
    ${CMAKE_BINARY_DIR}/../SandBox/Library/Tools/src/
    ${CMAKE_BINARY_DIR}/../SandBox/Library/Debug/src/
    ${CMAKE_BINARY_DIR}/../SandBox/Library/Entity-Component-System/src
)

target_include_directories(FlappyBird PRIVATE ${Stb_INCLUDE_DIR})
target_include_directories(FlappyBird PRIVATE ${CMAKE_BINARY_DIR}/_deps/imgui-src)

