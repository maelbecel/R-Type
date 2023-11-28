/*
** EPITECH PROJECT, 2023
** ExodiaGameEngine
** File description:
** OrthographicCamera
*/

#ifndef ORTHOGRAPHICCAMERA_HPP_
    #define ORTHOGRAPHICCAMERA_HPP_

    // Extern includes
    #include <glm/glm.hpp>

namespace Exodia {

    /**
     * @brief This class represents an orthographic camera for 2D rendering.
     */
    class OrthographicCamera {

        //////////////////////////////
        // Constructor & Destructor //
        //////////////////////////////
        public:

            /**
             * @brief Construct an OrthographicCamera object with specified bounds.
             * Call this constructor to create an orthographic camera with the specified projection bounds.
             *
             * @param left   (Type: Float) The left coordinate of the projection bounds.
             * @param right  (Type: Float) The right coordinate of the projection bounds.
             * @param bottom (Type: Float) The bottom coordinate of the projection bounds.
             * @param top    (Type: Float) The top coordinate of the projection bounds.
             */
            OrthographicCamera(float left, float right, float bottom, float top);

            /**
             * @brief Destroy the OrthographicCamera object.
             */
            ~OrthographicCamera() = default;

        /////////////
        // Methods //
        /////////////
        private:

            /**
             * @brief Recalculate the view matrix based on position and rotation.
             * Call this method to update the view matrix based on the camera's position and rotation.
             */
            void RecalculateViewMatrix();

        ///////////////////////
        // Getters & Setters //
        ///////////////////////
        public:

            /**
             * @brief Get the camera position.
             * Call this method to retrieve the position of the camera.
             *
             * @return (Type: const glm::vec3 &) The camera position.
             */
            const glm::vec3 &GetPosition() const;

            /**
             * @brief Get the projection matrix.
             * Call this method to retrieve the projection matrix of the camera.
             *
             * @return (Type: const glm::mat4 &) The projection matrix.
             */
            const glm::mat4 &GetProjectionMatrix() const;

            /**
             * @brief Get the view matrix.
             * Call this method to retrieve the view matrix of the camera.
             *
             * @return (Type: const glm::mat4 &) The view matrix.
             */
            const glm::mat4 &GetViewMatrix() const;

            /**
             * @brief Get the view projection matrix.
             * Call this method to retrieve the combined view projection matrix of the camera.
             *
             * @return (Type: const glm::mat4 &) The view projection matrix.
             */
            const glm::mat4 &GetViewProjectionMatrix() const;

            /**
             * @brief Get the camera rotation.
             * Call this method to retrieve the rotation angle of the camera.
             *
             * @return (Type: Float) The camera rotation angle.
             */
            float GetRotation() const;

            /**
             * @brief Set the camera position.
             * Call this method to set the position of the camera and recalculate the view matrix.
             *
             * @param position (Type: const glm::vec3 &) The new position for the camera.
             */
            void SetPosition(const glm::vec3 &position);

            /**
             * @brief Set the camera rotation.
             * Call this method to set the rotation angle of the camera and recalculate the view matrix.
             *
             * @param rotation (Type: Float) The new rotation angle for the camera.
             */
            void SetRotation(float rotation);

            /**
             * @brief Set the projection matrix.
             * Call this method to set the projection matrix with specified bounds and recalculate the view projection matrix.
             *
             * @param left   (Type: Float) The left coordinate of the projection bounds.
             * @param right  (Type: Float) The right coordinate of the projection bounds.
             * @param bottom (Type: Float) The bottom coordinate of the projection bounds.
             * @param top    (Type: Float) The top coordinate of the projection bounds.
             */
            void SetProjection(float left, float right, float bottom, float top);

        ////////////////
        // Attributes //
        ////////////////
        private:
            glm::mat4 _ProjectionMatrix;     /*!< The projection matrix of the OrthographicCamera object */
            glm::mat4 _ViewMatrix;           /*!< The view matrix of the OrthographicCamera object */
            glm::mat4 _ViewProjectionMatrix; /*!< The view projection matrix of the OrthographicCamera object */
            glm::vec3 _Position;             /*!< The position of the OrthographicCamera object */
            float     _Rotation;             /*!< The rotation of the OrthographicCamera object */
    };
};

#endif /* !ORTHOGRAPHICCAMERA_HPP_ */
