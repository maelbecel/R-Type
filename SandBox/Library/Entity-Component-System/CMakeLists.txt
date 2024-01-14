cmake_minimum_required(VERSION 3.12)

project(Exodia-ECS LANGUAGES CXX VERSION 1.0.1)

set(CMAKE_CXX_STANDARD 17)

# Set compiler flags
if (WIN32)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
else()
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fPIC")
endif()

# Set the source files for the Game Engine ECS Library
set(SOURCES_GAME_ENGINE
    src/Entity/Entity.cpp
    src/Entity/EntityIterator.cpp
    src/Entity/EntityView.cpp
    src/World/World.cpp
)

# Create the Game Engine Static Library
add_library(Exodia-ECS STATIC ${SOURCES_GAME_ENGINE})

target_link_libraries(Exodia-ECS PRIVATE
    spdlog::spdlog
    Exodia-Tools
    Exodia-Debug
)

target_include_directories(Exodia-ECS PRIVATE
    ${CMAKE_BINARY_DIR}/../SandBox/Library/Tools/src/
    ${CMAKE_BINARY_DIR}/../SandBox/Library/Debug/src/
)
target_include_directories(Exodia-ECS PRIVATE src)
