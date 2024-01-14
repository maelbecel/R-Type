/*
** EPITECH PROJECT, 2023
** ExodiaGameEngine
** File description:
** SceneCamera
*/

// Exodia Scene includes
#include "SceneCamera.hpp"

// Exodia Utils includes
#include "Exodia-Debug.hpp"

// External includes
#include <glm/gtc/matrix_transform.hpp>

namespace Exodia {

    //////////////////////////////
    // Constructor & Destructor //
    //////////////////////////////

    SceneCamera::SceneCamera()
        : _ProjectionType(ProjectionType::Orthographic), _OrthographicSize(10.0f), _OrthographicNear(-1.0f),
          _OrthographicFar(1.0f), _PerspectiveFOV(glm::radians(45.0f)), _PerspectiveNear(0.01f),
          _PerspectiveFar(1000.0f), _AspectRatio(0.0f) {
        RecalculateProjection();
    }

    /////////////
    // Methods //
    /////////////

    void SceneCamera::RecalculateProjection() {
        if (_ProjectionType == ProjectionType::Perspective)
            _Projection = glm::perspective(_PerspectiveFOV, _AspectRatio, _PerspectiveNear, _PerspectiveFar);
        else {
            float orthoLeft = -_OrthographicSize * _AspectRatio * 0.5f;
            float orthoRight = _OrthographicSize * _AspectRatio * 0.5f;
            float orthoBottom = -_OrthographicSize * 0.5f;
            float orthoTop = _OrthographicSize * 0.5f;

            _Projection = glm::ortho(orthoLeft, orthoRight, orthoBottom, orthoTop, _OrthographicNear, _OrthographicFar);
        }
    }

    ///////////////////////
    // Getters & Setters //
    ///////////////////////

    void SceneCamera::SetViewportSize(uint32_t width, uint32_t height) {
        EXODIA_CORE_ASSERT(width > 0 && height > 0, "Viewport size must be greater than 0 !");

        _AspectRatio = (float)width / (float)height;

        RecalculateProjection();
    }

    SceneCamera::ProjectionType SceneCamera::GetProjectionType() const { return _ProjectionType; }

    void SceneCamera::SetProjectionType(ProjectionType type) {
        _ProjectionType = type;

        RecalculateProjection();
    }

    // -- Orthographic -- //

    void SceneCamera::SetOrthographic(float size, float nearClip, float farClip) {
        _ProjectionType = ProjectionType::Orthographic;
        _OrthographicSize = size;
        _OrthographicNear = nearClip;
        _OrthographicFar = farClip;

        RecalculateProjection();
    }

    float SceneCamera::GetOrthographicSize() const { return _OrthographicSize; }

    void SceneCamera::SetOrthographicSize(float size) {
        _OrthographicSize = size;

        RecalculateProjection();
    }

    float SceneCamera::GetOrthographicNearClip() const { return _OrthographicNear; }

    void SceneCamera::SetOrthographicNearClip(float nearClip) {
        _OrthographicNear = nearClip;

        RecalculateProjection();
    }

    float SceneCamera::GetOrthographicFarClip() const { return _OrthographicFar; }

    void SceneCamera::SetOrthographicFarClip(float farClip) {
        _OrthographicFar = farClip;

        RecalculateProjection();
    }

    // -- Perspective -- //

    void SceneCamera::SetPersepective(float verticalFOV, float nearClip, float farClip) {
        _ProjectionType = ProjectionType::Perspective;
        _PerspectiveFOV = verticalFOV;
        _PerspectiveNear = nearClip;
        _PerspectiveFar = farClip;

        RecalculateProjection();
    }

    float SceneCamera::GetPerspectiveVerticalFOV() const { return _PerspectiveFOV; }

    void SceneCamera::SetPerspectiveVerticalFOV(float fov) {
        _PerspectiveFOV = fov;

        RecalculateProjection();
    }

    float SceneCamera::GetPerspectiveNearClip() const { return _PerspectiveNear; }

    void SceneCamera::SetPerspectiveNearClip(float nearClip) {
        _PerspectiveNear = nearClip;

        RecalculateProjection();
    }

    float SceneCamera::GetPerspectiveFarClip() const { return _PerspectiveFar; }

    void SceneCamera::SetPerspectiveFarClip(float farClip) {
        _PerspectiveFar = farClip;

        RecalculateProjection();
    }
}; // namespace Exodia
