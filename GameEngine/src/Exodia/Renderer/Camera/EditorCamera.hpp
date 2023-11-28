/*
** EPITECH PROJECT, 2023
** ExodiaGameEngine
** File description:
** EditorCamera
*/

#ifndef EDITORCAMERA_HPP_
    #define EDITORCAMERA_HPP_

    // Exodia Renderer includes
    #include "Renderer/Camera/Camera.hpp"

    // Exodia Core includes
    #include "Core/Time/Timestep.hpp"

    // Exodia Events includes
    #include "Events/Event.hpp"
    #include "Events/MouseEvent.hpp"

    // External includes
    #include <glm/glm.hpp>

namespace Exodia {

    class EditorCamera : public Camera {
        
        //////////////////////////////
        // Constructor & Destructor //
        //////////////////////////////
        public:

            EditorCamera(float fov = 45.0f, float aspectRatio = 1.778f, float nearClip = 0.1f, float farClip = 1000.0f);
            virtual ~EditorCamera() override = default;

        /////////////
        // Methods //
        /////////////
        public:

            void OnUpdate(Timestep ts);
            void OnEvent(Event &event);

        private:

            void UpdateProjection();
            void UpdateView();
            glm::vec3 CalculatePosition() const;

        ///////////////////////
        // Getters & Setters //
        ///////////////////////
        public:

            inline float GetDistance() const
            {
                return _Distance;
            }

            inline void SetDistance(float distance)
            {
                _Distance = distance;
            }

            inline void SetViewportSize(float width, float height)
            {
                _ViewportWidth = width;
                _ViewportHeight = height;
                UpdateProjection();
            }

            const glm::mat4 &GetViewMatrix() const;
            glm::mat4 GetViewProjection() const;
            const glm::vec3 &GetPosition() const;
            float GetPitch() const;
            float GetYaw() const;
            glm::vec3 GetUpDirection() const;
            glm::vec3 GetRightDirection() const;
            glm::vec3 GetForwardDirection() const;
            glm::quat GetOrientation() const;

        private:
            bool OnMouseScroll(MouseScrolledEvent &e);
            void MousePan(const glm::vec2 &delta);
            void MouseRotate(const glm::vec2 &delta);
            void MouseZoom(float delta);
            std::pair<float, float> PanSpeed() const;
            float RotationSpeed() const;
            float ZoomSpeed() const;

        ////////////////
        // Attributes //
        ////////////////
        private:
            float     _FOV;                  /* !< The field of view of the camera */
            float     _AspectRatio;          /* !< The aspect ratio of the camera */
            float     _NearClip;             /* !< The near clip of the camera */
            float     _FarClip;              /* !< The far clip of the camera */
            glm::mat4 _ViewMatrix;           /* !< The view matrix of the camera */
            glm::vec3 _Position;             /* !< The position of the camera */
            glm::vec3 _FocalPoint;           /* !< The focal point of the camera (the point the camera is looking at) */
            glm::vec2 _InitialMousePosition; /* !< The initial mouse position */
            float     _Distance;             /* !< The distance between the camera and the focal point */
            float     _Pitch;                /* !< The pitch of the camera (rotation on the X axis) */
            float     _Yaw;                  /* !< The yaw of the camera (rotation on the Y axis) */
            float     _ViewportWidth;        /* !< The viewport width */
            float     _ViewportHeight;       /* !< The viewport height */
    };
};

#endif /* !EDITORCAMERA_HPP_ */
