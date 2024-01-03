cmake_minimum_required(VERSION 3.12)

project(Exodia-Tools LANGUAGES CXX VERSION 1.0.1)

set(CMAKE_CXX_STANDARD 17)

# Set compiler flags
if (WIN32)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
else()
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fPIC")
endif()

# Set the source files for the Game Engine Tools Library
set(SOURCES_GAME_ENGINE src/Memory/Buffer.cpp)

# Create the Game Engine Static Library
add_library(Exodia-Tools STATIC ${SOURCES_GAME_ENGINE})

target_include_directories(Exodia-Tools PRIVATE src)
