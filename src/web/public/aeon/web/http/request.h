// Distributed under the BSD 2-Clause License - Copyright 2012-2023 Robin Degen

#pragma once

#include <aeon/web/http/method.h>
#include <aeon/streams/devices/memory_device.h>
#include <aeon/common/string.h>
#include <vector>
#include <map>

namespace aeon::web::http
{

class request
{
    friend class http_server_socket;

public:
    explicit request(const http_method method);
    explicit request(const Common::String &method, Common::String uri);

    auto get_method() const noexcept
    {
        return method_;
    }

    auto get_uri() const
    {
        return uri_;
    }

    void set_uri(const Common::String &uri)
    {
        uri_ = uri;
    }

    auto get_content_length() const
    {
        return content_.size();
    }

    auto has_content() const
    {
        return content_.size() != 0;
    }

    auto get_content() const -> std::vector<std::uint8_t>;

    auto get_content_string() const -> Common::String;

    auto get_content_type() const -> Common::String;

    auto get_raw_headers() const -> const std::vector<Common::String> &;

private:
    void append_raw_http_header_line(const Common::String &header_line);
    void append_raw_content_data(const std::vector<std::byte> &data) const;
    void set_content_type(const Common::String &content_type);

    http_method method_;
    Common::String uri_;
    std::vector<Common::String> raw_headers_;

    Common::String content_type_;
    mutable streams::memory_device<std::vector<char>> content_;
};

auto parse_raw_http_headers(const std::vector<Common::String> &raw_headers) -> std::map<Common::String, Common::String>;

} // namespace aeon::web::http
