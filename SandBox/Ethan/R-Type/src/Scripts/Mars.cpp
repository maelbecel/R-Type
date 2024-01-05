/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** Mars
*/

#include "Mars.hpp"
#include <random>

namespace RType {

    using namespace Exodia;

    /////////////
    // Methods //
    /////////////

    void Mars::OnCreate() {
        Scene *scene = HandleEntity.GetScene();

        if (!scene)
            return;

        // -- Create Mars -- //
        GameObject mars = scene->CreateNewEntity("Mars");

        if (mars.GetEntity()) {
            auto &tc = mars.GetComponent<TransformComponent>(); // tc = Transform component

            tc.Translation = {5.0f, 0.0f, 0.0f};
            tc.Scale = {6.0f, 5.0f, 1.0f};

            auto &sc = mars.AddComponent<SpriteRendererComponent>(); // sc = SpriteRenderer component

            sc.Texture = SubTexture2D::CreateFromCoords(MARS, {520.0f, 33.0f}, {1.0f, 1.0f}, {500.0f, 440.0f});
        }

        // -- Debris in orbit -- //
        GenerateDebris(scene);

        // TODO: Add RigidBody component to all the system for the real game.
    }

    void Mars::GenerateDebris(Scene *scene) {
        std::random_device rd;
        std::mt19937 gen(rd());

        std::uniform_real_distribution<float> dis(-4.0f, 3.5f);
        std::uniform_real_distribution<float> dis2(-2.0f, 2.0f);
        std::uniform_int_distribution<int> dis3(0, 1);

        // -- Generate Big Debris -- //
        GameObject ariane1 = scene->CreateNewEntity("Ariane 1");

        if (ariane1.GetEntity()) {
            auto &tc = ariane1.GetComponent<TransformComponent>(); // tc = Transform component

            tc.Translation = {dis(gen), dis2(gen), 0.2f};
            tc.Scale = {1.5f, 1.6f, 1.0f};

            auto &sc = ariane1.AddComponent<SpriteRendererComponent>(); // sc = SpriteRenderer component

            sc.Texture = SubTexture2D::CreateFromCoords(MARS, {310.0f, 108.0f}, {1.0f, 1.0f}, {187.0f, 198.0f});
            sc.Color = glm::vec4(0.4f, 0.5f, 0.6f, 1.0f);
        }

        GameObject ariane2 = scene->CreateNewEntity("Ariane 2");

        if (ariane2.GetEntity()) {
            auto &tc = ariane2.GetComponent<TransformComponent>(); // tc = Transform component

            tc.Translation = {dis(gen), dis2(gen), 0.4f};
            tc.Scale = {1.5f, 1.0f, 1.0f};

            auto &sc = ariane2.AddComponent<SpriteRendererComponent>(); // sc = SpriteRenderer component

            sc.Texture = SubTexture2D::CreateFromCoords(MARS, {313.0f, 331.0f}, {1.0f, 1.0f}, {194.0f, 146.0f});
            sc.Color = glm::vec4(0.4f, 0.5f, 0.6f, 1.0f);
        }

        for (uint32_t i = 0; i < 4; i++) {
            GameObject ariane3 = scene->CreateNewEntity("Ariane 3");

            if (ariane3.GetEntity()) {
                auto &tc = ariane3.GetComponent<TransformComponent>(); // tc = Transform component

                tc.Translation = {dis(gen), dis2(gen), 0.3f};
                tc.Rotation.z = dis(gen) * 360.0f;
                tc.Scale.x = 2.0f;

                auto &sc = ariane3.AddComponent<SpriteRendererComponent>(); // sc = SpriteRenderer component

                sc.Texture = SubTexture2D::CreateFromCoords(MARS, {497.0f, 811.0f}, {1.0f, 1.0f}, {193.0f, 96.0f});
                sc.Color = glm::vec4(0.4f, 0.5f, 0.6f, 1.0f);
            }
        }

        // -- Generate Small Debris -- //

        for (uint32_t i = 0; i < 16; i++) {
            GameObject ariane = scene->CreateNewEntity("Ariane Debris #1");

            if (ariane.GetEntity()) {
                auto &tc = ariane.GetComponent<TransformComponent>(); // tc = Transform component

                tc.Translation = {dis(gen), dis2(gen), dis3(gen) == 0 ? 0.6f : 0.4f};
                tc.Rotation.z = dis(gen) * 360.0f;
                tc.Scale = {0.4f, 0.4f, 1.0f};

                auto &sc = ariane.AddComponent<SpriteRendererComponent>(); // sc = SpriteRenderer component

                if (dis3(gen) == 0)
                    sc.Texture = SubTexture2D::CreateFromCoords(MARS, {151.0f, 245.0f}, {1.0f, 1.0f}, {62.0f, 59.0f});
                else
                    sc.Texture = SubTexture2D::CreateFromCoords(MARS, {380.0f, 4.0f}, {1.0f, 1.0f}, {56.0f, 52.0f});

                if (tc.Translation.z == 0.4f)
                    sc.Color = glm::vec4(0.4f, 0.5f, 0.6f, 1.0f);
            }
        }
    }
}; // namespace RType
