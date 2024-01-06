/*
** EXODIA PROJECT, 2023
** TryAGame
** File description:
** Collider
*/

#ifndef COLLIDER_HPP_
    #define COLLIDER_HPP_

    #include <glm/glm.hpp>

static bool PointInTriangle(const glm::vec2 &position, glm::vec2 &pa, const glm::vec2 &pb, const glm::vec2 &pc)
{
    float s = pa.y * pc.x - pa.x * pc.y + (pc.y - pa.y) * position.x + (pa.x - pc.x) * position.y;
    float t = pa.x * pb.y - pa.y * pb.x + (pa.y - pb.y) * position.x + (pb.x - pa.x) * position.y;

    if ((s < 0) != (t < 0))
        return false;

    float A = -pb.y * pc.x + pa.y * (pc.x - pb.x) + pa.x * (pb.y - pc.y) + pb.x * pc.y;

    return A < 0 ? (s <= 0 && s + t >= A) : (s >= 0 && s + t <= A);
}


#endif /* !COLLIDER_HPP_ */
