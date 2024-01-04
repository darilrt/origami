#pragma once

#include <memory>
#include <functional>
#include <optional>

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
using Optional = std::optional<T>;

template <typename T>
using Function = std::function<T>;

template <typename T>
class Hook
{
    T data;

public:
    std::function<void(const T, const T)> on_change;

    Hook(T val)
    {
        data = val;
    }

    T get()
    {
        return data;
    }

    void operator=(T val)
    {
        if (on_change)
            on_change(data, val);
        data = val;
    }

    operator T()
    {
        return data;
    }
};

template <typename T, typename... Args>
Hook<T> new_hook(Args &&...args)
{
    return Hook<T>(std::forward<Args>(args)...);
}