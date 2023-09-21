// Distributed under the BSD 2-Clause License - Copyright 2012-2023 Robin Degen

#pragma once

#include <aeon/common/bits.h>
#include <aeon/common/concepts.h>
#include <type_traits>
#include <cstdint>

namespace aeon::Common
{

template <typename UnderlyingTypeT>
class Flag
{
public:
    using UnderlyingType = UnderlyingTypeT;

    constexpr Flag(const std::int16_t ai) noexcept
        : Value{static_cast<UnderlyingType>(ai)}
    {
    }

    constexpr Flag(const std::uint16_t ai) noexcept
        : Value{static_cast<UnderlyingType>(ai)}
    {
    }

    constexpr Flag(const std::int32_t ai) noexcept
        : Value{static_cast<UnderlyingType>(ai)}
    {
    }

    constexpr Flag(const std::uint32_t ai) noexcept
        : Value{static_cast<UnderlyingType>(ai)}
    {
    }

    constexpr Flag(const std::int64_t ai) noexcept
        : Value{static_cast<UnderlyingType>(ai)}
    {
    }

    constexpr Flag(const std::uint64_t ai) noexcept
        : Value{static_cast<UnderlyingType>(ai)}
    {
    }

    constexpr operator UnderlyingType() const noexcept
    {
        return Value;
    }

    UnderlyingType Value;
};

template <Concepts::UnsignedEnumerable enum_type_t>
class Flags
{
public:
    using EnumType = enum_type_t;
    using UnderlyingType = std::underlying_type_t<enum_type_t>;

    constexpr Flags() noexcept
        : Value{}
    {
    }

    constexpr Flags(const EnumType value) noexcept
        : Value{static_cast<UnderlyingType>(value)}
    {
    }

    constexpr Flags(const Flag<UnderlyingType> value) noexcept
        : Value{value}
    {
    }

    constexpr Flags(const Flags<EnumType> &) noexcept = default;
    constexpr auto operator=(const Flags<EnumType> &) noexcept -> Flags<EnumType> & = default;

    constexpr Flags(Flags<EnumType> &&) noexcept = default;
    constexpr auto operator=(Flags<EnumType> &&) noexcept -> Flags<EnumType> & = default;

    ~Flags() = default;

    constexpr auto &operator&=(const UnderlyingType mask) noexcept
    {
        Value &= mask;
        return *this;
    }

    constexpr auto &operator&=(const EnumType mask) noexcept
    {
        Value &= static_cast<UnderlyingType>(mask);
        return *this;
    }

    constexpr auto &operator|=(const Flags<EnumType> f) noexcept
    {
        Value |= f.Value;
        return *this;
    }

    constexpr auto &operator|=(const EnumType f) noexcept
    {
        Value |= static_cast<UnderlyingType>(f);
        return *this;
    }

    constexpr auto &operator^=(const Flags<EnumType> f) noexcept
    {
        Value ^= f.Value;
        return *this;
    }

    constexpr auto &operator^=(const EnumType f) noexcept
    {
        Value ^= static_cast<UnderlyingType>(f);
        return *this;
    }

    constexpr operator UnderlyingType() const noexcept
    {
        return Value;
    }

    constexpr auto operator|(const Flags<EnumType> f) const noexcept
    {
        return Flags<EnumType>{Flag<UnderlyingType>{Value | f.Value}};
    }

    constexpr auto operator|(const EnumType f) const noexcept
    {
        return Flags<EnumType>{Flag<UnderlyingType>{Value | static_cast<UnderlyingType>(f)}};
    }

    constexpr auto operator^(const Flags<EnumType> f) const noexcept
    {
        return Flags<EnumType>{Flag<UnderlyingType>{Value ^ f.Value}};
    }

    constexpr auto operator^(const EnumType f) const noexcept
    {
        return Flags<EnumType>{Flag<UnderlyingType>{Value ^ static_cast<UnderlyingType>(f)}};
    }

    constexpr auto operator&(const UnderlyingType mask) const noexcept
    {
        return Flags<EnumType>{Flag<UnderlyingType>{Value & mask}};
    }

    constexpr auto operator&(const EnumType f) const noexcept
    {
        return Flags<EnumType>{Flag<UnderlyingType>{Value & static_cast<UnderlyingType>(f)}};
    }

    constexpr auto operator~() const noexcept
    {
        return flags<EnumType>(Flag<UnderlyingType>{~Value});
    }

    constexpr auto operator!() const noexcept
    {
        return !Value;
    }

    constexpr auto operator==(const Flags<EnumType> f) const noexcept
    {
        return Value == f.Value;
    }

    constexpr auto operator!=(const Flags<EnumType> f) const noexcept
    {
        return Value != f.Value;
    }

    constexpr auto operator==(const UnderlyingType mask) const noexcept
    {
        return Value == mask;
    }

    constexpr auto operator!=(const UnderlyingType mask) const noexcept
    {
        return Value != mask;
    }

    [[nodiscard]] constexpr auto IsSet(const EnumType f) const noexcept
    {
        const auto newValue = static_cast<UnderlyingType>(f);
        return Bits::CheckFlag(Value, newValue) && newValue != 0;
    }

    constexpr void Set(const EnumType f) noexcept
    {
        Value |= static_cast<UnderlyingType>(f);
    }

    constexpr void Set(const EnumType f, const bool condition) noexcept
    {
        if (condition)
            Set(f);
        else
            Unset(f);
    }

    constexpr void Unset(const EnumType f) noexcept
    {
        Value &= ~static_cast<UnderlyingType>(f);
    }

    constexpr void ConditionalSet(const bool condition, const EnumType f) noexcept
    {
        if (condition)
            set(f);
    }

    constexpr void ConditionalUnset(const bool condition, const EnumType f) noexcept
    {
        if (condition)
            unset(f);
    }

    constexpr void ForceSet(const UnderlyingType v) noexcept
    {
        Value = v;
    }

    UnderlyingType Value;
};

#define AeonDeclareFlagOperators(f)                                                                                 \
    inline constexpr auto operator|(const f lhs, const f rhs) noexcept -> aeon::Common::Flags<f>                       \
    {                                                                                                                  \
        return aeon::Common::Flags<f>(lhs) | rhs;                                                                      \
    }

} // namespace aeon::Common
