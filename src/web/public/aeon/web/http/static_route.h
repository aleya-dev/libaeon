// Distributed under the BSD 2-Clause License - Copyright 2012-2023 Robin Degen

#pragma once

#include <aeon/web/http/route.h>
#include <aeon/web/http/constants.h>
#include <aeon/common/string.h>
#include <filesystem>
#include <vector>

namespace aeon::web::http
{

namespace detail
{
auto to_url_path(const common::string &path) -> common::string;
auto is_image_extension(const common::string &extension) -> bool;
} // namespace detail

struct static_route_settings final
{
    static_route_settings() = default;
    ~static_route_settings() = default;

    static_route_settings(static_route_settings &&) = default;
    auto operator=(static_route_settings &&) -> static_route_settings & = default;

    static_route_settings(const static_route_settings &) = default;
    auto operator=(const static_route_settings &) -> static_route_settings & = default;

    // Default files that should be displayed when a directory is requested
    // For example: index.html, index.htm
    std::vector<common::string> default_files = detail::default_files;

    // Enable directory listing.
    bool enable_listing = true;

    // Detect if a folder contains only image files, and if so, display
    // the images as tiles instead. This is an experimental feature.
    bool detect_image_folder = false;

    // Files that should not be displayed when listing a directory.
    std::vector<common::string> hidden_files = detail::hidden_files;
};

class static_route final : public route
{
public:
    explicit static_route(common::string mount_point, const std::filesystem::path &base_path);
    explicit static_route(common::string mount_point, const std::filesystem::path &base_path,
                          static_route_settings settings);

    ~static_route() final;

    static_route(static_route &&) = default;
    auto operator=(static_route &&) -> static_route & = default;

    static_route(const static_route &) = delete;
    auto operator=(const static_route &) -> static_route & = delete;

private:
    struct directory_listing_entry
    {
        common::string display_name;
        bool is_directory = false;
    };

    void on_http_request(http_server_socket &source, routable_http_server_session &session,
                         const request &request) override;

    [[nodiscard]] auto get_path_for_default_files(const std::filesystem::path &path) const -> std::filesystem::path;

    void reply_file(http_server_socket &source, routable_http_server_session &session,
                    const std::filesystem::path &file) const;
    void reply_folder(http_server_socket &source, routable_http_server_session &session,
                      const std::filesystem::path &path) const;

    [[nodiscard]] auto get_current_directory_header_name(const std::filesystem::path &path) const -> common::string;
    [[nodiscard]] auto get_directory_listing_entries(const std::filesystem::path &path) const
        -> std::vector<directory_listing_entry>;
    [[nodiscard]] auto is_image_folder(const std::vector<directory_listing_entry> &entries) const -> bool;
    [[nodiscard]] auto is_hidden_file(const common::string &filename) const -> bool;
    [[nodiscard]] auto generate_hyperlink_html(const common::string &name, const common::string &destination) const
        -> common::string;

    std::filesystem::path base_path_;
    static_route_settings settings_;
};

} // namespace aeon::web::http
