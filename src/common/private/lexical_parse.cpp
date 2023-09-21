// Distributed under the BSD 2-Clause License - Copyright 2012-2023 Robin Degen

#include <aeon/common/lexical_parse.h>
#include <aeon/common/from_chars.h>
#include <cctype>

namespace aeon::Common::LexicalParse
{

namespace Internal
{

static auto IsPossiblyDouble(const StringView &str) noexcept
{
    for (const auto c : str)
    {
        if (c == 'e' || c == 'E' || c == '.')
            return true;
    }

    return false;
}

} // namespace internal

auto Number(const StringView &str) -> LexicalParseResult
{
    if (Internal::IsPossiblyDouble(str))
    {
        auto value = 0.0;
        auto [ptr, ec] = FromChars(str, value);

        if (ec != std::errc{})
            throw LexicalParseException{};

        return {value, static_cast<std::size_t>(ptr - std::data(str))};
    }

    std::int64_t value = 0;
    auto [ptr, ec] = FromChars(str, value);

    if (ec != std::errc{})
        throw LexicalParseException{};

    return {value, static_cast<std::size_t>(ptr - std::data(str))};
}

auto ExtractNumberString(const StringView &str) noexcept -> StringView
{
    std::size_t endOffset = 0;
    for (const auto c : str)
    {
        if (!std::isdigit(c) && c != 'e' && c != 'E' && c != '.')
            return str.Substr(0, endOffset);

        ++endOffset;
    }

    return {};
}

} // namespace aeon::Common::lexical_parse
