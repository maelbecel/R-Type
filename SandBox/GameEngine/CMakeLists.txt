cmake_minimum_required(VERSION 3.12)

project(SandBoxGE LANGUAGES CXX VERSION 1.0.1)

set(CMAKE_CXX_STANDARD 17)

# Set compiler flags
if (WIN32)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
else()
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fPIC")
endif()

set(GLAD_INCLUDE_DIRS ${CMAKE_BINARY_DIR}/GLAD/include CACHE STRING "GLAD Include directories")

# Set the source files for the Game Engine Library
set(SOURCES_GAME_ENGINE

    # Exodia source files

        # -- Core source files

    src/Exodia/Core/Application/Application.cpp
    src/Exodia/Core/Layer/LayerStack.cpp
    src/Exodia/Core/Layer/Layer.cpp

        # -- Renderer source files

    src/Exodia/Renderer/Renderer/RenderCommand.cpp
    src/Exodia/Renderer/Renderer/Renderer.cpp
    src/Exodia/Renderer/Renderer/Renderer2D.cpp
    src/Exodia/Renderer/Renderer/RendererAPI.cpp
    src/Exodia/Renderer/Texture/SubTexture2D.cpp
    src/Exodia/Renderer/Texture/Texture.cpp
    src/Exodia/Renderer/Camera/OrthographicCameraController.cpp
    src/Exodia/Renderer/Camera/OrthographicCamera.cpp
    src/Exodia/Renderer/Camera/EditorCamera.cpp
    src/Exodia/Renderer/Camera/Camera.cpp
    src/Exodia/Renderer/Buffer/UniformBuffer.cpp
    src/Exodia/Renderer/Buffer/Framebuffer.cpp
    src/Exodia/Renderer/Buffer/Buffers.cpp
    src/Exodia/Renderer/Context/GraphicsContext.cpp
    src/Exodia/Renderer/Shader/Shader.cpp
    src/Exodia/Renderer/Vertex/VertexArray.cpp
    src/Exodia/Renderer/Sound/Sound.cpp
    src/Exodia/Renderer/Font/Font.cpp

        # -- Scene source files

    src/Exodia/Scene/Camera/SceneCamera.cpp
    src/Exodia/Scene/Serializer/SceneSerializer.cpp
    src/Exodia/Scene/Scene/Scene.cpp
    src/Exodia/Scene/System/Collision/CollisionSystem.cpp
    src/Exodia/Scene/System/Physics/GravitySystem.cpp
    src/Exodia/Scene/System/Physics/MovingSystem.cpp
    src/Exodia/Scene/System/Particle/ParticleSystem.cpp
    src/Exodia/Scene/EventSubscriber/EventHover.cpp
    src/Exodia/Scene/GameObject/GameObject.cpp

        # -- Script source files
    
    src/Exodia/Script/Engine/ScriptEngine.cpp

        # -- Project source files

    src/Exodia/Project/Project.cpp
    src/Exodia/Project/ProjectSerializer.cpp

        # -- Exodia ImGui source files

    src/Exodia/ImGui/ImGuiLayer.cpp

        # -- Exodia Asset source files

    src/Exodia/Asset/Importer/TextureImporter.cpp
    src/Exodia/Asset/Importer/AssetImporter.cpp
    src/Exodia/Asset/Importer/SceneImporter.cpp
    src/Exodia/Asset/Importer/SoundImporter.cpp
    src/Exodia/Asset/Importer/FontImporter.cpp
    src/Exodia/Asset/Importer/PrefabsImporter.cpp
    src/Exodia/Asset/Manager/EditorAssetManager.cpp

        # -- Exodia Math source files

    src/Exodia/Math/Math.cpp

    # Platform source files

        # -- Windows source files

    src/Platform/Windows/WindowsPlatformUtils.cpp
    src/Platform/Windows/WindowsWindow.cpp
    src/Platform/Windows/WindowsInput.cpp
    src/Platform/Windows/WindowsFileDialog.cpp

        # -- OpenGL source files

    src/Platform/OpenGL/OpenGLContext.cpp
    src/Platform/OpenGL/OpenGLBuffer.cpp
    src/Platform/OpenGL/OpenGLFramebuffer.cpp
    src/Platform/OpenGL/OpenGLRendererAPI.cpp
    src/Platform/OpenGL/OpenGLShader.cpp
    src/Platform/OpenGL/OpenGLTexture.cpp
    src/Platform/OpenGL/OpenGLUniformBuffer.cpp
    src/Platform/OpenGL/OpenGLVertexArray.cpp
    src/Platform/OpenGL/OpenGLSound.cpp
    src/Platform/OpenGL/OpenGLFont.cpp
)

# Set the include directories for the Game Engine Library
set(INCLUDE_DIRS_GAME_ENGINE
    src/

    # Game Engine include directories
    src/Exodia

    # Game Engine ECS include directories
    src/Exodia/ECS

    # Game Engine Platform include directories
    src/Platform
)

# Create the Game Engine Static Library
add_library(SandBoxGE STATIC ${SOURCES_GAME_ENGINE})

target_link_libraries(SandBoxGE PRIVATE
    Exodia-Tools
    Exodia-Debug
    Exodia-ECS

    glm::glm
    glfw
    glad::glad
    imgui
    OpenAL::OpenAL
    spdlog::spdlog
    unofficial::nativefiledialog::nfd
    yaml-cpp::yaml-cpp
    FreeALUT::alut
    Vorbis::vorbisfile
)

set(EXODIA_LIB_DIR ${CMAKE_BINARY_DIR}/../SandBox/Library)

target_include_directories(SandBoxGE PRIVATE
    ${EXODIA_LIB_DIR}/Tools/src
    ${EXODIA_LIB_DIR}/Debug/src
    ${EXODIA_LIB_DIR}/Entity-Component-System/src
)
target_include_directories(SandBoxGE PRIVATE ${INCLUDE_DIRS_GAME_ENGINE})
target_include_directories(SandBoxGE PRIVATE ${Stb_INCLUDE_DIR})
target_include_directories(SandBoxGE PRIVATE ${CMAKE_BINARY_DIR}/_deps/imgui-src)
