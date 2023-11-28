/*
** EPITECH PROJECT, 2023
** ExodiaGameEngine
** File description:
** OrthographicCamera
*/

// Exodia Renderer
#include "OrthographicCamera.hpp"

// Exodia Debug
#include "Debug/Profiling.hpp"

// Extern includes
#include <glm/gtc/matrix_transform.hpp>

namespace Exodia {

    //////////////////////////////
    // Constructor & Destructor //
    //////////////////////////////

    OrthographicCamera::OrthographicCamera(float left, float right, float bottom, float top) : _ProjectionMatrix(glm::ortho(left, right, bottom, top, -1.0f, 1.0f)), _ViewMatrix(1.0f), _Position({0.0f, 0.0f, 0.0f}), _Rotation(0.0f)
    {
        EXODIA_PROFILE_FUNCTION(); // Performance instrumentation profiling for the function

        _ViewProjectionMatrix = _ProjectionMatrix * _ViewMatrix;
    }

    /////////////
    // Methods //
    /////////////

    void OrthographicCamera::RecalculateViewMatrix()
    {
        EXODIA_PROFILE_FUNCTION(); // Performance instrumentation profiling for the function

        glm::mat4 transform = glm::translate(glm::mat4(1.0f), _Position) * glm::rotate(glm::mat4(1.0f), glm::radians(_Rotation), glm::vec3(0, 0, 1));

        _ViewMatrix = glm::inverse(transform);
        _ViewProjectionMatrix = _ProjectionMatrix * _ViewMatrix;
    }

    ///////////////////////
    // Getters & Setters //
    ///////////////////////

    const glm::vec3 &OrthographicCamera::GetPosition() const
    {
        return _Position;
    }

    const glm::mat4 &OrthographicCamera::GetProjectionMatrix() const
    {
        return _ProjectionMatrix;
    }

    const glm::mat4 &OrthographicCamera::GetViewMatrix() const
    {
        return _ViewMatrix;
    }

    const glm::mat4 &OrthographicCamera::GetViewProjectionMatrix() const
    {
        return _ViewProjectionMatrix;
    }

    float OrthographicCamera::GetRotation() const
    {
        return _Rotation;
    }

    void OrthographicCamera::SetPosition(const glm::vec3 &position)
    {
        _Position = position;
        RecalculateViewMatrix();
    }

    void OrthographicCamera::SetRotation(float rotation)
    {
        _Rotation = rotation;
        RecalculateViewMatrix();
    }

    void OrthographicCamera::SetProjection(float left, float right, float bottom, float top)
    {
        EXODIA_PROFILE_FUNCTION(); // Performance instrumentation profiling for the function

        _ProjectionMatrix = glm::ortho(left, right, bottom, top, -1.0f, 1.0f);
        _ViewProjectionMatrix = _ProjectionMatrix * _ViewMatrix;
    }
};
