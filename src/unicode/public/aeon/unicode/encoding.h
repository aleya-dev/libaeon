// Distributed under the BSD 2-Clause License - Copyright 2012-2023 Robin Degen

#pragma once

#include <aeon/common/string_view.h>
#include <string_view>

namespace aeon::unicode
{

namespace utf8
{

[[nodiscard]] auto to_utf16(const common::string_view &str) -> std::u16string;
[[nodiscard]] auto to_utf32(const common::string_view &str) -> std::u32string;

} // namespace utf8

namespace utf16
{

[[nodiscard]] auto to_utf8(const std::u16string_view &str) -> common::string;
[[nodiscard]] auto to_utf32(const std::u16string_view &str) -> std::u32string;

} // namespace utf16

namespace utf32
{

[[nodiscard]] auto to_utf8(const char32_t c) -> common::string;
[[nodiscard]] auto to_utf8(const std::u32string_view &str) -> common::string;

[[nodiscard]] auto to_utf16(const char32_t c) -> std::u16string;
[[nodiscard]] auto to_utf16(const std::u32string_view &str) -> std::u16string;

} // namespace utf32

} // namespace aeon::unicode
