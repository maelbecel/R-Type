/*
** EPITECH PROJECT, 2023
** ExodiaGameEngine
** File description:
** OpenGLShader
*/

#ifndef OPENGLSHADER_HPP_
    #define OPENGLSHADER_HPP_

    // Exodia Renderer includes
    #include "Renderer/Shader/Shader.hpp"

    // External includes
    #include <unordered_map>
    #include <glm/glm.hpp>
    #include <glad/glad.h>

namespace Exodia {

    class OpenGLShader : public Shader {

        //////////////////////////////
        // Constructor & Destructor //
        //////////////////////////////
        public:

            /**
             * @brief Construct a new OpenGLShader object
             * Call this constructor if you want to create a OpenGLShader from a file
             * @param name        The name of the shader
             * @param vertexSrc   Path to the vertex shader
             * @param fragmentSrc Path to the fragment shader
             * @overload
             * @param filepath    Path to the shader
             */
            OpenGLShader(const std::string &name, const std::string &vertexSrc, const std::string &fragmentSrc);
            OpenGLShader(const std::string &filepath);

            /**
             * @brief Destroy the OpenGLShader object
             */
            virtual ~OpenGLShader();

        /////////////
        // Methods //
        /////////////
        public:

            /**
             * @brief Bind the shader
             * Call this method if you want to use the shader
             * Bind is the action to use the shader
             */
            virtual void Bind() const override;

            /**
             * @brief Unbind the shader
             * Call this method if you want to unbind the shader
             * Unbind is the action to stop using the shader
             */
            virtual void Unbind() const override;

            void UploadUniformInt(const std::string &name, int value);
            void UploadUniformFloat(const std::string &name, float value);
            void UploadUniformFloat2(const std::string &name, const glm::vec2 &values);
            void UploadUniformFloat3(const std::string &name, const glm::vec3 &values);
            void UploadUniformFloat4(const std::string &name, const glm::vec4 &values);
            void UploadUniformMat3(const std::string &name, const glm::mat3 &matrix);
            void UploadUniformMat4(const std::string &name, const glm::mat4 &matrix);

        private:
            std::string ReadFile(const std::string &filepath);
            std::unordered_map<GLenum, std::string> PreProcess(const std::string &source);
            void Compile(const std::unordered_map<GLenum, std::string> &shaderSources);


        ///////////////////////
        // Getters & Setters //
        ///////////////////////
        public:

            /**
             * @brief Get the Name of the shader
             * Call this method if you want to get the name of the shader
             * @return const std::string& The name of the shader
             */
            virtual const std::string &GetName() const override;

            virtual void SetInt(const std::string &name, int value) override;
            virtual void SetIntArray(const std::string &name, int *values, uint32_t count) override;
            virtual void SetFloat(const std::string &name, float value) override;
            virtual void SetFloat2(const std::string &name, const glm::vec2 &value) override;
            virtual void SetFloat3(const std::string &name, const glm::vec3 &value) override;
            virtual void SetFloat4(const std::string &name, const glm::vec4 &value) override;
            virtual void SetMat4(const std::string &name, const glm::mat4 &value) override;

        ////////////////
        // Attributes //
        ////////////////
        private:
            uint32_t _RendererID; /*!< ID of the shader */
            std::string _Name;    /*!< Name of the shader */

        ////////////
        // Define //
        ////////////
        private:
            static const int MAX_SHADER_SUPPORTED = 2; /*!< Max shader supported by OpenGL */
    };
};

#endif /* !OPENGLSHADER_HPP_ */
