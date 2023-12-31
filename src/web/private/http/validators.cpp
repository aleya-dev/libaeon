// Distributed under the BSD 2-Clause License - Copyright 2012-2023 Robin Degen

#include <aeon/web/http/validators.h>
#include <aeon/web/http/constants.h>
#include <aeon/common/string.h>

namespace aeon::web::http::detail
{

auto validate_http_version_string(const common::string &version_string) noexcept -> bool
{
    return version_string == http_version_string;
}

auto validate_uri(const common::string &uri) noexcept -> bool
{
    for (const auto c : uri)
    {
        // Valid character?
        if (!((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') || (c >= '0' && c <= '9') || c == '/' || c == '?' ||
              c == '%' || c == '&' || c == '=' || c == '+' || c == '-' || c == '*' || c == '.' || c == '_' ||
              c == '@' || c == ',' || c == '~'))
        {
            return false;
        }
    }

    return true;
}

} // namespace aeon::web::http::detail
