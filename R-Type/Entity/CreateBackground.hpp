/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** Create background
*/

#ifndef CREATEBACKGROUND_HPP_
    #define CREATEBACKGROUND_HPP_

    #include "Exodia.hpp"
    #include "ComponentExample.hpp"

namespace Exodia {

    /**
     * @brief Create the background
     *
     * @param _World
     */
    void CreateBackground(World *_World) {
        // Create background
        Entity *background = _World->CreateEntity("Background");

        background->AddComponent<IDComponent>();
        background->AddComponent<CircleRendererComponent>(glm::vec4{ 0.0f, 0.0f, 0.005f, 1.0f });
        background->GetComponent<TransformComponent>().Get().Scale.y = 100.0f;
        background->GetComponent<TransformComponent>().Get().Scale.x = 100.0f;
        background->GetComponent<TransformComponent>().Get().Translation.z = -0.5f;
    };
};

#endif /* !CREATEBACKGROUND_HPP_ */
