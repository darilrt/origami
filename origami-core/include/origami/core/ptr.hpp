#pragma once

#include <memory>

template <typename T>
using Shared = std::shared_ptr<T>;

template <typename T>
using Weak = std::weak_ptr<T>;

template <typename T, typename... Args>
Shared<T> make_shared(Args &&...args)
{
    return std::make_shared<T>(std::forward<Args>(args)...);
}

template <typename T>
using Unique = std::unique_ptr<T>;

template <typename T, typename... Args>
Unique<T> make_unique(Args &&...args)
{
    return std::make_unique<T>(std::forward<Args>(args)...);
}