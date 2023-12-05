cmake_minimum_required(VERSION 3.12)

project(r-type)

set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/CMake" ${CMAKE_MODULE_PATH})

# Option for compiling examples
option(COMPILE_EXAMPLES "Compile examples" OFF)

# Dependencies (find_package (vcpkg))
include(Dependencies)

# Project
include(BuildEngine)

if(COMPILE_EXAMPLES)
    add_subdirectory(Examples)
else()
    add_subdirectory(Client)
    add_subdirectory(Server)
endif()
