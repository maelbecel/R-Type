/*
** EPITECH PROJECT, 2023
** R-Type [WSL: Ubuntu]
** File description:
** IOContextManager
*/

// IOContextManager.hpp
#ifndef IO_CONTEXT_MANAGER_HPP
    #define IO_CONTEXT_MANAGER_HPP

#include <boost/asio.hpp>

namespace Exodia {

    namespace Network {

    class IOContextManager {
        public:

            /**
             * @brief Construct a new IOContextManager object and initialize the io_context_
             *
             */
            IOContextManager() : io_context_() {}

            ~IOContextManager()
            {
                if (isRunning_)
                    io_context_.stop();
            };

            /**
             * @brief Getter for the io_context_
             *
             * @return boost::asio::io_context&
             */
            boost::asio::io_context& getIOContext() {
                return io_context_;
            }

            /**
             * @brief Run the io_context_
             *
             */
            void run() {
                isRunning_ = true;
                io_context_.run();
            }

            /**
             * @brief Stop the io_context_
             *
             */
            void stop() {
                isRunning_ = false;
                io_context_.stop();
            }

        private:
            boost::asio::io_context io_context_;
            bool isRunning_;
        };
    } // namespace Network
} // namespace Exodia

#endif // IO_CONTEXT_MANAGER_HPP

