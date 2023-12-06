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

if(COMPILE_EXAMPLES)
    message(STATUS "Examples enabled")

    add_subdirectory(Examples)
endif()
