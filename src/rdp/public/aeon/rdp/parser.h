// Distributed under the BSD 2-Clause License - Copyright 2012-2023 Robin Degen

#pragma once

#include <aeon/common/string_view.h>
#include <initializer_list>
#include <regex>

namespace aeon::rdp
{

class cursor;

template <typename ResultT>
class parse_result;

enum class eof_mode
{
    match, // When eof is reached, still match the currently taken characters
    fail   // When eof is reached, fail the match
};

/*!
 * Recursive-Descent-Parsing (RDP).
 * This class contains helper methods (matches and skippers) to aid with implementing RDP.
 * The internal iterator is only moved when a match or check succeeds.
 *
 * Function and method naming scheme:
 * check_* - Check if a certain character is matched. Returns true or false.
 * match_* - Match 1 or more characters. Returns a parse_result with the result
 * skip_*  - Skip a certain character or characters.
 * parse_* - The same as match, however the result is parsed into a pod type (for example parse_hex
 *           would parse to an integer)
 */
class parser
{
    friend class scoped_state;

public:
    using char_type = common::string_view::value_type;
    using size_type = common::string_view::size_type;
    using difference_type = common::string_view::difference_type;
    using iterator = common::string_view::const_iterator;

    explicit parser(const common::string_view &v);
    explicit parser(const common::string_view &v, const common::string_view filename);

    template <std::contiguous_iterator iterator_t>
    explicit parser(iterator_t begin, iterator_t end);

    ~parser() = default;

    parser(const parser &) noexcept = default;
    auto operator=(const parser &) noexcept -> parser & = default;

    parser(parser &&) noexcept = default;
    auto operator=(parser &&) noexcept -> parser & = default;

    /*!
     * Check if the index is at the end of the given string ("end of file").
     * \return True on eof
     */
    [[nodiscard]] auto eof() const noexcept -> bool;

    /*!
     * Check if the index is at the beginning of the given string ("beginning of file").
     * \return True on bof
     */
    [[nodiscard]] auto bof() const noexcept -> bool;

    /*!
     * Return a view on the internal string that is being parsed
     */
    [[nodiscard]] auto str() const noexcept -> const common::string_view &;

    /*!
     * Advance to the next character
     * \return True if possible, false on eof
     */
    auto advance() noexcept -> bool;

    /*!
     * Advance a certain amount of characters
     * \return True if possible, false on eof
     */
    auto advance(const size_type count) noexcept -> bool;

    /*!
     * Advance to the end of the input string. This will make eof() return true.
     */
    void advance_to_end() noexcept;

    /*!
     * Reverse to the previous character
     * \return True if possible, false if the beginning is reached
     */
    auto reverse() noexcept -> bool;

    /*!
     * Get the character at the current position. Calling this when eof() is true results in undefined behavior.
     * \return Returns the current character.
     */
    [[nodiscard]] auto current() const noexcept -> char_type;

    /*!
     * Get the iterator to the character at the current position. Calling this when eof() is true results in undefined
     * behavior. \return Returns an iterator to the current character.
     */
    [[nodiscard]] auto current_iterator() const noexcept -> iterator;

    /*!
     * Get the character at the current position. Calling this when eof() is true results in undefined behavior.
     * \return Returns the current character.
     */
    [[nodiscard]] auto operator*() const noexcept -> char_type;

    /*!
     * Get the current parse offset index.
     * \return The current parse offset index.
     */
    [[nodiscard]] auto offset() const noexcept -> size_type;

    /*!
     * Get the size of the input string
     * \return The size of the input string
     */
    [[nodiscard]] auto size() const noexcept -> size_type;

    /*!
     * Get the remaining size of the input string
     * \return The remaining size of the input string
     */
    [[nodiscard]] auto remaining_size() const noexcept -> size_type;

    /*!
     * Get the cursor information of the current offset. The cursor contains the current line, the line number and
     * column. This class can help in forming user-friendly error messages. \return A cursor class containing
     * information of the current offset.
     */
    [[nodiscard]] auto cursor() const noexcept -> rdp::cursor;

    /*!
     * Get the filename of the current object being parsed (if set during construction).
     * This can help in forming user-friendly error messages.
     * \return A filename, if set.
     */
    [[nodiscard]] auto filename() const noexcept -> common::string_view;

    /*!
     * Get a range of characters based on given indices.
     * \return The string in the given range indices of characters. Returns error if the indices are out of range.
     */
    [[nodiscard]] auto get_range(const size_type begin, const size_type end) const noexcept
        -> parse_result<common::string_view>;

    /*!
     * Peek ahead to see if a certain string is at the current position. Unlike check(), it does not move the cursor.
     * In order to peek a single character, you should use the current() method.
     */
    [[nodiscard]] auto peek(const common::string_view str) noexcept -> bool;

    /*!
     * Check if a certain character is at the current position. Moves the internal index 1 if matched.
     * \return True if character is at current position
     */
    [[nodiscard]] auto check(const char_type c) noexcept -> bool;

    /*!
     * Check if a certain string is at the current position. Moves the internal index by the length
     * of the given string if matched.
     * \return True if character is at current position
     */
    [[nodiscard]] auto check(const common::string_view str) noexcept -> bool;

    /*!
     * Check if one of the given characters are the current position. Moves the internal index 1 if matched.
     * \return True if one of the given characters are at current position
     */
    [[nodiscard]] auto check(const std::initializer_list<char_type> c) noexcept -> bool;

    /*!
     * Skip all occurrences of a certain character and move the internal index to the first character
     * that does not match the given one.
     */
    void skip(const char_type c) noexcept;

    /*!
     * Skip all occurrences of the given characters and move the internal index to the first character
     * that does not match the given ones.
     */
    void skip(const std::initializer_list<char_type> c) noexcept;

    /*!
     * Skip all characters that are not the given character and move the internal index to right after the first
     * character that matches the given one.
     */
    void skip_until(const char_type c) noexcept;

    /*!
     * Skip all characters that are not the given characters and move the internal index to right after the first
     * character that matches the given ones.
     */
    void skip_until(const std::initializer_list<char_type> c) noexcept;

    /*!
     * Match each of the given characters. The match ends at the first character that isn't in the given list.
     */
    [[nodiscard]] auto match_each(const std::initializer_list<char_type> c) noexcept
        -> parse_result<common::string_view>;

    /*!
     * Match with a matcher.
     *
     * The matcher's signature is: auto pred(const char_type c) noexcept -> bool
     */
    template <typename matcher_t>
    [[nodiscard]] auto match(matcher_t pred) noexcept -> parse_result<common::string_view>;

    /*!
     * Match with a matcher. The second argument given to the predicate is the index of the matched character.
     * This allows for example for matching on C/C++ variable names that can't start with a number or certain
     * characters.
     *
     * The matcher's signature is: auto pred(const char_type c, const size_type index) noexcept -> bool
     */
    template <typename matcher_t>
    [[nodiscard]] auto match_indexed(matcher_t pred) noexcept -> parse_result<common::string_view>;

    /*!
     * Match any character until the given character. The result will not contain the given end character.
     * If eof is reached before the given character is found, unmatched will be returned.
     */
    [[nodiscard]] auto match_until(const char_type c, const eof_mode mode = eof_mode::fail) noexcept
        -> parse_result<common::string_view>;

    /*!
     * Match any character until the given string. The result will not contain the given end string.
     * If eof is reached before the given string is found, unmatched will be returned.
     */
    [[nodiscard]] auto match_until(const common::string_view str) noexcept -> parse_result<common::string_view>;

    /*!
     * Match any character until the given characters. The result will not contain the given end characters.
     * If eof is reached before the given characters are found, unmatched will be returned.
     */
    [[nodiscard]] auto match_until(const std::initializer_list<char_type> c,
                                   const eof_mode mode = eof_mode::fail) noexcept -> parse_result<common::string_view>;

private:
    common::string_view view_;
    iterator current_;
    common::string_view filename_;
};

auto eof(const parser &parser) noexcept -> bool;

auto bof(const parser &parser) noexcept -> bool;

auto current(const parser &parser) noexcept -> parser::char_type;

auto offset(const rdp::parser &parser) noexcept -> parser::size_type;

auto filename(const rdp::parser &parser) noexcept -> common::string_view;

} // namespace aeon::rdp

#include <aeon/rdp/impl/parser_impl.h>
