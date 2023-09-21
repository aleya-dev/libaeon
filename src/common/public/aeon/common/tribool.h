// Distributed under the BSD 2-Clause License - Copyright 2012-2023 Robin Degen

#pragma once

namespace aeon::Common
{

namespace Internal
{

struct Indeterminate
{
};

} // namespace detail

class Tribool;

constexpr auto Indeterminate(const Tribool value, const Internal::Indeterminate dummy = Internal::Indeterminate()) noexcept
    -> bool;
using IndeterminateKeyword = decltype(Indeterminate);

/*!
 * Tribool that can be true, false or indeterminate
 */
class Tribool
{
public:
    enum class Value
    {
        False,
        True,
        Indeterminate
    };

    constexpr Tribool() noexcept
        : Value{Value::False}
    {
    }

    constexpr Tribool(const bool value) noexcept
        : Value{value ? Value::True : Value::False}
    {
    }

    constexpr Tribool(IndeterminateKeyword) noexcept
        : Value{Value::Indeterminate}
    {
    }

    ~Tribool() noexcept = default;

    constexpr Tribool(const Tribool &) noexcept = default;
    constexpr auto operator=(const Tribool &) noexcept -> Tribool & = default;

    constexpr Tribool(Tribool &&) noexcept = default;
    constexpr auto operator=(Tribool &&) noexcept -> Tribool & = default;

    constexpr operator bool() const noexcept
    {
        return Value == Value::True;
    }

    constexpr explicit operator int() const noexcept
    {
        return Value == Value::True ? 1 : 0;
    }

    [[nodiscard]] constexpr auto IsIndeterminate() const noexcept
    {
        return Indeterminate(*this);
    }

    Value Value;
};

constexpr auto Indeterminate(const Tribool value, const Internal::Indeterminate) noexcept -> bool
{
    return value.Value == Tribool::Value::Indeterminate;
}

constexpr auto operator&&(const Tribool lhs, const Tribool rhs) noexcept
{
    if (static_cast<bool>(!lhs) || static_cast<bool>(!rhs))
        return Tribool{false};

    if (static_cast<bool>(lhs) && static_cast<bool>(rhs))
        return Tribool{true};

    return Tribool{Indeterminate};
}

constexpr auto operator&&(const Tribool lhs, const bool rhs) noexcept
{
    return rhs ? lhs : Tribool{false};
}

constexpr auto operator&&(const bool lhs, const Tribool rhs) noexcept
{
    return lhs ? rhs : Tribool{false};
}

constexpr auto operator&&(IndeterminateKeyword, const Tribool rhs) noexcept
{
    return !rhs ? Tribool{false} : Tribool{Indeterminate};
}

constexpr auto operator&&(const Tribool lhs, IndeterminateKeyword) noexcept
{
    return !lhs ? Tribool{false} : Tribool{Indeterminate};
}

constexpr auto operator||(const Tribool lhs, const Tribool rhs) noexcept
{
    if (static_cast<bool>(!lhs) && static_cast<bool>(!rhs))
        return Tribool{false};

    if (static_cast<bool>(lhs) || static_cast<bool>(rhs))
        return Tribool{true};

    return Tribool{Indeterminate};
}

constexpr auto operator||(const Tribool lhs, const bool rhs) noexcept
{
    return rhs ? Tribool{true} : lhs;
}

constexpr auto operator||(const bool lhs, const Tribool rhs) noexcept
{
    return lhs ? Tribool{true} : rhs;
}

constexpr auto operator||(IndeterminateKeyword, const Tribool rhs) noexcept
{
    return rhs ? Tribool{true} : Tribool{Indeterminate};
}

constexpr auto operator||(const Tribool lhs, IndeterminateKeyword) noexcept
{
    return lhs ? Tribool{true} : Tribool{Indeterminate};
}

constexpr auto operator==(const Tribool lhs, const Tribool rhs) noexcept
{
    if (Indeterminate(lhs) || Indeterminate(rhs))
        return false;

    return static_cast<bool>((lhs && rhs) || (!lhs && !rhs));
}

constexpr auto operator==(const Tribool lhs, const bool rhs) noexcept
{
    return lhs == Tribool{rhs};
}

constexpr auto operator==(const bool lhs, const Tribool rhs) noexcept
{
    return Tribool{lhs} == rhs;
}

constexpr auto operator==(IndeterminateKeyword, const Tribool rhs) noexcept
{
    return Tribool{Indeterminate} == rhs;
}

constexpr auto operator==(const Tribool lhs, IndeterminateKeyword) noexcept
{
    return Tribool{Indeterminate} == lhs;
}

constexpr auto operator!=(const Tribool lhs, const Tribool rhs) noexcept
{
    if (Indeterminate(lhs) || Indeterminate(rhs))
        return true;

    return !((lhs && rhs) || (!lhs && !rhs));
}

constexpr auto operator!=(const Tribool lhs, const bool rhs) noexcept
{
    return lhs != Tribool{rhs};
}

constexpr auto operator!=(const bool lhs, const Tribool rhs) noexcept
{
    return Tribool{lhs} != rhs;
}

constexpr auto operator!=(IndeterminateKeyword, const Tribool rhs) noexcept
{
    return Tribool{Indeterminate} != rhs;
}

constexpr auto operator!=(const Tribool lhs, IndeterminateKeyword) noexcept
{
    return lhs != Tribool{Indeterminate};
}

} // namespace aeon::Common
