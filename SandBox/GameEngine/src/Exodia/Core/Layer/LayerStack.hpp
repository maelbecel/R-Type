/*
** EPITECH PROJECT, 2023
** ExodiaGameEngine
** File description:
** LayerStack
*/

#ifndef LAYERSTACK_HPP_
#define LAYERSTACK_HPP_

// Exodia Core
#include "Core/Layer/Layer.hpp"

// External includes
#include <vector>

namespace Exodia {

    /**
     * @brief The LayerStack class represents a stack of layers
     * A layer is a part of the application
     * The difference between a layer and an overlay is that an overlay is always on top of the layer stack
     */
    class LayerStack {

        //////////////////////////////
        // Constructor & Destructor //
        //////////////////////////////
      public:
        /**
         * @brief Construct a new LayerStack object
         * Call this constructor to create a new layer stack
         */
        LayerStack();

        /**
         * @brief Destroy the LayerStack object
         */
        ~LayerStack();

        /////////////
        // Methods //
        /////////////
      public:
        /**
         * @brief PushLayer
         * Call this method to push a layer to the layer stack
         * A layer is a part of the application
         *
         * @param layer (Type: Layer *) The layer to push
         */
        void PushLayer(Layer *layer);

        /**
         * @brief PushOverlay
         * Call this method to push an overlay to the layer stack
         * An overlay is a part of the application
         *
         * @param overlay (Type: Layer *) The overlay to push
         */
        void PushOverlay(Layer *overlay);

        /**
         * @brief PopLayer
         * Call this method to pop a layer from the layer stack
         * A layer is a part of the application
         *
         * @param layer (Type: Layer *) The layer to pop
         */
        void PopLayer(Layer *layer);

        /**
         * @brief PopOverlay
         * Call this method to pop an overlay from the layer stack
         * An overlay is a part of the application
         *
         * @param overlay (Type: Layer *) The overlay to pop
         */
        void PopOverlay(Layer *overlay);

        ///////////////////////
        // Iterators methods //
        ///////////////////////
      public:
        /**
         * @brief GetLayers
         * Call this method to get the layers of the layer stack
         * The begin of the layer stack is the first layer
         *
         * @return (Type: std::vector<Layer *>::const_iterator) The begin of the layer stack
         */
        std::vector<Layer *>::const_iterator begin() const;

        /**
         * @brief GetLayers
         * Call this method to get the layers of the layer stack
         * The begin of the layer stack is the first layer
         *
         * @return (Type: std::vector<Layer *>::const_iterator) The begin of the layer stack
         */
        std::vector<Layer *>::const_iterator begin();

        /**
         * @brief GetLayers
         * Call this method to get the layers of the layer stack
         * The end of the layer stack is the last layer
         *
         * @return (Type: std::vector<Layer *>::const_iterator) The end of the layer stack
         */
        std::vector<Layer *>::const_iterator end() const;

        /**
         * @brief GetLayers
         * Call this method to get the layers of the layer stack
         * The end of the layer stack is the last layer
         *
         * @return (Type: std::vector<Layer *>::const_iterator) The end of the layer stack
         */
        std::vector<Layer *>::const_iterator end();

        /**
         * @brief GetLayers
         * Call this method to get the layers of the layer stack
         * The begin of the layer stack is the first layer
         *
         * @return (Type: std::vector<Layer *>::const_reverse_iterator) The begin of the layer stack
         */
        std::vector<Layer *>::const_reverse_iterator rbegin() const;

        /**
         * @brief GetLayers
         * Call this method to get the layers of the layer stack
         * The begin of the layer stack is the first layer
         *
         * @return (Type: std::vector<Layer *>::const_reverse_iterator) The begin of the layer stack
         */
        std::vector<Layer *>::const_reverse_iterator rbegin();

        /**
         * @brief GetLayers
         * Call this method to get the layers of the layer stack
         * The end of the layer stack is the last layer
         *
         * @return (Type: std::vector<Layer *>::const_reverse_iterator) The end of the layer stack
         */
        std::vector<Layer *>::const_reverse_iterator rend() const;

        /**
         * @brief GetLayers
         * Call this method to get the layers of the layer stack
         * The end of the layer stack is the last layer
         *
         * @return (Type: std::vector<Layer *>::const_reverse_iterator) The end of the layer stack
         */
        std::vector<Layer *>::const_reverse_iterator rend();

        ////////////////
        // Attributes //
        ////////////////
      private:
        std::vector<Layer *> _Layers;   /*!< The layers of the layer stack */
        unsigned int _LayerInsertIndex; /*!< The iterator of the layer stack */
    };
}; // namespace Exodia

#endif /* !LAYERSTACK_HPP_ */
