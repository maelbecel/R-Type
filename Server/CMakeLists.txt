cmake_minimum_required(VERSION 3.12)

project(r-type_server LANGUAGES CXX VERSION 1.0.1)

set(CMAKE_BUILD_TYPE Debug)

# Set C++ standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Set compiler flags
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Werror")

set(GAME_ENGINE_DIR  ${CMAKE_SOURCE_DIR}/GameEngine)
set(R_TYPE_DIR  ${CMAKE_SOURCE_DIR}/R-Type)

# Set source files for the Exodia Game Engine Application
set(SOURCES

    src/Main.cpp
)

# Set include directories for the Exodia Game Engine Application
set(INCLUDE_DIRS
    # Exodia-App include directories

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

# Add an executable for the r-type_server
add_executable(r-type_server ${SOURCES})

target_link_libraries(r-type_server PRIVATE
    GameEngine
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
)

target_include_directories(r-type_server PRIVATE ${Stb_INCLUDE_DIR})
target_include_directories(r-type_server PRIVATE ${CMAKE_BINARY_DIR}/_deps/imgui-src)

set_target_properties(r-type_server PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/../
)
