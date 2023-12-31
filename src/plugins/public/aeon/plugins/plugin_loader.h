// Distributed under the BSD 2-Clause License - Copyright 2012-2023 Robin Degen

#pragma once

#include <aeon/plugins/plugin.h>
#include <aeon/common/dynamic_library.h>
#include <aeon/common/string.h>
#include <aeon/common/string_view.h>
#include <memory>
#include <map>
#include <filesystem>
#include <functional>

namespace aeon::plugins
{

class plugin_loader
{
public:
    plugin_loader();
    ~plugin_loader();

    plugin_loader(const plugin_loader &) = delete;
    auto operator=(const plugin_loader &) noexcept -> plugin_loader & = delete;

    plugin_loader(plugin_loader &&) = delete;
    auto operator=(plugin_loader &&) noexcept -> plugin_loader & = delete;

    /*!
     * Load a plugin by name. The given template
     * must be the interface that the plugin uses.
     *
     * It's recommended to put the return value in "scoped_plugin"
     * so that the unloading and cleanup of the plugin is handled
     * RAII.
     */
    template <typename T>
    [[nodiscard]] auto load(const char *name) -> T *
    {
        return static_cast<T *>(load(name));
    }

    /*!
     * Check if a given plugin is loaded by pointer.
     */
    [[nodiscard]] auto is_loaded(const plugin *p) const -> bool;

    /*!
     * Check if a given plugin is loaded by name.
     */
    [[nodiscard]] auto is_loaded(const std::filesystem::path &path) const -> bool;

    /*!
     * Unload a plugin by pointer. If the given plugin pointer is unknown,
     * nothing will happen.
     */
    void unload(const plugin *p);

    /*!
     * Unload a plugin by path. If the given path is unknown,
     * nothing will happen.
     */
    void unload(const std::filesystem::path &path);

    /*!
     * Unload all loaded plugins.
     */
    void unload_all();

private:
    using initialize_plugin_proc = auto (*)() -> plugin *;
    using cleanup_plugin_proc = void (*)(const plugin *);

    /*!
     * Internal helper struct
     */
    struct plugin_cache
    {
        explicit plugin_cache(common::dynamic_library &&library,
                              std::unique_ptr<plugin, cleanup_plugin_proc> &&plugin_instance)
            : library{std::move(library)}
            , plugin_instance{std::move(plugin_instance)}
        {
        }

        ~plugin_cache() = default;

        plugin_cache(const plugin_cache &) = delete;
        auto operator=(const plugin_cache &) noexcept -> plugin_cache & = delete;

        plugin_cache(plugin_cache &&) = default;
        auto operator=(plugin_cache &&) noexcept -> plugin_cache & = default;

        // Order here is important. The plugin must be deleted before unloading the library.
        common::dynamic_library library;
        std::unique_ptr<plugin, cleanup_plugin_proc> plugin_instance;
    };

    /*!
     * Load a plugin by name.
     */
    [[nodiscard]] auto load(const std::filesystem::path &path) -> plugin *;

    /*!
     * Actually load the plugin by loading in the dll, getting the proc addresses
     * and calling them. Returns nullptr in case of an error.
     */
    [[nodiscard]] auto load_plugin(const std::filesystem::path &path) -> plugin *;

    /*!
     * Get a previously loaded plugin by name from the cache. Returns nullptr if
     * not found.
     */
    [[nodiscard]] auto find_in_cache(const std::filesystem::path &path) -> plugin *;

    /*!
     * Unload a plugin based on iterator. This is a helper method called by the
     * public unload methods.
     */
    void unload(std::map<std::filesystem::path, plugin_cache>::iterator itr);

    std::map<std::filesystem::path, plugin_cache> cache_;
};

template <typename T>
class [[nodiscard]] scoped_plugin
{
public:
    scoped_plugin()
        : plugin_interface_{}
        , loader_{}
    {
    }

    scoped_plugin(T *p)
        : plugin_interface_(p)
        , loader_(p ? &plugin_interface_->get_plugin_loader() : nullptr)
    {
    }

    ~scoped_plugin()
    {
        reset();
    }

    scoped_plugin(scoped_plugin &&other) noexcept
        : plugin_interface_(std::move(other.plugin_interface_))
        , loader_(std::move(other.loader_))
    {
        other.plugin_interface_ = nullptr;
        other.loader_ = nullptr;
    }

    scoped_plugin &operator=(scoped_plugin &&other) noexcept
    {
        if (this != &other) [[likely]]
        {
            reset();
            plugin_interface_ = std::move(other.plugin_interface_);
            loader_ = std::move(other.loader_);
            other.plugin_interface_ = nullptr;
            other.loader_ = nullptr;
        }
        return *this;
    }

    scoped_plugin(const scoped_plugin &other) = delete;
    scoped_plugin &operator=(const scoped_plugin &other) = delete;

    [[nodiscard]] auto valid() const noexcept
    {
        return plugin_interface_ && loader_;
    }

    operator bool() const noexcept
    {
        return valid();
    }

    [[nodiscard]] auto get() const noexcept
    {
        return plugin_interface_;
    }

    auto operator->() const noexcept
    {
        return plugin_interface_;
    }

    void reset()
    {
        if (plugin_interface_ && loader_)
        {
            loader_->unload(plugin_interface_);
        }

        plugin_interface_ = nullptr;
        loader_ = nullptr;
    }

    [[nodiscard]] auto release() noexcept
    {
        const auto plugin = plugin_interface_;
        plugin_interface_ = nullptr;
        return plugin;
    }

private:
    T *plugin_interface_;
    plugin_loader *loader_;
};

} // namespace aeon::plugins
