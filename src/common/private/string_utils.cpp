// Distributed under the BSD 2-Clause License - Copyright 2012-2023 Robin Degen

#include <aeon/common/string_utils.h>
#include <sstream>
#include <algorithm>
#include <functional>
#include <cctype>
#include <sstream>
#include <iomanip>

namespace aeon::Common::StringUtils
{

// TODO: Implement a generic version that doesn't depend on ostringstream so also utf8 can be added
auto CharToHex(const char c) -> String
{
    std::ostringstream ss;
    ss << '%' << std::setw(2) << std::setfill('0') << std::hex << std::uppercase << static_cast<short>(c & 0xff);
    return ss.str();
}

// TODO: Implement a generic version that doesn't depend on ostringstream so also utf8 can be added
auto HexToChar(const String &str) -> char
{
    if (str.Empty())
        return 0;

    std::istringstream in(str.Str());

    short c = 0;
    in >> std::hex >> c;

    if (in.fail())
        throw std::runtime_error("stream decode failure");

    return static_cast<char>(c & 0xff);
}

} // namespace aeon::Common::string_utils
