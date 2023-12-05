/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** CollisionDetection2DSystem
*/

// Exodia ECS System includes
#include "CollisionDetection2DSystem.hpp"

// Exodia ECS Events includes
#include "Events/Events.hpp"

// Exodia Debug includes
#include "Debug/Profiling.hpp"

// Exodia GLM includes
#include <glm/glm.hpp>
#include <glm/gtx/norm.hpp>

namespace Exodia {

    /////////////
    // Methods //
    /////////////

    void CollisionDetection2DSystem::Update(World *world, Timestep ts)
    {
        EXODIA_PROFILE_FUNCTION();

        {
            EXODIA_PROFILE_SCOPE("CollisionDetection2DSystem::Update::BoxCollider2D");

            world->ForEach<BoxCollider2DComponent, TransformComponent>([&](Entity *entityA, ComponentHandle<BoxCollider2DComponent> colliderA, ComponentHandle<TransformComponent> transformA) {
                world->ForEach<BoxCollider2DComponent, TransformComponent>([&](Entity *entityB, ComponentHandle<BoxCollider2DComponent> colliderB, ComponentHandle<TransformComponent> transformB) {
                    if (entityA != entityB && CheckCollision(colliderA, transformA, colliderB, transformB)) {
                        EmitCollisionEvent(entityA, entityB);
                    }
                });

                world->ForEach<CircleCollider2DComponent, TransformComponent>([&](Entity *entityB, ComponentHandle<CircleCollider2DComponent> colliderB, ComponentHandle<TransformComponent> transformB) {
                    if (CheckCollision(colliderA, transformA, colliderB, transformB))
                        EmitCollisionEvent(entityA, entityB);
                });
            });
        }

        {
            EXODIA_PROFILE_SCOPE("CollisionDetection2DSystem::Update::CircleCollider2D");

            world->ForEach<CircleCollider2DComponent, TransformComponent>([&](Entity *entityA, ComponentHandle<CircleCollider2DComponent> colliderA, ComponentHandle<TransformComponent> transformA) {
                world->ForEach<CircleCollider2DComponent, TransformComponent>([&](Entity *entityB, ComponentHandle<CircleCollider2DComponent> colliderB, ComponentHandle<TransformComponent> transformB) {
                    if (entityA != entityB && CheckCollision(colliderA, transformA, colliderB, transformB))
                        EmitCollisionEvent(entityA, entityB);
                });
            });
        }
    }

    bool CollisionDetection2DSystem::CheckCollision(ComponentHandle<BoxCollider2DComponent> collider1, ComponentHandle<TransformComponent> transform1, ComponentHandle<BoxCollider2DComponent> collider2, ComponentHandle<TransformComponent> transform2)
    {
        auto &boxTransform1 = transform1.Get();
        auto &boxCollider1 = collider1.Get();
        auto &boxTransform2 = transform2.Get();
        auto &boxCollider2 = collider2.Get();

        uint32_t colliderMask1 = boxCollider1.ColliderMask;
        uint32_t colliderMask2 = boxCollider2.ColliderMask;

        if ((colliderMask1 & colliderMask2) == 0)
            return false;

        // Calculate transformed bounding boxes for both colliders based on their transformations
        BoundingBox transformedBox1 = CalculateTransformedBoundingBox(boxCollider1, boxTransform1);
        BoundingBox transformedBox2 = CalculateTransformedBoundingBox(boxCollider2, boxTransform2);

        // Check for intersection between the transformed bounding boxes
        bool collisionDetected = IntersectBoundingBoxes(transformedBox1, transformedBox2);
        return collisionDetected;
    }

    bool CollisionDetection2DSystem::CheckCollision(ComponentHandle<BoxCollider2DComponent> collider1, ComponentHandle<TransformComponent> transform1, ComponentHandle<CircleCollider2DComponent> collider2, ComponentHandle<TransformComponent> transform2)
    {
        auto &boxTransform    = transform1.Get();
        auto &boxCollider     = collider1.Get();
        auto &circleTransform = transform2.Get();
        auto &circleCollider  = collider2.Get();

        uint32_t colliderMask1 = boxCollider.ColliderMask;
        uint32_t colliderMask2 = circleCollider.ColliderMask;

        if ((colliderMask1 & colliderMask2) == 0)
            return false;

        //TODO: Enhance this function
        glm::vec2 boxSize       = boxCollider.Size;
        glm::vec2 boxPosition    = glm::vec2(boxTransform.Translation.x, boxTransform.Translation.y);
        glm::vec3 boxRotation    = boxTransform.Rotation;
        glm::vec2 circlePosition = glm::vec2(circleTransform.Translation.x, circleTransform.Translation.y);
        float circleRadius       = circleCollider.Radius;

        glm::vec2 circleLocalPos = circlePosition - boxPosition;

        float cosTheta = cos(-boxRotation.z);
        float sinTheta = sin(-boxRotation.z);

        glm::vec2 scaledCircleLocalPos = circleLocalPos;
        scaledCircleLocalPos.x /= boxTransform.Scale.x;
        scaledCircleLocalPos.y /= boxTransform.Scale.y;

        glm::vec2 rotatedCircleLocalPos;
        rotatedCircleLocalPos.x = scaledCircleLocalPos.x * cosTheta - scaledCircleLocalPos.y * sinTheta;
        rotatedCircleLocalPos.y = scaledCircleLocalPos.x * sinTheta + scaledCircleLocalPos.y * cosTheta;

        float closestX = glm::clamp(rotatedCircleLocalPos.x, -boxSize.x / 2.0f, boxSize.x / 2.0f);
        float closestY = glm::clamp(rotatedCircleLocalPos.y, -boxSize.y / 2.0f, boxSize.y / 2.0f);

        glm::vec2 closestPoint = glm::vec2(closestX, closestY);
        glm::vec2 distanceVec  = rotatedCircleLocalPos - closestPoint;
        float distance         = glm::length(distanceVec);

        return (distance <= circleRadius);
    }

    bool CollisionDetection2DSystem::CheckCollision(ComponentHandle<CircleCollider2DComponent> collider1, ComponentHandle<TransformComponent> transform1, ComponentHandle<CircleCollider2DComponent> collider2, ComponentHandle<TransformComponent> transform2)
    {
        auto &circleTransform1 = transform1.Get();
        auto &circleCollider1  = collider1.Get();
        auto &circleTransform2 = transform2.Get();
        auto &circleCollider2  = collider2.Get();

        uint32_t colliderMask1 = circleCollider1.ColliderMask;
        uint32_t colliderMask2 = circleCollider2.ColliderMask;

        if ((colliderMask1 & colliderMask2) == 0)
            return false;

        //TODO: Enhance this function

        // Extract necessary parameters for calculations
        glm::vec2 position1 = glm::vec2(circleTransform1.Translation.x, circleTransform1.Translation.y);
        float radius1 = circleCollider1.Radius;
        glm::vec2 position2 = glm::vec2(circleTransform2.Translation.x, circleTransform2.Translation.y);
        float radius2 = circleCollider2.Radius;

        // Calculate distance between centers of circles
        float distance = glm::distance(position1, position2);

        // Check for collision (circles intersect if the distance between centers is less than the sum of their radii)
        if (distance <= (radius1 + radius2)) {
            // Move collision handling
            float distanceToMove = (radius1 + radius2) - distance;

            float angle = atan2(position2.y - position1.y, position2.x - position1.x);

            position2.x += cos(angle) * distanceToMove;
            position2.y += sin(angle) * distanceToMove;

            // Update the transformed positions back to the components
            circleTransform2.Translation.x = position2.x;
            circleTransform2.Translation.y = position2.y;

            return true; // Collision detected
        }

        return false; // No collision
    }

    CollisionDetection2DSystem::BoundingBox CollisionDetection2DSystem::CalculateTransformedBoundingBox(const BoxCollider2DComponent &collider, const TransformComponent &transform)
    {
        // Get the size and offset from the collider
        glm::vec2 size = collider.Size;
        glm::vec2 offset = collider.Offset;

        // Transform the size according to the entity's scale
        size *= glm::vec2({ transform.Scale.x, transform.Scale.y });

        // Transform the offset according to the entity's rotation
        glm::vec2 rotatedOffset = glm::vec2({ transform.Rotation.x, transform.Rotation.y }) * offset;

        // Calculate the center of the box based on the translation and rotated offset
        glm::vec2 center = glm::vec2({ transform.Translation.x, transform.Translation.y }) + rotatedOffset;

        // Calculate the minimum and maximum points of the bounding box
        BoundingBox bbox;

        bbox.min = center - size;
        bbox.max = center + size;
        return bbox;
    }

    bool CollisionDetection2DSystem::IntersectBoundingBoxes(const BoundingBox &box1, const BoundingBox &box2)
    {
        // Check for intersection along each axis (x, y)
        bool collisionX = (box1.max.x >= box2.min.x) && (box1.min.x <= box2.max.x);
        bool collisionY = (box1.max.y >= box2.min.y) && (box1.min.y <= box2.max.y);

        // Check for intersection in all axes to determine if collision occurs
        return collisionX && collisionY;
    }

    void CollisionDetection2DSystem::EmitCollisionEvent(Entity *entityA, Entity *entityB)
    {
        Events::OnCollisionEntered event;

        event.EntityA = entityA;
        event.EntityB = entityB;

        entityA->GetWorld()->Emit<Events::OnCollisionEntered>(event);
    }
};
