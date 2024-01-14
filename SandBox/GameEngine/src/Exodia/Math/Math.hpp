/*
** EXODIA PROJECT, 2023
** ExodiaGameEngine
** File description:
** Math
*/

#ifndef MATH_HPP_
#define MATH_HPP_

// External includes
#include <glm/glm.hpp>

namespace Exodia {
    namespace Math {

        bool DecomposeTransform(const glm::mat4 &transform, glm::vec3 &translation, glm::vec3 &rotation,
                                glm::vec3 &scale);
    };
}; // namespace Exodia

#endif /* !MATH_HPP_ */
