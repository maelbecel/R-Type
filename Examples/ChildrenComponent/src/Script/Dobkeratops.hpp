/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** Dobkeratops
*/

#ifndef DOBKERATOPS_HPP_
    #define DOBKERATOPS_HPP_

    #include "Exodia.hpp"

namespace Exodia {

    class DobkeratopsTails : public ScriptableEntity {

        /////////////
        // Methods //
        /////////////
        public:

            virtual void OnCreate() override
            {
                Ref<Texture2D> dobkeratopsTexture = Texture2D::Create("Assets/Textures/Dobkeratops.png");

                HandleEntity->AddComponent<ChildrenComponent>();

                OnCreateLastTail(dobkeratopsTexture);
            }

        private:
            void OnCreateLastTail(Ref<Texture2D> dobkeratopsTexture)
            {
                auto &children = HandleEntity->GetComponent<ChildrenComponent>().Get();

                Entity *tail = HandleEntity->GetWorld()->CreateEntity("DobkeratopsTail - #" + std::to_string(0));

                auto &tc = tail->GetComponent<TransformComponent>().Get();
                
                tc.Translation = { 0, 0, 0 };
                tc.Rotation = { 0, 0, 45 };

                auto sprite = tail->AddComponent<SpriteRendererComponent>();

                sprite.Get().Texture = SubTexture2D::CreateFromCoords(dobkeratopsTexture, { 630.84, 1.5 }, { 18, 16 }, { 1, 1 });

                children.AddChild(tail->GetComponent<IDComponent>().Get().ID);
            }
    };
};

#endif /* !DOBKERATOPS_HPP_ */
