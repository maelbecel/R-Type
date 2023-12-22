/*
** EPITECH PROJECT, 2023
** ExodiaGameEngine
** File description:
** ImGUILayer
*/

#ifndef IMGUILAYER_HPP_
    #define IMGUILAYER_HPP_

    // Exodia Events
    #include "Events/MouseEvent.hpp"
    #include "Events/KeyEvent.hpp"
    #include "Events/ApplicationEvent.hpp"

    // Exodia Core
    #include "Core/Layer/Layer.hpp"

namespace Exodia {

    /**
     * @brief The ImGUILayer class represents a layer that integrates ImGui for GUI rendering.
     * It provides methods to manage ImGui's initialization, rendering, and cleanup within a layer.
     */
    class ImGuiLayer : public Layer {

        //////////////////////////////
        // Constructor & Destructor //
        //////////////////////////////
        public:

            /**
             * @brief Construct a new ImGui Layer object
             */
            ImGuiLayer();

            /**
             * @brief Destroy the ImGui Layer object
             */
            ~ImGuiLayer() = default;

        /////////////
        // Methods //
        /////////////
        public:

            /**
             * @brief Called when the layer is attached to the application.
             * It initializes ImGui and sets up platform/renderer bindings.
             */
            virtual void OnAttach() override;

            /**
             * @brief Called when the layer is detached from the application.
             * It shuts down ImGui and releases related resources.
             */
            virtual void OnDetach() override;

            /**
             * @brief Called when the layer is updated.
             *
             * @param event The event that triggered the update.
             */
            virtual void OnEvent(Event &event) override;

            /**
             * @brief Begin ImGui rendering. This function should be called before rendering ImGui elements.
             */
            void Begin();

            /**
             * @brief End ImGui rendering. This function should be called after rendering ImGui elements.
             */
            void End();

        ///////////////////////
        // Setters & Getters //
        ///////////////////////
        public:

            /**
             * @brief Set whether ImGui should block events or not.
             *
             * @param block (Type: bool) Whether ImGui should block events or not.
             */
            void SetBlockEvents(bool block);

            void SetDarkThemeColors();

            uint32_t GetActiveWidgetID() const;

        ////////////////
        // Attributes //
        ////////////////
        private:
            bool  _BlockEvents; /*!< Whether ImGui should block events or not */
            float _Time;        /*!< Time, that will be used to render the ImGui window */
    };
};

#endif /* !IMGUILAYER_HPP_ */
