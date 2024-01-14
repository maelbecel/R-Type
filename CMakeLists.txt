cmake_minimum_required(VERSION 3.12)

project(r-type)

set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/CMake" ${CMAKE_MODULE_PATH})

include($ENV{VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake)

# Dependencies (find_package (vcpkg))
include(Dependencies)

# Project
include(BuildEngine)
include(BuildBinaries)

# Compilation Flags
include(CompileFlags)

file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/Assets                    DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/../Release)
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/SandBox/FlappyBird/Assets DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/../Release/FlappyBird/)
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/SandBox/R-Type/Assets     DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/../Release/R-Type/)
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/SandBox/R-Type/imgui.ini  DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/../Release/R-Type/)
