cmake_minimum_required(VERSION 3.12)

project(UDPWrapper_server)

set(CMAKE_BUILD_TYPE Debug)

# Set C++ standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Set compiler flags
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Werror")

set(GAME_ENGINE_DIR ${CMAKE_SOURCE_DIR}/GameEngine)

set(SOURCES

    src/Server.cpp
)

set(INCLUDE_DIRS
    src/

    # GameEngine include directories
    ${GAME_ENGINE_DIR}/src
    ${GAME_ENGINE_DIR}/src/Exodia
    ${GAME_ENGINE_DIR}/src/Exodia/ECS/
    ${GAME_ENGINE_DIR}/src/Platform
)

# Include directories
include_directories(${INCLUDE_DIRS})

# Add an executable for the UDPWrapper_server
add_executable(UDPWrapper_server ${SOURCES})

target_link_libraries(UDPWrapper_server PRIVATE
    GameEngine
    glad::glad
    glfw
    imgui
    glm::glm
    Boost::boost
    OpenAL::OpenAL
    spdlog::spdlog
    Catch2::Catch2 Catch2::Catch2WithMain
    sol2
    unofficial::nativefiledialog::nfd
    yaml-cpp::yaml-cpp
    imguizmo::imguizmo
)

target_include_directories(UDPWrapper_server PRIVATE ${Stb_INCLUDE_DIR})
target_include_directories(UDPWrapper_server PRIVATE ${CMAKE_BINARY_DIR}/_deps/imgui-src)


set_target_properties(UDPWrapper_server PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/../bin_examples
)
