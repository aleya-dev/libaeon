// Distributed under the BSD 2-Clause License - Copyright 2012-2023 Robin Degen

#pragma once

#include <aeon/common/concepts.h>
#include <type_traits>
#include <memory>

namespace aeon::Common
{

template <typename T>
concept IntrusiveReferenceCountable = requires(T val) {
    val.IntrusivePtrAddRef();
    val.IntrusivePtrRelease();
};

template <Concepts::IntegralOrAtomicIntegral T, typename DerivedT, typename DeleterT = std::default_delete<DerivedT>>
class IntrusiveRefCounter
{
public:
    using RefCountType = T;

    constexpr IntrusiveRefCounter() noexcept
        : ref_count_{0}
    {
        static_assert(std::is_base_of_v<IntrusiveRefCounter<T, DerivedT, DeleterT>, DerivedT>,
                      "derived_t must be the inherited class.");
    }

    constexpr IntrusiveRefCounter(const IntrusiveRefCounter<RefCountType, DerivedT, DeleterT> &) noexcept = default;
    constexpr auto operator=(const IntrusiveRefCounter<RefCountType, DerivedT, DeleterT> &) noexcept
        -> IntrusiveRefCounter<RefCountType, DerivedT, DeleterT> & = default;

    constexpr IntrusiveRefCounter(IntrusiveRefCounter<RefCountType, DerivedT, DeleterT> &&) noexcept = default;
    constexpr auto operator=(IntrusiveRefCounter<RefCountType, DerivedT, DeleterT> &&) noexcept
        -> IntrusiveRefCounter<RefCountType, DerivedT, DeleterT> & = default;

    constexpr void IntrusivePtrAddRef() noexcept
    {
        ++ref_count_;
    }

    constexpr void IntrusivePtrRelease() noexcept
    {
        --ref_count_;

        if (ref_count_ == 0)
            DeleterT{}(static_cast<DerivedT *>(this));
    }

    [[nodiscard]] constexpr auto IntrusivePtrRefCount() const noexcept -> const T &
    {
        return ref_count_;
    }

protected:
    ~IntrusiveRefCounter() = default;

private:
    T ref_count_;
};

template <IntrusiveReferenceCountable T>
class IntrusivePtr final
{
public:
    using ElementType = std::remove_extent_t<T>;

    explicit IntrusivePtr() noexcept
        : m_ptr{nullptr}
    {
    }

    IntrusivePtr(ElementType *p)
        : m_ptr{p}
    {
        if (m_ptr != nullptr)
            m_ptr->IntrusivePtrAddRef();
    }

    IntrusivePtr(std::unique_ptr<ElementType> &&other)
        : m_ptr{other.release()}
    {
        if (m_ptr != nullptr)
            m_ptr->IntrusivePtrAddRef();
    }

    IntrusivePtr(const IntrusivePtr<ElementType> &other)
        : m_ptr{other.Get()}
    {
        if (m_ptr != nullptr)
            m_ptr->IntrusivePtrAddRef();
    }

    auto operator=(const IntrusivePtr<ElementType> &other) -> IntrusivePtr<ElementType> &
    {
        IntrusivePtr<ElementType>{other}.Swap(*this);
        return *this;
    }

    IntrusivePtr(IntrusivePtr<ElementType> &&other) noexcept
        : m_ptr{other.Get()}
    {
        other.m_ptr = nullptr;
    }

    IntrusivePtr &operator=(IntrusivePtr<ElementType> &&other) noexcept
    {
        IntrusivePtr<ElementType>{other}.Swap(*this);
        return *this;
    }

    template <typename U, std::enable_if_t<!std::is_convertible_v<ElementType, U>> * = nullptr>
    IntrusivePtr(const IntrusivePtr<U> &other)
        : m_ptr{other.Get()}
    {
        if (m_ptr != nullptr)
            m_ptr->IntrusivePtrAddRef();
    }

    template <class U, std::enable_if_t<!std::is_convertible_v<ElementType, U>> * = nullptr>
    auto operator=(const IntrusivePtr<U> &other) -> IntrusivePtr<ElementType> &
    {
        IntrusivePtr<ElementType>{other}.Swap(*this);
        return *this;
    }

    auto operator=(ElementType *other) -> IntrusivePtr<ElementType> &
    {
        IntrusivePtr<ElementType>{other}.Swap(*this);
        return *this;
    }

    ~IntrusivePtr()
    {
        if (m_ptr != nullptr)
            m_ptr->IntrusivePtrRelease();
    }

    void Reset()
    {
        IntrusivePtr<ElementType>{}.Swap(*this);
    }

    void Reset(T *other)
    {
        IntrusivePtr<ElementType>{other}.Swap(*this);
    }

    [[nodiscard]] auto Get() const noexcept
    {
        return m_ptr;
    }

    auto Release() noexcept
    {
        const auto ret = m_ptr;
        m_ptr = nullptr;
        return ret;
    }

    [[nodiscard]] auto operator*() const noexcept -> ElementType &
    {
        return *m_ptr;
    }

    [[nodiscard]] auto operator->() const noexcept -> ElementType *
    {
        return m_ptr;
    }

    void Swap(IntrusivePtr<ElementType> &other) noexcept
    {
        auto *const temp = m_ptr;
        m_ptr = other.m_ptr;
        other.m_ptr = temp;
    }

private:
    ElementType *m_ptr;
};

template <IntrusiveReferenceCountable T, IntrusiveReferenceCountable U>
inline auto operator==(const IntrusivePtr<T> &lhs, const IntrusivePtr<U> &rhs) noexcept
{
    return lhs.Get() == rhs.Get();
}

template <IntrusiveReferenceCountable T, IntrusiveReferenceCountable U>
inline bool operator!=(const IntrusivePtr<T> &lhs, const IntrusivePtr<U> &rhs) noexcept
{
    return !(lhs == rhs);
}

template <IntrusiveReferenceCountable T, IntrusiveReferenceCountable U>
inline bool operator==(const IntrusivePtr<T> &lhs, const U *rhs) noexcept
{
    return lhs.Get() == rhs;
}

template <IntrusiveReferenceCountable T, IntrusiveReferenceCountable U>
inline bool operator!=(const IntrusivePtr<T> &lhs, const U *rhs) noexcept
{
    return !(lhs == rhs);
}

template <IntrusiveReferenceCountable T, IntrusiveReferenceCountable U>
inline bool operator==(const T *lhs, const IntrusivePtr<U> &rhs) noexcept
{
    return lhs == rhs.Get();
}

template <IntrusiveReferenceCountable T, IntrusiveReferenceCountable U>
inline bool operator!=(const T *lhs, const IntrusivePtr<U> &rhs) noexcept
{
    return !(lhs == rhs);
}

template <IntrusiveReferenceCountable T>
inline bool operator==(const IntrusivePtr<T> &lhs, const std::nullptr_t) noexcept
{
    return lhs.Get() == nullptr;
}

template <IntrusiveReferenceCountable T, IntrusiveReferenceCountable U>
inline bool operator!=(const IntrusivePtr<T> &lhs, const std::nullptr_t) noexcept
{
    return !(lhs == nullptr);
}

template <IntrusiveReferenceCountable T, typename... ArgsT>
[[nodiscard]] inline auto make_intrusive_ptr(ArgsT &&...args) -> IntrusivePtr<T>
{
    return IntrusivePtr<T>{std::make_unique<T>(std::forward<ArgsT>(args)...)};
}

} // namespace aeon::Common
