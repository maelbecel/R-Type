cmake_minimum_required(VERSION 3.12)

project(client LANGUAGES CXX VERSION 1.0.1)

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

# Set source files for the Exodia Game Engine Application
set(SOURCES

    src/RType.cpp

        # R-Type Layer sources files

    src/Layer/RTypeLayer.cpp
)

# Set include directories for the Exodia Game Engine Application
set(INCLUDE_DIRS
    # Exodia-App include directories
    src/

    # R-Type include directories
    ${R_TYPE_DIR}
    ${R_TYPE_DIR}/src

    # GameEngine include directories
    ${GAME_ENGINE_DIR}/src
    ${GAME_ENGINE_DIR}/src/Exodia
    ${GAME_ENGINE_DIR}/src/Platform
)

# Include directories
include_directories(${INCLUDE_DIRS})

# Add an executable for the client
add_executable(client ${SOURCES})

target_link_libraries(client PRIVATE
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
    FreeALUT::alut
    Vorbis::vorbisfile
)

target_include_directories(client PRIVATE
    ${CMAKE_BINARY_DIR}/../SandBox/Library/Tools/src/
    ${CMAKE_BINARY_DIR}/../SandBox/Library/Debug/src/
    ${CMAKE_BINARY_DIR}/../SandBox/Library/Entity-Component-System/src
)

target_include_directories(client PRIVATE ${Stb_INCLUDE_DIR})
target_include_directories(client PRIVATE ${CMAKE_BINARY_DIR}/_deps/imgui-src)

set_target_properties(client PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/../Release/R-Type/
)
