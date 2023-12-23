cmake_minimum_required(VERSION 3.12)

project(enzo)

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

set(GAME_ENGINE_DIR ${CMAKE_SOURCE_DIR}/GameEngine)

set(SOURCES

    src/ApplicationExample.cpp
    src/DefaultLayer.cpp
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

# Add an executable for the enzo
add_executable(enzo ${SOURCES})

target_link_libraries(enzo GameEngine glad glfw glm imgui)

target_include_directories(enzo PRIVATE ${glad_INCLUDE_DIRS})
target_include_directories(enzo PRIVATE ${CMAKE_BINARY_DIR}/_deps/opengl-src/GLAD/include)
target_include_directories(enzo PRIVATE ${CMAKE_BINARY_DIR}/_deps/opengl-src/stb_image)
target_include_directories(enzo PRIVATE ${CMAKE_BINARY_DIR}/_deps/glfw-src/include)
target_include_directories(enzo PRIVATE ${CMAKE_BINARY_DIR}/_deps/glm-src)
target_include_directories(enzo PRIVATE ${CMAKE_BINARY_DIR}/_deps/imgui-src)

set_target_properties(enzo PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/../SandBox/bin/enzo
)

add_custom_command(TARGET enzo POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_SOURCE_DIR}/Assets $<TARGET_FILE_DIR:enzo>/Assets
)
