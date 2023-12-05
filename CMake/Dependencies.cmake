# Find packages with vcpkg

   # -- Network Library --------------------------------------------------------
find_package(Boost REQUIRED) # Boost::boost

    # -- Graphics Library -------------------------------------------------------
find_package(Stb          REQUIRED) # ${Stb_INCLUDE_DIRS}
find_package(glm   CONFIG REQUIRED) # glm::glm
find_package(glfw3 CONFIG REQUIRED) # glfw
find_package(glad  CONFIG REQUIRED) # glad::glad

    # -- Audio Library ---------------------------------------------------------
find_package(OpenAL   CONFIG REQUIRED) # OpenAL::OpenAL

    # -- Serialization Library -------------------------------------------------
find_package(yaml-cpp CONFIG REQUIRED) # yaml-cpp::yaml-cpp

    # -- Debugging Library -----------------------------------------------------
find_package(spdlog   CONFIG REQUIRED) # spdlog::spdlog

    # -- Unit Testing Library --------------------------------------------------
find_package(Catch2   CONFIG REQUIRED) # Catch2::Catch2 Catch2::Catch2WithMain

    # -- Scripting Library -----------------------------------------------------
find_package(sol2     CONFIG REQUIRED) # sol2

    # -- Game Editor Library ---------------------------------------------------
find_package(unofficial-nativefiledialog CONFIG REQUIRED) # unofficial::nativefiledialog::nfd
find_package(imguizmo                    CONFIG REQUIRED) # imguizmo::imguizmo

# Find dependencies with FetchContent
add_subdirectory(3rd-party)
