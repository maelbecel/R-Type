/*
** EPITECH PROJECT, 2023
** ExodiaGameEngine
** File description:
** UUID
*/

#ifndef UUID_HPP_
    #define UUID_HPP_

    // External includes
    #include <unordered_map>
    #include <random>

namespace Exodia {

    class UUID {

        //////////////////////////////
        // Constructor & Destructor //
        //////////////////////////////
        public:

            UUID(uint64_t uuid = 0);
            UUID(const UUID &uuid);
            ~UUID() = default;

        //////////////
        // Operator //
        //////////////
        public:

            operator uint64_t() const;
            UUID &operator=(const UUID &uuid);

        ////////////////
        // Attributes //
        ////////////////
        private:
            uint64_t _uuid; /*!< The UUID */
    };
};

namespace std {
    template<typename T>
    struct hash;

    template<>
    struct hash<Exodia::UUID> {
        size_t operator()(const Exodia::UUID &uuid) const
        {
            return static_cast<uint64_t>(uuid);
        }
    };
}

#endif /* !UUID_HPP_ */
