// Distributed under the BSD 2-Clause License - Copyright 2012-2023 Robin Degen

#include <aeon/common/uuid.h>
#include <aeon/common/literals.h>
#include <algorithm>
#include <random>
#include <stdexcept>
#include <cstring>

namespace aeon::Common
{

namespace Internal
{

[[nodiscard]] static auto ToChar(const size_t i) noexcept
{
    if (i <= 9)
        return static_cast<char>('0' + i);

    return static_cast<char>('a' + (i - 10));
}

[[nodiscard]] static auto GetNextChar(StringView::const_iterator &begin, StringView::const_iterator &end,
                                        char &c) noexcept
{
    if (begin == end)
        return false;

    c = *begin++;
    return true;
}

[[nodiscard]] static auto IsOpenBrace(const char c) noexcept
{
    return (c == '{');
}

[[nodiscard]] static auto IsDash(const char c) noexcept
{
    return c == '-';
}

[[nodiscard]] static auto GetValue(const char c) noexcept
{
    static char const *const DigitsBegin = "0123456789abcdefABCDEF";
    static char const *const DigitsEnd = DigitsBegin + 22;

    static constexpr unsigned char values[] = {
        0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 10, 11, 12, 13, 14, 15, static_cast<unsigned char>(-1)};

    char const *d = std::find(DigitsBegin, DigitsEnd, c);
    return values[d - DigitsBegin];
}

[[nodiscard]] static auto CheckCloseBrace(const char c, const char openBrace) noexcept -> bool
{
    return openBrace == '{' && c == '}';
}

[[nodiscard]] auto ToString(const Uuid::DataType &data) -> String
{
    String result;
    result.Reserve(36);

    auto i = 0_size_t;
    for (const auto val : data)
    {
        const size_t hi = (val >> 4) & 0x0F;
        result += Internal::ToChar(hi);

        const size_t lo = val & 0x0F;
        result += Internal::ToChar(lo);

        if (i == 3 || i == 5 || i == 7 || i == 9)
        {
            result += '-';
        }

        ++i;
    }
    return result;
}

} // namespace detail

Uuid::Uuid() noexcept
    : Data{}
{
    std::ranges::fill(Data, 0_uint8_t);
}

Uuid::Uuid(DataType data) noexcept
    : Data{data}
{
}

Uuid::~Uuid() noexcept = default;

[[nodiscard]] auto Uuid::begin() noexcept -> DataType::iterator
{
    return Data.begin();
}

[[nodiscard]] auto Uuid::begin() const noexcept -> DataType::const_iterator
{
    return Data.cbegin();
}

[[nodiscard]] auto Uuid::end() noexcept -> DataType::iterator
{
    return Data.end();
}

[[nodiscard]] auto Uuid::end() const noexcept -> DataType::const_iterator
{
    return Data.cend();
}

[[nodiscard]] auto Uuid::IsNil() const noexcept -> bool
{
    for (auto i : Data)
    {
        if (i != 0)
            return false;
    }
    return true;
}

[[nodiscard]] auto Uuid::Variant() const noexcept -> VariantType
{
    // variant is stored in octet 7
    // which is index 8, since indexes count backwards
    const auto octet7 = Data[8]; // octet 7 is array index 8
    if ((octet7 & 0x80) == 0x00)
    { // 0b0xxxxxxx
        return VariantType::VariantNcs;
    }
    else if ((octet7 & 0xC0) == 0x80)
    { // 0b10xxxxxx
        return VariantType::VariantRfc4122;
    }
    else if ((octet7 & 0xE0) == 0xC0)
    { // 0b110xxxxx
        return VariantType::VariantMicrosoft;
    }
    else
    {
        return VariantType::VariantFuture;
    }
}

[[nodiscard]] auto Uuid::Version() const noexcept -> VersionType
{
    // version is stored in octet 9
    // which is index 6, since indexes count backwards
    const auto octet9 = Data[6];
    if ((octet9 & 0xF0) == 0x10)
    {
        return VersionType::VersionTimeBased;
    }
    else if ((octet9 & 0xF0) == 0x20)
    {
        return VersionType::VersionDceSecurity;
    }
    else if ((octet9 & 0xF0) == 0x30)
    {
        return VersionType::VersionNameBasedMd5;
    }
    else if ((octet9 & 0xF0) == 0x40)
    {
        return VersionType::VersionRandomNumberBased;
    }
    else if ((octet9 & 0xF0) == 0x50)
    {
        return VersionType::VersionNameBasedSha1;
    }
    else
    {
        return VersionType::VersionUnknown;
    }
}

[[nodiscard]] auto Uuid::Str() const -> String
{
    return Internal::ToString(Data);
}

[[nodiscard]] auto Uuid::Size() const noexcept -> std::size_t
{
    return Data.size();
}

[[nodiscard]] auto Uuid::Generate() noexcept -> Uuid
{
    std::random_device r;
    std::default_random_engine e1(r());
    std::uniform_int_distribution<unsigned long> uniformDist;

    Uuid u;

    int i = 0;
    auto randomValue = uniformDist(e1);
    for (auto &val : u.Data)
    {
        if (i == sizeof(unsigned long))
        {
            randomValue = uniformDist(e1);
            i = 0;
        }

        val = static_cast<Uuid::value_type>((randomValue >> (i * 8)) & 0xFF);
        ++i;
    }

    // set variant
    // must be 0b10xxxxxx
    *(u.begin() + 8) &= 0xBF;
    *(u.begin() + 8) |= 0x80;

    // set version
    // must be 0b0100xxxx
    *(u.begin() + 6) &= 0x4F; // 0b01001111
    *(u.begin() + 6) |= 0x40; // 0b01000000

    return u;
}

[[nodiscard]] auto Uuid::Nil() noexcept -> Uuid
{
    return {};
}

auto Uuid::Parse(const StringView &str) -> Uuid
{
    const auto result = TryParse(str);

    if (!result)
        throw UuidParseException{};

    return *result;
}

auto Uuid::TryParse(const StringView &str) noexcept -> std::optional<Uuid>
{
    auto begin = str.begin();
    auto end = str.end();

    char c;

    // check open brace
    if (!Internal::GetNextChar(begin, end, c))
        return std::nullopt;

    const bool hasOpenBrace = Internal::IsOpenBrace(c);
    const auto openBraceChar = c;

    if (hasOpenBrace)
    {
        if (!Internal::GetNextChar(begin, end, c))
            return std::nullopt;
    }

    bool hasDashes = false;

    int i = 0;
    DataType data;

    for (auto &val : data)
    {
        if (i != 0)
        {
            if (!Internal::GetNextChar(begin, end, c))
                return std::nullopt;
        }

        if (i == 4)
        {
            hasDashes = Internal::IsDash(c);
            if (hasDashes)
            {
                if (!Internal::GetNextChar(begin, end, c))
                    return std::nullopt;
            }
        }

        if (hasDashes)
        {
            if (i == 6 || i == 8 || i == 10)
            {
                if (Internal::IsDash(c))
                {
                    if (!Internal::GetNextChar(begin, end, c))
                        return std::nullopt;
                }
                else
                {
                    return std::nullopt;
                }
            }
        }

        val = Internal::GetValue(c);

        if (!Internal::GetNextChar(begin, end, c))
            return std::nullopt;

        val <<= 4;
        val |= Internal::GetValue(c);
        ++i;
    }

    // check close brace
    if (hasOpenBrace)
    {
        if (!Internal::GetNextChar(begin, end, c))
            return std::nullopt;

        if (!Internal::CheckCloseBrace(c, openBraceChar))
            return std::nullopt;
    }

    return Uuid{data};
}

Uuid::operator bool() const noexcept
{
    return !IsNil();
}

bool operator==(Uuid const &lhs, Uuid const &rhs) noexcept
{
    return std::equal(lhs.begin(), lhs.end(), rhs.begin());
}

bool operator<(Uuid const &lhs, Uuid const &rhs) noexcept
{
    return std::memcmp(lhs.Data.data(), rhs.Data.data(), lhs.Data.size()) < 0;
}
} // namespace aeon::Common
