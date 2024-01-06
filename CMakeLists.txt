cmake_minimum_required(VERSION 3.12)

project(r-type)

set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/CMake" ${CMAKE_MODULE_PATH})

include($ENV{VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake)

# Dependencies (find_package (vcpkg))
include(Dependencies)

# Project
include(BuildEngine)
include(BuildBinaries)
include(BuildSandbox)

# Compilation Flags
include(CompileFlags)

if (MSVC)
    file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/Assets DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/../Debug)
    file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/Assets DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/../Release)
endif()
