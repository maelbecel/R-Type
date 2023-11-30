/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** ECS
*/

#include "FortniteEvent.hpp"

using namespace Exodia;

int main()
{
    std::cout << "Creating world..." << std::endl;

    World *world = World::CreateWorld();

    world->RegisterSystem(new GravitySystem(-6.9f));

    std::cout << "Creating entity..." << std::endl;

    Entity *entity = world->CreateEntity();

    entity->AddComponent<Transform>(glm::vec3(0.0f, 5.0f, 0.0f));
    entity->AddComponent<Health>(175);

    world->Update(Timestep(1.0f / 60.0f));

    ComponentHandle<Transform> transform = entity->GetComponent<Transform>();

    if (transform /* or transform.IsValid() */)
        std::cout << "My position is " << transform->Translation.x << ", " << transform->Translation.y << std::endl;
    else
        std::cout << "I don't have a Transform component !" << std::endl;

    entity->RemoveComponent<Transform>();

    transform = entity->GetComponent<Transform>();

    if (transform /* or transform.IsValid() */)
        std::cout << "My position is " << transform.Get().Translation.x << ", " << transform.Get().Translation.y << std::endl;
    else
        std::cout << "I don't have a Transform component !" << std::endl;

    TakeDamageSubscriber *subscriber = new TakeDamageSubscriber();

    world->Subscribe<TakeDamageEvent>(subscriber);

    world->Emit<TakeDamageEvent>(TakeDamageEvent{ 25 });

    ComponentHandle<Health> health = entity->GetComponent<Health>();

    if (health /* or health.IsValid() */)
        std::cout << "My health is " << health.Get().CurrentHealth << std::endl;
    else
        std::cout << "I don't have a Health component !" << std::endl;

    std::cout << "Destroying world..." << std::endl;
    world->DestroyWorld();
    return 0;
}
