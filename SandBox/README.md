# SandBox

## What is SandBox ?

The Sandbox directory within this game engine is a dedicated space designed for experimentation, and honing one's skills with the game engine's functionalities. It's an open area where developers, enthusiasts, and learners can experiment freely to understand and leverage the game engine's capabilities to create game components, prototype game mechanics, or craft entirely new games.

## How to use Sandbox ?

### Building Sandbox

To build the Sandbox, follow these steps:

-   Create a build directory: `mkdir build`
-   Navigate to the build directory: `cd build`
-   Generate the project files using CMake and Ninja: `cmake .. -DCOMPILE_SANDBOX=ON -G Ninja`
-   Build the project using Ninja: `ninja`

or

-   `./make.sh`
-   `make sandbox`

### Adding your own SandBox area

First create a folder :

```bash
tree

├── SandBox
│   ├── README.md
│   ├── CMakeLists.txt
│   ├── FirstSandBox
│   │   ├── CMakeLists.txt
│   │   ├── Assets/
│   │   ├── src/
```

Then add your own CMakeLists.txt, here is the template :

```cmake
cmake_minimum_required(VERSION 3.12)

project({{PROJECT_NAME}})

set(CMAKE_BUILD_TYPE Debug)

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

set(SOURCES

    src/{{SOURCE_FILE}}.cpp
)

set(INCLUDE_DIRS
    src/

    # GameEngine include directories
    ${GAME_ENGINE_DIR}/src
    ${GAME_ENGINE_DIR}/src/Exodia
    ${GAME_ENGINE_DIR}/src/Exodia/ECS/
    ${GAME_ENGINE_DIR}/src/Platform
)

# Include directories
include_directories(${INCLUDE_DIRS})

# Add an executable for the {{PROJECT_NAME}}
add_executable({{PROJECT_NAME}} ${SOURCES})

target_link_libraries({{PROJECT_NAME}} GameEngine glad glfw glm imgui)

target_include_directories({{PROJECT_NAME}} PRIVATE ${glad_INCLUDE_DIRS})
target_include_directories({{PROJECT_NAME}} PRIVATE ${CMAKE_BINARY_DIR}/_deps/opengl-src/GLAD/include)
target_include_directories({{PROJECT_NAME}} PRIVATE ${CMAKE_BINARY_DIR}/_deps/opengl-src/stb_image)
target_include_directories({{PROJECT_NAME}} PRIVATE ${CMAKE_BINARY_DIR}/_deps/glfw-src/include)
target_include_directories({{PROJECT_NAME}} PRIVATE ${CMAKE_BINARY_DIR}/_deps/glm-src)
target_include_directories({{PROJECT_NAME}} PRIVATE ${CMAKE_BINARY_DIR}/_deps/imgui-src)

set_target_properties({{PROJECT_NAME}} PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/../SandBox/bin/{{PROJECT_NAME}}
)

add_custom_command(TARGET {{PROJECT_NAME}} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_SOURCE_DIR}/Assets $<TARGET_FILE_DIR:{{PROJECT_NAME}}>/Assets
)
```

Change all {{PROJECT_NAME}} by your own project name.
Change all {{SOURCE_FILE}} by your own source file name.

Importante if it's a graphical project, do not forget to add the Assets folder to the build directory.

### For executable

```bash
cd SandBox/bin/{{PROJECT_NAME}} ; ./{{PROJECT_NAME}}
```
