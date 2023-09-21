// Distributed under the BSD 2-Clause License - Copyright 2012-2023 Robin Degen

#pragma once

#include <aeon/common/string.h>

namespace aeon::web::http::detail
{

auto validate_http_version_string(const Common::String &version_string) noexcept -> bool;
auto validate_uri(const Common::String &uri) noexcept -> bool;

} // namespace aeon::web::http::detail
