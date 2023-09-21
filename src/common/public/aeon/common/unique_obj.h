// Distributed under the BSD 2-Clause License - Copyright 2012-2023 Robin Degen

#pragma once

#include <concepts>
#include <utility>

namespace aeon::Common
{

template <std::move_constructible T>
class UniqueObj final
{
public:
    using ElementType = T;

    UniqueObj() noexcept = default;
    ~UniqueObj() = default;

    UniqueObj(UniqueObj &&) noexcept = default;
    UniqueObj &operator=(UniqueObj &&) noexcept = default;

    UniqueObj(const UniqueObj &) noexcept = delete;
    auto operator=(const UniqueObj &) noexcept -> UniqueObj & = delete;

    UniqueObj(ElementType &&element) noexcept
        : m_value{std::move(element)}
    {
    }

    auto operator=(ElementType &&element) noexcept -> UniqueObj &
    {
        m_value = std::move(element);
        return *this;
    }

    [[nodiscard]] auto Get() noexcept -> ElementType &
    {
        return m_value;
    }

    [[nodiscard]] auto Get() const noexcept -> const ElementType &
    {
        return m_value;
    }

    [[nodiscard]] auto operator*() noexcept -> ElementType &
    {
        return Get();
    }

    [[nodiscard]] auto operator*() const noexcept -> const ElementType &
    {
        return Get();
    }

    [[nodiscard]] auto operator->() const noexcept -> ElementType *
    {
        return &m_value;
    }

    [[nodiscard]] auto Release() noexcept -> ElementType
    {
        return std::move(m_value);
    }

private:
    ElementType m_value;
};

} // namespace aeon::Common
