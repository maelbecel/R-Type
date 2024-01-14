cmake_minimum_required(VERSION 3.12)

project(Game LANGUAGES CXX VERSION 1.0.1)

set(CMAKE_CXX_STANDARD 17)

# Set compiler flags
if (WIN32)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
else()
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fPIC")
endif()

set(GLAD_INCLUDE_DIRS ${CMAKE_BINARY_DIR}/GLAD/include CACHE STRING "GLAD Include directories")
set(GAME_ENGINE_DIR  ${CMAKE_SOURCE_DIR}/GameEngine)

# Set the source files for the Game Engine Library
set(SOURCES_GAME_ENGINE

    # Game source files

        # -- System source files

        src/Systems/AnimationSystem.cpp
        src/Systems/FadeSystem.cpp

        # -- Script source files

        src/Scripts/Mars.cpp

        # -- Events source files

        # -- Entity source files

        # -- Component source files
)

# Set the include directories for the Game Engine Library
set(INCLUDE_DIRS_GAME_ENGINE
    src/

    # GameEngine include directories
    ${GAME_ENGINE_DIR}/src
    ${GAME_ENGINE_DIR}/src/Exodia
    ${GAME_ENGINE_DIR}/src/Exodia/ECS/
    ${GAME_ENGINE_DIR}/src/Platform
)

# Create the Game Engine Static Library
add_library(Game STATIC ${SOURCES_GAME_ENGINE})

target_link_libraries(Game PRIVATE
    GameEngine
    asio::asio
    glm::glm
    glfw
    glad::glad
    imgui
    OpenAL::OpenAL
    spdlog::spdlog
    
    
    unofficial::nativefiledialog::nfd
    yaml-cpp::yaml-cpp
)

target_include_directories(Game PRIVATE ${INCLUDE_DIRS_GAME_ENGINE})
target_include_directories(Game PRIVATE ${Stb_INCLUDE_DIR})
target_include_directories(Game PRIVATE ${CMAKE_BINARY_DIR}/_deps/imgui-src)
