// Distributed under the BSD 2-Clause License - Copyright 2012-2023 Robin Degen

#pragma once

#include <aeon/reflection/exception.h>
#include <aeon/reflection/field_info.h>
#include <aeon/reflection/reflection_object.h>
#include <aeon/common/string_view.h>
#include <vector>
#include <type_traits>
#include <memory>

namespace aeon::reflection
{

class reflection_info
{
public:
    reflection_info() noexcept;
    virtual ~reflection_info();

    reflection_info(const reflection_info &) noexcept = default;
    auto operator=(const reflection_info &) noexcept -> reflection_info & = default;

    reflection_info(reflection_info &&) noexcept = default;
    auto operator=(reflection_info &&) noexcept -> reflection_info & = default;

    template <typename U, reflection_object_implementation T>
    auto get_field(T &instance, const char *const name) const -> U *
    {
        const auto &field_info = get_field_info();
        for (const auto &field : field_info)
        {
            if (field.name() == name)
                return reinterpret_cast<U *>(reinterpret_cast<std::uint8_t *>(&instance) + field.offset());
        }

        throw reflection_exception{};
    }

    auto get_field_type(const char *const name) const -> common::string_view;

    [[nodiscard]] virtual auto create() const -> std::unique_ptr<reflection_object> = 0;
    [[nodiscard]] virtual auto get_field_info() const noexcept -> const std::vector<field_info> & = 0;
};

} // namespace aeon::reflection
