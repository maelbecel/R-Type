cmake_minimum_required(VERSION 3.12)

project(r-type_client)

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

    # GameEngine include directories
    ${GAME_ENGINE_DIR}/src
    ${GAME_ENGINE_DIR}/src/Exodia
    ${GAME_ENGINE_DIR}/src/Exodia/ECS/
    ${GAME_ENGINE_DIR}/src/Platform
)

# Include directories
include_directories(${INCLUDE_DIRS})

# Add an executable for the r-type_client
add_executable(r-type_client ${SOURCES})

target_link_libraries(r-type_client GameEngine glad glfw glm imgui)

target_include_directories(r-type_client PRIVATE ${glad_INCLUDE_DIRS})
target_include_directories(r-type_client PRIVATE ${CMAKE_BINARY_DIR}/_deps/opengl-src/GLAD/include)
target_include_directories(r-type_client PRIVATE ${CMAKE_BINARY_DIR}/_deps/opengl-src/stb_image)
target_include_directories(r-type_client PRIVATE ${CMAKE_BINARY_DIR}/_deps/glfw-src/include)
target_include_directories(r-type_client PRIVATE ${CMAKE_BINARY_DIR}/_deps/glm-src)
target_include_directories(r-type_client PRIVATE ${CMAKE_BINARY_DIR}/_deps/imgui-src)
target_include_directories(r-type_client PRIVATE ${CMAKE_BINARY_DIR}/_deps/asio-src/asio/include)

set_target_properties(r-type_client PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/../
)
