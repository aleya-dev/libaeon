// Distributed under the BSD 2-Clause License - Copyright 2012-2023 Robin Degen

#pragma once

#include <aeon/common/string_view.h>

namespace aeon::rdp
{

/*!
 * Class that contains information about the current parser position (line, line number and column).
 * This can be used to display informational messages to the user (ie. displaying parse errors in a user friendly way).
 */
class cursor final
{
    friend class parser;

public:
    ;
    using char_type = parser::char_type;
    using size_type = parser::size_type;
    using difference_type = parser::difference_type;

    ~cursor() = default;

    cursor(const cursor &) noexcept = default;
    auto operator=(const cursor &) noexcept -> cursor & = default;

    cursor(cursor &&) noexcept = default;
    auto operator=(cursor &&) noexcept -> cursor & = default;

    [[nodiscard]] auto filename() const noexcept -> Common::StringView;
    [[nodiscard]] auto line() const noexcept -> Common::StringView;
    [[nodiscard]] auto line_number() const noexcept -> size_type;
    [[nodiscard]] auto column() const noexcept -> size_type;

private:
    explicit cursor(const Common::StringView filename, const Common::StringView line, const difference_type line_number,
                    const difference_type column) noexcept;

    Common::StringView filename_;
    Common::StringView line_;
    size_type line_number_;
    size_type column_;
};

auto line(const cursor &cursor) noexcept -> Common::StringView;

auto line_number(const cursor &cursor) noexcept -> cursor::size_type;

auto column(const cursor &cursor) noexcept -> cursor::size_type;

void print_cursor_info(const cursor &cursor);

void print_cursor_info(const cursor &cursor, std::ostream &stream);

void print_parse_error(const cursor &cursor, const Common::StringView message);

void print_parse_error(const cursor &cursor, const Common::StringView message, std::ostream &stream);

} // namespace aeon::rdp

#include <aeon/rdp/impl/cursor_impl.h>
