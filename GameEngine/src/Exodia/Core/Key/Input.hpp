/*
** EPITECH PROJECT, 2023
** ExodiaGameEngine
** File description:
** Input
*/

#ifndef INPUT_HPP_
    #define INPUT_HPP_

    // Exodia Utils
    #include "Utils/CrossPlatform.hpp"

    // Exodia Key
    #include "Core/Key/KeyCodes.hpp"

    // External includes
    #include <utility>
    #include <glm/glm.hpp>

namespace Exodia {

    /**
     * @brief Input class, that can't be instanciated
     * This class is used to get input from the user
     */
    class EXODIA_API Input {

        ///////////////////////
        // Getters & Setters //
        ///////////////////////
        public:

            /**
             * @brief Check if a key is pressed
             * Call this function to check if a key is pressed
             *
             * @param keycode (Type: int)  The key code
             * @return        (Type: bool) true if the key is pressed or repeated, false otherwise
             */
            static bool IsKeyPressed(int keycode);

            static bool IsKeyReleased(int keycode = Exodia::Key::Unknown);

            /**
             * @brief Check if a mouse button is pressed
             * Call this function to check if a mouse button is pressed
             *
             * @param button (Type: int)  The mouse button
             * @return       (Type: bool) true if the mouse button is pressed, false otherwise
             */
            static bool IsMouseButtonPressed(int button);

            /**
             * @brief Get the mouse position
             * Call this function to get the mouse position
             *
             * @return (Type: glm::vec2) The mouse position
             */
            static glm::vec2 GetMousePosition();

            /**
             * @brief Get the mouse X position
             * Call this function to get the mouse X position
             *
             * @return (Type: float) The mouse X position
             */
            static float GetMouseX();

            /**
             * @brief Get the mouse Y position
             * Call this function to get the mouse Y position
             *
             * @return (Type: float) The mouse Y position
             */
            static float GetMouseY();
    };
};

#endif /* !INPUT_HPP_ */
