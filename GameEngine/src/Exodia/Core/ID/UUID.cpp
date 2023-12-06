/*
** EPITECH PROJECT, 2023
** ExodiaGameEngine
** File description:
** UUID
*/

// Exodia Core includes
#include "UUID.hpp"

namespace Exodia {

    ///////////////////////
    // Static attributes //
    ///////////////////////

    static std::random_device                      _RandomDevice;
    static std::mt19937_64                         _Engine(_RandomDevice());
    static std::uniform_int_distribution<uint64_t> _UniformDistribution;

    //////////////////////////////
    // Constructor & Destructor //
    //////////////////////////////

    UUID::UUID(uint64_t uuid) : _uuid(uuid)
    {
        if (_uuid == 0)
            _uuid = _UniformDistribution(_Engine);
    }

    UUID::UUID(const UUID &uuid) : _uuid(uuid._uuid) {};

    //////////////
    // Operator //
    //////////////

    UUID::operator uint64_t() const
    {
        return _uuid;
    }

    UUID &UUID::operator=(const UUID &uuid)
    {
        _uuid = uuid._uuid;

        return *this;
    }
};
