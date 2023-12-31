// Distributed under the BSD 2-Clause License - Copyright 2012-2023 Robin Degen

#pragma once

#include <aeon/web/http/http_server_socket.h>
#include <aeon/web/http/route.h>
#include <aeon/web/http/http_server_session.h>
#include <aeon/common/string.h>
#include <memory>

namespace aeon::web::http
{

class routable_http_server_session final : public http_server_session
{
public:
    explicit routable_http_server_session();
    ~routable_http_server_session() final;

    routable_http_server_session(routable_http_server_session &&) = default;
    auto operator=(routable_http_server_session &&) -> routable_http_server_session & = default;

    routable_http_server_session(const routable_http_server_session &) = delete;
    auto operator=(const routable_http_server_session &) -> routable_http_server_session & = delete;

    void add_route(std::unique_ptr<route> route);
    void remove_route(const common::string &mountpoint);

    auto find_best_match_route(const common::string &path, common::string &route_path) const -> route *;

private:
    std::map<common::string, std::unique_ptr<route>> routes_;
};

} // namespace aeon::web::http
