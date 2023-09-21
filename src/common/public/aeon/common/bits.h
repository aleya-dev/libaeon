// Distributed under the BSD 2-Clause License - Copyright 2012-2023 Robin Degen

#pragma once

#include <cstdint>
#include <limits>
#include <array>

namespace aeon::Common::Bits
{

template <typename T>
[[nodiscard]] inline static constexpr auto Get(const T val, const unsigned int bit) noexcept
{
    return ((val & (1 << bit)) >> bit);
}

template <typename T>
[[nodiscard]] inline static constexpr auto GetRange(const T val, const unsigned int offset,
                                                     const unsigned int length) noexcept
{
    return ((val & (((1 << length) - 1) << offset)) >> offset);
}

template <typename T>
inline static constexpr void Set(T &val, const unsigned int bit) noexcept
{
    val |= (1 << bit);
}

template <typename T>
inline static constexpr void Clear(T &val, const unsigned int bit) noexcept
{
    val &= (val & ~(1 << bit));
}

template <typename T>
inline static constexpr void SetFlag(T &val, const T flag) noexcept
{
    val |= flag;
}

template <typename T>
inline static constexpr void ClearFlag(T &val, const T flag) noexcept
{
    val &= (val & (~flag));
}

template <typename T, typename U>
[[nodiscard]] inline static constexpr auto CheckFlag(const T value, const U flag) noexcept
{
    return (value & flag) == flag;
}

[[nodiscard]] inline static constexpr auto LowNibble(const unsigned char value) noexcept
{
    return static_cast<unsigned char>(value & 0x0F);
}

[[nodiscard]] inline static constexpr auto HighNibble(const unsigned char value) noexcept
{
    return static_cast<unsigned char>((value & 0xF0) >> 4);
}

template <typename T, typename U>
[[nodiscard]] inline static constexpr auto Mask(const U value) noexcept
{
    return static_cast<T>(value & std::numeric_limits<T>::max());
}

template <typename T>
[[nodiscard]] inline static constexpr auto MaskU8(const T value) noexcept
{
    return Mask<std::uint8_t>(value);
}

template <typename T>
[[nodiscard]] inline static constexpr auto MaskU16(const T value) noexcept
{
    return Mask<std::uint16_t>(value);
}

template <typename T>
[[nodiscard]] inline static constexpr auto MaskU32(const T value) noexcept
{
    return Mask<std::uint32_t>(value);
}

template <typename T>
[[nodiscard]] inline static constexpr auto MaskU64(const T value) noexcept
{
    return Mask<std::uint64_t>(value);
}

inline static constexpr void Unpack32(const std::uint32_t value, std::uint8_t *dest) noexcept
{
    dest[3] = static_cast<std::uint8_t>((value));
    dest[2] = static_cast<std::uint8_t>((value) >> 8);
    dest[1] = static_cast<std::uint8_t>((value) >> 16);
    dest[0] = static_cast<std::uint8_t>((value) >> 24);
}

inline static constexpr auto Unpack32(const std::uint32_t value) noexcept
{
    std::array<std::uint8_t, 4> result{};
    Unpack32(value, std::data(result));
    return result;
}

[[nodiscard]] inline static constexpr auto Pack32(const std::uint8_t *value) noexcept -> std::uint32_t
{
    return static_cast<std::uint32_t>(value[3]) | static_cast<std::uint32_t>(value[2]) << 8 |
           static_cast<std::uint32_t>(value[1]) << 16 | static_cast<std::uint32_t>(value[0]) << 24;
}

template <typename T, typename U>
[[nodiscard]] inline static constexpr auto Rol(const T value, const U count) noexcept
{
    return ((value << count) | (value >> (sizeof(T) * 8 - count)));
}

template <typename T, typename U>
[[nodiscard]] inline static constexpr auto Ror(const T value, const U count) noexcept
{
    return ((value >> count) | (value << (sizeof(T) * 8 - count)));
}

} // namespace aeon::Common::bits
