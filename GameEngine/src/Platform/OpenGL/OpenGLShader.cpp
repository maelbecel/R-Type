/*
** EPITECH PROJECT, 2023
** ExodiaGameEngine
** File description:
** OpenGLShader
*/

// OpenGL includes
#include "OpenGLShader.hpp"

// Exodia Utils includes
#include "Utils/Assert.hpp"

// Exodia Debug includes
#include "Debug/Logs.hpp"
#include "Debug/Profiling.hpp"

// External includes
#include <glm/gtc/type_ptr.hpp>
#include <fstream>
#include <vector>
#include <array>

namespace Exodia {

    static GLenum ShaderTypeFromString(const std::string &type)
    {
        if (type == "vertex")
            return GL_VERTEX_SHADER;
        if (type == "fragment" || type == "pixel")
            return GL_FRAGMENT_SHADER;

        EXODIA_CORE_ASSERT(false, "Unknown shader type !");
        return 0;
    }

    //////////////////////////////
    // Constructor & Destructor //
    //////////////////////////////

    OpenGLShader::OpenGLShader(const std::string &name, const std::string &vertexSrc, const std::string &fragmentSrc) : _Name(name)
    {
        EXODIA_PROFILE_FUNCTION();

        std::unordered_map<GLenum, std::string> shaderSources;

        shaderSources[GL_VERTEX_SHADER] = vertexSrc;
        shaderSources[GL_FRAGMENT_SHADER] = fragmentSrc;

        Compile(shaderSources);
    }

    OpenGLShader::OpenGLShader(const std::string &filepath)
    {
        EXODIA_PROFILE_FUNCTION();

        std::string ShaderSrc = ReadFile(filepath);

        std::unordered_map<GLenum, std::string> shaderSources = PreProcess(ShaderSrc);

        Compile(shaderSources);

        // Extract name from filepath

        std::size_t lastSlash = filepath.find_last_of("/\\");
        std::size_t lastDot = filepath.rfind('.');

        lastSlash = (lastSlash == std::string::npos) ? 0 : lastSlash + 1;

        std::size_t count = (lastDot == std::string::npos) ? filepath.size() - lastSlash : lastDot - lastSlash;

        _Name = filepath.substr(lastSlash, count);
    }

    OpenGLShader::~OpenGLShader()
    {
        EXODIA_PROFILE_FUNCTION();

        glDeleteProgram(_RendererID);
    }

    /////////////
    // Methods //
    /////////////

    void OpenGLShader::Bind() const
    {
        EXODIA_PROFILE_FUNCTION();

        glUseProgram(_RendererID);
    }

    void OpenGLShader::Unbind() const
    {
        EXODIA_PROFILE_FUNCTION();

        glUseProgram(0);
    }

    void OpenGLShader::UploadUniformInt(const std::string &name, int value)
    {
        GLint location = glGetUniformLocation(_RendererID, name.c_str());

        glUniform1i(location, value);
    }

    void OpenGLShader::UploadUniformFloat(const std::string &name, float value)
    {
        GLint location = glGetUniformLocation(_RendererID, name.c_str());

        glUniform1f(location, value);
    }

    void OpenGLShader::UploadUniformFloat2(const std::string &name, const glm::vec2 &values)
    {
        GLint location = glGetUniformLocation(_RendererID, name.c_str());

        glUniform2f(location, values.x, values.y);
    }

    void OpenGLShader::UploadUniformFloat3(const std::string &name, const glm::vec3 &values)
    {
        GLint location = glGetUniformLocation(_RendererID, name.c_str());

        glUniform3f(location, values.x, values.y, values.z);
    }

    void OpenGLShader::UploadUniformFloat4(const std::string &name, const glm::vec4 &values)
    {
        GLint location = glGetUniformLocation(_RendererID, name.c_str());

        glUniform4f(location, values.x, values.y, values.z, values.w);
    }

    void OpenGLShader::UploadUniformMat3(const std::string &name, const glm::mat3 &matrix)
    {
        GLint location = glGetUniformLocation(_RendererID, name.c_str());

        glUniformMatrix3fv(location, 1, GL_FALSE, glm::value_ptr(matrix));
    }

    void OpenGLShader::UploadUniformMat4(const std::string &name, const glm::mat4 &matrix)
    {
        GLint location = glGetUniformLocation(_RendererID, name.c_str());

        glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(matrix));
    }

    std::string OpenGLShader::ReadFile(const std::string &filepath)
    {
        EXODIA_PROFILE_FUNCTION();

        std::ifstream in(filepath, std::ios::in | std::ios::binary);
        std::string contents;

        if (in) {
            in.seekg(0, std::ios::end);
            contents.resize(in.tellg());
            in.seekg(0, std::ios::beg);
            in.read(&contents[0], contents.size());
            in.close();
        } else
            EXODIA_CORE_ERROR("Could not open file '{0}'", filepath);

        return contents;
    }

    std::unordered_map<GLenum, std::string> OpenGLShader::PreProcess(const std::string &source)
    {
        EXODIA_PROFILE_FUNCTION();

        std::unordered_map<GLenum, std::string> shaderSources;

        const char *typeToken = "#type";
        size_t typeTokenLength = strlen(typeToken);
        size_t pos = source.find(typeToken, 0);

        while (pos != std::string::npos) {
            size_t eol = source.find_first_of("\r\n", pos);

            EXODIA_CORE_ASSERT(eol != std::string::npos, "Syntax error");

            size_t begin = pos + typeTokenLength + 1;
            std::string type = source.substr(begin, eol - begin);
            
            EXODIA_CORE_ASSERT(ShaderTypeFromString(type), "Invalid shader type specified");

            size_t nextLinePos = source.find_first_not_of("\r\n", eol);
            
            EXODIA_CORE_ASSERT(nextLinePos != std::string::npos, "Syntax error");

            pos = source.find(typeToken, nextLinePos);
            shaderSources[ShaderTypeFromString(type)] = (pos == std::string::npos) ? source.substr(nextLinePos) : source.substr(nextLinePos, pos - nextLinePos);
        }

        return shaderSources;
    }

    void OpenGLShader::Compile(const std::unordered_map<GLenum, std::string> &shaderSources)
    {
        EXODIA_PROFILE_FUNCTION();

        GLuint program = glCreateProgram();

        EXODIA_CORE_ASSERT(shaderSources.size() <= MAX_SHADER_SUPPORTED, std::string("We only support " + std::to_string(MAX_SHADER_SUPPORTED) + " shaders for now !").c_str());

        std::array<GLenum, MAX_SHADER_SUPPORTED> glShaderIDs;
        int glShaderIDIndex = 0;

        for (auto &kv : shaderSources) {
            GLenum type = kv.first;
            const std::string &source = kv.second;
            GLuint shader = glCreateShader(type);
            const GLchar *sourceCStr = source.c_str();

            glShaderSource(shader, 1, &sourceCStr, 0);
            glCompileShader(shader);

            GLint isCompiled = 0;

            glGetShaderiv(shader, GL_COMPILE_STATUS, &isCompiled);
            if (isCompiled == GL_FALSE) {
                GLint maxLength = 0;

                glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &maxLength);

                std::vector<GLchar> infoLog(maxLength);

                glGetShaderInfoLog(shader, maxLength, &maxLength, &infoLog[0]);
                glDeleteShader(shader);

                EXODIA_CORE_ERROR(infoLog.data());
                EXODIA_CORE_ASSERT(false, "Shader compilation failure!");
                break;
            }

            glAttachShader(program, shader);

            glShaderIDs[glShaderIDIndex++] = shader;
        }

        _RendererID = program;

        // Link our program
        glLinkProgram(program);

        // Note the different functions here: glGetProgram* instead of glGetShader*.
        GLint isLinked = 0;

        glGetProgramiv(program, GL_LINK_STATUS, (int *)&isLinked);
        if (isLinked == GL_FALSE) {
            GLint maxLength = 0;

            glGetProgramiv(program, GL_INFO_LOG_LENGTH, &maxLength);

            // The maxLength includes the NULL character
            std::vector<GLchar> infoLog(maxLength);

            glGetProgramInfoLog(program, maxLength, &maxLength, &infoLog[0]);
            // We don't need the program anymore.
            glDeleteProgram(program);
            
            for (auto id : glShaderIDs)
                glDeleteShader(id);

            EXODIA_CORE_ERROR(infoLog.data());
            EXODIA_CORE_ASSERT(false, "Shader link failure!");
            return;
        }

        for (auto id : glShaderIDs)
            glDetachShader(program, id);
    }

    ///////////////////////
    // Getters & Setters //
    ///////////////////////

    const std::string &OpenGLShader::GetName() const
    {
        return _Name;
    }

    void OpenGLShader::SetInt(const std::string &name, int value)
    {
        EXODIA_PROFILE_FUNCTION();

        UploadUniformInt(name, value);
    }

    void OpenGLShader::SetIntArray(const std::string &name, int *values, uint32_t count)
    {
        EXODIA_PROFILE_FUNCTION();

        GLint location = glGetUniformLocation(_RendererID, name.c_str());
    
        if (location != -1)
            glUniform1iv(location, count, values);
    }

    void OpenGLShader::SetFloat(const std::string &name, float value)
    {
        EXODIA_PROFILE_FUNCTION();

        UploadUniformFloat(name, value);
    }

    void OpenGLShader::SetFloat2(const std::string &name, const glm::vec2 &value)
    {
        EXODIA_PROFILE_FUNCTION();

        UploadUniformFloat2(name, value);
    }

    void OpenGLShader::SetFloat3(const std::string &name, const glm::vec3 &value)
    {
        EXODIA_PROFILE_FUNCTION();

        UploadUniformFloat3(name, value);
    }

    void OpenGLShader::SetFloat4(const std::string &name, const glm::vec4 &value)
    {
        EXODIA_PROFILE_FUNCTION();

        UploadUniformFloat4(name, value);
    }

    void OpenGLShader::SetMat4(const std::string &name, const glm::mat4 &value)
    {
        EXODIA_PROFILE_FUNCTION();

        UploadUniformMat4(name, value);
    }
};
