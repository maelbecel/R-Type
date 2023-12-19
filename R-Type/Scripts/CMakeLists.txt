cmake_minimum_required(VERSION 3.12)

project(test LANGUAGES CXX VERSION 1.0.1)

# Set C++ standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(GAME_ENGINE_DIR  ${CMAKE_SOURCE_DIR}/GameEngine)
set(R_TYPE_DIR  ${CMAKE_SOURCE_DIR}/R-Type)

# Set source files for the Exodia Game Engine Application
set(SOURCES
    TestScript.cpp
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

# Add an executable for the test
add_library(test SHARED ${SOURCES})

if(WIN32)
    set_target_properties(test PROPERTIES 
        ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
        LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
        RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
    )

    target_compile_definitions(test PRIVATE _CRT_SECURE_NO_WARNINGS)
else()
    set_target_properties(test PROPERTIES 
        LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
    )
endif()

target_link_libraries(test PRIVATE
    GameEngine
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
)

target_include_directories(test PRIVATE ${Stb_INCLUDE_DIR})
target_include_directories(test PRIVATE ${CMAKE_BINARY_DIR}/_deps/imgui-src)
