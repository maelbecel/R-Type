# Option for compiling in debug mode
option(COMPILE_DEBUG "Compile debug" OFF)

# Add the game engine
add_subdirectory(GameEngine)

# Checking COMPILE_DEBUG option
if(COMPILE_DEBUG)
    target_compile_definitions(GameEngine PUBLIC EXODIA_DEBUG)
endif()
