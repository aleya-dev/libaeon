// Distributed under the BSD 2-Clause License - Copyright 2012-2023 Robin Degen

#include <aeon/web/http/request.h>
#include <aeon/streams/stream_reader.h>
#include <aeon/common/string_utils.h>

namespace aeon::web::http
{

request::request(const http_method method)
    : method_{method}
    , uri_{}
    , raw_headers_{}
    , content_type_{}
    , content_{}
{
}

request::request(const common::string &method, common::string uri)
    : method_{string_to_method(method)}
    , uri_{std::move(uri)}
    , raw_headers_{}
    , content_type_{}
    , content_{}
{
}

auto request::get_content() const -> std::vector<std::uint8_t>
{
    streams::stream_reader reader{content_};
    std::vector<std::uint8_t> vec;
    reader.read_to_vector(vec);
    return vec;
}

auto request::get_content_string() const -> common::string
{
    streams::stream_reader reader{content_};
    const auto data = reader.read_to_string();
    return data;
}

auto request::get_content_type() const -> common::string
{
    return content_type_;
}

auto request::get_raw_headers() const -> const std::vector<common::string> &
{
    return raw_headers_;
}

void request::append_raw_http_header_line(const common::string &header_line)
{
    raw_headers_.push_back(header_line);
}

void request::append_raw_content_data(const std::vector<std::byte> &data) const
{
    content_.write(std::data(data), std::size(data));
}

void request::set_content_type(const common::string &content_type)
{
    content_type_ = content_type;
}

auto parse_raw_http_headers(const std::vector<common::string> &raw_headers) -> std::map<common::string, common::string>
{
    std::map<common::string, common::string> headers;

    for (const auto &header_line : raw_headers)
    {
        const auto header_name_end = header_line.find_first_of(':');

        if (header_name_end == common::string::npos)
            return {};

        if (header_name_end + 2 >= header_line.size())
            return {};

        const auto header_name = common::string_utils::to_lower_copy(header_line.substr(0, header_name_end));
        const auto header_value = header_line.substr(header_name_end + 2);

        headers.insert({header_name, header_value});
    }

    return headers;
}

} // namespace aeon::web::http
