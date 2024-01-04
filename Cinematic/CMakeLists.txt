cmake_minimum_required(VERSION 3.12)

project(Cinematic LANGUAGES CXX VERSION 1.0.1)

set(CMAKE_CXX_STANDARD 17)

# Set compiler flags
if (WIN32)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
else()
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fPIC")
endif()

set(GLAD_INCLUDE_DIRS ${CMAKE_BINARY_DIR}/GLAD/include CACHE STRING "GLAD Include directories")
set(GAME_ENGINE_DIR  ${CMAKE_SOURCE_DIR}/GameEngine)

#Set the source files for the Game Engine Library
set(SOURCES_GAME_ENGINE

    ## Entity

    src/Entity/CreateBackground.cpp
)

# Set the include directories for the Game Engine Library
set(INCLUDE_DIRS_GAME_ENGINE
    src/

    src/Entity/

    # GameEngine include directories
    ${GAME_ENGINE_DIR}/src
    ${GAME_ENGINE_DIR}/src/Exodia
    ${GAME_ENGINE_DIR}/src/Exodia/ECS/
    ${GAME_ENGINE_DIR}/src/Platform
)

# Create the Game Engine Static Library
add_library(Cinematic STATIC ${SOURCES_GAME_ENGINE})

target_link_libraries(Cinematic PRIVATE
    GameEngine
    asio::asio
    glm::glm
    glfw
    glad::glad
    imgui
    OpenAL::OpenAL
    spdlog::spdlog
    Catch2::Catch2 Catch2::Catch2WithMain
    sol2
    unofficial::nativefiledialog::nfd
    yaml-cpp::yaml-cpp
    imguizmo::imguizmo
)

target_include_directories(Cinematic PRIVATE ${INCLUDE_DIRS_GAME_ENGINE})
target_include_directories(Cinematic PRIVATE ${Stb_INCLUDE_DIR})
target_include_directories(Cinematic PRIVATE ${CMAKE_BINARY_DIR}/_deps/imgui-src)
