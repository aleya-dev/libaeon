// Copyright (c) 2012-2019 Robin Degen

#pragma once

#include <aeon/reflection/ast/entity.h>
#include <aeon/reflection/ast/access_specifier.h>
#include <aeon/common/flags.h>

namespace aeon::reflection::ast
{

enum class field_flag : int
{
    is_mutable = 0x01,
    is_static = 0x02,
};

aeon_declare_flag_operators(field_flag);

class ast_field final : public ast_entity
{
public:
    explicit ast_field(std::string name, std::string type, const access_specifier access,
                       const common::flags<field_flag> flags, const ast::linkage_kind linkage_kind) noexcept
        : ast_entity{ast_entity_type::field_t, std::move(name), linkage_kind}
        , type_{std::move(type)}
        , access_{access}
        , flags_{flags}
    {
    }

    virtual ~ast_field() = default;

    ast_field(const ast_field &) noexcept = delete;
    auto operator=(const ast_field &) noexcept -> ast_field & = delete;

    ast_field(ast_field &&) noexcept = default;
    auto operator=(ast_field &&) noexcept -> ast_field & = default;

    [[nodiscard]] const auto &type() const noexcept
    {
        return type_;
    }

    [[nodiscard]] auto access() const noexcept
    {
        return access_;
    }

    [[nodiscard]] auto is_mutable() const noexcept
    {
        return flags_.is_set(field_flag::is_mutable);
    }

    [[nodiscard]] auto is_static() const noexcept
    {
        return flags_.is_set(field_flag::is_static);
    }

private:
    std::string type_;
    access_specifier access_;
    common::flags<field_flag> flags_;
};

} // namespace aeon::reflection::ast
