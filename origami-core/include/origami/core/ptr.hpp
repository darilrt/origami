#pragma once

#include <memory>
#include <functional>

template <typename T>
using Shared = std::shared_ptr<T>;

template <typename T>
using Weak = std::weak_ptr<T>;

template <typename T, typename... Args>
inline Shared<T> new_shared(Args &&...args)
{
    return std::make_shared<T>(std::forward<Args>(args)...);
}

template <typename T>
using Unique = std::unique_ptr<T>;

template <typename T, typename... Args>
inline Unique<T> new_unique(Args &&...args)
{
    return std::make_unique<T>(std::forward<Args>(args)...);
}

template <typename T>
class Hook
{
    T data;

public:
    std::function<void(T, T)> on_change;

    Hook(T val)
    {
        data = val;
    }

    T get()
    {
        data;
    }

    operator=(T val)
    {
        on_change(data, val);
        data = val;
        return *this;
    }

    operator T()
    {
        return data;
    }
};