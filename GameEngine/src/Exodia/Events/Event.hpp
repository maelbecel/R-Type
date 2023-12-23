/*
** EPITECH PROJECT, 2023
** ExodiaGameEngine
** File description:
** Event
*/

#ifndef EVENT_HPP_
#define EVENT_HPP_

// Exodia Utils
#include "Utils/Memory.hpp"

// External includes
#include <functional>
#include <string>

namespace Exodia
{
    class WindowCloseEvent;

    /**
     * @brief Enum that refer all the type of event that exist
     */
    enum class EventType
    {
        // Nothing
        None,
        // Window
        WindowClose,
        WindowResize,
        WindowFocus,
        WindowLostFocus,
        WindowMoved,
        WindowDrop,
        // App
        AppTick,
        AppUpdate,
        AppRender,
        // Key
        KeyPressed,
        KeyReleased,
        KeyTyped,
        // Mouse
        MouseButtonPressed,
        MouseButtonReleased,
        MouseMoved,
        MouseScrolled
    };

    /**
     * @brief Enum that refer all the different category of event that exist
     */
    enum class EventCategory
    {
        None                     = 0,
        EventCategoryApplication = BIT( 0 ),
        EventCategoryInput       = BIT( 1 ),
        EventCategoryKeyboard    = BIT( 2 ),
        EventCategoryMouse       = BIT( 3 ),
        EventCategoryMouseButton = BIT( 4 )
    };

    // -- Event Macros -------------------------------------------------------------

#define EVENT_CLASS_TYPE( type )                                                  \
    static EventType    GetStaticType() { return EventType::type; }               \
    virtual EventType   GetEventType() const override { return GetStaticType(); } \
    virtual const char *GetName() const override { return #type; }

#define EVENT_CLASS_CATEGORY( category ) \
    virtual int GetCategoryFlags() const override { return static_cast<int>( category ); }

#define EVENT_BIND_FUNC( func ) std::bind( &func, this, std::placeholders::_1 )

    /**
     * @brief The Event class
     * This class is the base class for all the events
     * It's used to create a event
     */
    class Event
    {

        ////////////////
        // Destructor //
        ////////////////
      public:
        /**
         * @brief Destroy the Event object
         */
        virtual ~Event() = default;

        /////////////
        // Methods //
        /////////////
      public:
        /**
         * @brief Convert the event to a string
         * This function is used for debug
         * @return std::string The name of the event
         */
        virtual std::string ToString() const { return GetName(); }

        /////////////
        // Getters //
        /////////////
      public:
        /**
         * @brief Get the Event Type object
         * Call this function for know the type of the event
         * @return EventType The type of the event
         * @see EventType
         */
        virtual EventType GetEventType() const = 0;

        /**
         * @brief Get the Name object
         * Call this function for know the name of the event
         * @return const char * The name of the event
         */
        virtual const char *GetName() const = 0;

        /**
         * @brief Get the Category Flags object
         * Call this function for know the category of the event
         * @return int The category of the event
         * @see EventCategory
         */
        virtual int GetCategoryFlags() const = 0;

        /**
         * @brief Check if the event is in the category
         * Call this function for know if the event is a valid event
         * @param category The category to check
         * @return true    If the event is in the category
         * @return false   If the event is not in the category
         */
        bool IsInCategory( EventCategory category ) { return GetCategoryFlags() & static_cast<int>( category ); }

        ////////////////
        // Attributes //
        ////////////////
      public:
        bool Handled = false; /*!< If the event is handled or not */
    };

    /**
     * @brief The Event Dispatcher
     * This class is here to collect a event and dispatch it in the right function
     */
    class EventDispatcher
    {

        ////////////////////////////////////////
        // Constructor / Destructor (default) //
        ////////////////////////////////////////
      public:
        /**
         * @brief Construct a new Event Dispatcher object
         * The Event Dispatcher is used to dispatch the event
         * dispatch = send the event to the right function
         * @param event The event to dispatch
         */
        EventDispatcher( Event &event ) : _Event( event ){};

        /**
         * @brief Destroy the Event Dispatcher object
         */
        ~EventDispatcher() = default;

        /////////////
        // Methods //
        /////////////
      public:
        /**
         * @brief Dispatch the event
         * This function will dispatch the event in the right function
         * And check if the event is valid or not
         *
         * Example:
         * @code
         *      EventDispatcher dispatcher(event);
         *      dispatcher.Dispatch<MouseMovedEvent>(BIND_EVENT_FN(OnMouseMoved));
         *
         * @tparam T     The type of the event
         * @tparam F     The type of the function
         * @param func   The function to call
         * @return true  If the event is valid
         * @return false If the event is not valid
         */
        template <typename T, typename F> bool Dispatch( const F &func )
        {
            if ( _Event.GetEventType() == T::GetStaticType() )
            {
                _Event.Handled = func( static_cast<T &>( _Event ) );
                return true;
            }
            return false;
        }

        ////////////////
        // Attributes //
        ////////////////
      private:
        Event &_Event; /*!< The event to dispatch */
    };

    /**
     * @brief Overload of the << operator
     * It's a debug function for print the event
     * He will send the event to the ToString() function
     * @param os              The output stream
     * @param e               The event to print
     * @return std::ostream & The output stream
     */
    inline std::ostream &operator<<( std::ostream &os, const Event &e ) { return os << e.ToString(); }
}; // namespace Exodia

#endif /* !EVENT_HPP_ */
