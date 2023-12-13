/*
** EPITECH PROJECT, 2023
** ECS
** File description:
** ComponentContainer
*/

#ifndef COMPONENTCONTAINER_HPP_
    #define COMPONENTCONTAINER_HPP_

    // Exodia Core includes
    #include "Core/Buffer/Buffer.hpp"

    // Exodia ECS Interface includes
    #include "Interface/IComponentContainer.hpp"

    // Exodia ECS Events includes
    #include "Events/Events.hpp"

    // Exodia World includes
    #include "World/World.hpp"

    // Exodia Utils includes
    #include "Utils/CrossPlatform.hpp"

    // External includes
    #include <memory>

namespace Exodia {

    template<typename Component>
    struct EXODIA_API ComponentContainer : public IComponentContainer {
        public:
            Component Data;

            ComponentContainer() {};
            ComponentContainer(const Component &data) : Data(data) {};

            ComponentContainer(const Buffer &data)
            {
                Data.DeserializeData(data);
            }

        protected:
            virtual TypeIndex GetTypeIndexOfComponent()
            {
                return GetTypeIndex<Component>();
            }

            virtual void Destroy(World *world)
            {
                using ComponentAllocator = std::allocator_traits<World::EntityAllocator>::template rebind_alloc<ComponentContainer<Component>>;

                ComponentAllocator allocator(world->GetPrimaryAllocator());

                std::allocator_traits<ComponentAllocator>::destroy(allocator, this);
                std::allocator_traits<ComponentAllocator>::deallocate(allocator, this, 1);
            }

            virtual void Removed(Entity *entity)
            {
                auto handle = ComponentHandle<Component>(&Data);

                entity->GetWorld()->Emit<Events::OnComponentRemoved<Component>>({ entity, handle });
            }

            virtual void Serialize(YAML::Emitter &out)
            {
                Data.Serialize(out);
            }

            virtual void Deserialize(const YAML::Node &node)
            {
                Data.Deserialize(node);
            }
    };
};

#endif /* !COMPONENTCONTAINER_HPP_ */
