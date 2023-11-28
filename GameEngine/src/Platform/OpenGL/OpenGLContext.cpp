/*
** EPITECH PROJECT, 2023
** ExodiaGameEngine
** File description:
** OpenGLContext
*/

// OpenGL
#include "OpenGLContext.hpp"
#include <glad/glad.h>

// Exodia Utils
#include "Utils/Assert.hpp"

// Exodia Debug
#include "Debug/Profiling.hpp"

// GLFW
#include <GLFW/glfw3.h>

namespace Exodia {

    /////////////////////////////
    // Contructor & Destructor //
    /////////////////////////////

    OpenGLContext::OpenGLContext(GLFWwindow *windowHandle) : _WindowHandle(windowHandle)
    {
        EXODIA_CORE_ASSERT(windowHandle, "Window handle is null !");
    }

    OpenGLContext::~OpenGLContext() {};

    /////////////
    // Methods //
    /////////////

    void OpenGLContext::Init()
    {
        EXODIA_PROFILE_FUNCTION(); // Performance instrumentation profiling for the function

        // -- Set the current context -- //
        glfwMakeContextCurrent(_WindowHandle);

        int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);

        // -- Check if glad is initialized -- //
        EXODIA_CORE_ASSERT(status, "Failed to initialize Glad !");

        // -- Log the renderer information -- //
        EXODIA_CORE_INFO("OpenGL Renderer :");
        EXODIA_CORE_INFO("  Vendor   : ", glGetString(GL_VENDOR));
        EXODIA_CORE_INFO("  Renderer : ", glGetString(GL_RENDERER));
        EXODIA_CORE_INFO("  Version  : ", glGetString(GL_VERSION));

        // -- OpenGL version check -- //
        int versionMajor;
		int versionMinor;

        glGetIntegerv(GL_MAJOR_VERSION, &versionMajor);
		glGetIntegerv(GL_MINOR_VERSION, &versionMinor);

		EXODIA_CORE_ASSERT(versionMajor > 4 || (versionMajor == 4 && versionMinor >= 5), "Exodia requires at least OpenGL version 4.5!");

        // -- To remove the warning of unused variable -- //
        (void)status;
    }

    void OpenGLContext::SwapBuffers()
    {
        EXODIA_PROFILE_FUNCTION(); // Performance instrumentation profiling for the function

        glfwSwapBuffers(_WindowHandle); // Swap the render buffers
    }
};
