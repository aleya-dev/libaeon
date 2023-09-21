// Distributed under the BSD 2-Clause License - Copyright 2012-2023 Robin Degen

#pragma once

#include <aeon/common/version.h>
#include <aeon/common/string.h>

struct VkExtensionProperties;

namespace aeon::vulkan
{

class application_info final
{
public:
    application_info();
    explicit application_info(Common::String name, Common::Version3<uint32_t> application_version,
                              Common::String engine_name, Common::Version3<uint32_t> engine_version);

    ~application_info() = default;

    application_info(const application_info &) = default;
    auto operator=(const application_info &) -> application_info & = default;

    application_info(application_info &&) noexcept = default;
    auto operator=(application_info &&) noexcept -> application_info & = default;

    [[nodiscard]] auto name() const noexcept -> const Common::String &;
    [[nodiscard]] auto application_version() const noexcept -> const Common::Version3<uint32_t> &;
    [[nodiscard]] auto engine_name() const noexcept -> const Common::String &;
    [[nodiscard]] auto engine_version() const noexcept -> const Common::Version3<uint32_t> &;

private:
    Common::String name_;
    Common::Version3<uint32_t> application_version_;
    Common::String engine_name_;
    Common::Version3<uint32_t> engine_version_;
};

inline application_info::application_info()
    : name_{"aeon"}
    , application_version_{1, 0}
    , engine_name_{"libaeon"}
    , engine_version_{1, 0}
{
}

inline application_info::application_info(Common::String name, Common::Version3<uint32_t> application_version,
                                          Common::String engine_name, Common::Version3<uint32_t> engine_version)
    : name_{std::move(name)}
    , application_version_{application_version}
    , engine_name_{std::move(engine_name)}
    , engine_version_{engine_version}
{
}

inline auto application_info::name() const noexcept -> const Common::String &
{
    return name_;
}

inline auto application_info::application_version() const noexcept -> const Common::Version3<uint32_t> &
{
    return application_version_;
}

inline auto application_info::engine_name() const noexcept -> const Common::String &
{
    return engine_name_;
}

inline auto application_info::engine_version() const noexcept -> const Common::Version3<uint32_t> &
{
    return engine_version_;
}

} // namespace aeon::vulkan
