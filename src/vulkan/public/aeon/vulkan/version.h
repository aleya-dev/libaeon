// Distributed under the BSD 2-Clause License - Copyright 2012-2023 Robin Degen

#pragma once

#include <aeon/common/version.h>
#include <vulkan/vulkan_core.h>

namespace aeon::vulkan::version
{

inline auto from_vulkan(const std::uint32_t v) noexcept
{
    return Common::Version3<uint32_t>{VK_VERSION_MAJOR(v), VK_VERSION_MINOR(v), VK_VERSION_PATCH(v)};
}

inline auto to_vulkan(const Common::Version3<uint32_t> &v) noexcept
{
    return VK_MAKE_VERSION(v.Major, v.Minor, v.Patch);
}

} // namespace aeon::vulkan::version
