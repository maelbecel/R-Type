/*
** EPITECH PROJECT, 2023
** ExodiaGameEngine
** File description:
** EditorCamera
*/

// Exodia Renderer includes
#include "EditorCamera.hpp"

// Exodia Core includes
#include "Core/Key/Input.hpp"
#include "Core/Key/KeyCodes.hpp"
#include "Core/Key/MouseButtonCodes.hpp"
#include "Core/Application/Application.hpp"

// External includes
#define GLM_ENABLE_EXPERIMENTAL
    #include <glm/gtx/quaternion.hpp>

namespace Exodia {

    //////////////////////////////
    // Constructor & Destructor //
    //////////////////////////////

    EditorCamera::EditorCamera(float fov, float aspectRatio, float nearClip, float farClip) : _FOV(fov), _AspectRatio(aspectRatio), _NearClip(nearClip), _FarClip(farClip), _Position(glm::vec3(0.0f)), _FocalPoint(glm::vec3(0.0f)), _InitialMousePosition(glm::vec2(0.0f)), _Distance(10.0f), _Pitch(0.0f), _Yaw(0.0f), _ViewportWidth(1280), _ViewportHeight(720)
    {
        UpdateView();
    }

    /////////////
    // Methods //
    /////////////

    void EditorCamera::OnUpdate(Timestep ts)
    {
        (void)ts;

        if (Input::IsKeyPressed(Exodia::Key::LEFTALT)) {
            const glm::vec2 &mouse{
                Input::GetMouseX(),
                Input::GetMouseY()
            };

            glm::vec2 delta = (mouse - _InitialMousePosition) * 0.003f;

            _InitialMousePosition = mouse;

            //(void)delta;
            if (Input::IsMouseButtonPressed(Exodia::Mouse::BUTTONRIGHT) || Input::IsKeyPressed(Exodia::Key::V))
                MousePan(delta);
            else if (Input::IsMouseButtonPressed(Exodia::Mouse::BUTTONLEFT) || Input::IsKeyPressed(Exodia::Key::C))
                MouseRotate(delta);
            else if (Input::IsMouseButtonPressed(Exodia::Mouse::BUTTONRIGHT) || Input::IsKeyPressed(Exodia::Key::B))
                MouseZoom(delta.y);
        }
        UpdateView();
    }

    void EditorCamera::OnEvent(Event& event)
    {
        EventDispatcher dispatcher(event);

        dispatcher.Dispatch<MouseScrolledEvent>(BIND_EVENT_FN(EditorCamera::OnMouseScroll));
    }

    void EditorCamera::UpdateProjection()
    {
        _AspectRatio = _ViewportWidth / _ViewportHeight;

        _Projection = glm::perspective(glm::radians(_FOV), _AspectRatio, _NearClip, _FarClip);
    }

    void EditorCamera::UpdateView()
    {
        _Position = CalculatePosition();

        glm::quat orientation = GetOrientation();

        _ViewMatrix = glm::translate(glm::mat4(1.0f), _Position) * glm::toMat4(orientation);
        _ViewMatrix = glm::inverse(_ViewMatrix);
    }

    glm::vec3 EditorCamera::CalculatePosition() const
    {
        return _FocalPoint - GetForwardDirection() * _Distance;
    }

    ///////////////////////
    // Getters & Setters //
    ///////////////////////

    const glm::mat4 &EditorCamera::GetViewMatrix() const
    {
        return _ViewMatrix;
    }

    glm::mat4 EditorCamera::GetViewProjection() const
    {
        return _Projection * _ViewMatrix;
    }

    const glm::vec3 &EditorCamera::GetPosition() const
    {
        return _Position;
    }

    float EditorCamera::GetPitch() const
    {
        return _Pitch;
    }

    float EditorCamera::GetYaw() const
    {
        return _Yaw;
    }

    glm::vec3 EditorCamera::GetUpDirection() const
    {
        return glm::rotate(GetOrientation(), glm::vec3(0.0f, 1.0f, 0.0f));
    }

    glm::vec3 EditorCamera::GetRightDirection() const
    {
        return glm::rotate(GetOrientation(), glm::vec3(1.0f, 0.0f, 0.0f));
    }

    glm::vec3 EditorCamera::GetForwardDirection() const
    {
        return glm::rotate(GetOrientation(), glm::vec3(0.0f, 0.0f, -1.0f));
    }

    glm::quat EditorCamera::GetOrientation() const
    {
        return glm::quat(glm::vec3(-_Pitch, -_Yaw, 0.0f));
    }

    bool EditorCamera::OnMouseScroll(MouseScrolledEvent &e)
    {
        float delta = e.GetYOffset() * 0.1f;

        MouseZoom(delta);
        UpdateView();
        return false;
    }

    void EditorCamera::MousePan(const glm::vec2 &delta)
    {
        float xSpeed = PanSpeed().first;
        float ySpeed = PanSpeed().second;

        _FocalPoint += -GetRightDirection() * delta.x * xSpeed * _Distance;
        _FocalPoint +=  GetUpDirection()    * delta.y * ySpeed * _Distance;
    }

    void EditorCamera::MouseRotate(const glm::vec2 &delta)
    {
        float yawSign = (GetUpDirection().y < 0) ? -1.0f : 1.0f;

        _Yaw   += yawSign * delta.x * RotationSpeed();
        _Pitch += delta.y * RotationSpeed();
    }

    void EditorCamera::MouseZoom(float delta)
    {
        _Distance -= delta * ZoomSpeed();

        if (_Distance < 1.0f) {
            _FocalPoint += GetForwardDirection();
            _Distance = 1.0f;
        }
    }

    std::pair<float, float> EditorCamera::PanSpeed() const
    {
        float x = std::min(_ViewportWidth / 1000.0f, 2.4f); // max = 2.4f
        float xFactor = 0.0366f * (x * x) - 0.1778f * x + 0.3021f;

        float y = std::min(_ViewportHeight / 1000.0f, 2.4f); // max = 2.4f
        float yFactor = 0.0366f * (y * y) - 0.1778f * y + 0.3021f;

        return {
            xFactor,
            yFactor
        };
    }

    float EditorCamera::RotationSpeed() const
    {
        return 0.8f;
    }

    float EditorCamera::ZoomSpeed() const
    {
        float distance = _Distance * 0.2f;

        distance = std::max(distance, 0.0f);

        float speed = distance * distance;

        speed = std::min(speed, 100.0f); // max speed = 100
        return speed;
    }
}
