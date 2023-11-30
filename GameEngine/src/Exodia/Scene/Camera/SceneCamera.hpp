/*
** EPITECH PROJECT, 2023
** ExodiaGameEngine
** File description:
** SceneCamera
*/

#ifndef SCENECAMERA_HPP_
    #define SCENECAMERA_HPP_

    // Exodia Renderer includes
    #include "Renderer/Camera/Camera.hpp"

namespace Exodia {

    class SceneCamera : public Camera {

        //////////////////
        // Enumerations //
        //////////////////
        public:

            enum class ProjectionType {
                Perspective,
                Orthographic
            };

        //////////////////////////////
        // Constructor & Destructor //
        //////////////////////////////
        public:

            SceneCamera();
            virtual ~SceneCamera() = default;

        /////////////
        // Methods //
        /////////////
        private:

            void RecalculateProjection();

        ///////////////////////
        // Getters & Setters //
        ///////////////////////
        public:

            void SetViewportSize(uint32_t width, uint32_t height);
            ProjectionType GetProjectionType() const;
            void SetProjectionType(ProjectionType type);

            // -- Orthographic -- //
                void SetOrthographic(float size, float nearClip, float farClip);
                float GetOrthographicSize() const;
                void SetOrthographicSize(float size);
                float GetOrthographicNearClip() const;
                void SetOrthographicNearClip(float nearClip);
                float GetOrthographicFarClip() const;
                void SetOrthographicFarClip(float farClip);

            // -- Perspective -- //
                void SetPersepective(float verticalFOV, float nearClip, float farClip);
                float GetPerspectiveVerticalFOV() const;
                void SetPerspectiveVerticalFOV(float fov);
                float GetPerspectiveNearClip() const;
                void SetPerspectiveNearClip(float nearClip);
                float GetPerspectiveFarClip() const;
                void SetPerspectiveFarClip(float farClip);

        ////////////////
        // Attributes //
        ////////////////
        private:
            ProjectionType _ProjectionType;   /* !< The projection type of the camera */
            float          _OrthographicSize; /* !< The orthographic size of the camera */
            float          _OrthographicNear; /* !< The orthographic near of the camera */
            float          _OrthographicFar;  /* !< The orthographic far of the camera */
            float          _PerspectiveFOV;   /* !< The perspective fov of the camera */
            float          _PerspectiveNear;  /* !< The perspective near of the camera */
            float          _PerspectiveFar;   /* !< The perspective far of the camera */
            float          _AspectRatio;      /* !< The aspect ratio of the camera */
    };
};

#endif /* !SCENECAMERA_HPP_ */
