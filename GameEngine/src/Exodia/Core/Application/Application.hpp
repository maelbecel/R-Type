/*
** EPITECH PROJECT, 2023
** ExodiaGameEngine
** File description:
** Application
*/

#ifndef APPLICATION_HPP_
    #define APPLICATION_HPP_

    // Exodia Events
    #include "Events/ApplicationEvent.hpp"

    // Exodia Core
    #include "Core/Layer/LayerStack.hpp"
    #include "Core/Time/Timestep.hpp"
    #include "Core/Application/Window.hpp"
    #include "Core/Time/Timer.hpp"

    // Exodia Debug
    #include "Debug/Logs.hpp"

    // Exodia ImGUI
    #include "ImGui/ImGuiLayer.hpp"

    // Exodia Utils
    #include "Utils/Memory.hpp"
    #include "Utils/Assert.hpp"

namespace Exodia {

    /////////////
    // Struct //
    /////////////

    struct ApplicationCommandLineArgs {
        int    Count = 0;
        char **Args  = nullptr;

        const char *operator[](int index) const
        {
            EXODIA_CORE_ASSERT(index < Count, "Index out of range !");

            return Args[index];
        }
    };

    struct ApplicationSpecification {
        std::string Name = "Exodia Application";
        std::string WorkingDirectory;
        ApplicationCommandLineArgs CommandLineArgs;
    };

    ////////////
    // Macros //
    ////////////
    #define BIND_EVENT_FN(x) std::bind(&x, this, std::placeholders::_1)

    /**
     * @brief Class that will be used for the application
     */
    class EXODIA_API Application {

        //////////////////////////////
        // Constructor & Destructor //
        //////////////////////////////
        public:

            /**
             * @brief Construct a new Application object
             * Call this function for create the application
             * 
             * @param spec (Type: const ApplicationSpecification &) The specification of the application
             */
            Application(const ApplicationSpecification &spec);

            /**
             * @brief Destroy the Application object
             */
            virtual ~Application();

        /////////////
        // Methods //
        /////////////
        public:

            /**
             * @brief Run the application
             * Call this function for run the application
             */
            void Run();

            /**
             * @brief Close the application
             * Call this function for close the application
             */
            void Close();

            /**
             * @brief Function that will be called when an event is triggered
             * Call this function for handle the events
             *
             * @param event (Type: Event) The event triggered
             */
            void OnEvent(Event &event);

            /**
             * @brief Push a layer in the layer stack
             * Call this function for push a layer in the layer stack
             *
             * @param layer (Type: Layer *) The layer to push
             */
            void PushLayer(Layer *layer);

            /**
             * @brief Push a overlay in the layer stack
             * Call this function for push a overlay in the layer stack
             *
             * @param layer (Type: Layer *) The overlay to push
             */
            void PushOverlay(Layer *layer);

        private:

            /**
             * @brief Function that will be called when the window is closed
             * Call this function for close the window
             *
             * @param event (Type: WindowCloseEvent &) The window close event
             * @return      (Type: bool)                Always true
             */
            bool OnWindowClose(WindowCloseEvent &event);

            /**
             * @brief Function that will be called when the window is resized
             * Call this function for resize the window
             *
             * @param event (Type: WindowResizeEvent) The window resize event
             * @return      (Type: bool)              Always true
             */
            bool OnWindowResize(WindowResizeEvent &event);

        ///////////////////////
        // Getters & Setters //
        ///////////////////////
        public:

            /**
             * @brief Get the ImGuiLayer object
             * Call this function for get the ImGUI layer of the application
             *
             * @return (Type: ImGUILayer *) The ImGUI layer of the application
             */
            ImGuiLayer *GetImGuiLayer();

            ApplicationSpecification GetSpecification() const;

            /**
             * @brief Get the Application object
             * Call this function for get the application
             *
             * @return (Type: Application &) The application
             */
            inline static Application &Get()
            {
                return *_Instance;
            }

            /**
             * @brief Get the Window object
             * Call this function for get the window of the application
             *
             * @return (Type: Window &) The window of the application
             */
            inline Window &GetWindow()
            {
                return *_Window;
            }

        ////////////////
        // Attributes //
        ////////////////
        private:
            ApplicationSpecification   _Specification; /*!< The specification of the application */
            Scope<Window>              _Window;        /*!< The window of the application */
            ImGuiLayer *               _ImGuiLayer;    /*!< The ImGUI layer of the application */
            bool                       _Running;       /*!< The running state of the application */
            bool                       _Minimized;     /*!< The minimized state of the application */
            LayerStack                 _LayerStack;    /*!< The layer stack of the application */
            float                      _LastTime;      /*!< The last time of the last frame of the application */
            Timer                      _Timer;         /*!< The timer of the application */

        private:
            static Application *_Instance; /*!< The instance of the application */
    };

    // To be defined in CLIENT

    /**
     * @brief Create a Application object
     * Call this function for create the application
     *
     * @param args (Type: ApplicationCommandLineArgs) The command line arguments of the application (default: ApplicationCommandLineArgs())
     * @return     (Type: Application *)              The application created
     */
    Application *CreateApplication(ApplicationCommandLineArgs args = ApplicationCommandLineArgs());
};

#endif /* !APPLICATION_HPP_ */
