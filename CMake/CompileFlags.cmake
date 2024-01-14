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

    # -- Flappy Bird -----------------------------------------------------------
# Option for compiling sandbox
option(COMPILE_FLAPPYBIRD "Compile flappy bird" OFF)

if (COMPILE_FLAPPYBIRD)
    message(STATUS "Sandbox enabled")

    add_subdirectory(SandBox/FlappyBird)
endif()

    # -- Solo R-Type -----------------------------------------------------------
# Option for compiling solo r-type
option(COMPILE_SOLORTYPE "Compile solo r-type" OFF)

if (COMPILE_SOLORTYPE)
    message(STATUS "Solo R-Type enabled")

    add_subdirectory(SandBox/R-Type/R-Type)
    add_subdirectory(SandBox/R-Type/RT_Client)
endif()
