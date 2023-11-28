/*
** EPITECH PROJECT, 2023
** ExodiaGameEngine
** File description:
** OrthographicCameraController
*/

// Exodia Renderer
#include "OrthographicCameraController.hpp"

// Exodia Debug
#include "Debug/Profiling.hpp"

// Exodia Core
#include "Core/Application/Application.hpp"
#include "Core/Key/KeyCodes.hpp"
#include "Core/Key/Input.hpp"

namespace Exodia {

    //////////////////////////////
    // Constructor & Destructor //
    //////////////////////////////

    OrthographicCameraController::OrthographicCameraController(float aspectRatio, bool rotation) : _ZoomLevel(1.0f), _Bounds({ -aspectRatio * _ZoomLevel, aspectRatio * _ZoomLevel, -_ZoomLevel, _ZoomLevel }), _Camera(_Bounds.Left, _Bounds.Right, _Bounds.Bottom, _Bounds.Top), _AspectRatio(aspectRatio), _Rotation(rotation), _CameraPos({0.0f, 0.0f, 0.0f}), _CameraRotation(0.0f), _CameraTranslationSpeed(5.0f), _CameraRotationSpeed(180.0f) {};

    /////////////
    // Methods //
    /////////////

    void OrthographicCameraController::OnUpdate(Timestep ts)
    {
        if (Input::IsKeyPressed(EXODIA_KEY_LEFT)) {
            _CameraPos.x -= cos(glm::radians(_CameraRotation)) * _CameraTranslationSpeed * ts;
            _CameraPos.y -= sin(glm::radians(_CameraRotation)) * _CameraTranslationSpeed * ts;
        } else if (Input::IsKeyPressed(EXODIA_KEY_RIGHT)) {
            _CameraPos.x += cos(glm::radians(_CameraRotation)) * _CameraTranslationSpeed * ts;
            _CameraPos.y += sin(glm::radians(_CameraRotation)) * _CameraTranslationSpeed * ts;
        } else if (Input::IsKeyPressed(EXODIA_KEY_UP)) {
            _CameraPos.x += -sin(glm::radians(_CameraRotation)) * _CameraTranslationSpeed * ts;
            _CameraPos.y += cos(glm::radians(_CameraRotation)) * _CameraTranslationSpeed * ts;
        } else if (Input::IsKeyPressed(EXODIA_KEY_DOWN)) {
            _CameraPos.x -= -sin(glm::radians(_CameraRotation)) * _CameraTranslationSpeed * ts;
            _CameraPos.y -= cos(glm::radians(_CameraRotation)) * _CameraTranslationSpeed * ts;
        }

        if (_Rotation) {
            if (Input::IsKeyPressed(EXODIA_KEY_A))
                _CameraRotation += _CameraRotationSpeed * ts;
            else if (Input::IsKeyPressed(EXODIA_KEY_E))
                _CameraRotation -= _CameraRotationSpeed * ts;

            if (_CameraRotation > 180.0f)
                _CameraRotation -= 360.0f;
            else if (_CameraRotation <= -180.0f)
                _CameraRotation += 360.0f;

            _Camera.SetRotation(_CameraRotation);
        }

        _Camera.SetPosition(_CameraPos);

        _CameraTranslationSpeed = _ZoomLevel;
    }

    void OrthographicCameraController::OnEvent(Event &event)
    {
        EXODIA_PROFILE_FUNCTION(); // Performance instrumentation profiling for the function

        EventDispatcher dispatcher(event);

        dispatcher.Dispatch<MouseScrolledEvent>(BIND_EVENT_FN(OrthographicCameraController::OnMouseScrolled));
        dispatcher.Dispatch<WindowResizeEvent>(BIND_EVENT_FN(OrthographicCameraController::OnWindowResized));
    }

    void OrthographicCameraController::OnResize(float width, float height)
    {
        _AspectRatio = width / height;

        CalculateView();
    }

    void OrthographicCameraController::CalculateView()
    {
        _Bounds = { -_AspectRatio * _ZoomLevel, _AspectRatio * _ZoomLevel, -_ZoomLevel, _ZoomLevel };
        _Camera.SetProjection(_Bounds.Left, _Bounds.Right, _Bounds.Bottom, _Bounds.Top);
    }

    bool OrthographicCameraController::OnMouseScrolled(MouseScrolledEvent &event)
    {
        EXODIA_PROFILE_FUNCTION(); // Performance instrumentation profiling for the function

        _ZoomLevel -= event.GetYOffset() * 0.25f;
        _ZoomLevel = std::max(_ZoomLevel, 0.25f);

        CalculateView();
        return false;
    }

    bool OrthographicCameraController::OnWindowResized(WindowResizeEvent &event)
    {
        EXODIA_PROFILE_FUNCTION(); // Performance instrumentation profiling for the function

        OnResize((float)event.GetWidth(), (float)event.GetHeight());

        return false;
    }

    ///////////////////////
    // Getters & Setters //
    ///////////////////////

    OrthographicCamera &OrthographicCameraController::GetCamera()
    {
        return _Camera;
    }

    const OrthographicCamera &OrthographicCameraController::GetCamera() const
    {
        return _Camera;
    }

    void OrthographicCameraController::SetZoomLevel(float level)
    {
        _ZoomLevel = level;

        CalculateView();
    }

    float OrthographicCameraController::GetZoomLevel() const
    {
        return _ZoomLevel;
    }

    const OrthographicCameraBounds &OrthographicCameraController::GetBounds() const
    {
        return _Bounds;
    }
};
