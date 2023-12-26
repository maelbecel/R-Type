/*
** EPITECH PROJECT, 2023
** ExodiaGameEngine
** File description:
** ApplicationEvent
*/

#ifndef APPLICATIONEVENT_HPP_
#define APPLICATIONEVENT_HPP_

// Exodia Utils
#include "Utils/CrossPlatform.hpp"

// Exodia Events
#include "Events/Event.hpp"

// External includes
#include <sstream>
#include <filesystem>
#include <vector>

///////////////////////////////////////////////////////////////////////////////
// In this file, we define all the event that are related to the application //
///////////////////////////////////////////////////////////////////////////////

namespace Exodia {

    /**
     * @brief Class that will be call when the window is resized
     */
    class WindowResizeEvent : public Event {

        ////////////////////////////////////////
        // Constructor & Destructor (default) //
        ////////////////////////////////////////
      public:
        /**
         * @brief Construct a new Window Resize Event object
         * Class that will be call when the window is resized
         * @param width  The new width of the window
         * @param height The new height of the window
         */
        WindowResizeEvent(unsigned int width, unsigned int height) : _Width(width), _Height(height){};

        /**
         * @brief Destroy the Window Resize Event object
         */
        ~WindowResizeEvent() override = default;

        /////////////
        // Methods //
        /////////////
      public:
        /**
         * @brief ToString function
         * Call this function for print the event in the console (debug)
         * @return std::string : WindowResizeEvent: {width}, {height}
         */
        std::string ToString() const override {
            std::stringstream ss;

            ss << "WindowResizeEvent: " << _Width << ", " << _Height;
            return ss.str();
        }

        ///////////////////////
        // Getters & Setters //
        ///////////////////////
      public:
        /**
         * @brief Get the Width object
         * Call this function for know the width of the window
         * @return unsigned int The width of the window
         */
        inline unsigned int GetWidth() const { return _Width; }

        /**
         * @brief Get the Height object
         * Call this function for know the height of the window
         * @return unsigned int The height of the window
         */
        inline unsigned int GetHeight() const { return _Height; }

        EVENT_CLASS_TYPE(WindowResize)                                // Define the event type
        EVENT_CLASS_CATEGORY(EventCategory::EventCategoryApplication) // Define the event category

        ////////////////
        // Attributes //
        ////////////////
      private:
        unsigned int _Width;  /*!< The width of the window */
        unsigned int _Height; /*!< The height of the window */
    };

    /**
     * @brief Class that will be call when the window is closed
     */
    class WindowCloseEvent : public Event {

        //////////////////////////////////////////////////
        // Constructor (default) & Destructor (default) //
        //////////////////////////////////////////////////
      public:
        /**
         * @brief Construct a new Window Close Event object
         */
        WindowCloseEvent() = default;

        /**
         * @brief Destroy the Window Close Event object
         */
        ~WindowCloseEvent() override = default;

        /////////////
        // Setters //
        /////////////
      public:
        EVENT_CLASS_TYPE(WindowClose);                                 // Define the event type
        EVENT_CLASS_CATEGORY(EventCategory::EventCategoryApplication); // Define the event category
    };

    /**
     * @brief Class that will be call when the Application is ticked
     * This event is called every frame
     * The difference between AppTickEvent and AppUpdateEvent is that AppTickEvent is called before AppUpdateEvent
     */
    class AppTickEvent : public Event {

        //////////////////////////////////////////////////
        // Constructor (default) & Destructor (default) //
        //////////////////////////////////////////////////
      public:
        /**
         * @brief Construct a new App Tick Event object
         */
        AppTickEvent() = default;

        /**
         * @brief Destroy the App Tick Event object
         */
        ~AppTickEvent() override = default;

        /////////////
        // Setters //
        /////////////
      public:
        EVENT_CLASS_TYPE(AppTick);                                     // Define the event type
        EVENT_CLASS_CATEGORY(EventCategory::EventCategoryApplication); // Define the event category
    };

    /**
     * @brief Class that will be call when the Application is updated
     * This event is called every frame
     * The difference between AppTickEvent and AppUpdateEvent is that AppTickEvent is called before AppUpdateEvent
     */
    class AppUpdateEvent : public Event {

        //////////////////////////////////////////////////
        // Constructor (default) & Destructor (default) //
        //////////////////////////////////////////////////
      public:
        /**
         * @brief Construct a new App Update Event object
         */
        AppUpdateEvent() = default;

        /**
         * @brief Destroy the App Update Event object
         */
        ~AppUpdateEvent() override = default;

        /////////////
        // Setters //
        /////////////
      public:
        EVENT_CLASS_TYPE(AppUpdate);                                   // Define the event type
        EVENT_CLASS_CATEGORY(EventCategory::EventCategoryApplication); // Define the event category
    };

    /**
     * @brief Class that will be call when the Application is rendered
     * This event is called every frame
     */
    class AppRenderEvent : public Event {

        //////////////////////////////////////////////////
        // Constructor (default) & Destructor (default) //
        //////////////////////////////////////////////////
      public:
        /**
         * @brief Construct a new App Render Event object
         */
        AppRenderEvent() = default;

        /**
         * @brief Destroy the App Render Event object
         */
        ~AppRenderEvent() override = default;

        // Setters
      public:
        EVENT_CLASS_TYPE(AppRender);                                   // Define the event type
        EVENT_CLASS_CATEGORY(EventCategory::EventCategoryApplication); // Define the event category
    };

    class WindowDropEvent : public Event {

        //////////////////////////////
        // Constructor & Destructor //
        //////////////////////////////
      public:
        WindowDropEvent(const std::vector<std::filesystem::path> &paths) : _Paths(paths){};
        WindowDropEvent(const std::vector<std::filesystem::path> &&paths) : _Paths(std::move(paths)){};

        ///////////////////////
        // Getters & Setters //
        ///////////////////////
      public:
        const std::vector<std::filesystem::path> &GetPaths() const { return _Paths; };

        EVENT_CLASS_TYPE(WindowDrop);                                  // Define the event type
        EVENT_CLASS_CATEGORY(EventCategory::EventCategoryApplication); // Define the event category

        ////////////////
        // Attributes //
        ////////////////
      private:
        std::vector<std::filesystem::path> _Paths; /*!< The paths of the files dropped */
    };
}; // namespace Exodia

#endif /* !APPLICATIONEVENT_HPP_ */
