/*
** EPITECH PROJECT, 2023
** ExodiaGameEngine
** File description:
** KeyEvent
*/

#ifndef KEYEVENT_HPP_
#define KEYEVENT_HPP_

// Exodia Events
#include "Events/Event.hpp"

// External includes
#include <sstream>

namespace Exodia {

    /**
     * @brief Class that will be call when a key is pressed
     */
    class KeyEvent : public Event {

        /////////////////
        // Constructor //
        /////////////////
      protected:
        /**
         * @brief Construct a new Key Event object
         * Class that will be call when a key is pressed
         * @param keyCode The key code of the event
         */
        KeyEvent(int keyCode) : _KeyCode(keyCode){};

        ///////////////////////
        // Getters & Setters //
        ///////////////////////
      public:
        /**
         * @brief Get the Key Code object
         * Call this function for get the key code of the event
         * @return int : The key code of the event
         */
        inline int GetKeyCode() const { return _KeyCode; }

        EVENT_CLASS_CATEGORY(
            (int)EventCategory::EventCategoryKeyboard |
            (int)EventCategory::EventCategoryInput); // Define the category of the event (Keyboard & Input)

        ////////////////
        // Attributes //
        ////////////////
      protected:
        int _KeyCode; /*!< The key code of the event */
    };

    /**
     * @brief Class that will be call when a key is pressed
     */
    class KeyPressedEvent : public KeyEvent {

        ////////////////////////////////////////
        // Constructor & Destructor (default) //
        ////////////////////////////////////////
      public:
        /**
         * @brief Construct a new Key Pressed Event object
         * Class that will be call when a key is pressed
         * @param keyCode  The key code of the event
         * @param isRepeat If the key is pressed again
         */
        KeyPressedEvent(int keyCode, bool isRepeat) : KeyEvent(keyCode), _IsRepeat(isRepeat){};

        /**
         * @brief Destroy the Key Pressed Event object
         */
        ~KeyPressedEvent() override = default;

        /////////////
        // Methods //
        /////////////
      public:
        /**
         * @brief ToString function
         * Call this function for print the event in the console (debug)
         * @return std::string : KeyPressedEvent: {key code} ({repeat count} reapeats)
         */
        std::string ToString() const override {
            std::stringstream ss;

            ss << "KeyPressedEvent: " << _KeyCode << " (repeat = " << _IsRepeat << ")";
            return ss.str();
        }

        ///////////////////////
        // Getters & Setters //
        ///////////////////////
      public:
        /**
         * @brief Get the Repeat Count object
         * Call this function for get the number of time the key is pressed
         * @return bool : The number of time the key is pressed
         */
        inline bool IsRepeat() const { return _IsRepeat; }

        EVENT_CLASS_TYPE(KeyPressed); // Define the type of the event

        ////////////////
        // Attributes //
        ////////////////
      private:
        bool _IsRepeat; /*!< If the key is pressed again */
    };

    /**
     * @brief Class that will be call when a key is released
     * Release it's when the key is not pressed anymore
     */
    class KeyReleasedEvent : public KeyEvent {

        ////////////////////////////////////////
        // Constructor & Destructor (default) //
        ////////////////////////////////////////
      public:
        /**
         * @brief Construct a new Key Released Event object
         * Class that will be call when a key is released
         * @param keyCode The key code of the event
         */
        KeyReleasedEvent(int keyCode) : KeyEvent(keyCode){};

        /**
         * @brief Destroy the Key Released Event object
         */
        ~KeyReleasedEvent() override = default;

        /////////////
        // Methods //
        /////////////
      public:
        /**
         * @brief ToString function
         * Call this function for print the event in the console (debug)
         * @return std::string : KeyReleasedEvent: {key code}
         */
        std::string ToString() const override {
            std::stringstream ss;

            ss << "KeyReleasedEvent: " << _KeyCode;
            return ss.str();
        }

        /////////////
        // Setters //
        /////////////
      public:
        EVENT_CLASS_TYPE(KeyReleased); // Define the type of the event
    };

    /**
     * @brief Class that will be call when a key is typed
     * Type it's when the key is pressed and released
     */
    class KeyTypedEvent : public KeyEvent {

        ////////////////////////////////////////
        // Constructor & Destructor (default) //
        ////////////////////////////////////////
      public:
        /**
         * @brief Construct a new Key Typed Event object
         * Class that will be call when a key is typed
         * @param keyCode The key code of the event
         */
        KeyTypedEvent(int keyCode) : KeyEvent(keyCode){};

        /**
         * @brief Destroy the Key Typed Event object
         */
        ~KeyTypedEvent() override = default;

        /////////////
        // Methods //
        /////////////
      public:
        /**
         * @brief ToString function
         * Call this function for print the event in the console (debug)
         * @return std::string : KeyTypedEvent: {key code}
         */
        std::string ToString() const override {
            std::stringstream ss;

            ss << "KeyTypedEvent: " << _KeyCode;
            return ss.str();
        }

        /////////////
        // Setters //
        /////////////
      public:
        EVENT_CLASS_TYPE(KeyTyped); // Define the type of the event
    };
}; // namespace Exodia

#endif /* !KEYEVENT_HPP_ */
