// Distributed under the BSD 2-Clause License - Copyright 2012-2023 Robin Degen

#include <aeon/unicode/stringutils.h>

namespace aeon::unicode::stringutils
{

[[nodiscard]] auto escape(const Common::StringView &str) -> Common::String
{
    utf_string_view view{str};
    return escape(std::begin(view), std::end(view));
}

[[nodiscard]] auto escape(const utf_string_view<Common::StringView>::iterator begin,
                          const utf_string_view<Common::StringView>::iterator end) -> Common::String
{
    Common::String result;
    result.Reserve(std::distance(begin, end));

    for (auto itr = begin; itr != end; ++itr)
    {
        switch (*itr)
        {
            case '\b':
                result += "\\b";
                break;
            case '\f':
                result += "\\f";
                break;
            case '\n':
                result += "\\n";
                break;
            case '\r':
                result += "\\r";
                break;
            case '\t':
                result += "\\t";
                break;
            case '\\':
                result += "\\\\";
                break;
            case '"':
                result += "\\\"";
                break;
            case '/':
                result += "\\/";
                break;
            default:
                result += itr.character_str();
        }
    }

    return result;
}

[[nodiscard]] auto unescape(const Common::StringView &str, const unescape_mode mode) -> Common::String
{
    utf_string_view view{str};
    return unescape(std::begin(view), std::end(view), mode);
}

[[nodiscard]] auto unescape(const utf_string_view<Common::StringView>::iterator begin,
                            const utf_string_view<Common::StringView>::iterator end, const unescape_mode mode)
    -> Common::String
{
    Common::String result;
    result.Reserve(std::distance(begin, end));

    for (auto itr = begin; itr != end; ++itr)
    {
        if (*itr == '\\')
        {
            ++itr;

            if (itr == end)
                throw unescape_exception{};

            switch (*itr)
            {
                case 'b':
                    result += '\b';
                    break;
                case 'f':
                    result += '\f';
                    break;
                case 'n':
                    result += '\n';
                    break;
                case 'r':
                    result += '\r';
                    break;
                case 't':
                    result += '\t';
                    break;
                case '\\':
                case '"':
                case '/':
                    result += static_cast<char>(*itr);
                    break;
                default:
                {
                    if (mode == unescape_mode::error_on_unknown)
                        throw unescape_exception{};

                    result += itr.character_str();
                }
                break;
            }
        }
        else
        {
            result += itr.character_str();
        }
    }

    return result;
}

} // namespace aeon::unicode::stringutils
