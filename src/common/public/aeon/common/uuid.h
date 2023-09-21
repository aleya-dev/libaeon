// Distributed under the BSD 2-Clause License - Copyright 2012-2023 Robin Degen

#pragma once

#include <aeon/common/string.h>
#include <array>
#include <cstdint>
#include <optional>
#include <stdexcept>

namespace aeon::Common
{

class UuidParseException : public std::exception
{
};

/*!
 * UUID class based on boost::uuid.
 */
class Uuid
{
public:
    using value_type = std::uint8_t;
    using DataType = std::array<value_type, 16>;

    enum class VariantType
    {
        VariantNcs,
        VariantRfc4122,
        VariantMicrosoft,
        VariantFuture
    };

    enum class VersionType
    {
        VersionUnknown = -1,
        VersionTimeBased = 1,
        VersionDceSecurity = 2,
        VersionNameBasedMd5 = 3,
        VersionRandomNumberBased = 4,
        VersionNameBasedSha1 = 5
    };

    Uuid() noexcept;
    explicit Uuid(DataType data) noexcept;
    ~Uuid() noexcept;

    Uuid(const Uuid &) noexcept = default;
    auto operator=(const Uuid &) noexcept -> Uuid & = default;

    Uuid(Uuid &&) noexcept = default;
    auto operator=(Uuid &&) noexcept -> Uuid & = default;

    [[nodiscard]] auto begin() noexcept -> DataType::iterator;
    [[nodiscard]] auto begin() const noexcept -> DataType::const_iterator;
    [[nodiscard]] auto end() noexcept -> DataType::iterator;
    [[nodiscard]] auto end() const noexcept -> DataType::const_iterator;

    [[nodiscard]] auto IsNil() const noexcept -> bool;

    [[nodiscard]] auto Variant() const noexcept -> VariantType;

    [[nodiscard]] auto Version() const noexcept -> VersionType;

    [[nodiscard]] auto Str() const -> String;

    [[nodiscard]] auto Size() const noexcept -> std::size_t;

    [[nodiscard]] static auto Generate() noexcept -> Uuid;

    [[nodiscard]] static auto Nil() noexcept -> Uuid;

    [[nodiscard]] static auto Parse(const StringView &str) -> Uuid;
    [[nodiscard]] static auto TryParse(const StringView &str) noexcept -> std::optional<Uuid>;

    [[nodiscard]] operator bool() const noexcept;

    DataType Data;
};

bool operator==(Uuid const &lhs, Uuid const &rhs) noexcept;
bool operator<(Uuid const &lhs, Uuid const &rhs) noexcept;

inline bool operator!=(Uuid const &lhs, Uuid const &rhs) noexcept
{
    return !(lhs == rhs);
}

inline bool operator>(Uuid const &lhs, Uuid const &rhs) noexcept
{
    return rhs < lhs;
}
inline bool operator<=(Uuid const &lhs, Uuid const &rhs) noexcept
{
    return rhs >= lhs;
}

inline bool operator>=(Uuid const &lhs, Uuid const &rhs) noexcept
{
    return !(lhs < rhs);
}

} // namespace aeon::Common
