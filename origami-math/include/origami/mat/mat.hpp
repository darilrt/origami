#pragma once

#include <cstddef>

template <typename T, int N, size_t M>
class Mat
{
public:
    T data[N * M];
};