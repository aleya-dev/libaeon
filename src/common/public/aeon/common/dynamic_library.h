// Distributed under the BSD 2-Clause License - Copyright 2012-2023 Robin Degen

#pragma once

#include <aeon/common/string_view.h>
#include <filesystem>
#include <exception>

namespace aeon::Common
{

class DynamicLibraryLoadException final : public std::exception
{
};

class DynamicLibrary final
{
public:
    explicit DynamicLibrary() noexcept;

    /*!
     * Wrap an already loaded platform-specific dynamic library handle
     */
    explicit DynamicLibrary(void *handle) noexcept;

    /*!
     * Load a dynamic library from the given path.
     */
    explicit DynamicLibrary(const std::filesystem::path &path) noexcept;

    ~DynamicLibrary();

    DynamicLibrary(const DynamicLibrary &) noexcept = delete;
    auto operator=(const DynamicLibrary &) noexcept -> DynamicLibrary & = delete;

    DynamicLibrary(DynamicLibrary &&other) noexcept;
    auto operator=(DynamicLibrary &&other) noexcept -> DynamicLibrary &;

    /*!
     * Returns true if the dynamic library was loaded correctly.
     * Will also return false if the internal handle was released to the outside
     */
    [[nodiscard]] auto IsValid() const noexcept -> bool;

    /*!
     * Returns the platform-specific native handle to the loaded library or nullptr
     */
    [[nodiscard]] auto Handle() const noexcept -> void *;

    /*!
     * Get the address of a proc inside of the loaded dll or nullptr
     * if it was not found.
     */
    [[nodiscard]] auto GetProcAddress(const StringView &name) const noexcept -> void *;

    /*!
     * Get the address of a proc inside of the loaded dll or nullptr
     * if it was not found.
     */
    template <typename T>
    [[nodiscard]] auto GetProcAddress(const char *proc) const noexcept -> T
    {
        return reinterpret_cast<T>(GetProcAddress(proc));
    }

    /*!
     * Get the address of a proc inside of the loaded dll or nullptr
     * if it was not found.
     */
    template <typename T>
    [[nodiscard]] auto GetProcAddressPtr(const char *proc) const noexcept -> T *
    {
        return reinterpret_cast<T *>(GetProcAddress(proc));
    }

    /*!
     * Release the dll handle. This will return the internal handle
     * and stop it from getting removed when this class goes out of
     * scope. Be aware that free_dll_handle must be called on this
     * returned handle manually.
     */
    [[nodiscard]] auto Release() noexcept -> void *;

private:
    void Destroy();

    void *m_handle;
};

} // namespace aeon::Common
