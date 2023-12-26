#pragma once

#include <cstddef>

typedef size_t typeid_t;

class TypeIDCounter
{
public:
    static size_t value;
};

template <typename T>
class TypeID
{
public:
    inline static size_t value()
    {
        static size_t id = TypeIDCounter::value++;
        return id;
    }
};