// Distributed under the BSD 2-Clause License - Copyright 2012-2023 Robin Degen

#pragma once

#include <aeon/common/string.h>
#include <map>

namespace aeon::web::http
{

class http_server_session
{
public:
    explicit http_server_session();
    virtual ~http_server_session();

    http_server_session(http_server_session &&) = default;
    auto operator=(http_server_session &&) -> http_server_session & = default;

    http_server_session(const http_server_session &) = delete;
    auto operator=(const http_server_session &) -> http_server_session & = delete;

    /*!
     * Register a mime type to a file extension. If the extension already had a
     * mime type, it will be overwritten.
     */
    void register_mine_type(const common::string &extension, const common::string &mime_type);

    /*!
     * Attempt to find a suitable mime type for a given file extension.
     * Returns the default mime type if this could not be found.
     */
    [[nodiscard]] auto find_mime_type_by_extension(const common::string &extension) const -> common::string;

    /*!
     * Attempt to find a suitable file extension for a mime type. Returns an empty
     * string if this could not be found. Since this method is used considerably less
     * than finding a mime type by extension, it's performance will be relatively bad.
     */
    [[nodiscard]] auto find_extension_by_mime_type(const common::string &mime_type) const -> common::string;

    /*!
     * Set the default mime type. This is the mime type that will be used if the
     * file extension is not registered, and thus unknown.
     */
    void set_default_mime_type(const common::string &mime_type);

    /*!
     * Get the default mime type. This is the mime type that will be used if the
     * file extension is not registered, and thus unknown.
     */
    [[nodiscard]] auto get_default_mime_type() const noexcept -> const common::string &;

private:
    /*!
     * Register internal mime types.
     */
    void register_mime_types();

    std::map<common::string, common::string> mime_types_;
    common::string default_mime_type_;
};

} // namespace aeon::web::http
