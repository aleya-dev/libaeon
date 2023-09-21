// Distributed under the BSD 2-Clause License - Copyright 2012-2023 Robin Degen

#include <aeon/web/http/url_encoding.h>
#include <aeon/common/string_utils.h>
#include <aeon/common/literals.h>

namespace aeon::web::http
{

auto url_encode(const Common::String &str) -> Common::String
{
    Common::String out;
    out.Reserve(str.Size());

    for (const auto t : str)
    {
        if (t == '-' || t == '.' || (t >= '0' && t <= '9') || (t >= 'A' && t <= 'Z') || t == '_' ||
            (t >= 'a' && t <= 'z') || t == '~' || t == '/')
        {
            out += t;
        }
        else
        {
            out += Common::StringUtils::CharToHex(t);
        }
    }

    return out;
}

auto url_decode(const Common::String &str) -> Common::String
{
    Common::String out;
    out.Reserve(str.Size());

    for (auto i = 0_size_t; i < str.Size(); ++i)
    {
        if (str.At(i) == '%')
        {
            out += Common::StringUtils::HexToChar(str.Substr(i + 1, 2));
            i += 2;
        }
        else
        {
            out += str.At(i);
        }
    }

    return out;
}

} // namespace aeon::web::http
