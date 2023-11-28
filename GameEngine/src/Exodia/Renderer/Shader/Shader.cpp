/*
** EPITECH PROJECT, 2023
** ExodiaGameEngine
** File description:
** Shader
*/

// Exodia Renderer
#include "Shader.hpp"
#include "Renderer/Renderer/Renderer.hpp"

// Exodia Utils
#include "Utils/Assert.hpp"

// Entry Point
#include "OpenGL/OpenGLShader.hpp"

namespace Exodia {

    //////////////////////////////////////////////////////////////////////////////////////////
    ////////////////////////////////////// Shader ////////////////////////////////////////////
    //////////////////////////////////////////////////////////////////////////////////////////

    /////////////
    // Factory //
    /////////////

    Ref<Shader> Shader::Create(const std::string &filepath)
    {
        switch (Renderer::GetAPI()) {
            case RendererAPI::API::None:
                EXODIA_CORE_ASSERT(false, "RendererAPI::None is not supported !");
                return nullptr;
            case RendererAPI::API::OpenGL:
                return CreateRef<OpenGLShader>(filepath);
            default:
                break;
        }

        EXODIA_CORE_ASSERT(false, "Unknown RendererAPI !");
        return nullptr;
    }

    Ref<Shader> Shader::Create(const std::string &name, const std::string &vertexSrc, const std::string &fragmentSrc)
    {
        switch (Renderer::GetAPI()) {
            case RendererAPI::API::None:
                EXODIA_CORE_ASSERT(false, "RendererAPI::None is not supported !");
                return nullptr;
            case RendererAPI::API::OpenGL:
                return CreateRef<OpenGLShader>(name, vertexSrc, fragmentSrc);
            default:
                break;
        }

        EXODIA_CORE_ASSERT(false, "Unknown RendererAPI !");
        return nullptr;
    }

    //////////////////////////////////////////////////////////////////////////////////////////
    ////////////////////////////////// ShaderLibrary /////////////////////////////////////////
    //////////////////////////////////////////////////////////////////////////////////////////

    /////////////
    // Methods //
    /////////////

    Ref<Shader> ShaderLibrary::Load(const std::string &filepath)
    {
        // Call the shader factory
        Ref<Shader> shader = Shader::Create(filepath);

        // Add the shader to the collection
        Add(shader);
        return shader;
    }

    Ref<Shader> ShaderLibrary::Load(const std::string &name, const std::string &filepath)
    {
        // Call the shader factory
        Ref<Shader> shader = Shader::Create(filepath);

        // Add the shader to the collection
        Add(name, shader);
        return shader;
    }

    ///////////////////////
    // Getters & Setters //
    ///////////////////////

    void ShaderLibrary::Add(const Ref<Shader> &shader)
    {
        const std::string &name = shader->GetName();

        EXODIA_CORE_ASSERT(!Exists(name), "Shader already exists !");

        _Shaders[name] = shader;
    }

    void ShaderLibrary::Add(const std::string &name, const Ref<Shader> &shader)
    {
        EXODIA_CORE_ASSERT(!Exists(name), "Shader already exists !");

        _Shaders[name] = shader;
    }

    Ref<Shader> ShaderLibrary::Get(const std::string &name)
    {
        EXODIA_CORE_ASSERT(Exists(name), "Shader not found !");

        return _Shaders[name];
    }

    bool ShaderLibrary::Exists(const std::string &name) const
    {
        return _Shaders.find(name) != _Shaders.end();
    }
};
