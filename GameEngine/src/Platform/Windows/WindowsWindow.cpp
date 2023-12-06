/*
** EPITECH PROJECT, 2023
** ExodiaGameEngine
** File description:
** WindowsWindow
*/

// Platform includes
#include "WindowsWindow.hpp"
#include "OpenGL/OpenGLContext.hpp"

// Exodia Events
#include "Events/ApplicationEvent.hpp"
#include "Events/MouseEvent.hpp"
#include "Events/KeyEvent.hpp"

// Exodia Debug
#include "Debug/Profiling.hpp"

namespace Exodia {

    ///////////////////////
    // Statics Variables //
    ///////////////////////

    static uint8_t GLFWWindowCount = 0; /* !< The number of GLFW windows that are currently opened. */

    ///////////////////////
    // Statics functions //
    ///////////////////////

    /**
     * @brief GLFW error callback function.
     * This static function is used as an error callback for GLFW library. It logs GLFW errors with the provided error code and description.
     *
     * @param error       (Type: int)          The error code reported by GLFW.
     * @param description (Type: char const *) The error description provided by GLFW.
     */
    static void GLFWErrorCallback(int error, char const *description)
    {
        EXODIA_CORE_ERROR("GLFW Error ({0}): {1}", error, description);
    }

    /////////////
    // Factory //
    /////////////

    Scope<Window> Window::Create(const WindowProps &props)
    {
        return CreateScope<WindowsWindow>(props);
    }

    //////////////////////////////
    // Constructor & Destructor //
    //////////////////////////////

    WindowsWindow::WindowsWindow(const WindowProps &props)
    {
        EXODIA_PROFILE_FUNCTION(); // Performance instrumentation profiling for the function

        Init(props); // Initialize the window
    }

    WindowsWindow::~WindowsWindow()
    {
        EXODIA_PROFILE_FUNCTION(); // Performance instrumentation profiling for the function

        Shutdown(); // Shutdown the window
    }

    /////////////
    // Methods //
    /////////////

    void WindowsWindow::Init(const WindowProps &props)
    {
        EXODIA_PROFILE_FUNCTION(); // Performance instrumentation profiling for the function

        // Initialize the WindowData properties
        _Data.Title = props.Title;
        _Data.Width = props.Width;
        _Data.Height = props.Height;

        // Log the window creation
        EXODIA_CORE_INFO("Creating window {0} ({1}, {2})", props.Title, props.Width, props.Height);

        // Check if GLFW is initialized and initialize it if not
        if (GLFWWindowCount == 0) {
            EXODIA_PROFILE_SCOPE("glfwInit"); // Performance instrumentation profiling for the scope

            int success = glfwInit();

            EXODIA_CORE_ASSERT(success, "Could not initialize GLFW !");

            // TODO: glfwSetErrorCallback to be handled by the client
            // Currently we got GLFW Error (65539): Invalid window attribute 0x0002000D
            //glfwSetErrorCallback(GLFWErrorCallback);

            // -- To remove the warning of unused variable -- //
            (void)success;
        }

        // Create the GLFW window
        {
            EXODIA_PROFILE_SCOPE("glfwCreateWindow"); // Performance instrumentation profiling for the scope

            _Window = glfwCreateWindow(
                (int)props.Width,
                (int)props.Height,
                _Data.Title.c_str(),
                nullptr,
                nullptr
            );
            GLFWWindowCount++; // Increment the number of GLFW windows
        }

        // Initialize the OpenGL context
        _Context = GraphicsContext::Create(_Window);
        _Context->Init();

        glfwSetWindowUserPointer(_Window, &_Data); // Set the user pointer to the WindowData
        SetVSync(true);                            // Enable VSync by default

        // Set GLFW callbacks
        glfwSetWindowSizeCallback(_Window, [](GLFWwindow *window, int width, int height) {
            WindowData &data = *(WindowData *)glfwGetWindowUserPointer(window);

            data.Width = width;
            data.Height = height;

            WindowResizeEvent event(width, height);

            data.EventCallback(event);
        });

        glfwSetWindowCloseCallback(_Window, [](GLFWwindow *window) {
            WindowData &data = *(WindowData *)glfwGetWindowUserPointer(window);
            WindowCloseEvent event;

            data.EventCallback(event);
        });

        glfwSetKeyCallback(_Window, [](GLFWwindow *window, int key, UNUSED int scancode, int action, UNUSED int mods) {
            WindowData &data = *(WindowData *)glfwGetWindowUserPointer(window);

            switch (action) {
                case GLFW_PRESS: {
                    KeyPressedEvent event(key, 0);
                    data.EventCallback(event);
                    break;
                }

                case GLFW_RELEASE: {
                    KeyReleasedEvent event(key);
                    data.EventCallback(event);
                    break;
                }

                case GLFW_REPEAT: {
                    KeyPressedEvent event(key, true);
                    data.EventCallback(event);
                    break;
                }
            }
        });

        glfwSetCharCallback(_Window, [](GLFWwindow *window, unsigned int keycode) {
            WindowData &data = *(WindowData *)glfwGetWindowUserPointer(window);
            KeyTypedEvent event(keycode);

            data.EventCallback(event);
        });

        glfwSetMouseButtonCallback(_Window, [](GLFWwindow *window, int button, int action, UNUSED int mods) {
            WindowData &data = *(WindowData *)glfwGetWindowUserPointer(window);

            switch (action) {
                case GLFW_PRESS: {
                    MouseButtonPressedEvent event(button);
                    data.EventCallback(event);
                    break;
                }

                case GLFW_RELEASE: {
                    MouseButtonReleasedEvent event(button);
                    data.EventCallback(event);
                    break;
                }
            }
        });

        glfwSetScrollCallback(_Window, [](GLFWwindow *window, double xOffset, double yOffset) {
            WindowData &data = *(WindowData *)glfwGetWindowUserPointer(window);
            MouseScrolledEvent event((float)xOffset, (float)yOffset);

            data.EventCallback(event);
        });

        glfwSetCursorPosCallback(_Window, [](GLFWwindow *window, double xPos, double yPos) {
            WindowData &data = *(WindowData *)glfwGetWindowUserPointer(window);
            MouseMovedEvent event((float)xPos, (float)yPos);

            data.EventCallback(event);
        });
    }

    void WindowsWindow::Shutdown()
    {
        EXODIA_PROFILE_FUNCTION(); // Performance instrumentation profiling for the function

        glfwDestroyWindow(_Window); // Destroy the GLFW window

        GLFWWindowCount--; // Decrement the number of GLFW windows

        if (GLFWWindowCount == 0)
            glfwTerminate(); // Terminate GLFW if there is no more windows
    }

    void WindowsWindow::OnUpdate()
    {
        EXODIA_PROFILE_FUNCTION(); // Performance instrumentation profiling for the function

        glfwPollEvents();

        _Context->SwapBuffers();
    }

    /////////////
    // Setters //
    /////////////

    void WindowsWindow::SetVSync(bool enabled)
    {
        EXODIA_PROFILE_FUNCTION();

        if (enabled)
            glfwSwapInterval(1); // Enable VSync
        else
            glfwSwapInterval(0); // Disable VSync

        _Data.VSync = enabled;
    }

    bool WindowsWindow::IsVSync() const
    {
        return _Data.VSync;
    }
};
