cmake_minimum_required(VERSION 3.25)

include(FetchContent)

project(Vendor)

FetchContent_Declare(
    opengl
    GIT_REPOSITORY https://github.com/PharaEthan/OpenGL.git
    GIT_TAG        main
)

FetchContent_MakeAvailable(opengl)

set(IGG_COMPONENTS "IMGUI;GLFW;GLM" CACHE STRING "The components to import and build")

foreach (comp IN ITEMS ${IGG_COMPONENTS})
    set(IMPORT_${comp} ON)
endforeach ()

if (IMPORT_IMGUI)
    set(IMPORT_GLFW ON)
endif ()

if (IMPORT_IMGUI)
    set(IGG_IMGUI_TAG docking CACHE STRING "Defines the imgui version (e.g. master, v1.89.4, v1.89.3, ...")
    set(IMPORT_GLFW ON)
else ()
    unset(IGG_IMGUI_TAG CACHE)
endif ()

if (IMPORT_GLFW)
    set(IGG_GLFW_TAG master CACHE STRING "Defines the glfw version (e.g. master, 3.3.8, 3.3.7, ...) ")
else ()
    unset(IGG_GLFW_TAG CACHE)
endif ()

if (IMPORT_GLM)
    set(IGG_GLM_TAG master CACHE STRING "Defines the glm version (e.g. master, 0.9.9.8, 0.9.9.7, ...")
else ()
    unset(IGG_GLM_TAG CACHE)
endif ()

if (IMPORT_GLFW)
    FetchContent_Declare(
            glfw
            GIT_REPOSITORY https://github.com/glfw/glfw.git
            GIT_TAG ${IGG_GLFW_TAG}
    )
    list(APPEND components glfw)
endif ()

if (IMPORT_GLM)
    FetchContent_Declare(
            glm
            GIT_REPOSITORY https://github.com/g-truc/glm.git
            GIT_TAG ${IGG_GLM_TAG}
    )
    list(APPEND components glm)
endif ()

if (IMPORT_IMGUI)
    FetchContent_Declare(
            imgui
            GIT_REPOSITORY https://github.com/ocornut/imgui.git
            GIT_TAG ${IGG_IMGUI_TAG}
    )
    list(APPEND components imgui)
endif ()

if (components)
    FetchContent_MakeAvailable(${components})
endif ()

if (IMPORT_IMGUI)
    file(GLOB imgui_SRC ${imgui_SOURCE_DIR}/*.cpp ${imgui_SOURCE_DIR}/*.h)

    add_library(imgui ${imgui_SRC} ${imgui_SOURCE_DIR}/backends/imgui_impl_opengl3.cpp ${imgui_SOURCE_DIR}/backends/imgui_impl_opengl3.h ${imgui_SOURCE_DIR}/backends/imgui_impl_glfw.cpp ${imgui_SOURCE_DIR}/backends/imgui_impl_glfw.h)

    target_link_libraries(imgui PUBLIC glfw glad)

    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DIMGUI_IMPL_OPENGL_LOADER_GLAD2")

    target_include_directories(imgui PUBLIC ${imgui_SOURCE_DIR} ${imgui_SOURCE_DIR}/backends)
endif ()

include(FetchContent)

FetchContent_Declare(
  Boost
  GIT_REPOSITORY https://github.com/boostorg/asio.git
  GIT_TAG develop
)

FetchContent_MakeAvailable(Boost)
