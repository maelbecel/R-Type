/*
** EPITECH PROJECT, 2023
** ExodiaGameEngine
** File description:
** Window
*/

#ifndef WINDOW_HPP_
#define WINDOW_HPP_

// Exodia Utils
#include "Utils/CrossPlatform.hpp"

// Exodia Events
#include "Events/Event.hpp"

// External includes
#include <functional>

namespace Exodia {

    /**
     * @brief The WindowProps struct represents the properties of a window.
     */
    struct WindowProps {
        std::string Title; /*!< The title of the window */
        uint32_t Width;    /*!< The width of the window */
        uint32_t Height;   /*!< The height of the window */

        /**
         * @brief Construct a new Window Props object
         * Call this function to construct a new window properties
         *
         * @param title  (Type: std::string)  The title of the window (default: "Exodia Engine")
         * @param width  (Type: uint32_t)     The width of the window (default: 1600)
         * @param height (Type: uint32_t)     The height of the window (default: 900)
         */
        WindowProps(const std::string &title = "Exodia Engine", uint32_t width = 1600, uint32_t height = 900)
            : Title(title), Width(width), Height(height){};
    };

    /**
     * @brief Interface representing a desktop system based window
     */
    class Window {

        /////////////
        // Factory //
        /////////////
      public:
        /**
         * @brief Create a new window
         * Call this function to create a new window
         * @param props (Type: WindowProps &) The window properties
         * @return      (Type: Scope<Window>) The created window
         */
        static Scope<Window> Create(const WindowProps &props = WindowProps());

        //////////////////////////////
        // Constructor & Destructor //
        //////////////////////////////
      public:
        /**
         * @brief Destroy the Window object
         */
        virtual ~Window() = default;

        /////////////
        // Methods //
        /////////////
      public:
        /**
         * @brief Called when the window is updated
         */
        virtual void OnUpdate() = 0;

        ///////////////////////
        // Getters & Setters //
        ///////////////////////
      public:
        /**
         * @brief Get the width of the window
         * Call this function to get the width of the window
         *
         * @return (Type: uint32_t) The width of the window
         */
        virtual uint32_t GetWidth() const = 0;

        /**
         * @brief Get the height of the window
         * Call this function to get the height of the window
         *
         * @return (Type: uint32_t) The height of the window
         */
        virtual uint32_t GetHeight() const = 0;

        /**
         * @brief Set the event callback function
         * Call this function to set the event callback function
         *
         * @param callback (Type: std::function<void(Event &)> &) The callback function
         */
        virtual void SetEventCallback(const std::function<void(Event &)> &callback) = 0;

        /**
         * @brief Set the VSync state
         * Call this function to set the VSync state
         *
         * @param enabled (Type: bool) The VSync state
         */
        virtual void SetVSync(bool enabled) = 0;

        /**
         * @brief Get the VSync state
         * Call this function to get the VSync state
         *
         * @return (Type: bool) The VSync state
         */
        virtual bool IsVSync() const = 0;

        /**
         * @brief Get the Native Window object
         * Call this function to get the native window
         *
         * @return (Type: void *) The native window
         */
        virtual void *GetNativeWindow() const = 0;
    };
}; // namespace Exodia

#endif /* !WINDOW_HPP_ */
