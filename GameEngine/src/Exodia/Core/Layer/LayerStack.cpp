/*
** EPITECH PROJECT, 2023
** ExodiaGameEngine
** File description:
** LayerStack
*/

// Exodia Core
#include "LayerStack.hpp"

// External includes
#include <algorithm>
#include <sstream>

namespace Exodia {

    //////////////////////////////
    // Constructor & Destructor //
    //////////////////////////////

    LayerStack::LayerStack() : _LayerInsertIndex(0){};

    LayerStack::~LayerStack() {
        // TODO: Put every layer in a smart pointer
        /*for (Layer *layer : _Layers) {
            if (layer)
                delete layer;
        }*/
    }

    /////////////
    // Methods //
    /////////////

    void LayerStack::PushLayer(Layer *layer) {
        _Layers.emplace(_Layers.begin() + _LayerInsertIndex, layer);
        _LayerInsertIndex++;
    }

    void LayerStack::PushOverlay(Layer *overlay) { _Layers.emplace_back(overlay); }

    void LayerStack::PopLayer(Layer *layer) {
        std::vector<Exodia::Layer *>::iterator it = std::find(_Layers.begin(), _Layers.end(), layer);

        // If the layer is found, erase it
        if (it != _Layers.end()) {
            _Layers.erase(it);
            _LayerInsertIndex--;
        }
    }

    void LayerStack::PopOverlay(Layer *overlay) {
        std::vector<Exodia::Layer *>::iterator it = std::find(_Layers.begin(), _Layers.end(), overlay);

        // If the layer is found, erase it
        if (it != _Layers.end())
            _Layers.erase(it);
    }

    //////////////////////
    // Iterator methods //
    //////////////////////

    std::vector<Layer *>::const_iterator LayerStack::begin() const { return _Layers.begin(); }

    std::vector<Layer *>::const_iterator LayerStack::begin() { return _Layers.begin(); }

    std::vector<Layer *>::const_iterator LayerStack::end() const { return _Layers.end(); }

    std::vector<Layer *>::const_iterator LayerStack::end() { return _Layers.end(); }

    std::vector<Layer *>::const_reverse_iterator LayerStack::rbegin() const { return _Layers.rbegin(); }

    std::vector<Layer *>::const_reverse_iterator LayerStack::rbegin() { return _Layers.rbegin(); }

    std::vector<Layer *>::const_reverse_iterator LayerStack::rend() const { return _Layers.rend(); }

    std::vector<Layer *>::const_reverse_iterator LayerStack::rend() { return _Layers.rend(); }
}; // namespace Exodia
