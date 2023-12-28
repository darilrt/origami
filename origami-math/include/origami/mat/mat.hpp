#pragma once

template <typename T, int N, size_t M>
class Mat
{
public:
    T data[N * M];
};