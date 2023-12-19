/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** CollisionSystem
*/

#ifndef CollisionSystem_HPP_
    #define CollisionSystem_HPP_

    // Exodia ECS Interface includes
    #include "Interface/EntitySystem.hpp"
    #include "Interface/EventSubscriber.hpp"

    // Exodia ECS Event includes
    #include "Events/Events.hpp"

    // Exodia ECS Components includes
    #include "Component/Components.hpp"
    #include "Component/ComponentHandle.hpp"

    // External includes
    #include <vector>

namespace Exodia {

    ///////////////////////////////////////////////////////////////////////////////////////////////////////
    // TODO: A Collision Detection System is not optimized at all, it should be optimized                //
    // For that, https://www.linkedin.com/advice/0/how-can-you-optimize-game-physics-collision-detection //
    ///////////////////////////////////////////////////////////////////////////////////////////////////////

    struct BoxCollider2DComponent;
    struct CircleCollider2DComponent;
    struct TransformComponent;
    struct ScriptComponent;

    class CollisionSystem : public EntitySystem, public EventSubscriber<Events::OnCollisionEntered> {

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

            CollisionSystem() = default;
            virtual ~CollisionSystem() override = default;

        /////////////
        // Methods //
        /////////////
        public:

            virtual void Update(World *world, Timestep ts) override;

            virtual void Receive(World *world, const Events::OnCollisionEntered &event) override;

        private:
            bool CheckCollision(ComponentHandle<BoxCollider2DComponent> collider1, ComponentHandle<TransformComponent> transform1, ComponentHandle<BoxCollider2DComponent> collider2, ComponentHandle<TransformComponent> transform2);
            bool CheckCollision(ComponentHandle<BoxCollider2DComponent> collider1, ComponentHandle<TransformComponent> transform1, ComponentHandle<CircleCollider2DComponent> collider2, ComponentHandle<TransformComponent> transform2);
            bool CheckCollision(ComponentHandle<CircleCollider2DComponent> collider1, ComponentHandle<TransformComponent> transform1, ComponentHandle<CircleCollider2DComponent> collider2, ComponentHandle<TransformComponent> transform2);

            BoundingBox CalculateTransformedBoundingBox(const BoxCollider2DComponent &collider, const TransformComponent &transform);
            bool IntersectBoundingBoxes(const BoundingBox &box1, const BoundingBox &box2);

            void EmitOnCollisionEnterEvent(Entity *entityA, Entity *entityB);

            void CompareCollisions(const std::vector<std::pair<Entity *, Entity *>> &collisions);

        ////////////////
        // Attributes //
        ////////////////
        private:
            std::vector<std::pair<Entity *, Entity *>> _LastCollisions;
    };
};

#endif /* !CollisionSystem_HPP_ */
