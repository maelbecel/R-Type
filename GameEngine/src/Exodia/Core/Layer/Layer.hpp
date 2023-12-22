/*
** EPITECH PROJECT, 2023
** ExodiaGameEngine
** File description:
** Layer
*/

#ifndef LAYER_HPP_
    #define LAYER_HPP_

    // Exodia Events
    #include "Events/Event.hpp"

    // External includes
    #include <string>

namespace Exodia {

    class Timestep;

    /**
     * @brief The Layer class represents a layer of the application
     * A layer is a part of the application
     * The difference between a layer and an overlay is that an overlay is always on top of the layer stack
     */
    class Layer {

        //////////////////////////////
        // Constructor & Destructor //
        //////////////////////////////
        public:

            /**
             * @brief Construct a new Layer object
             * Call this constructor to create a new layer
             *
             * @param name (Type: std::string &) The name of the layer (default: "Layer")
             */
            Layer(const std::string &name = "Layer");

            /**
             * @brief Destroy the Layer object
             */
            virtual ~Layer() = default;

        /////////////
        // Methods //
        /////////////
        public:

            /**
             * @brief OnAttach
             * Call this method when the layer is attached to the application.
             * Attached is when the layer is used
             */
            virtual void OnAttach();

            /**
             * @brief OnDetach
             * Call this method when the layer is detached from the application.
             * Detached is when the layer is not used anymore
             */
            virtual void OnDetach();

            /**
             * @brief OnUpdate
             * Call this method when the layer is updated
             *
             * @param Timestep (Type: Timestep) The current frame to update
             */
            virtual void OnUpdate(Timestep ts);

            /**
             * @brief OnImGUIRender
             * Call this method when the layer is rendered
             */
            virtual void OnImGUIRender();

            /**
             * @brief OnEvent
             * Call this method when the layer receive an event
             *
             * @param event (Type: Event) The event received
             */
            virtual void OnEvent(Event &event);

        ///////////////////////
        // Getters & Setters //
        ///////////////////////
        public:

            /**
             * @brief Get the Name object
             * Call this method to get the name of the layer
             *
             * @return (Type: const std::string &) The name of the layer
             */
            inline const std::string &GetName() const
            {
                return _DebugName;
            }

        ////////////////
        // Attributes //
        ////////////////
        protected:
            std::string _DebugName; /*!< The name of the layer */
    };
};

#endif /* !LAYER_HPP_ */
