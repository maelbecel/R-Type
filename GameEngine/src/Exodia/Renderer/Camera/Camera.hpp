/*
** EPITECH PROJECT, 2023
** ExodiaGameEngine
** File description:
** Camera
*/

#ifndef CAMERA_HPP_
    #define CAMERA_HPP_

    // External includes
    #include <glm/glm.hpp>

namespace Exodia {

    class Camera {

        //////////////////////////////
        // Constructor & Destructor //
        //////////////////////////////
        public:

            Camera(const glm::mat4 &projection = glm::mat4(1.0f));
            virtual ~Camera() = default;

        ///////////////////////
        // Getters & Setters //
        ///////////////////////
        public:

            const glm::mat4 &GetProjection() const;

        ////////////////
        // Attributes //
        ////////////////
        protected:
            glm::mat4 _Projection; /* !< The projection matrix of the camera */
    };
};

#endif /* !CAMERA_HPP_ */
