cmake_minimum_required(VERSION 3.25)

include(FetchContent)

project(Vendor)

set(IGG_IMGUI_TAG docking CACHE STRING "Defines the imgui version (e.g. master, v1.89.4, v1.89.3, ...")

FetchContent_Declare(
        imgui
        GIT_REPOSITORY https://github.com/ocornut/imgui.git
        GIT_TAG ${IGG_IMGUI_TAG}
)

FetchContent_MakeAvailable(imgui)

file(GLOB imgui_SRC ${imgui_SOURCE_DIR}/*.cpp ${imgui_SOURCE_DIR}/*.h)

add_library(imgui ${imgui_SRC} ${imgui_SOURCE_DIR}/backends/imgui_impl_opengl3.cpp ${imgui_SOURCE_DIR}/backends/imgui_impl_opengl3.h ${imgui_SOURCE_DIR}/backends/imgui_impl_glfw.cpp ${imgui_SOURCE_DIR}/backends/imgui_impl_glfw.h)

target_link_libraries(imgui PUBLIC glfw glad::glad)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DIMGUI_IMPL_OPENGL_LOADER_GLAD2")

target_include_directories(imgui PUBLIC ${imgui_SOURCE_DIR} ${imgui_SOURCE_DIR}/backends)
