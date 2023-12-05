cmake_minimum_required(VERSION 3.12)

project(r-type)

# Option for compiling examples
option(COMPILE_EXAMPLES "Compile examples" OFF)

# Find Packages
find_package(Boost REQUIRED)
find_package(glm REQUIRED)
find_package(glfw3 REQUIRED)
find_package(glad REQUIRED)
find_package(Stb REQUIRED)

add_subdirectory(3rd-party)
add_subdirectory(GameEngine)

if(COMPILE_EXAMPLES)
    add_subdirectory(Examples)
else()
    add_subdirectory(Client)
    add_subdirectory(Server)
endif()
