cmake_minimum_required(VERSION 3.12)

project(r-type)

# Option for compiling examples
option(COMPILE_EXAMPLES "Compile examples" OFF)

# Find Packages
find_package(Boost REQUIRED)
find_package(Stb   REQUIRED)

find_package(glm                         CONFIG REQUIRED)
find_package(glfw3                       CONFIG REQUIRED)
find_package(glad                        CONFIG REQUIRED)
find_package(OpenAL                      CONFIG REQUIRED)
find_package(spdlog                      CONFIG REQUIRED)
find_package(Catch2                      CONFIG REQUIRED)
find_package(sol2                        CONFIG REQUIRED)
find_package(unofficial-nativefiledialog CONFIG REQUIRED)
find_package(yaml-cpp                    CONFIG REQUIRED)
find_package(imguizmo                    CONFIG REQUIRED)

add_subdirectory(3rd-party)
add_subdirectory(GameEngine)

if(COMPILE_EXAMPLES)
    add_subdirectory(Examples)
else()
    add_subdirectory(Client)
    add_subdirectory(Server)
endif()
