// Distributed under the BSD 2-Clause License - Copyright 2012-2023 Robin Degen

#pragma once

#include <aeon/common/string.h>

namespace aeon::web::http
{

auto url_encode(const Common::String &str) -> Common::String;
auto url_decode(const Common::String &str) -> Common::String;

} // namespace aeon::web::http
