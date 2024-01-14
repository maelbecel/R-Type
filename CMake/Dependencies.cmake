# Find packages with vcpkg

message(STATUS "Searching for packages with vcpkg...")

   # -- Network Library --------------------------------------------------------
find_package(asio  CONFIG REQUIRED) # asio::asio

    # -- Graphics Library -------------------------------------------------------
find_package(Stb          REQUIRED) # ${Stb_INCLUDE_DIRS}
find_package(glm   CONFIG REQUIRED) # glm::glm
find_package(glfw3 CONFIG REQUIRED) # glfw
find_package(glad  CONFIG REQUIRED) # glad::glad

    # -- Audio Library ---------------------------------------------------------
find_package(OpenAL   CONFIG REQUIRED) # OpenAL::OpenAL
find_package(FreeALUT CONFIG REQUIRED) # FreeALUT::alut
find_package(Vorbis   CONFIG REQUIRED) # Vorbis::vorbisfile

    # -- Serialization Library -------------------------------------------------
find_package(yaml-cpp CONFIG REQUIRED) # yaml-cpp::yaml-cpp

    # -- Debugging Library -----------------------------------------------------
find_package(spdlog   CONFIG REQUIRED) # spdlog::spdlog

    # -- Game Editor Library ---------------------------------------------------
find_package(unofficial-nativefiledialog CONFIG REQUIRED) # unofficial::nativefiledialog::nfd

message(STATUS "Searching for packages with vcpkg... done")
message(STATUS "Searching for 3rd-party libraries with FetchContent...")

# Find dependencies with FetchContent
add_subdirectory(3rd-party)

message(STATUS "Searching for 3rd-party libraries with FetchContent... done")
