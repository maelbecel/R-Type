/*
** EPITECH PROJECT, 2023
** ExodiaGameEngine
** File description:
** Application
*/

// Exodia Core includes
#include "Core/Application/Application.hpp"

// Exodia Debug includes
#include "Exodia-Debug.hpp"

// Exodia Utils includes
#include "Utils/PlatformUtils.hpp"

// Exodia Renderer includes
#include "Renderer/Renderer/Renderer.hpp"

// External includes
#include <filesystem>
#include <imgui.h>
#include <iostream>
#include <fstream>
#include <string>

#ifdef WIN32
    #include <windows.h>
    #include <psapi.h>
#endif

namespace Exodia {

    Application *Application::_Instance = nullptr;

    //////////////////////////////
    // Constructor & Destructor //
    //////////////////////////////

    Application::Application(const ApplicationSpecification &spec)
        : _Specification(spec), _Running(true), _Minimized(false), _LastTime(0.0f), _Frames(0), _FPSTimer(0.0f) {
        EXODIA_PROFILE_FUNCTION();

        EXODIA_CORE_ASSERT(!_Instance, "Application already exists !");

        _Instance = this;

        // Set working directory here
        if (!_Specification.WorkingDirectory.empty())
            std::filesystem::current_path(_Specification.WorkingDirectory);

        _Window = Window::Create(WindowProps(_Specification.Name));

        _Window->SetEventCallback(BIND_EVENT_FN(Application::OnEvent));
        _Window->SetVSync(false);

        Renderer::Init();

        _ImGuiLayer = new ImGuiLayer();

        PushOverlay(_ImGuiLayer);
    }

    Application::~Application() {
        EXODIA_PROFILE_FUNCTION();

        Renderer::Shutdown();
    }

    /////////////
    // Methods //
    /////////////

    void Application::Run() {
        EXODIA_PROFILE_FUNCTION();

        while (_Running) {
            EXODIA_PROFILE_SCOPE("RunLoop");

            float time = _Timer.Elapsed();

            Timestep timestep(time - _LastTime);

            _LastTime = time;

            if (!_Minimized) {
                {
                    EXODIA_PROFILE_SCOPE("LayerStack OnUpdate");
                    for (Layer *layer : _LayerStack)
                        layer->OnUpdate(timestep);
                }

                // TODO: Put this block in a Thread
                _ImGuiLayer->Begin();

                {
                    EXODIA_PROFILE_SCOPE("LayerStack OnImGUIRender");
                    for (Layer *layer : _LayerStack)
                        layer->OnImGUIRender();
                }

                _ImGuiLayer->End();
                ///////////////////////////////////
            }

            _Window->OnUpdate();

            UpdateStatistics(timestep);
        }

        {
            EXODIA_PROFILE_SCOPE("LayerStack OnDetach");

            for (Layer *layer : _LayerStack)
                layer->OnDetach();
        }
    }

    void Application::Close() { _Running = false; }

    void Application::OnEvent(Event &event) {
        EventDispatcher dispatcher(event);

        dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_FN(Application::OnWindowClose));
        dispatcher.Dispatch<WindowResizeEvent>(BIND_EVENT_FN(Application::OnWindowResize));

        for (auto it = _LayerStack.begin(); it != _LayerStack.end(); ++it) {
            if (event.Handled)
                break;
            (*it)->OnEvent(event);
        }
    }

    void Application::PushLayer(Layer *layer) {
        EXODIA_PROFILE_FUNCTION();

        _LayerStack.PushLayer(layer);
        layer->OnAttach();
    }

    void Application::PushOverlay(Layer *overlay) {
        EXODIA_PROFILE_FUNCTION();

        _LayerStack.PushOverlay(overlay);
        overlay->OnAttach();
    }

    bool Application::OnWindowClose(UNUSED(WindowCloseEvent &event)) {
        _Running = false;

        return true;
    }

    bool Application::OnWindowResize(WindowResizeEvent &event) {
        EXODIA_PROFILE_FUNCTION();

        if (event.GetWidth() == 0 || event.GetHeight() == 0) {
            _Minimized = true;
            return false;
        }

        _Minimized = false;
        Renderer::OnWindowResize(event.GetWidth(), event.GetHeight());

        return false;
    }

    void Application::UpdateStatistics(Timestep ts) {
        static float timer = 10.0f;

        _Frames++;
        _FPSTimer += ts;
        timer += ts;

        if (_FPSTimer >= 1.0f) {
            _Statistics.FPS = _Frames / _FPSTimer;
            _Statistics.FrameTime = 1000.0f / _Statistics.FPS;

            _FPSTimer = 0.0f;
            _Frames = 0;
        }

        if (timer >= 10.0f) {
            _Statistics.MemoryUsage = GetMemoryUsage();

            timer = 0.0f;
        }
    }

    ///////////////////////
    // Getters & Setters //
    ///////////////////////

    ImGuiLayer *Application::GetImGuiLayer() { return _ImGuiLayer; }

    ApplicationSpecification Application::GetSpecification() const { return _Specification; }

    ApplicationStatistics Application::GetStatistics() const { return _Statistics; }

    uint64_t Application::GetMemoryUsage()
    {
    #ifdef WIN32
        PROCESS_MEMORY_COUNTERS_EX pmc;

        GetProcessMemoryInfo(GetCurrentProcess(), (PROCESS_MEMORY_COUNTERS *)&pmc, sizeof(pmc));

        return pmc.PrivateUsage;
    #else
        std::ifstream file("/proc/self/status");
        std::string line;
        uint64_t memoryUsage = 0;

        if (!file.is_open())
            return 0;

        while (std::getline(file, line)) {
            if (line.find("VmRSS") != std::string::npos) {
                std::istringstream iss(line);
                std::string label;
                uint64_t value;

                iss >> label >> value;
                memoryUsage = value; // Value in KB
                break;
            }
        }

        return memoryUsage;
    #endif
    }
}; // namespace Exodia
