cmake_minimum_required(VERSION 3.12)

project(r-type)

# Option for compiling examples
option(COMPILE_EXAMPLES "Compile examples" OFF)
option(COMPILE_SANDBOX "Compile sandbox" OFF)

add_subdirectory(3rd-party)
add_subdirectory(GameEngine)

if(COMPILE_EXAMPLES)
    add_subdirectory(Examples)
elseif(COMPILE_SANDBOX)
    add_subdirectory(SandBox)
else()
    add_subdirectory(Client)
    add_subdirectory(Server)
endif()
