cmake_minimum_required(VERSION 3.12)

project(r-type_game LANGUAGES CXX VERSION 1.0.1)

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
set(R_TYPE_DIR      ${CMAKE_SOURCE_DIR}/SandBox/Ethan/R-Type) # TODO: Replace by the real R-Type directory

# Set source files for the Exodia Game Engine Application
set(SOURCES

    src/RType.cpp

        # R-Type Layer sources files

    src/Layer/GameLayer.cpp

        # R-Type GameScene sources files

    src/GameScene/LoadingScene.cpp
    src/GameScene/MenuScene.cpp

        # R-Type Events sources files
    
    src/Events/Transition.cpp

        # R-Type Scripts sources files
    
    src/Scripts/Intro.cpp
    src/Scripts/MenuHandler.cpp

        # R-Type Diverses sources files

    src/Settings/Config.cpp
    src/Settings/Settings.cpp
)

# Set include directories for the Exodia Game Engine Application
set(INCLUDE_DIRS
    # Exodia-App include directories
    src/

    # R-Type include directories
    ${R_TYPE_DIR}
    ${R_TYPE_DIR}/src

    # GameEngine include directories
    ${GAME_ENGINE_DIR}/src
    ${GAME_ENGINE_DIR}/src/Exodia
    ${GAME_ENGINE_DIR}/src/Exodia/ECS/
    ${GAME_ENGINE_DIR}/src/Platform
)

# Include directories
include_directories(${INCLUDE_DIRS})

# Add an executable for the r-type_game
add_executable(r-type_game ${SOURCES})

target_link_libraries(r-type_game PRIVATE
    Exodia-Tools
    Exodia-Debug

    GameEngine
    Game
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
    FreeALUT::alut
)

target_include_directories(r-type_game PRIVATE
    ${CMAKE_BINARY_DIR}/../Library/Debug/src/
    ${CMAKE_BINARY_DIR}/../Library/Tools/src/
)
target_include_directories(r-type_game PRIVATE ${Stb_INCLUDE_DIR})
target_include_directories(r-type_game PRIVATE ${CMAKE_BINARY_DIR}/_deps/imgui-src)

set_target_properties(r-type_game PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/../
)
