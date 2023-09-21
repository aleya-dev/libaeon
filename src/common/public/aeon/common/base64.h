// Distributed under the BSD 2-Clause License - Copyright 2012-2023 Robin Degen

#pragma once

#include <aeon/common/string.h>
#include <aeon/common/string_view.h>
#include <vector>
#include <cstdint>

namespace aeon::Common::Base64
{

[[nodiscard]] auto Encode(const StringView &data) -> String;
[[nodiscard]] auto Encode(const std::vector<std::uint8_t> &data) -> String;
[[nodiscard]] auto Encode(const std::uint8_t *data, const std::streamsize size) -> String;

[[nodiscard]] auto Decode(const StringView &str) -> std::vector<std::uint8_t>;
[[nodiscard]] auto DecodeString(const StringView &str) -> String;

} // namespace aeon::Common::base64
