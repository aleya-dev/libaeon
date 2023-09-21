// Distributed under the BSD 2-Clause License - Copyright 2012-2023 Robin Degen

#include <aeon/vulkan/layer.h>
#include <aeon/vulkan/version.h>
#include <vulkan/vulkan_core.h>

namespace aeon::vulkan
{

layer::layer(Common::String name, const Common::Version3<uint32_t> &spec_version,
             const Common::Version3<uint32_t> &implementation_version, Common::String description)
    : name_{std::move(name)}
    , spec_version_{spec_version}
    , implementation_version_{implementation_version}
    , description_{std::move(description)}
{
}

layer::layer(const VkLayerProperties &extension_properties)
    : name_{extension_properties.layerName}
    , spec_version_{version::from_vulkan(extension_properties.specVersion)}
    , implementation_version_{version::from_vulkan(extension_properties.implementationVersion)}
    , description_{extension_properties.description}
{
}

auto layer::name() const noexcept -> const Common::String &
{
    return name_;
}

auto layer::spec_version() const noexcept -> const Common::Version3<uint32_t> &
{
    return spec_version_;
}

auto layer::implementation_version() const noexcept -> const Common::Version3<uint32_t> &
{
    return implementation_version_;
}

auto layer::description() const noexcept -> const Common::String &
{
    return description_;
}

auto layer::operator==(const layer &other) const noexcept -> bool
{
    return name_ == other.name_ && spec_version_ == other.spec_version_ &&
           implementation_version_ == other.implementation_version_;
}

auto layer::operator!=(const layer &other) const noexcept -> bool
{
    return !(*this == other);
}

} // namespace aeon::vulkan
