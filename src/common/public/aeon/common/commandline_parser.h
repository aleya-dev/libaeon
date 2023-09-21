// Distributed under the BSD 2-Clause License - Copyright 2012-2023 Robin Degen

#pragma once

#include <aeon/common/containers/unordered_flatmap.h>
#include <aeon/common/containers/unordered_flatset.h>
#include <aeon/common/string.h>
#include <aeon/common/string_view.h>
#include <vector>
#include <tuple>
#include <stdexcept>

namespace aeon::Common
{

class [[nodiscard]] CommandlineParseResult final
{
public:
    CommandlineParseResult() noexcept
        : m_result{false}
        , m_positional{}
        , m_options{}
        , m_arguments{}
    {
    }

    explicit CommandlineParseResult(std::vector<StringView> positional,
                                    Containers::UnorderedFlatset<StringView> options,
                                    Containers::UnorderedFlatmap<StringView, StringView> arguments) noexcept
        : m_result{true}
        , m_positional{std::move(positional)}
        , m_options{std::move(options)}
        , m_arguments{std::move(arguments)}
    {
    }

    ~CommandlineParseResult() = default;

    CommandlineParseResult(const CommandlineParseResult &) = default;
    auto operator=(const CommandlineParseResult &) -> CommandlineParseResult & = default;

    CommandlineParseResult(CommandlineParseResult &&) noexcept = default;
    CommandlineParseResult &operator=(CommandlineParseResult &&) noexcept = default;

    [[nodiscard]] auto Success() const noexcept -> bool
    {
        return m_result;
    }

    [[nodiscard]] auto Failed() const noexcept -> bool
    {
        return !Success();
    }

    [[nodiscard]] operator bool() const noexcept
    {
        return Success();
    }

    [[nodiscard]] auto Positional(const std::size_t i) const -> StringView
    {
        if (Failed())
            throw std::logic_error{"Parse result failed."};

        if (i >= std::size(m_positional))
            throw std::out_of_range{"index out of range"};

        return m_positional[i];
    }

    [[nodiscard]] auto HasOption(const StringView option) const -> bool
    {
        if (Failed())
            throw std::logic_error{"Parse result failed."};

        return m_options.Contains(option);
    }

    [[nodiscard]] auto HasArgument(const StringView arg) const -> bool
    {
        if (Failed())
            throw std::logic_error{"Parse result failed."};

        return m_arguments.Contains(arg);
    }

    [[nodiscard]] auto GetArgument(const StringView arg) const -> StringView
    {
        if (Failed())
            throw std::logic_error{"Parse result failed."};

        const auto result = m_arguments.Find(arg);

        if (result != std::end(m_arguments))
            return result->second;

        throw std::out_of_range{"Argument not found."};
    }

    [[nodiscard]] auto GetArgument(const StringView arg, const StringView defaultValue) const -> StringView
    {
        if (Failed())
            throw std::logic_error{"Parse result failed."};

        const auto result = m_arguments.Find(arg);

        if (result != std::end(m_arguments))
            return result->second;

        return defaultValue;
    }

private:
    bool m_result;
    std::vector<StringView> m_positional;
    Containers::UnorderedFlatset<StringView> m_options;
    Containers::UnorderedFlatmap<StringView, StringView> m_arguments;
};

class CommandlineParser final
{
public:
    CommandlineParser();
    ~CommandlineParser();

    CommandlineParser(const CommandlineParser &) = default;
    auto operator=(const CommandlineParser &) -> CommandlineParser & = default;

    CommandlineParser(CommandlineParser &&) noexcept = default;
    CommandlineParser &operator=(CommandlineParser &&) noexcept = default;

    void AddPositional(String name, String description);
    void AddOption(const String &name, String description);
    void AddArgument(const String &name, String description);

    auto Parse(const int argc, char *argv[]) const -> CommandlineParseResult;
    auto Parse(const std::vector<StringView> &args) const -> CommandlineParseResult;

    void PrintHelpText(const StringView exeName) const;

private:
    [[nodiscard]] auto IsOption(const StringView arg) const noexcept -> bool;
    [[nodiscard]] auto IsArgument(const StringView arg) const noexcept -> bool;

    Containers::UnorderedFlatmap<String, String> m_positional;
    Containers::UnorderedFlatmap<String, String> m_options;
    Containers::UnorderedFlatmap<String, String> m_arguments;
};

} // namespace aeon::Common
