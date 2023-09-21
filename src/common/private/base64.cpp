// Distributed under the BSD 2-Clause License - Copyright 2012-2023 Robin Degen

// Based on an implementation by Megumi Tomita, https://gist.github.com/tomykaira/f0fd86b6c73063283afe550bc5d77594

#include <aeon/common/base64.h>
#include <aeon/common/bits.h>
#include <stdexcept>

namespace aeon::Common::Base64
{

namespace Internal
{

// clang-format off
static constexpr char EncodeLookup[] =
{
    'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H',
    'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P',
    'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X',
    'Y', 'Z', 'a', 'b', 'c', 'd', 'e', 'f',
    'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n',
    'o', 'p', 'q', 'r', 's', 't', 'u', 'v',
    'w', 'x', 'y', 'z', '0', '1', '2', '3',
    '4', '5', '6', '7', '8', '9', '+', '/'
};

static constexpr unsigned char DecodeLookup[] =
{
    64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64,
    64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64,
    64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 62, 64, 64, 64, 63,
    52, 53, 54, 55, 56, 57, 58, 59, 60, 61, 64, 64, 64, 64, 64, 64,
    64,  0,  1,  2,  3,  4,  5,  6,  7,  8,  9, 10, 11, 12, 13, 14,
    15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 64, 64, 64, 64, 64,
    64, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40,
    41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51, 64, 64, 64, 64, 64,
    64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64,
    64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64,
    64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64,
    64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64,
    64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64,
    64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64,
    64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64,
    64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64
};
// clang-format on

auto DecodePart(const StringView &str, unsigned int &i)
{
    return str[i] == '=' ? 0 & i++ : DecodeLookup[static_cast<int>(str[i++])];
}

} // namespace internal

auto Encode(const StringView &data) -> String
{
    return Encode(reinterpret_cast<const std::uint8_t *>(std::data(data)),
                  static_cast<std::streamsize>(std::size(data)));
}

auto Encode(const std::vector<std::uint8_t> &data) -> String
{
    return Encode(std::data(data), static_cast<std::streamsize>(std::size(data)));
}

auto Encode(const std::uint8_t *data, const std::streamsize size) -> String
{
    const auto outputLength = 4 * ((size + 2) / 3);

    if (outputLength == 0)
        return "";

    String result(outputLength, '\0');

    auto p = result.Data();

    auto i = 0u;
    for (; i < size - 2; i += 3)
    {
        *p++ = Internal::EncodeLookup[data[i] >> 2 & 0x3F];
        *p++ = Internal::EncodeLookup[(data[i] & 0x3) << 4 | static_cast<int>(data[i + 1] & 0xF0) >> 4];
        *p++ = Internal::EncodeLookup[(data[i + 1] & 0xF) << 2 | static_cast<int>(data[i + 2] & 0xC0) >> 6];
        *p++ = Internal::EncodeLookup[data[i + 2] & 0x3F];
    }

    if (i < size)
    {
        *p++ = Internal::EncodeLookup[data[i] >> 2 & 0x3F];
        if (i == (size - 1))
        {
            *p++ = Internal::EncodeLookup[((data[i] & 0x3) << 4)];
            *p++ = '=';
        }
        else
        {
            *p++ = Internal::EncodeLookup[(data[i] & 0x3) << 4 | static_cast<int>(data[i + 1] & 0xF0) >> 4];
            *p++ = Internal::EncodeLookup[((data[i + 1] & 0xF) << 2)];
        }
        *p++ = '=';
    }

    return result;
}

auto Decode(const StringView &str) -> std::vector<std::uint8_t>
{
    if (str.Empty())
        return {};

    const auto len = std::size(str);

    if (len % 4 != 0)
        throw std::invalid_argument{"Base64 requires multiple of 4."};

    auto outputLength = len / 4 * 3;

    if (str[len - 1] == '=')
        --outputLength;

    if (str[len - 2] == '=')
        --outputLength;

    std::vector<std::uint8_t> result(outputLength);

    for (auto i = 0u, j = 0u; i < len;)
    {
        const auto triple = (Internal::DecodePart(str, i) << 3 * 6) + (Internal::DecodePart(str, i) << 2 * 6) +
                            (Internal::DecodePart(str, i) << 1 * 6) + (Internal::DecodePart(str, i) << 0 * 6);

        if (j < outputLength)
            result[j++] = Bits::MaskU8(triple >> 2 * 8);

        if (j < outputLength)
            result[j++] = Bits::MaskU8(triple >> 1 * 8);

        if (j < outputLength)
            result[j++] = Bits::MaskU8(triple >> 0 * 8);
    }

    return result;
}

auto DecodeString(const StringView &str) -> String
{
    const auto result = Decode(str);
    return {std::begin(result), std::end(result)};
}

} // namespace aeon::Common::base64
