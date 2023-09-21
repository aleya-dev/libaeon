// Distributed under the BSD 2-Clause License - Copyright 2012-2023 Robin Degen

#pragma once

#include <tuple>

namespace aeon::Common
{

template <typename T>
inline constexpr Version2<T>::Version2() noexcept
    : Major{}
    , Minor{}
{
}

template <typename T>
inline constexpr Version2<T>::Version2(const T major, const T minor) noexcept
    : Major{major}
    , Minor{minor}
{
}

template <typename T>
template <typename U>
inline constexpr Version2<T>::Version2(const Version2<U> other) noexcept
    : Major{static_cast<T>(other.Major)}
    , Minor{static_cast<T>(other.Minor)}
{
}

template <typename T>
template <typename U>
inline constexpr Version2<T>::Version2(const U major, const U minor) noexcept
    : Major{static_cast<T>(major)}
    , Minor{static_cast<T>(minor)}
{
}

template <typename T>
inline auto Version2<T>::Str() const -> String
{
    String version;
    version.Reserve(3); // Typically 1.2
    version += std::to_string(Major);
    version += '.';
    version += std::to_string(Minor);
    return version;
}

template <typename T>
inline constexpr Version3<T>::Version3() noexcept
    : Version2<T>{}
    , Patch{}
{
}

template <typename T>
inline constexpr Version3<T>::Version3(const T major, const T minor) noexcept
    : Version3{major, minor, {}}
{
}

template <typename T>
inline constexpr Version3<T>::Version3(const T major, const T minor, const T patch) noexcept
    : Version2<T>{major, minor}
    , Patch{patch}
{
}

template <typename T>
inline constexpr Version3<T>::Version3(const Version2<T> &ver) noexcept
    : Version3{ver, {}}
{
}

template <typename T>
inline constexpr Version3<T>::Version3(const Version2<T> &ver, const T Patch) noexcept
    : Version2<T>{ver}
    , Patch{Patch}
{
}

template <typename T>
template <typename U>
inline constexpr Version3<T>::Version3(const U major, const U minor) noexcept
    : Version3{static_cast<T>(major), static_cast<T>(minor), {}}
{
}

template <typename T>
template <typename U>
inline constexpr Version3<T>::Version3(const U major, const U minor, const U patch) noexcept
    : Version2<T>{static_cast<T>(major), static_cast<T>(minor)}
    , Patch{static_cast<T>(patch)}
{
}

template <typename T>
template <typename U>
inline constexpr Version3<T>::Version3(const Version2<U> &ver) noexcept
    : Version3{ver, {}}
{
}

template <typename T>
template <typename U>
inline constexpr Version3<T>::Version3(const Version2<U> &ver, const U patch) noexcept
    : Version2<T>{ver}
    , Patch{static_cast<T>(patch)}
{
}

template <typename T>
template <typename U>
inline constexpr Version3<T>::Version3(const Version3<U> &ver) noexcept
    : Version3<T>{static_cast<T>(ver.Major), static_cast<T>(ver.Minor), static_cast<T>(ver.Patch)}
{
}

template <typename T>
inline auto Version3<T>::Str() const -> String
{
    String version;
    version.Reserve(5); // Typically 1.2.3
    version += std::to_string(Version2<T>::Major);
    version += '.';
    version += std::to_string(Version2<T>::Minor);
    version += '.';
    version += std::to_string(Patch);
    return version;
}

template <typename T>
inline constexpr Version4<T>::Version4() noexcept
    : Version3<T>{}
    , Build{}
{
}

template <typename T>
inline constexpr Version4<T>::Version4(const T major, const T minor) noexcept
    : Version4{major, minor, {}, {}}
{
}

template <typename T>
inline constexpr Version4<T>::Version4(const T major, const T minor, const T patch) noexcept
    : Version4{major, minor, patch, {}}
{
}

template <typename T>
inline constexpr Version4<T>::Version4(const T major, const T minor, const T patch, const T build) noexcept
    : Version3<T>{major, minor, patch}
    , Build{build}
{
}

template <typename T>
inline constexpr Version4<T>::Version4(const Version2<T> &ver) noexcept
    : Version3<T>{ver.Major, ver.Minor, {}}
    , Build{}
{
}

template <typename T>
inline constexpr Version4<T>::Version4(const Version2<T> &ver, const T patch) noexcept
    : Version4{ver, patch, {}}
{
}

template <typename T>
inline constexpr Version4<T>::Version4(const Version2<T> &ver, const T patch, const T build) noexcept
    : Version3<T>{ver.Major, ver.Minor, patch}
    , Build{build}
{
}

template <typename T>
inline constexpr Version4<T>::Version4(const Version3<T> &ver) noexcept
    : Version4{ver, {}}
{
}

template <typename T>
inline constexpr Version4<T>::Version4(const Version3<T> &ver, const T build) noexcept
    : Version3<T>{ver}
    , Build{build}
{
}

template <typename T>
template <typename U>
inline constexpr Version4<T>::Version4(const U major, const U minor) noexcept
    : Version4{static_cast<T>(major), static_cast<T>(minor), {}, {}}
{
}

template <typename T>
template <typename U>
inline constexpr Version4<T>::Version4(const U major, const U minor, const U patch) noexcept
    : Version4{static_cast<T>(major), static_cast<T>(minor), static_cast<T>(patch), {}}
{
}

template <typename T>
template <typename U>
inline constexpr Version4<T>::Version4(const U major, const U minor, const U patch, const U build) noexcept
    : Version3<T>{static_cast<T>(major), static_cast<T>(minor), static_cast<T>(patch)}
    , Build{static_cast<T>(build)}
{
}

template <typename T>
template <typename U>
inline constexpr Version4<T>::Version4(const Version2<U> &ver) noexcept
    : Version3<T>{static_cast<T>(ver.Major), static_cast<T>(ver.Minor), {}}
    , Build{}
{
}

template <typename T>
template <typename U>
inline constexpr Version4<T>::Version4(const Version2<U> &ver, const U patch) noexcept
    : Version4{ver, patch, {}}
{
}

template <typename T>
template <typename U>
inline constexpr Version4<T>::Version4(const Version2<U> &ver, const U patch, const U build) noexcept
    : Version3<T>{static_cast<T>(ver.Major), static_cast<T>(ver.Minor), static_cast<T>(patch)}
    , Build{static_cast<T>(build)}
{
}

template <typename T>
template <typename U>
inline constexpr Version4<T>::Version4(const Version3<U> &ver) noexcept
    : Version4{ver, {}}
{
}

template <typename T>
template <typename U>
inline constexpr Version4<T>::Version4(const Version3<U> &ver, const U build) noexcept
    : Version3<T>{ver}
    , Build{static_cast<T>(build)}
{
}

template <typename T>
template <typename U>
inline constexpr Version4<T>::Version4(const Version4<U> &ver) noexcept
    : Version4{static_cast<T>(ver.Major), static_cast<T>(ver.Minor), static_cast<T>(ver.Patch),
               static_cast<T>(ver.Build)}
{
}

template <typename T>
inline auto Version4<T>::Str() const -> String
{
    String version;
    version.Reserve(7); // Typically 1.2.3.4
    version += std::to_string(Version2<T>::Major);
    version += '.';
    version += std::to_string(Version2<T>::Minor);
    version += '.';
    version += std::to_string(Version3<T>::Patch);
    version += '.';
    version += std::to_string(Build);
    return version;
}

template <typename T>
inline constexpr auto operator<(const Version2<T> &lhs, const Version2<T> &rhs) noexcept -> bool
{
    return std::tie(lhs.Major, lhs.Minor) < std::tie(rhs.Major, rhs.Minor);
}

template <typename T>
inline constexpr auto operator<=(const Version2<T> &lhs, const Version2<T> &rhs) noexcept -> bool
{
    return std::tie(lhs.Major, lhs.Minor) <= std::tie(rhs.Major, rhs.Minor);
}

template <typename T>
inline constexpr auto operator>(const Version2<T> &lhs, const Version2<T> &rhs) noexcept -> bool
{
    return std::tie(lhs.Major, lhs.Minor) > std::tie(rhs.Major, rhs.Minor);
}

template <typename T>
inline constexpr auto operator>=(const Version2<T> &lhs, const Version2<T> &rhs) noexcept -> bool
{
    return std::tie(lhs.Major, lhs.Minor) >= std::tie(rhs.Major, rhs.Minor);
}

template <typename T>
inline constexpr auto operator==(const Version2<T> &lhs, const Version2<T> &rhs) noexcept -> bool
{
    return lhs.Major == rhs.Major && lhs.Minor == rhs.Minor;
}

template <typename T>
inline constexpr auto operator!=(const Version2<T> &lhs, const Version2<T> &rhs) noexcept -> bool
{
    return !(lhs == rhs);
}

template <typename T>
inline constexpr auto operator<<(std::ostream &os, const Version2<T> &v) -> std::ostream &
{
    return os << std::to_string(v.Major) << "." << std::to_string(v.Minor);
}

template <typename T>
inline constexpr auto operator<(const Version3<T> &lhs, const Version3<T> &rhs) noexcept -> bool
{
    return std::tie(lhs.Major, lhs.Minor, lhs.Patch) < std::tie(rhs.Major, rhs.Minor, rhs.Patch);
}

template <typename T>
inline constexpr auto operator<=(const Version3<T> &lhs, const Version3<T> &rhs) noexcept -> bool
{
    return std::tie(lhs.Major, lhs.Minor, lhs.Patch) <= std::tie(rhs.Major, rhs.Minor, rhs.Patch);
}

template <typename T>
inline constexpr auto operator>(const Version3<T> &lhs, const Version3<T> &rhs) noexcept -> bool
{
    return std::tie(lhs.Major, lhs.Minor, lhs.Patch) > std::tie(rhs.Major, rhs.Minor, rhs.Patch);
}

template <typename T>
inline constexpr auto operator>=(const Version3<T> &lhs, const Version3<T> &rhs) noexcept -> bool
{
    return std::tie(lhs.Major, lhs.Minor, lhs.Patch) >= std::tie(rhs.Major, rhs.Minor, rhs.Patch);
}

template <typename T>
inline constexpr auto operator==(const Version3<T> &lhs, const Version3<T> &rhs) noexcept -> bool
{
    return lhs.Major == rhs.Major && lhs.Minor == rhs.Minor && lhs.Patch == rhs.Patch;
}

template <typename T>
inline constexpr auto operator!=(const Version3<T> &lhs, const Version3<T> &rhs) noexcept -> bool
{
    return !(lhs == rhs);
}

template <typename T>
inline constexpr auto operator<<(std::ostream &os, const Version3<T> &v) -> std::ostream &
{
    return os << v.Major << "." << v.Minor << "." << v.Patch;
}

template <typename T>
inline constexpr auto operator<(const Version4<T> &lhs, const Version4<T> &rhs) noexcept -> bool
{
    return std::tie(lhs.Major, lhs.Minor, lhs.Patch, lhs.Build) < std::tie(rhs.Major, rhs.Minor, rhs.Patch, rhs.Build);
}

template <typename T>
inline constexpr auto operator<=(const Version4<T> &lhs, const Version4<T> &rhs) noexcept -> bool
{
    return std::tie(lhs.Major, lhs.Minor, lhs.Patch, lhs.Build) <= std::tie(rhs.Major, rhs.Minor, rhs.Patch, rhs.Build);
}

template <typename T>
inline constexpr auto operator>(const Version4<T> &lhs, const Version4<T> &rhs) noexcept -> bool
{
    return std::tie(lhs.Major, lhs.Minor, lhs.Patch, lhs.Build) > std::tie(rhs.Major, rhs.Minor, rhs.Patch, rhs.Build);
}

template <typename T>
inline constexpr auto operator>=(const Version4<T> &lhs, const Version4<T> &rhs) noexcept -> bool
{
    return std::tie(lhs.Major, lhs.Minor, lhs.Patch, lhs.Build) >= std::tie(rhs.Major, rhs.Minor, rhs.Patch, rhs.Build);
}

template <typename T>
inline constexpr auto operator==(const Version4<T> &lhs, const Version4<T> &rhs) noexcept -> bool
{
    return lhs.Major == rhs.Major && lhs.Minor == rhs.Minor && lhs.Patch == rhs.Patch && lhs.Build == rhs.Build;
}

template <typename T>
inline constexpr auto operator!=(const Version4<T> &lhs, const Version4<T> &rhs) noexcept -> bool
{
    return !(lhs == rhs);
}

template <typename T>
inline constexpr auto operator<<(std::ostream &os, const Version4<T> &v) -> std::ostream &
{
    return os << v.Major << "." << v.Minor << "." << v.Patch << "." << v.Build;
}

} // namespace aeon::Common
