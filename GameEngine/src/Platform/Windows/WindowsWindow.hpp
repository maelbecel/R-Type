/*
** EPITECH PROJECT, 2023
** ExodiaGameEngine
** File description:
** WindowsWindow
*/

#ifndef WINDOWSWINDOW_HPP_
    #define WINDOWSWINDOW_HPP_

    // Exodia Renderer
    #include "Renderer/Context/GraphicsContext.hpp"

    // Exodia Core
    #include "Core/Application/Window.hpp"

    // Exodia Utils
    #include "Utils/Assert.hpp"
    #include "Utils/CrossPlatform.hpp"

    // External includes
    #include <glad/glad.h>
    #include <GLFW/glfw3.h>

namespace Exodia {

    /**
     * @brief Structure named WindowData_t, which represents data related to a graphical window.
     * The structure contains the following fields:
     *  - Title         (Type: std::string)
     *  - Width         (Type: unsigned int)
     *  - Height        (Type: unsigned int)
     *  - VSync         (Type: bool)
     *  - EventCallback (Type: std::function<void(Event &)>)
     */
    typedef struct WindowData_t {
        std::string Title;                          /* !< The title of the window. */
        unsigned int Width;                         /* !< The width of the window in pixels. */
        unsigned int Height;                        /* !< The height of the window in pixels. */
        bool VSync;                                 /* !< The VSync state that indicates whether Vertical Synchronization (V-Sync) is enabled for the window. */
        std::function<void(Event &)> EventCallback; /* !< The event callback that will be invoked when events occur in the window, with an Event parameter passed to it. */
    } WindowData;

    /**
     * @brief Implementation of the `Window` interface.
     * This class represents a graphical window that can be used to render graphics in it.
     */
    class EXODIA_API WindowsWindow : public Window {

        //////////////////////////////
        // Constructor & Destructor //
        //////////////////////////////
        public:

            /**
             * @brief Construct a new Windows window object.
             * This constructor is called to create a new WindowsWindow object representing a graphical window.
             *
             * @param props (Type: const WindowProps &): The window properties containing details about the window's initial settings.
             */
            WindowsWindow(const WindowProps &props);

            /**
             * @brief Destroy the Windows window object.
             * This destructor is called when the WindowsWindow object is being destroyed, allowing for proper cleanup and resource release.
             */
            virtual ~WindowsWindow();

        /////////////
        // Methods //
        /////////////
        public:

            /**
             * @brief Update the window.
             * This method is called to update the state of the window and handle any pending events or rendering updates.
             */
            void OnUpdate() override;

        private:

            /**
             * @brief Initialize the window.
             * This method is called to initialize the window with the provided properties. It sets up the window's graphical context and other initial settings.
             * @param props (Type: const WindowProps &): The window properties specifying the initial configuration.
             */
            virtual void Init(const WindowProps &props);

            /**
             * @brief Shutdown the window.
             * This method is called to gracefully shut down the window, releasing any resources associated with it.
             */
            virtual void Shutdown();

        ///////////////////////
        // Getters & Setters //
        ///////////////////////
        public:

            /**
             * @brief Get the width of the window.
             * This method is used to retrieve the current width of the window.
             * @return (Type: unsigned int): The width of the window in pixels.
             */
            inline unsigned int GetWidth() const override
            {
                return _Data.Width;
            }

            /**
             * @brief Get the height of the window.
             * This method is used to retrieve the current height of the window.
             * @return (Type: unsigned int): The height of the window in pixels.
             */
            inline unsigned int GetHeight() const override
            {
                return _Data.Height;
            }

            /**
             * @brief Set the event callback function.
             * This method is used to set the callback function that will be called when events occur in the window.
             *
             * @param callback (Type: const std::function<void(Event &)> &): The callback function that takes an Event reference as a parameter.
             */
            inline void SetEventCallback(const std::function<void(Event &)> &callback) override
            {
                _Data.EventCallback = callback;
            }

            /**
             * @brief Set the vertical synchronization (VSync) state.
             * This method is used to enable or disable Vertical Synchronization (VSync) for the window.
             *
             * @param enabled (Type: bool): The desired VSync state (true to enable, false to disable).
             */
            void SetVSync(bool enabled);

            /**
             * @brief Get the vertical synchronization (VSync) state.
             * This method is used to check whether Vertical Synchronization (VSync) is currently enabled for the window.
             *
             * @return (Type: bool): true if VSync is enabled, false if VSync is disabled.
             */
            bool IsVSync() const;

            /**
             * @brief Get the native window pointer.
             * This method is used to retrieve the native window pointer associated with the WindowsWindow object. This pointer is platform-specific and can be used for interoperability.
             *
             * @return (Type: void *): The native window pointer.
             */
            inline virtual void *GetNativeWindow() const override
            {
                return _Window;
            }

        ////////////////
        // Attributes //
        ////////////////
        private:
            GLFWwindow            *_Window;  /*!< The GLFW window handle */
            Scope<GraphicsContext> _Context; /*!< The graphics context associated with the window */
            WindowData             _Data;    /*!< Window-specific data and settings */
    };
};

#endif /* !WINDOWSWINDOW_HPP_ */
