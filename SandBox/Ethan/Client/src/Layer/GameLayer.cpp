/*
** EPITECH PROJECT, 2023
** ExodiaGameEngine
** File description:
** ExodiaEngine
*/

#include "GameLayer.hpp"
#include "R-Type.hpp"

namespace RType {

    using namespace Exodia;

    //////////////////////////////
    // Constructor & Destructor //
    //////////////////////////////

    GameLayer::GameLayer() : Layer("R-Type Layer")
    {
        RType::EntryPoint();

        Config::Init();

        if (!Config::Read())
            Config::Write();
    }

    /////////////
    // Methods //
    /////////////

    void GameLayer::OnAttach()
    {
        _Scene = CreateRef<Scene>();

        // -- Init the camera -- //
        Entity *MainCamera = _Scene->CreateEntity("Camera");

        MainCamera->GetComponent<TransformComponent>().Get().Translation.z = 6.0f;
        
        CameraComponent &camera = MainCamera->AddComponent<CameraComponent>().Get();

        camera.Camera.SetPersepective(45.0f, 0.01f, 1000.0f);
        camera.Camera.SetViewportSize(Application::Get().GetWindow().GetWidth(), Application::Get().GetWindow().GetHeight());

        // -- Init the Animation frame try -- //
        // Create x16 Entity for each frame of the animation
        //  0  1  2  3
        //  4  5  6  7
        //  8  9 10 11
        // 12 13 14 15

        std::vector<Ref<SubTexture2D>> Frames;

        /*for (uint32_t y = 0; y < 4; y ++) {
            for (uint32_t x = 0; x < 4; x ++) {
                Ref<SubTexture2D> subTexture = SubTexture2D::CreateFromCoords(UUID(51584511521211), { x * 128, y * 128 }, { 1.0f, 1.0f }, { 128.0f, 128.0f });
                EXODIA_CORE_INFO("Frames#{0}: ({1}, {2})", Frames.size(), x * 128, y * 128);

                Frames.push_back(subTexture);
            }
        }*/

        /*Frames.push_back(SubTexture2D::CreateFromCoords(UUID(51584511521211), { 0, 0 }, { 1.0f, 1.0f }, { 128.0f, 128.0f }));
        Frames.push_back(SubTexture2D::CreateFromCoords(UUID(51584511521211), { 128, 0 }, { 1.0f, 1.0f }, { 128.0f, 128.0f }));
        Frames.push_back(SubTexture2D::CreateFromCoords(UUID(51584511521211), { 256, 0 }, { 1.0f, 1.0f }, { 128.0f, 128.0f }));
        Frames.push_back(SubTexture2D::CreateFromCoords(UUID(51584511521211), { 384, 0 }, { 1.0f, 1.0f }, { 128.0f, 128.0f }));
        Frames.push_back(SubTexture2D::CreateFromCoords(UUID(51584511521211), { 0, 384 }, { 1.0f, 1.0f }, { 128.0f, 128.0f }));
        Frames.push_back(SubTexture2D::CreateFromCoords(UUID(51584511521211), { 128, 384 }, { 1.0f, 1.0f }, { 128.0f, 128.0f }));
        Frames.push_back(SubTexture2D::CreateFromCoords(UUID(51584511521211), { 256, 384 }, { 1.0f, 1.0f }, { 128.0f, 128.0f }));
        Frames.push_back(SubTexture2D::CreateFromCoords(UUID(51584511521211), { 384, 384 }, { 1.0f, 1.0f }, { 128.0f, 128.0f }));
        Frames.push_back(SubTexture2D::CreateFromCoords(UUID(51584511521211), { 0, 256 }, { 1.0f, 1.0f }, { 128.0f, 128.0f }));
        Frames.push_back(SubTexture2D::CreateFromCoords(UUID(51584511521211), { 128, 256 }, { 1.0f, 1.0f }, { 128.0f, 128.0f }));
        Frames.push_back(SubTexture2D::CreateFromCoords(UUID(51584511521211), { 256, 256 }, { 1.0f, 1.0f }, { 128.0f, 128.0f }));
        Frames.push_back(SubTexture2D::CreateFromCoords(UUID(51584511521211), { 384, 256 }, { 1.0f, 1.0f }, { 128.0f, 128.0f }));
        Frames.push_back(SubTexture2D::CreateFromCoords(UUID(51584511521211), { 0, 128 }, { 1.0f, 1.0f }, { 128.0f, 128.0f }));
        Frames.push_back(SubTexture2D::CreateFromCoords(UUID(51584511521211), { 128, 128 }, { 1.0f, 1.0f }, { 128.0f, 128.0f }));
        Frames.push_back(SubTexture2D::CreateFromCoords(UUID(51584511521211), { 256, 128 }, { 1.0f, 1.0f }, { 128.0f, 128.0f }));
        Frames.push_back(SubTexture2D::CreateFromCoords(UUID(51584511521211), { 384, 128 }, { 1.0f, 1.0f }, { 128.0f, 128.0f }));*/

        // Create x7 Entity for each frame of the animation
        // 0 1 2 3
        // 4 5 6

        /*for (uint32_t y = 0; y < 2; y++) {
            for (uint32_t x = 0; x < 4; x++) {
                Ref<SubTexture2D> subTexture = SubTexture2D::CreateFromCoords(UUID(120584531521562), { x * 128.0f, y * 128.0f }, { 1.0f, 1.0f }, { 128.0f, 128.0f });

                Frames.push_back(subTexture);
            }
        }*/

        Frames.push_back(SubTexture2D::CreateFromCoords(UUID(120584531521562), { 0, 0 }  , { 1.0f, 1.0f }, { 128.0f, 128.0f }));
        Frames.push_back(SubTexture2D::CreateFromCoords(UUID(120584531521562), { 128, 0 }, { 1.0f, 1.0f }, { 128.0f, 128.0f }));
        Frames.push_back(SubTexture2D::CreateFromCoords(UUID(120584531521562), { 256, 0 }, { 1.0f, 1.0f }, { 128.0f, 128.0f }));
        Frames.push_back(SubTexture2D::CreateFromCoords(UUID(120584531521562), { 0, 128 }, { 1.0f, 1.0f }, { 128.0f, 128.0f }));
        Frames.push_back(SubTexture2D::CreateFromCoords(UUID(120584531521562), { 128, 128 }, { 1.0f, 1.0f }, { 128.0f, 128.0f }));
        Frames.push_back(SubTexture2D::CreateFromCoords(UUID(120584531521562), { 256, 128 }, { 1.0f, 1.0f }, { 128.0f, 128.0f }));
        Frames.push_back(SubTexture2D::CreateFromCoords(UUID(120584531521562), { 384, 128 }, { 1.0f, 1.0f }, { 128.0f, 128.0f }));

        // -- Init the background -- //
        Entity *Background = _Scene->CreateEntity("Background");

        Background->GetComponent<TransformComponent>().Get().Translation.z = -0.5f;
        Background->GetComponent<TransformComponent>().Get().Scale = { 13.0f, 8.0f, 1.0f };

        AnimationComponent &anim = Background->AddComponent<AnimationComponent>(Frames).Get();

        anim.IsPlaying = true;
        anim.Repeat    = true;
        anim.FrameRate = 7.0f;

        Background->AddComponent<SpriteRendererComponent>().Get().Texture = anim.Frames[0];

        // -- Scene System -- //
        _Scene->RegisterSystem(new AnimationSystem());

        // -- Start the scene -- //
        _Scene->OnRuntimeStart();
    }

    void GameLayer::OnUpdate(Timestep ts)
    {
        RenderCommand::SetClearColor({ 0.0f, 0.0f, 0.0f, 1.0f });
        RenderCommand::Clear();

        _Scene->OnUpdateRuntime(ts);
    }
};
