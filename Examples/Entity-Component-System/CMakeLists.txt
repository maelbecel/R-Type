cmake_minimum_required(VERSION 3.12)

project(ecs)

set(CMAKE_BUILD_TYPE Debug)

# Set C++ standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Set compiler flags
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Werror")

set(GAME_ENGINE_DIR ${CMAKE_SOURCE_DIR}/GameEngine)

set(SOURCES

    src/Main.cpp
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

# Add an executable for the ecs
add_executable(ecs ${SOURCES})

target_link_libraries(ecs GameEngine glad glfw glm imgui)

target_include_directories(ecs PRIVATE ${glad_INCLUDE_DIRS})
target_include_directories(ecs PRIVATE ${CMAKE_BINARY_DIR}/_deps/opengl-src/GLAD/include)
target_include_directories(ecs PRIVATE ${CMAKE_BINARY_DIR}/_deps/opengl-src/stb_image)
target_include_directories(ecs PRIVATE ${CMAKE_BINARY_DIR}/_deps/glfw-src/include)
target_include_directories(ecs PRIVATE ${CMAKE_BINARY_DIR}/_deps/glm-src)
target_include_directories(ecs PRIVATE ${CMAKE_BINARY_DIR}/_deps/imgui-src)

set_target_properties(ecs PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/../bin_examples
)
