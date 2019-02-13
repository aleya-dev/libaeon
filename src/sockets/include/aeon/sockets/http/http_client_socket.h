// Copyright (c) 2012-2019 Robin Degen

#pragma once

#include <aeon/sockets/http/request.h>
#include <aeon/sockets/http/status_code.h>
#include <aeon/sockets/http/reply.h>
#include <aeon/sockets/tcp_socket.h>
#include <aeon/streams/devices/memory_device.h>
#include <aeon/streams/filters/circular_buffer_filter.h>
#include <aeon/streams/stream.h>
#include <asio.hpp>
#include <string>

namespace aeon::sockets::http
{

class http_client_socket : public tcp_socket
{
    enum class http_state
    {
        client_read_status,
        client_read_headers,
        client_read_body
    };

public:
    explicit http_client_socket(asio::io_context &context);

    virtual ~http_client_socket();

    http_client_socket(http_client_socket &&) = delete;
    auto operator=(http_client_socket &&) -> http_client_socket & = delete;

    http_client_socket(const http_client_socket &) = delete;
    auto operator=(const http_client_socket &) -> http_client_socket & = delete;

    void request_async(const std::string &host, const std::string &uri, const http_method method = http_method::get);

    virtual void on_http_reply(reply &reply) = 0;

private:
    void on_data(const std::uint8_t *data, const std::size_t size) override;

    auto __on_line(const std::string &line) -> bool;

    auto __parse_expected_content_length() -> bool;

    auto __handle_read_status_state(const std::string &line) -> bool;
    auto __handle_read_headers_state(const std::string &line) -> bool;

    http_state state_;
    reply reply_;
    streams::aggregate_device<streams::circular_buffer_filter, streams::memory_device<std::vector<char>>>
        circular_buffer_;
    std::streamoff expected_content_length_;
};

} // namespace aeon::sockets::http
