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

namespace Exodia {

    /////////////
    // Methods //
    /////////////

    void CollisionDetection2DSystem::Update(World *world, Timestep ts)
    {
        world->ForEach<BoxCollider2DComponent, TransformComponent>([&](Entity *entityA, ComponentHandle<BoxCollider2DComponent> colliderA, ComponentHandle<TransformComponent> transformA) {
            world->ForEach<BoxCollider2DComponent, TransformComponent>([&](Entity *entityB, ComponentHandle<BoxCollider2DComponent> colliderB, ComponentHandle<TransformComponent> transformB) {
                if (entityA != entityB && CheckCollision(colliderA, transformA, colliderB, transformB))
                    EmitCollisionEvent(entityA, entityB);
            });

            world->ForEach<CircleCollider2DComponent, TransformComponent>([&](Entity *entityB, ComponentHandle<CircleCollider2DComponent> colliderB, ComponentHandle<TransformComponent> transformB) {
                if (CheckCollision(colliderA, transformA, colliderB, transformB))
                    EmitCollisionEvent(entityA, entityB);
            });
        });

        world->ForEach<CircleCollider2DComponent, TransformComponent>([&](Entity *entityA, ComponentHandle<CircleCollider2DComponent> colliderA, ComponentHandle<TransformComponent> transformA) {
            world->ForEach<CircleCollider2DComponent, TransformComponent>([&](Entity *entityB, ComponentHandle<CircleCollider2DComponent> colliderB, ComponentHandle<TransformComponent> transformB) {
                if (entityA != entityB && CheckCollision(colliderA, transformA, colliderB, transformB))
                    EmitCollisionEvent(entityA, entityB);
            });
        });
    }

    bool CollisionDetection2DSystem::CheckCollision(ComponentHandle<BoxCollider2DComponent> collider1, ComponentHandle<TransformComponent> transform1, ComponentHandle<BoxCollider2DComponent> collider2, ComponentHandle<TransformComponent> transform2)
    {
        auto &boxTransform1 = transform1.Get();
        auto &boxCollider1  = collider1.Get();
        auto &boxTransform2 = transform2.Get();
        auto &boxCollider2  = collider2.Get();

        uint32_t colliderMask1 = boxCollider1.ColliderMask;
        uint32_t colliderMask2 = boxCollider2.ColliderMask;

        if ((colliderMask1 & colliderMask2) == 0)
            return false;

        glm::vec2 position1 = glm::vec2(boxTransform1.Translation.x, boxTransform1.Translation.y);
        glm::vec2 position2 = glm::vec2(boxTransform2.Translation.x, boxTransform2.Translation.y);
        glm::vec2 size1     = boxCollider1.Size;
        glm::vec2 size2     = boxCollider2.Size;

        glm::vec2 min1 = position1 - size1 / 2.0f;
        glm::vec2 max1 = position1 + size1 / 2.0f;

        glm::vec2 min2 = position2 - size2 / 2.0f;
        glm::vec2 max2 = position2 + size2 / 2.0f;

        bool collisionX = min1.x <= max2.x && max1.x >= min2.x;
        bool collisionY = min1.y <= max2.y && max1.y >= min2.y;

        return collisionX && collisionY;
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

        glm::vec2 boxPosition    = glm::vec2(boxTransform.Translation.x, boxTransform.Translation.y);
        glm::vec2 boxSize        = boxCollider.Size;
        glm::vec2 circlePosition = glm::vec2(circleTransform.Translation.x, circleTransform.Translation.y);
        float circleRadius       = circleCollider.Radius;

        glm::vec2 boxMin = glm::vec2(boxPosition.x - boxSize.x / 2.0f, boxPosition.y - boxSize.y / 2.0f);
        glm::vec2 boxMax = glm::vec2(boxPosition.x + boxSize.x / 2.0f, boxPosition.y + boxSize.y / 2.0f);

        glm::vec2 closestPoint = glm::clamp(glm::vec2(circlePosition.x, circlePosition.y), boxMin, boxMax);

        float distance = glm::distance(closestPoint, glm::vec2(circlePosition.x, circlePosition.y));

        return distance <= circleRadius;
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

        glm::vec2 position1 = glm::vec2(circleTransform1.Translation.x, circleTransform1.Translation.y);
        float radius1       = circleCollider1.Radius;
        glm::vec2 position2 = glm::vec2(circleTransform2.Translation.x, circleTransform2.Translation.y);
        float radius2       = circleCollider2.Radius;

        float distance = glm::distance(glm::vec2(position1.x, position1.y), glm::vec2(position2.x, position2.y));

        return distance <= (radius1 + radius2);
    }

    void CollisionDetection2DSystem::EmitCollisionEvent(Entity *entityA, Entity *entityB)
    {
        Events::OnCollisionEntered event;

        event.EntityA = entityA;
        event.EntityB = entityB;

        entityA->GetWorld()->Emit<Events::OnCollisionEntered>(event);
    }
};
