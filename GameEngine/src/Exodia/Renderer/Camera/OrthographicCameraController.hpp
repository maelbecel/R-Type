/*
** EPITECH PROJECT, 2023
** ExodiaGameEngine
** File description:
** OrthographicCameraController
*/

#ifndef ORTHOGRAPHICCAMERACONTROLLER_HPP_
#define ORTHOGRAPHICCAMERACONTROLLER_HPP_

// Exodia Renderer
#include "Renderer/Camera/OrthographicCamera.hpp"

// Exodia Core
#include "Core/Time/Timestep.hpp"

// Exodia Events
#include "Events/ApplicationEvent.hpp"
#include "Events/MouseEvent.hpp"

namespace Exodia
{

    /**
     * @brief This structure represents the bounds of an orthographic camera's projection.
     */
    struct OrthographicCameraBounds
    {
        float Left;   /*!< The left of the Orthographic Camera */
        float Right;  /*!< The right of the Orthographic Camera */
        float Bottom; /*!< The bottom of the Orthographic Camera */
        float Top;    /*!< The top of the Orthographic Camera */

        /**
         * @brief Get the width of the camera's projection bounds.
         * Call this method to calculate and retrieve the width of the camera's projection bounds.
         *
         * @return (Type: Float) The width of the camera's projection bounds.
         */
        float GetWidth() { return Right - Left; }

        /**
         * @brief Get the height of the camera's projection bounds.
         * Call this method to calculate and retrieve the height of the camera's projection bounds.
         *
         * @return (Type: Float) The height of the camera's projection bounds.
         */
        float GetHeight() { return Top - Bottom; }
    };

    /**
     * @brief This class represents a controller for an orthographic camera.
     * It provides methods to control the camera's position, rotation, zoom level, and aspect ratio.
     */
    class OrthographicCameraController
    {

        //////////////////////////////
        // Constructor & Destructor //
        //////////////////////////////
      public:
        /**
         * @brief Construct an OrthographicCameraController
         *
         * @param aspectRatio (Type: Float) The aspect ratio of the camera's projection
         * @param rotation    (Type: Bool)  If true, enables camera rotation (default is false)
         */
        OrthographicCameraController( float aspectRatio, bool rotation = false );

        /**
         * @brief Destructor for OrthographicCameraController
         */
        ~OrthographicCameraController() = default;

        /////////////
        // Methods //
        /////////////
      public:
        /**
         * @brief Update the camera's state based on elapsed time.
         *
         * @param ts (Type: Timestep) The timestep since the last frame
         */
        void OnUpdate( Timestep ts );

        /**
         * @brief Handle events related to the camera
         *
         * @param event (Type: Event) The event to handle
         */
        void OnEvent( Event &event );

        /**
         * @brief Resize the bounds of the camera's projection.
         *
         * @param width  (Type: Float) The new width of the camera's projection
         * @param height (Type: Float) The new height of the camera's projection
         */
        void OnResize( float width, float height );

      private:
        /**
         * @brief Calculate the view matrix of the camera depend on its position, rotation and the zoom level.
         * Call this method to calculate the view matrix of the camera.
         */
        void CalculateView();

        /**
         * @brief Handle the MouseScrolledEvent
         * @param event (Type: MouseScrolledEvent) The MouseScrolledEvent to handle
         * @return      (Type: Bool)               True if the event was handled, false otherwise
         */
        bool OnMouseScrolled( MouseScrolledEvent &event );

        /**
         * @brief Handle the WindowResizeEvent
         * @param event (Type: WindowResizeEvent) The WindowResizeEvent to handle
         * @return      (Type: Bool)              True if the event was handled, false otherwise
         */
        bool OnWindowResized( WindowResizeEvent &event );

        ///////////////////////
        // Getters & Setters //
        ///////////////////////
      public:
        /**
         * @brief Get the OrthographicCamera controlled by this controller
         *
         * @return (Type: OrthographicCamera &) Reference to the OrthographicCamera controlled by this controller
         */
        OrthographicCamera &GetCamera();

        /**
         * @brief Get the const OrthographicCamera controlled by this controller
         *
         * @return (Type: const OrthographicCamera) Const reference to the OrthographicCamera controlled by this
         * controller
         */
        const OrthographicCamera &GetCamera() const;

        /**
         * @brief Set the zoom level of the camera
         *
         * @param level (Type: Float) The zoom level to set
         */
        void SetZoomLevel( float level );

        /**
         * @brief Get the zoom level of the camera
         *
         * @return (Type: Float) The current zoom level of the camera
         */
        float GetZoomLevel() const;

        /**
         * @brief Get the bounds of the camera's projection.
         *
         * @return (Type: const OrthographicCameraBounds) Const reference to the bounds of the camera's projection
         */
        const OrthographicCameraBounds &GetBounds() const;

        ////////////////
        // Attributes //
        ////////////////
      private:
        float                    _ZoomLevel;              /*!< The zoom level of the Orthographic Camera */
        OrthographicCameraBounds _Bounds;                 /*!< The bounds of the Orthographic Camera */
        OrthographicCamera       _Camera;                 /*!< The Orthographic Camera to control */
        float                    _AspectRatio;            /*!< The aspect ratio of the Orthographic Camera */
        bool                     _Rotation;               /*!< If the Orthographic Camera is rotating */
        glm::vec3                _CameraPos;              /*!< The position of the Orthographic Camera */
        float                    _CameraRotation;         /*!< The rotation of the Orthographic Camera */
        float                    _CameraTranslationSpeed; /*!< The translation speed of the Orthographic Camera */
        float                    _CameraRotationSpeed;    /*!< The rotation speed of the Orthographic Camera */
    };
}; // namespace Exodia

#endif /* !ORTHOGRAPHICCAMERACONTROLLER_HPP_ */
