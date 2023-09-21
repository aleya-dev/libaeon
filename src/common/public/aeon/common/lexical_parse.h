// Distributed under the BSD 2-Clause License - Copyright 2012-2023 Robin Degen

#pragma once

#include <aeon/common/string.h>
#include <stdexcept>
#include <variant>
#include <cstdint>

namespace aeon::Common::LexicalParse
{

class LexicalParseException : public std::exception
{
};

class LexicalParseResult final
{
public:
    LexicalParseResult(const std::int64_t value, const std::size_t offset) noexcept
        : m_value{value}
        , m_offset{offset}
    {
    }

    LexicalParseResult(const double value, const std::size_t offset) noexcept
        : m_value{value}
        , m_offset{offset}
    {
    }

    ~LexicalParseResult() = default;

    LexicalParseResult(const LexicalParseResult &) = default;
    auto operator=(const LexicalParseResult &) -> LexicalParseResult & = default;

    LexicalParseResult(LexicalParseResult &&) noexcept = default;
    auto operator=(LexicalParseResult &&) noexcept -> LexicalParseResult & = default;

    /*!
     * Get the type of the parsed value. T must be either std::int64_t or double.
     * Returns true of the parsed value is of the given type T.
     */
    template <typename T>
    [[nodiscard]] auto IsType() const noexcept
    {
        return std::holds_alternative<T>(m_value);
    }

    /*!
     * Get the parsed value. T must be either std::int64_t or double.
     * If the parsed value is of a different type, an exception will be thrown.
     */
    template <typename T>
    [[nodiscard]] auto Value() const
    {
        return std::get<T>(m_value);
    }

    /*!
     * Returns true of the parsed value is an integer.
     */
    [[nodiscard]] auto IsInteger() const noexcept
    {
        return IsType<std::int64_t>();
    }

    /*!
     * Returns true of the parsed value is a double.
     */
    [[nodiscard]] auto IsDouble() const noexcept
    {
        return IsType<double>();
    }

    /*!
     * The offset of the first character within the parsed string that was not evaluated
     * as part of the number.
     */
    [[nodiscard]] auto Offset() const noexcept
    {
        return m_offset;
    }

    /*!
     * Get the parsed value. If the parsed value is of a different type, an exception will be thrown.
     */
    [[nodiscard]] auto IntegerValue() const
    {
        return Value<std::int64_t>();
    }

    /*!
     * Get the parsed value. If the parsed value is of a different type, an exception will be thrown.
     */
    [[nodiscard]] auto DoubleValue() const
    {
        return Value<double>();
    }

private:
    std::variant<std::int64_t, double> m_value;
    std::size_t m_offset;
};

/*!
 * Convert a decimal number string to a double or int64. The resulting value depends on the parsed string.
 * For example 123 will be parsed to int64, while 1.23 will be parsed to a double.
 * Scientific notation in the form of 3e2 or 3E2 is also supported and will be parsed to a double.
 *
 * Will throw an exception if no number could be parsed.
 */
auto Number(const StringView &str) -> LexicalParseResult;

/*!
 * Extract a possible number string from a given longer string. The string is split where the first character
 * does not equal 0-9, e, E or .
 *
 * This function can be used as a pre-sanitization for the number function.
 *
 * Examples:
 *     "1234abc" will return "1234"
 *     "1234.123abc" will return "1234.123"
 *     "1234,12" will return "1234"
 */
auto ExtractNumberString(const StringView &str) noexcept -> StringView;

} // namespace aeon::Common::lexical_parse
