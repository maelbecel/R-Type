/*
** EPITECH PROJECT, 2023
** ExodiaGameEngine
** File description:
** MouseEvent
*/

#ifndef MOUSEEVENT_HPP_
#define MOUSEEVENT_HPP_

// Exodia Utils
#include "Utils/CrossPlatform.hpp"

// Exodia Events
#include "Events/Event.hpp"

// External includes
#include <sstream>

namespace Exodia
{

    /**
     * @brief Class that will be call when the mouse is moved
     */
    class MouseMovedEvent : public Event
    {

        ////////////////////////////////////////
        // Constructor & Destructor (default) //
        ////////////////////////////////////////
      public:
        /**
         * @brief Construct a new Mouse Moved Event object
         * Class that will be call when the mouse is moved
         * @param x The x position of the mouse
         * @param y The y position of the mouse
         */
        MouseMovedEvent( float x, float y ) : _MouseX( x ), _MouseY( y ){};

        /**
         * @brief Destroy the Mouse Moved Event object
         */
        ~MouseMovedEvent() override = default;

        /////////////
        // Methods //
        /////////////
      public:
        /**
         * @brief ToString function
         * Call this function for print the event in the console (debug)
         * @return std::string : MouseMovedEvent: {x}, {y}
         */
        std::string ToString() const override
        {
            std::stringstream ss;

            ss << "MouseMovedEvent: " << _MouseX << ", " << _MouseY;
            return ss.str();
        }

        /////////////
        // Getters //
        /////////////
      public:
        /**
         * @brief Get the X position of the mouse
         * Call this function for get the x position of the mouse
         * @return float Position of the mouse (X)
         */
        float GetMouseX() const { return _MouseX; }

        /**
         * @brief Get the Y position of the mouse
         * Call this function for get the y position of the mouse
         * @return float Position of the mouse (Y)
         */
        float GetMouseY() const { return _MouseY; }

        /////////////
        // Setters //
        /////////////
      public:
        EVENT_CLASS_TYPE( MouseMoved ); // Define the type of the event
        EVENT_CLASS_CATEGORY(
            (int) EventCategory::EventCategoryMouse |
            (int) EventCategory::EventCategoryInput ); // Define the category of the event (Mouse & Input)

        ////////////////
        // Attributes //
        ////////////////
      private:
        float _MouseX; /*!< The x position of the mouse */
        float _MouseY; /*!< The y position of the mouse */
    };

    /**
     * @brief Class that will be call when the scroll is moved
     */
    class MouseScrolledEvent : public Event
    {

        ////////////////////////////////////////
        // Constructor & Destructor (default) //
        ////////////////////////////////////////
      public:
        /**
         * @brief Construct a new Mouse Scrolled Event object
         * Class that will be call when the scroll is moved
         * @param xOffset The x offset of the scroll
         * @param yOffset The y offset of the scroll
         */
        MouseScrolledEvent( float xOffset, float yOffset ) : _XOffset( xOffset ), _YOffset( yOffset ){};

        /**
         * @brief Destroy the Mouse Scrolled Event object
         */
        ~MouseScrolledEvent() override = default;

        /////////////
        // Methods //
        /////////////
      public:
        /**
         * @brief ToString function
         * Call this function for print the event in the console (debug)
         * @return std::string : MouseScrolledEvent: {xOffset}, {yOffset}
         */
        std::string ToString() const override
        {
            std::stringstream ss;

            ss << "MouseScrolledEvent: " << _XOffset << ", " << _YOffset;
            return ss.str();
        }

        /////////////
        // Getters //
        /////////////
      public:
        /**
         * @brief Get the X Offset object
         * Call this function for get the x offset of the scroll
         * @return float The x offset of the scroll
         */
        float GetXOffset() const { return _XOffset; }

        /**
         * @brief Get the Y Offset object
         * Call this function for get the y offset of the scroll
         * @return float The y offset of the scroll
         */
        float GetYOffset() const { return _YOffset; }

        /////////////
        // Setters //
        /////////////
      public:
        EVENT_CLASS_TYPE( MouseScrolled ); // Define the type of the event
        EVENT_CLASS_CATEGORY(
            (int) EventCategory::EventCategoryMouse |
            (int) EventCategory::EventCategoryInput ); // Define the category of the event (Mouse & Input)

        ////////////////
        // Attributes //
        ////////////////
      private:
        float _XOffset; /*!< The x offset of the scroll */
        float _YOffset; /*!< The y offset of the scroll */
    };

    /**
     * @brief Class that will be call when a mouse button is pressed
     */
    class MouseButtonEvent : public Event
    {

        ///////////////////////
        // Getters & Setters //
        ///////////////////////
      public:
        /**
         * @brief Get the Button object
         * Call this function for get the button that is pressed
         * @return int The button that is pressed
         */
        inline int GetButton() const { return _Button; }

        EVENT_CLASS_CATEGORY(
            (int) EventCategory::EventCategoryMouse |
            (int) EventCategory::EventCategoryInput ); // Define the category of the event (Mouse & Input)

        /////////////////
        // Constructor //
        /////////////////
      protected:
        /**
         * @brief Construct a new Mouse Button Event object
         * Class that will be call when a mouse button is pressed
         * @param button The button that is pressed
         */
        MouseButtonEvent( int button ) : _Button( button ){};

        ////////////////
        // Attributes //
        ////////////////
      protected:
        int _Button; /*!< The button that is pressed */
    };

    /**
     * @brief Class that will be call when a mouse button is pressed
     */
    class MouseButtonPressedEvent : public MouseButtonEvent
    {

        ////////////////////////////////////////
        // Constructor & Destructor (default) //
        ////////////////////////////////////////
      public:
        /**
         * @brief Construct a new Mouse Button Pressed Event object
         * Class that will be call when a mouse button is pressed
         * @param button The button that is pressed
         */
        MouseButtonPressedEvent( int button ) : MouseButtonEvent( button ){};

        /**
         * @brief Destroy the Mouse Button Pressed Event object
         */
        ~MouseButtonPressedEvent() = default;

        /////////////
        // Methods //
        /////////////
      public:
        /**
         * @brief ToString function
         * Call this function for print the event in the console (debug)
         * @return std::string : MouseButtonPressedEvent: {button}
         */
        std::string ToString() const override
        {
            std::stringstream ss;

            ss << "MouseButtonPressedEvent: " << _Button;
            return ss.str();
        }

        /////////////
        // Setters //
        /////////////
      public:
        EVENT_CLASS_TYPE( MouseButtonPressed ); // Define the type of the event
    };

    /**
     * @brief Class that will be call when a mouse button is released
     * Release it's when the button is not pressed anymore
     */
    class MouseButtonReleasedEvent : public MouseButtonEvent
    {

        ////////////////////////////////////////
        // Constructor & Destructor (default) //
        ////////////////////////////////////////
      public:
        /**
         * @brief Construct a new Mouse Button Released Event object
         * Class that will be call when a mouse button is released
         * @param button The button that is released
         */
        MouseButtonReleasedEvent( int button ) : MouseButtonEvent( button ){};

        /**
         * @brief Destroy the Mouse Button Released Event object
         */
        ~MouseButtonReleasedEvent() = default;

        /////////////
        // Methods //
        /////////////
      public:
        /**
         * @brief ToString function
         * Call this function for print the event in the console (debug)
         * @return std::string : MouseButtonReleasedEvent: {button}
         */
        std::string ToString() const override
        {
            std::stringstream ss;

            ss << "MouseButtonReleasedEvent: " << _Button;
            return ss.str();
        }

        /////////////
        // Setters //
        /////////////
      public:
        EVENT_CLASS_TYPE( MouseButtonReleased ); // Define the type of the event
    };
}; // namespace Exodia

#endif /* !MOUSEEVENT_HPP_ */
