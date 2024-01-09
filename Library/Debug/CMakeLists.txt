cmake_minimum_required(VERSION 3.12)

project(Exodia-Debug LANGUAGES CXX VERSION 1.0.1)

set(CMAKE_CXX_STANDARD 17)

# Set compiler flags
if (WIN32)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
else()
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fPIC")
endif()

# Set the source files for the Game Engine Debug Library
set(SOURCES_GAME_ENGINE
    src/Logger/Log.cpp
    src/Profiling/Instrumentor.cpp
    src/Profiling/InstrumentorTimer.cpp
)

# Create the Game Engine Static Library
add_library(Exodia-Debug STATIC ${SOURCES_GAME_ENGINE})

target_link_libraries(Exodia-Debug PRIVATE
    spdlog::spdlog
    Exodia-Tools
)

target_include_directories(Exodia-Debug PRIVATE src)
target_include_directories(Exodia-Debug PRIVATE ${CMAKE_BINARY_DIR}/../Library/Tools/src/)
