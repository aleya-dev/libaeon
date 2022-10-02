// Distributed under the BSD 2-Clause License - Copyright 2012-2022 Robin Degen

#pragma once

#include <aeon/common/unordered_flatmap.h>
#include <aeon/common/unordered_flatset.h>
#include <string>
#include <vector>
#include <tuple>
#include <string_view>
#include <stdexcept>

namespace aeon::common
{

class [[nodiscard]] commandline_parse_result final
{
public:
    commandline_parse_result() noexcept
        : result_{false}
        , positional_{}
        , options_{}
        , arguments_{}
    {
    }

    explicit commandline_parse_result(std::vector<std::string_view> positional,
                                      unordered_flatset<std::string_view> options,
                                      unordered_flatmap<std::string_view, std::string_view> arguments) noexcept
        : result_{true}
        , positional_{std::move(positional)}
        , options_{std::move(options)}
        , arguments_{std::move(arguments)}
    {
    }

    ~commandline_parse_result() = default;

    commandline_parse_result(const commandline_parse_result &) = default;
    auto operator=(const commandline_parse_result &) -> commandline_parse_result & = default;

    commandline_parse_result(commandline_parse_result &&) noexcept = default;
    commandline_parse_result &operator=(commandline_parse_result &&) noexcept = default;

    [[nodiscard]] auto success() const noexcept -> bool
    {
        return result_;
    }

    [[nodiscard]] auto failed() const noexcept -> bool
    {
        return !success();
    }

    [[nodiscard]] operator bool() const noexcept
    {
        return success();
    }

    [[nodiscard]] auto positional(const std::size_t i) const -> std::string_view
    {
        if (failed())
            throw std::logic_error{"Parse result failed."};

        if (i >= std::size(positional_))
            throw std::out_of_range{"index out of range"};

        return positional_[i];
    }

    [[nodiscard]] auto has_option(const std::string_view option) const -> bool
    {
        if (failed())
            throw std::logic_error{"Parse result failed."};

        return options_.contains(option);
    }

    [[nodiscard]] auto has_argument(const std::string_view arg) const -> bool
    {
        if (failed())
            throw std::logic_error{"Parse result failed."};

        return arguments_.contains(arg);
    }

    [[nodiscard]] auto get_argument(const std::string_view arg) const -> std::string_view
    {
        if (failed())
            throw std::logic_error{"Parse result failed."};

        const auto result = arguments_.find(arg);

        if (result != std::end(arguments_))
            return result->second;

        throw std::out_of_range{"Argument not found."};
    }

    [[nodiscard]] auto get_argument(const std::string_view arg, const std::string_view default_value) const
        -> std::string_view
    {
        if (failed())
            throw std::logic_error{"Parse result failed."};

        const auto result = arguments_.find(arg);

        if (result != std::end(arguments_))
            return result->second;

        return default_value;
    }

private:
    bool result_;
    std::vector<std::string_view> positional_;
    unordered_flatset<std::string_view> options_;
    unordered_flatmap<std::string_view, std::string_view> arguments_;
};

class commandline_parser final
{
public:
    commandline_parser();
    ~commandline_parser();

    commandline_parser(const commandline_parser &) = default;
    auto operator=(const commandline_parser &) -> commandline_parser & = default;

    commandline_parser(commandline_parser &&) noexcept = default;
    commandline_parser &operator=(commandline_parser &&) noexcept = default;

    void add_positional(std::string name, std::string description);
    void add_option(const std::string &name, std::string description);
    void add_argument(const std::string &name, std::string description);

    auto parse(const int argc, char *argv[]) const -> commandline_parse_result;
    auto parse(const std::vector<std::string_view> &args) const -> commandline_parse_result;

    void print_help_text(const std::string_view exe_name) const;

private:
    [[nodiscard]] auto is_option(const std::string_view arg) const noexcept -> bool;
    [[nodiscard]] auto is_argument(const std::string_view arg) const noexcept -> bool;

    unordered_flatmap<std::string, std::string> positional_;
    unordered_flatmap<std::string, std::string> options_;
    unordered_flatmap<std::string, std::string> arguments_;
};

} // namespace aeon::common
