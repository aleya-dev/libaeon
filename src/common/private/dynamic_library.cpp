// Distributed under the BSD 2-Clause License - Copyright 2012-2023 Robin Degen

#include <aeon/common/dynamic_library.h>
#include <aeon/common/platform.h>

#if (defined(AEON_PLATFORM_OS_WINDOWS))
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#else
#include <dlfcn.h>
#endif

namespace aeon::Common
{

namespace Internal
{

[[nodiscard]] static auto LoadLibrary(const std::filesystem::path &path) noexcept -> void *
{
#if (defined(AEON_PLATFORM_OS_WINDOWS))
    auto result = LoadLibraryW(path.wstring().c_str());
#else
    auto p = u8"./" + path.u8string();

#if (defined(AEON_PLATFORM_OS_LINUX))
    p += u8".so";
#elif (defined(AEON_PLATFORM_OS_MACOS))
    p += u8".dylib";
#endif
    auto result = dlopen(reinterpret_cast<const char *>(p.c_str()), RTLD_LAZY | RTLD_LOCAL);
#endif

    return result;
}

[[nodiscard]] static auto GetProcAddress(void *handle, const StringView &name) noexcept -> void *
{
#if (defined(AEON_PLATFORM_OS_WINDOWS))
    return reinterpret_cast<void *>(GetProcAddress(static_cast<const HMODULE>(handle), std::data(name)));
#else
    return dlsym(handle, std::data(name));
#endif
}

void FreeLibrary(void *handle) noexcept
{
#if (defined(AEON_PLATFORM_OS_WINDOWS))
    FreeLibrary(static_cast<HMODULE>(handle));
#else
    dlclose(handle);
#endif
}

} // namespace internal

DynamicLibrary::DynamicLibrary() noexcept
    : m_handle{nullptr}
{
}

DynamicLibrary::DynamicLibrary(void *handle) noexcept
    : m_handle{handle}
{
}

DynamicLibrary::DynamicLibrary(const std::filesystem::path &path) noexcept
    : m_handle{Internal::LoadLibrary(path)}
{
}

DynamicLibrary::~DynamicLibrary()
{
    Destroy();
}

DynamicLibrary::DynamicLibrary(DynamicLibrary &&other) noexcept
    : m_handle{other.m_handle}
{
    other.m_handle = nullptr;
}

auto DynamicLibrary::operator=(DynamicLibrary &&other) noexcept -> DynamicLibrary &
{
    if (this != &other) [[likely]]
    {
        Destroy();
        m_handle = other.m_handle;
        other.m_handle = nullptr;
    }

    return *this;
}

auto DynamicLibrary::IsValid() const noexcept -> bool
{
    return m_handle != nullptr;
}

auto DynamicLibrary::Handle() const noexcept -> void *
{
    return m_handle;
}

auto DynamicLibrary::GetProcAddress(const StringView &name) const noexcept -> void *
{
    return Internal::GetProcAddress(m_handle, name);
}

auto DynamicLibrary::Release() noexcept -> void *
{
    const auto handle = m_handle;
    m_handle = nullptr;
    return handle;
}

void DynamicLibrary::Destroy()
{
    if (m_handle)
        Internal::FreeLibrary(m_handle);

    m_handle = nullptr;
}

} // namespace aeon::Common
