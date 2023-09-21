// Distributed under the BSD 2-Clause License - Copyright 2012-2023 Robin Degen

#pragma once

#include <aeon/common/string.h>
#include <array>

namespace aeon::Common::Bom
{

namespace Utf8
{

/*!
 * The signature of a UTF-8 byte order marker.
 */
static constexpr std::array<const char8_t, 3> Signature{0xef, 0xbb, 0xbf};

/*!
 * Generate a UTF-8 byte order marker as regular string.
 */
inline auto String()
{
    return Common::String{std::begin(Signature), std::end(Signature)};
}

} // namespace utf8

namespace Utf16
{

/*!
 * The signature of a UTF-16 byte order marker.
 */
static constexpr char16_t Signature = 0xfeff;

/*!
 * The signature of a UTF-16 byte order marker in big endian.
 */
static constexpr char16_t BigEndianSignature = 0xfeff;

} // namespace utf16

} // namespace aeon::Common::bom
