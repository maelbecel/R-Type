cmake_minimum_required(VERSION 3.12)

project(r-type)

set(CMAKE_TOOLCHAIN_FILE $ENV{VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake CACHE STRING "Vcpkg toolchain file")
set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/CMake" ${CMAKE_MODULE_PATH})

# Include VCPKG
include($ENV{VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake)

# Dependencies (find_package (vcpkg))
include(Dependencies)

# Project
include(BuildEngine)
include(BuildBinaries)

# Compilation Flags
include(CompileFlags)
