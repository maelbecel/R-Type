/*
** EPITECH PROJECT, 2023
** ExodiaGameEngine
** File description:
** OpenGLRendererAPI
*/

// OpenGL
#include "OpenGLRendererAPI.hpp"
#include <glad/glad.h>

// Exodia Debug
#include "Exodia-Debug.hpp"

namespace Exodia {

    /////////////
    // Methods //
    /////////////

    void OpenGLRendererAPI::Init() {
        EXODIA_PROFILE_FUNCTION(); // Performance instrumentation profiling for the function

        glEnable(GL_BLEND);                                // Enable blending
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA); // Set the blending function
        glEnable(GL_DEPTH_TEST);                           // Enable depth testing
    }

    void OpenGLRendererAPI::Clear() {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Clear the color and depth buffers
    }

    void OpenGLRendererAPI::DrawIndexed(const Ref<VertexArray> &vertexArray, uint32_t indexCount) {
        vertexArray->Bind();

        uint32_t count = (indexCount == 0) ? vertexArray->GetIndexBuffer()->GetCount() : indexCount;

        glDrawElements(GL_TRIANGLES, count, GL_UNSIGNED_INT, nullptr); // Draw the vertex array
    }

    void OpenGLRendererAPI::DrawLines(const Ref<VertexArray> &vertexArray, uint32_t indexCount) {
        vertexArray->Bind();

        glDrawArrays(GL_LINES, 0, indexCount);
    }

    void OpenGLRendererAPI::SetLineWidth(float width) { glLineWidth(width); }

    ///////////////////////
    // Getters & Setters //
    ///////////////////////

    void OpenGLRendererAPI::SetClearColor(const glm::vec4 &color) { glClearColor(color.r, color.g, color.b, color.a); }

    void OpenGLRendererAPI::SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height) {
        glViewport(x, y, width, height);
    }
}; // namespace Exodia
