# Check all the compilation flags

    # -- Debug mode ------------------------------------------------------------    
# Option for compiling in debug mode
option(COMPILE_DEBUG "Compile debug" OFF)

# Checking COMPILE_DEBUG option and definition
if(COMPILE_DEBUG)
    message(STATUS "Debug mode enabled")

    target_compile_options(GameEngine PRIVATE -g)
    target_compile_options(r-type_server PRIVATE -g)
    target_compile_options(r-type_client PRIVATE -g)

    target_compile_definitions(GameEngine PUBLIC EXODIA_DEBUG)
endif()

    # -- Examples --------------------------------------------------------------
# Option for compiling examples
option(COMPILE_EXAMPLES "Compile examples" OFF)

if (COMPILE_EXAMPLES)
    message(STATUS "Examples enabled")

    add_subdirectory(Examples)
endif()

option(COMPILE_FLAPPYBIRD "Compile flappy bird" OFF)
option(COMPILE_SOLORTYPE  "Compile solo r-type" OFF)
option(COMPILE_EDITOR "Compile editor" OFF)

if (COMPILE_EDITOR)
    set(COMPILE_FLAPPYBIRD ON)
    set(COMPILE_SOLORTYPE  ON)
endif()

if (COMPILE_FLAPPYBIRD)
    message(STATUS "Sandbox enabled")

    add_subdirectory(SandBox/FlappyBird)
endif()

if (COMPILE_SOLORTYPE)
    message(STATUS "Solo R-Type enabled")

    add_subdirectory(SandBox/R-Type/R-Type)
    add_subdirectory(SandBox/R-Type/RT_Client)
endif()

if (COMPILE_EDITOR)
    message(STATUS "Editor enabled")

    add_subdirectory(SandBox/Editor)
endif()
