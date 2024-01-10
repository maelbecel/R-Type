/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** CollisionSystem
*/

// Exodia ECS System includes
#include "CollisionSystem.hpp"

// Exodia ECS Events includes
#include "Events/Events.hpp"

// Exodia Debug includes
#include "Exodia-Debug.hpp"

// Exodia GLM includes
#include <glm/glm.hpp>
#include <glm/gtx/norm.hpp>

// External includes
#include <algorithm>

namespace Exodia {

    /////////////
    // Methods //
    /////////////

    void CollisionSystem::Update(World *world, Timestep ts) {
        EXODIA_PROFILE_FUNCTION();

        std::vector<std::pair<Entity *, Entity *>> collisions;

        {
            EXODIA_PROFILE_SCOPE("CollisionSystem::Update::BoxCollider2D");

            world->LockMutex();
            world->ForEach<BoxCollider2DComponent, TransformComponent>(
                [&](Entity *entityA, ComponentHandle<BoxCollider2DComponent> colliderA,
                    ComponentHandle<TransformComponent> transformA) {
                    world->ForEach<BoxCollider2DComponent, TransformComponent>(
                        [&](Entity *entityB, ComponentHandle<BoxCollider2DComponent> colliderB,
                            ComponentHandle<TransformComponent> transformB) {
                            if (std::find(collisions.begin(), collisions.end(), std::make_pair(entityB, entityA)) !=
                                collisions.end())
                                return;

                            if (entityA != entityB && CheckCollision(colliderA, transformA, colliderB, transformB))
                                collisions.push_back(std::make_pair(entityA, entityB));
                        });

                    world->ForEach<CircleCollider2DComponent, TransformComponent>(
                        [&](Entity *entityB, ComponentHandle<CircleCollider2DComponent> colliderB,
                            ComponentHandle<TransformComponent> transformB) {
                            if (std::find(collisions.begin(), collisions.end(), std::make_pair(entityB, entityA)) !=
                                collisions.end())
                                return;

                            if (CheckCollision(colliderA, transformA, colliderB, transformB))
                                collisions.push_back(std::make_pair(entityA, entityB));
                        });

                    world->ForEach<TriangleCollider2DComponent, TransformComponent>(
                        [&](Entity *entityB, ComponentHandle<TriangleCollider2DComponent> colliderB,
                            ComponentHandle<TransformComponent> transformB) {
                            if (std::find(collisions.begin(), collisions.end(), std::make_pair(entityB, entityA)) !=
                                collisions.end())
                                return;

                            if (CheckCollision(colliderA, transformA, colliderB, transformB))
                                collisions.push_back(std::make_pair(entityA, entityB));
                        });
                });
            world->UnlockMutex();
        }

        {
            EXODIA_PROFILE_SCOPE("CollisionSystem::Update::CircleCollider2D");

            world->LockMutex();
            world->ForEach<CircleCollider2DComponent, TransformComponent>(
                [&](Entity *entityA, ComponentHandle<CircleCollider2DComponent> colliderA,
                    ComponentHandle<TransformComponent> transformA) {
                    world->ForEach<CircleCollider2DComponent, TransformComponent>(
                        [&](Entity *entityB, ComponentHandle<CircleCollider2DComponent> colliderB,
                            ComponentHandle<TransformComponent> transformB) {
                            if (std::find(collisions.begin(), collisions.end(), std::make_pair(entityB, entityA)) !=
                                collisions.end())
                                return;

                            if (entityA != entityB && CheckCollision(colliderA, transformA, colliderB, transformB))
                                collisions.push_back(std::make_pair(entityA, entityB));
                        });
                });

            world->ForEach<BoxCollider2DComponent, TransformComponent>(
                [&](Entity *entityA, ComponentHandle<BoxCollider2DComponent> colliderA,
                    ComponentHandle<TransformComponent> transformA) {
                    world->ForEach<CircleCollider2DComponent, TransformComponent>(
                        [&](Entity *entityB, ComponentHandle<CircleCollider2DComponent> colliderB,
                            ComponentHandle<TransformComponent> transformB) {
                            if (std::find(collisions.begin(), collisions.end(), std::make_pair(entityB, entityA)) !=
                                collisions.end())
                                return;

                            if (CheckCollision(colliderA, transformA, colliderB, transformB))
                                collisions.push_back(std::make_pair(entityA, entityB));
                        });
                });

            world->ForEach<TriangleCollider2DComponent, TransformComponent>(
                [&](Entity *entityA, ComponentHandle<TriangleCollider2DComponent> colliderA,
                    ComponentHandle<TransformComponent> transformA) {
                    world->ForEach<CircleCollider2DComponent, TransformComponent>(
                        [&](Entity *entityB, ComponentHandle<CircleCollider2DComponent> colliderB,
                            ComponentHandle<TransformComponent> transformB) {
                            if (std::find(collisions.begin(), collisions.end(), std::make_pair(entityB, entityA)) !=
                                collisions.end())
                                return;

                            if (CheckCollision(colliderB, transformB, colliderA, transformA))
                                collisions.push_back(std::make_pair(entityA, entityB));
                        });
                });
            world->UnlockMutex();
        }

        { EXODIA_PROFILE_SCOPE("CollisionSystem::Update::TriangleCollider2D"); }

        CompareCollisions(collisions);
    }

    void CollisionSystem::Receive(World *world, const Events::OnCollisionEntered &event) {
        EXODIA_PROFILE_FUNCTION();

        Entity *entityA = event.EntityA;
        Entity *entityB = event.EntityB;

        auto scriptA = entityA->GetComponent<ScriptComponent>();
        auto scriptB = entityB->GetComponent<ScriptComponent>();

        if (scriptA) {
            auto instance = scriptA.Get().Instance;

            if (instance)
                instance->OnCollisionEnter(entityB);
        }

        if (scriptB) {
            auto instance = scriptB.Get().Instance;

            if (instance)
                instance->OnCollisionEnter(entityA);
        }
    }

    bool CollisionSystem::CheckCollision(ComponentHandle<BoxCollider2DComponent> collider1,
                                         ComponentHandle<TransformComponent> transform1,
                                         ComponentHandle<BoxCollider2DComponent> collider2,
                                         ComponentHandle<TransformComponent> transform2) {
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

    bool CollisionSystem::CheckCollision(ComponentHandle<BoxCollider2DComponent> collider1,
                                         ComponentHandle<TransformComponent> transform1,
                                         ComponentHandle<CircleCollider2DComponent> collider2,
                                         ComponentHandle<TransformComponent> transform2) {
        auto &boxTransform = transform1.Get();
        auto &boxCollider = collider1.Get();
        auto &circleTransform = transform2.Get();
        auto &circleCollider = collider2.Get();

        uint32_t colliderMask1 = boxCollider.ColliderMask;
        uint32_t colliderMask2 = circleCollider.ColliderMask;

        if ((colliderMask1 & colliderMask2) == 0)
            return false;

        // TODO: Enhance this function
        glm::vec2 boxSize = boxCollider.Size;
        glm::vec2 boxPosition = glm::vec2(boxTransform.Translation.x, boxTransform.Translation.y);
        glm::vec3 boxRotation = boxTransform.Rotation;
        glm::vec2 circlePosition = glm::vec2(circleTransform.Translation.x, circleTransform.Translation.y);
        float circleRadius = circleCollider.Radius;

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
        glm::vec2 distanceVec = rotatedCircleLocalPos - closestPoint;
        float distance = glm::length(distanceVec);

        return (distance <= circleRadius);
    }

    bool CollisionSystem::CheckCollision(ComponentHandle<CircleCollider2DComponent> collider1,
                                         ComponentHandle<TransformComponent> transform1,
                                         ComponentHandle<CircleCollider2DComponent> collider2,
                                         ComponentHandle<TransformComponent> transform2) {
        auto &circleTransform1 = transform1.Get();
        auto &circleCollider1 = collider1.Get();
        auto &circleTransform2 = transform2.Get();
        auto &circleCollider2 = collider2.Get();

        uint32_t colliderMask1 = circleCollider1.ColliderMask;
        uint32_t colliderMask2 = circleCollider2.ColliderMask;

        if ((colliderMask1 & colliderMask2) == 0)
            return false;

        // TODO: Enhance this function

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

    bool CollisionSystem::CheckCollision(ComponentHandle<CircleCollider2DComponent> circleCollider,
                                         ComponentHandle<TransformComponent> circleTransform,
                                         ComponentHandle<TriangleCollider2DComponent> triangleCollider,
                                         ComponentHandle<TransformComponent> triangleTransform) {
        // Get the components
        auto &circle = circleCollider.Get();
        auto &circlePos = circleTransform.Get();
        auto &triangle = triangleCollider.Get();
        auto &trianglePos = triangleTransform.Get();

        // Check if the masks collide
        uint32_t colliderMask1 = circle.ColliderMask;
        uint32_t colliderMask2 = triangle.ColliderMask;

        if ((colliderMask1 & colliderMask2) == 0)
            return false;

        // Check for collision using Separating Axis Theorem (SAT)
        // This is a simplified version and assumes that the triangle and circle are defined in a 2D space
        for (int i = 0; i < 3; i++) {
            // Get the normal of the current edge
            glm::vec2 edge = triangle.edges[i];
            glm::vec2 normal(edge.y, -edge.x);

            // Project the circle onto the normal
            float circleProjection = glm::dot(normal, glm::vec2(circlePos.Translation.x, circlePos.Translation.y));

            // Apply transformation to the triangle vertices
            std::array<glm::vec2, 3> transformedVertices;
            for (int i = 0; i < 3; i++) {
                transformedVertices[i] = (glm::vec2){trianglePos.Scale.x, trianglePos.Scale.y} * triangle.vertices[i] +
                                         (glm::vec2){trianglePos.Translation.x, trianglePos.Translation.y};
            }

            // Project the transformed vertices of the triangle onto the normal
            float minTriangleProjection = glm::dot(normal, transformedVertices[0]);
            float maxTriangleProjection = minTriangleProjection;
            for (int j = 1; j < 3; j++) {
                float projection = glm::dot(normal, transformedVertices[j]);
                minTriangleProjection = std::min(minTriangleProjection, projection);
                maxTriangleProjection = std::max(maxTriangleProjection, projection);
            }

            // Check if projections overlap
            if (circleProjection + circle.Radius < minTriangleProjection ||
                circleProjection - circle.Radius > maxTriangleProjection) {
                // The projections do not overlap, so no collision
                return false;
            }
        }

        // If we get here, all projections overlapped so there is a collision
        return true;
    }

    bool CollisionSystem::CheckCollision(ComponentHandle<TriangleCollider2DComponent> triangleCollider1,
                                         ComponentHandle<TransformComponent> triangleTransform1,
                                         ComponentHandle<TriangleCollider2DComponent> triangleCollider2,
                                         ComponentHandle<TransformComponent> triangleTransform2) {
        // Get the components
        auto &triangle1 = triangleCollider1.Get();
        auto &trianglePos1 = triangleTransform1.Get();
        auto &triangle2 = triangleCollider2.Get();
        auto &trianglePos2 = triangleTransform2.Get();

        // Check if the masks collide
        uint32_t colliderMask1 = triangle1.ColliderMask;
        uint32_t colliderMask2 = triangle2.ColliderMask;

        if ((colliderMask1 & colliderMask2) == 0)
            return false;

        // Check for collision using Separating Axis Theorem (SAT)
        // This is a simplified version and assumes that the triangles are defined in a 2D space
        for (int i = 0; i < 3; i++) {
            // Get the normal of the current edge
            glm::vec2 edge = triangle1.edges[i];
            glm::vec2 normal(edge.y, -edge.x);

            // Apply transformation to the first triangle vertices
            std::array<glm::vec2, 3> transformedVertices1;
            for (int i = 0; i < 3; i++) {
                transformedVertices1[i] =
                    (glm::vec2){trianglePos1.Scale.x, trianglePos1.Scale.y} * triangle1.vertices[i] +
                    (glm::vec2){trianglePos1.Translation.x, trianglePos1.Translation.y};
            }

            // Project the transformed vertices of the first triangle onto the normal
            float minTriangleProjection1 = glm::dot(normal, transformedVertices1[0]);
            float maxTriangleProjection1 = minTriangleProjection1;
            for (int j = 1; j < 3; j++) {
                float projection = glm::dot(normal, transformedVertices1[j]);
                minTriangleProjection1 = std::min(minTriangleProjection1, projection);
                maxTriangleProjection1 = std::max(maxTriangleProjection1, projection);
            }

            // Apply transformation to the second triangle vertices
            std::array<glm::vec2, 3> transformedVertices2;
            for (int i = 0; i < 3; i++) {
                transformedVertices2[i] =
                    (glm::vec2){trianglePos2.Scale.x, trianglePos2.Scale.y} * triangle2.vertices[i] +
                    (glm::vec2){trianglePos2.Translation.x, trianglePos2.Translation.y};
            }

            // Project the transformed vertices of the second triangle onto the normal
            float minTriangleProjection2 = glm::dot(normal, transformedVertices2[0]);
            float maxTriangleProjection2 = minTriangleProjection2;
            for (int j = 1; j < 3; j++) {
                float projection = glm::dot(normal, transformedVertices2[j]);
                minTriangleProjection2 = std::min(minTriangleProjection2, projection);
                maxTriangleProjection2 = std::max(maxTriangleProjection2, projection);
            }

            // Check if projections overlap
            if (maxTriangleProjection1 < minTriangleProjection2 || maxTriangleProjection2 < minTriangleProjection1) {
                // The projections do not overlap, so no collision
                return false;
            }
        }

        // If we get here, all projections overlapped so there is a collision
        return true;
    }

    bool CollisionSystem::CheckCollision(ComponentHandle<BoxCollider2DComponent> boxCollider,
                                         ComponentHandle<TransformComponent> boxTransform,
                                         ComponentHandle<TriangleCollider2DComponent> triangleCollider,
                                         ComponentHandle<TransformComponent> triangleTransform) {
        // Get the components
        auto &box = boxCollider.Get();
        auto &boxPos = boxTransform.Get();
        auto &triangle = triangleCollider.Get();
        auto &trianglePos = triangleTransform.Get();

        // Check if the masks collide
        uint32_t colliderMask1 = box.ColliderMask;
        uint32_t colliderMask2 = triangle.ColliderMask;

        if ((colliderMask1 & colliderMask2) == 0)
            return false;

        // Calculate the vertices of the box
        std::array<glm::vec2, 4> boxVertices;
        boxVertices[0] = glm::vec2(boxPos.Translation.x - boxPos.Scale.x / 2,
                                   boxPos.Translation.y - boxPos.Scale.y / 2); // Bottom-left
        boxVertices[1] = glm::vec2(boxPos.Translation.x + boxPos.Scale.x / 2,
                                   boxPos.Translation.y - boxPos.Scale.y / 2); // Bottom-right
        boxVertices[2] = glm::vec2(boxPos.Translation.x + boxPos.Scale.x / 2,
                                   boxPos.Translation.y + boxPos.Scale.y / 2); // Top-right
        boxVertices[3] =
            glm::vec2(boxPos.Translation.x - boxPos.Scale.x / 2, boxPos.Translation.y + boxPos.Scale.y / 2); // Top-left

        // Check for collision using Separating Axis Theorem (SAT)
        // This is a simplified version and assumes that the box and triangle are defined in a 2D space
        for (int i = 0; i < 3; i++) {
            // Get the normal of the current edge
            glm::vec2 edge = triangle.edges[i];
            glm::vec2 normal(edge.y, -edge.x);

            // Project the vertices of the box onto the normal
            float minBoxProjection = glm::dot(normal, boxVertices[0]);
            float maxBoxProjection = minBoxProjection;
            for (int j = 1; j < 4; j++) {
                float projection = glm::dot(normal, boxVertices[j]);
                minBoxProjection = std::min(minBoxProjection, projection);
                maxBoxProjection = std::max(maxBoxProjection, projection);
            }

            std::array<glm::vec2, 3> transformedVertices;
            for (int i = 0; i < 3; i++) {
                transformedVertices[i] = (glm::vec2){trianglePos.Scale.x, trianglePos.Scale.y} * triangle.vertices[i] +
                                         (glm::vec2){trianglePos.Translation.x, trianglePos.Translation.y};
            }

            // Project the vertices of the triangle onto the normal
            float minTriangleProjection = glm::dot(normal, transformedVertices[0]);
            float maxTriangleProjection = minTriangleProjection;
            for (int j = 1; j < 3; j++) {
                float projection = glm::dot(normal, transformedVertices[j]);
                minTriangleProjection = std::min(minTriangleProjection, projection);
                maxTriangleProjection = std::max(maxTriangleProjection, projection);
            }

            // Check if projections overlap
            if (maxBoxProjection < minTriangleProjection || maxTriangleProjection < minBoxProjection) {
                // The projections do not overlap, so no collision
                return false;
            }
        }

        // If we get here, all projections overlapped so there is a collision
        return true;
    }

    CollisionSystem::BoundingBox
    CollisionSystem::CalculateTransformedBoundingBox(const BoxCollider2DComponent &collider,
                                                     const TransformComponent &transform) {
        // Get the size and offset from the collider
        glm::vec2 size = collider.Size;
        glm::vec2 offset = collider.Offset;

        // Transform the size according to the entity's scale
        size *= glm::vec2({transform.Scale.x, transform.Scale.y});

        // Transform the offset according to the entity's rotation
        glm::vec2 rotatedOffset = glm::vec2({transform.Rotation.x, transform.Rotation.y}) * offset;

        // Calculate the center of the box based on the translation and rotated offset
        glm::vec2 center = glm::vec2({transform.Translation.x, transform.Translation.y}) + rotatedOffset;

        // Calculate the minimum and maximum points of the bounding box
        BoundingBox bbox;

        bbox.min = center - size;
        bbox.max = center + size;
        return bbox;
    }

    bool CollisionSystem::IntersectBoundingBoxes(const BoundingBox &box1, const BoundingBox &box2) {
        // Check for intersection along each axis (x, y)
        bool collisionX = (box1.max.x >= box2.min.x) && (box1.min.x <= box2.max.x);
        bool collisionY = (box1.max.y >= box2.min.y) && (box1.min.y <= box2.max.y);

        // Check for intersection in all axes to determine if collision occurs
        return collisionX && collisionY;
    }

    void CollisionSystem::EmitOnCollisionEnterEvent(Entity *entityA, Entity *entityB) {
        Events::OnCollisionEntered event;

        event.EntityA = entityA;
        event.EntityB = entityB;

        entityA->GetWorld()->Emit<Events::OnCollisionEntered>(event);
    }

    void CollisionSystem::CompareCollisions(const std::vector<std::pair<Entity *, Entity *>> &collisions) {
        if (collisions.empty()) {
            _LastCollisions.clear();
            return;
        }

        if (_LastCollisions.empty()) {
            for (auto &collision : collisions)
                EmitOnCollisionEnterEvent(collision.first, collision.second);
        } else {
            for (auto &collision : _LastCollisions) {
                bool found = false;

                for (auto &newCollision : collisions) {
                    if ((collision.first == newCollision.first && collision.second == newCollision.second) ||
                        (collision.first == newCollision.second && collision.second == newCollision.first)) {
                        found = true;
                        break;
                    }
                }

                if (found == false) {
                    EXODIA_CORE_INFO("Collision between {0} and {1}",
                                     collision.first->GetComponent<TagComponent>().Get().Tag,
                                     collision.second->GetComponent<TagComponent>().Get().Tag);
                    EmitOnCollisionEnterEvent(collision.first, collision.second);
                }
            }
        }

        _LastCollisions = collisions;
    }
}; // namespace Exodia
