// Distributed under the BSD 2-Clause License - Copyright 2012-2023 Robin Degen

#pragma once

#include <aeon/reflection/reflection_info.h>
#include <aeon/reflection/reflection_object.h>
#include <aeon/common/preprocessor.h>

#define AEON_REFLECTION_BEGIN(classname)                                                                               \
    class reflection_info_impl final : public aeon::reflection::reflection_info                                        \
    {                                                                                                                  \
    public:                                                                                                            \
        reflection_info_impl() noexcept = default;                                                                     \
        ~reflection_info_impl() override = default;                                                                    \
                                                                                                                       \
        reflection_info_impl(const reflection_info_impl &) noexcept = default;                                         \
        auto operator=(const reflection_info_impl &) noexcept -> reflection_info_impl & = default;                     \
                                                                                                                       \
        reflection_info_impl(reflection_info_impl &&) noexcept = default;                                              \
        auto operator=(reflection_info_impl &&) noexcept -> reflection_info_impl & = default;                          \
                                                                                                                       \
        [[nodiscard]] auto create() const -> std::unique_ptr<aeon::reflection::reflection_object> override             \
        {                                                                                                              \
            return std::make_unique<classname>();                                                                      \
        }                                                                                                              \
                                                                                                                       \
        [[nodiscard]] auto get_field_info() const noexcept                                                             \
            -> const std::vector<aeon::reflection::field_info> & override                                              \
        {                                                                                                              \
            using reflection_class_type = classname;                                                                   \
                                                                                                                       \
            static std::vector<aeon::reflection::field_info> info = {

// clang-format off
#define AEON_REFLECTION_FIELD(type, name)                                                                              \
                {                                                                                                      \
                    (aeon_concatenate(u8, #name)), (aeon_concatenate(u8, #type)),                                      \
                    reinterpret_cast<std::ptrdiff_t>(                                                                  \
                    &reinterpret_cast<std::uint8_t const &>((static_cast<reflection_class_type *>(nullptr)->name)))    \
                },

#define AEON_REFLECTION_END()                                                                                          \
            };                                                                                                         \
                                                                                                                       \
            return info;                                                                                               \
        }                                                                                                              \
    };                                                                                                                 \
                                                                                                                       \
public:                                                                                                                \
    [[nodiscard]] static auto reflection_info() noexcept->const aeon::reflection::reflection_info &                    \
    {                                                                                                                  \
        static reflection_info_impl info;                                                                              \
        return info;                                                                                                   \
    }                                                                                                                  \
                                                                                                                       \
private:
// clang-format on
