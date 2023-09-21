// Distributed under the BSD 2-Clause License - Copyright 2012-2023 Robin Degen

#pragma once

namespace aeon::Common
{

/*!
 * Base class for thread-safe singletons.
 */
template <class Type>
class Singleton
{
public:
    [[nodiscard]] static auto GetSingleton() -> Type &
    {
        static Type instance;
        return instance;
    }

    [[nodiscard]] static auto GetSingletonPtr() -> Type *
    {
        return &GetSingleton();
    }
};

} // namespace aeon::Common
