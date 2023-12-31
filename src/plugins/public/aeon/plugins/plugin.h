// Distributed under the BSD 2-Clause License - Copyright 2012-2023 Robin Degen

#pragma once

#include <aeon/plugins/plugin_export.h>
#include <memory>

namespace aeon::plugins
{

class plugin_loader;

/*!
 * Base class for a plugin that can be loaded with the plugin loader.
 *
 * The plugin interface must be inherited from this base class. Example:
 * plugin <- imy_plugin_interface <- my_plugin
 */
class plugin
{
public:
    virtual ~plugin() = default;

    plugin(const plugin &) = delete;
    auto operator=(const plugin &) noexcept -> plugin & = delete;

    plugin(plugin &&) = delete;
    auto operator=(plugin &&) noexcept -> plugin & = delete;

    /*!
     * This should return a short descriptive name of the plugin.
     */
    [[nodiscard]] virtual auto plugin_name() const noexcept -> const char * = 0;

    /*!
     * This should return a version string for this plugin.
     */
    [[nodiscard]] virtual auto plugin_version_string() const noexcept -> const char * = 0;

    /*!
     * Called when the plugin is being loaded, right before the interface is
     * given to the application that loaded it. Here, dependencies can be loaded.
     */
    virtual void plugin_on_load()
    {
    }

    /*!
     * Called when the plugin is about to be unloaded.
     */
    virtual void plugin_on_unload()
    {
    }

    /*!
     * Get the interface to the loader that loaded this plugin.
     */
    [[nodiscard]] auto get_plugin_loader() const -> plugin_loader &;

    /*!
     * Set the interface to the loader that loaded this plugin.
     * Internal method. Do not call.
     */
    void set_plugin_loader_internal(plugin_loader &loader);

protected:
    plugin();

    plugin_loader *loader_;
};

} // namespace aeon::plugins

#define aeon_register_plugin(plugin_class)                                                                             \
    extern "C" AEON_DLL_EXPORT aeon::plugins::plugin *aeon_initialize_plugin()                                         \
    {                                                                                                                  \
        return std::make_unique<plugin_class>().release();                                                             \
    }                                                                                                                  \
                                                                                                                       \
    extern "C" AEON_DLL_EXPORT void aeon_cleanup_plugin(const aeon::plugins::plugin *plugin)                           \
    {                                                                                                                  \
        delete plugin;                                                                                                 \
    }
