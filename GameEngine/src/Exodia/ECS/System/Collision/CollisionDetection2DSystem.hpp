/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** CollisionDetection2DSystem
*/

#ifndef COLLISIONDETECTION2DSYSTEM_HPP_
    #define COLLISIONDETECTION2DSYSTEM_HPP_

    // Exodia ECS Interface includes
    #include "Interface/EntitySystem.hpp"

    // Exodia ECS Components includes
    #include "Component/Components.hpp"
    #include "Component/ComponentHandle.hpp"

namespace Exodia {

    ///////////////////////////////////////////////////////////////////////////////////////////////////////
    // TODO: A Collision Detection System is not optimized at all, it should be optimized                //
    // For that, https://www.linkedin.com/advice/0/how-can-you-optimize-game-physics-collision-detection //
    ///////////////////////////////////////////////////////////////////////////////////////////////////////

    struct BoxCollider2DComponent;
    struct CircleCollider2DComponent;
    struct TransformComponent;

    class EXODIA_API CollisionDetection2DSystem : public EntitySystem {

        ////////////
        // Struct //
        ////////////
        public:
            struct BoundingBox {
                glm::vec2 min;
                glm::vec2 max;
            };

        ///////////////////////////////
        // Constructors & Destructor //
        ///////////////////////////////
        public:

            CollisionDetection2DSystem() = default;
            virtual ~CollisionDetection2DSystem() override = default;

        /////////////
        // Methods //
        /////////////
        public:

            virtual void Update(World *world, Timestep ts) override;

        private:
            bool CheckCollision(ComponentHandle<BoxCollider2DComponent> collider1, ComponentHandle<TransformComponent> transform1, ComponentHandle<BoxCollider2DComponent> collider2, ComponentHandle<TransformComponent> transform2);
            bool CheckCollision(ComponentHandle<BoxCollider2DComponent> collider1, ComponentHandle<TransformComponent> transform1, ComponentHandle<CircleCollider2DComponent> collider2, ComponentHandle<TransformComponent> transform2);
            bool CheckCollision(ComponentHandle<CircleCollider2DComponent> collider1, ComponentHandle<TransformComponent> transform1, ComponentHandle<CircleCollider2DComponent> collider2, ComponentHandle<TransformComponent> transform2);

            BoundingBox CalculateTransformedBoundingBox(const BoxCollider2DComponent &collider, const TransformComponent &transform);
            bool IntersectBoundingBoxes(const BoundingBox &box1, const BoundingBox &box2);

            void EmitCollisionEvent(Entity *entityA, Entity *entityB);
    };
};

#endif /* !COLLISIONDETECTION2DSYSTEM_HPP_ */
