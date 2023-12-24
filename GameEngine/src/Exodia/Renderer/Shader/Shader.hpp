/*
** EPITECH PROJECT, 2023
** ExodiaGameEngine
** File description:
** Shader
*/

#ifndef SHADER_HPP_
#define SHADER_HPP_

// Exodia Utils
#include "Utils/Memory.hpp"

// External include
#include <unordered_map>
#include <glm/glm.hpp>
#include <string>

namespace Exodia {

    /**
     * @brief The Shader class defines an abstract interface for creating, binding, and managing shaders.
     * It provides methods to create shader instances, set uniforms, and manage shader resources.
     */
    class Shader {

        /////////////
        // Factory //
        /////////////
      public:
        /**
         * @brief Create a shader instance from a file.
         *
         * @param filepath (Type: const std::string &) The path to the shader file.
         * @return         (Type: Ref<Shader>)         A reference to the created shader.
         */
        static Ref<Shader> Create(const std::string &filepath);

        /**
         * @brief Create a shader instance from vertex and fragment source code.
         *
         * @param name        (Type: const std::string &) The name of the shader.
         * @param vertexSrc   (Type: const std::string &) The source code of the vertex shader.
         * @param fragmentSrc (Type: const std::string &) The source code of the fragment shader.
         * @return            (Type: Ref<Shader>)         A reference to the created shader.
         */
        static Ref<Shader> Create(const std::string &name, const std::string &vertexSrc,
                                  const std::string &fragmentSrc);

        //////////////////////////////
        // Constructor & Destructor //
        //////////////////////////////
      public:
        virtual ~Shader() = default;

        /////////////
        // Methods //
        /////////////
      public:
        /**
         * @brief Bind the shader for rendering. This function makes the shader active for rendering.
         */
        virtual void Bind() const = 0;

        /**
         * @brief Unbind the shader. This function makes the shader inactive for rendering.
         */
        virtual void Unbind() const = 0;

        ///////////////////////
        // Getters & Setters //
        ///////////////////////
      public:
        /**
         * @brief Get the name of the shader.
         *
         * @return (Type: const std::string &) The name of the shader.
         */
        virtual const std::string &GetName() const = 0;

        /**
         * @brief Set an integer uniform in the shader.
         *
         * @param name  (Type: const std::string &) The name of the uniform.
         * @param value (Type: int)                 The value to set.
         */
        virtual void SetInt(const std::string &name, int value) = 0;

        /**
         * @brief Set an array of integer uniforms in the shader.
         *
         * @param name    (Type: const std::string &) The name of the uniform array.
         * @param values  (Type: int *)               Pointer to the array of values.
         * @param count   (Type: uint32_t)            The number of elements in the array.
         */
        virtual void SetIntArray(const std::string &name, int *values, uint32_t count) = 0;

        /**
         * @brief Set a float uniform in the shader.
         *
         * @param name  (Type: const std::string &) The name of the uniform.
         * @param value (Type: float)               The value to set.
         */
        virtual void SetFloat(const std::string &name, float value) = 0;

        /**
         * @brief Set a float uniform in the shader.
         *
         * @param name  (Type: const std::string &) The name of the uniform.
         * @param value (Type: const glm::vec2 &)   The value to set.
         */
        virtual void SetFloat2(const std::string &name, const glm::vec2 &value) = 0;

        /**
         * @brief Set a glm::vec3 uniform in the shader.
         *
         * @param name  (Type: const std::string &) The name of the uniform.
         * @param value (Type: const glm::vec3 &)   The value to set.
         */
        virtual void SetFloat3(const std::string &name, const glm::vec3 &value) = 0;

        /**
         * @brief Set a glm::vec4 uniform in the shader.
         *
         * @param name  (Type: const std::string &) The name of the uniform.
         * @param value (Type: const glm::vec4 &)   The value to set.
         */
        virtual void SetFloat4(const std::string &name, const glm::vec4 &value) = 0;

        /**
         * @brief Set a glm::mat4 uniform in the shader.
         *
         * @param name  (Type: const std::string &) The name of the uniform.
         * @param value (Type: const glm::mat4 &)   The value to set.
         */
        virtual void SetMat4(const std::string &name, const glm::mat4 &value) = 0;
    };

    /**
     * @brief The ShaderLibrary class provides functionality to manage and access shader instances.
     * It allows adding, loading, and retrieving shaders by name.
     */
    class ShaderLibrary {

        //////////////////////////////
        // Constructor & Destructor //
        //////////////////////////////
      public:
        ShaderLibrary() = default;
        ~ShaderLibrary() = default;

        // Methods
      public:
        /**
         * @brief Load and add a shader from a file to the library.
         *
         * @param filepath (Type: const std::string &) The path to the shader file.
         * @return         (Type: Ref<Shader>)         A reference to the loaded shader.
         */
        Ref<Shader> Load(const std::string &filepath);

        /**
         * @brief Load and add a shader from a file to the library with a specific name.
         *
         * @param name     (Type: const std::string &) The name of the shader.
         * @param filepath (Type: const std::string &) The path to the shader file.
         * @return         (Type: Ref<Shader>)         A reference to the loaded shader.
         */
        Ref<Shader> Load(const std::string &name, const std::string &filepath);

        ///////////////////////
        // Getters & Setters //
        ///////////////////////
      public:
        /**
         * @brief Add a shader to the library.
         *
         * @param shader (Type: const Ref<Shader> &) A reference to the shader to add.
         *
         * @note If a shader with the same name already exists, an assertion is raised.
         */
        void Add(const Ref<Shader> &shader);

        /**
         * @brief Add a shader with a specific name to the library.
         *
         * @param name   (Type: const std::string &) The name of the shader.
         * @param shader (Type: const Ref<Shader> &)  A reference to the shader to add.
         *
         * @note If a shader with the same name already exists, an assertion is raised.
         */
        void Add(const std::string &name, const Ref<Shader> &shader);

        /**
         * @brief Get a reference to a shader by name.
         *
         * @param name (Type: const std::string &) The name of the shader to retrieve.
         * @return     (Type: Ref<Shader>)         A reference to the shader.
         *
         * @note If the shader does not exist, an assertion is raised.
         */
        Ref<Shader> Get(const std::string &name);

        /**
         * @brief Check if a shader with a given name exists in the library.
         *
         * @param name (Type: const std::string &) The name of the shader to check.
         * @return     (Type: bool)                True if the shader exists, otherwise false.
         */
        bool Exists(const std::string &name) const;

        ////////////////
        // Attributes //
        ////////////////
      private:
        std::unordered_map<std::string, Ref<Shader>> _Shaders; /*!< A collection of shaders. */
    };
}; // namespace Exodia

#endif /* !SHADER_HPP_ */
