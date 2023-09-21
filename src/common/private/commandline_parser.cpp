#include <aeon/common/commandline_parser.h>
#include <aeon/common/string_utils.h>
#include <aeon/common/fmtflags.h>
#include <iostream>

namespace aeon::Common
{

CommandlineParser::CommandlineParser() = default;

CommandlineParser::~CommandlineParser() = default;

void CommandlineParser::AddPositional(String name, String description)
{
    m_positional.Emplace(std::move(name), std::move(description));
}

void CommandlineParser::AddOption(const String &name, String description)
{
    String argName;

    if (name.Size() == 1)
        argName = "-" + name;
    else
        argName = "--" + name;

    m_options.Emplace(std::move(argName), std::move(description));
}

void CommandlineParser::AddArgument(const String &name, String description)
{
    String argName;

    if (name.Size() == 1)
        argName = "-" + name;
    else
        argName = "--" + name;

    m_arguments.Emplace(std::move(argName), std::move(description));
}

auto CommandlineParser::Parse(const int argc, char *argv[]) const -> CommandlineParseResult
{
    std::vector<StringView> arguments;

    arguments.reserve(argc - 1);
    for (auto i = 1; i < argc; ++i)
        arguments.emplace_back(argv[i]);

    return Parse(arguments);
}

auto CommandlineParser::Parse(const std::vector<StringView> &args) const -> CommandlineParseResult
{
    if (std::size(args) < m_positional.Size())
        return {};

    auto itr = std::begin(args);

    std::vector<StringView> positional;
    for (auto i = 0u; i < m_positional.Size(); ++i)
    {
        positional.emplace_back(*itr);
        ++itr;
    }

    Containers::UnorderedFlatset<StringView> options;
    Containers::UnorderedFlatmap<StringView, StringView> arguments;

    for (; itr != std::end(args); ++itr)
    {
        if (IsOption(*itr))
        {
            options.Insert(StringUtils::CharStrippedLeftsv(*itr, '-'));
        }
        else if (IsArgument(*itr))
        {
            const auto argName = StringUtils::CharStrippedLeftsv(*itr, '-');
            ++itr;

            if (itr == std::end(args))
                return {};

            arguments.Insert(argName, *itr);
        }
        else
        {
            return {};
        }
    }

    return CommandlineParseResult{std::move(positional), std::move(options), std::move(arguments)};
}

void CommandlineParser::PrintHelpText(const StringView exeName) const
{
    ScopedFmtFlags flags{std::cout};

    std::cout << exeName << ' ';
    for (const auto &arg : m_positional)
    {
        std::cout << arg.first << ' ';
    }

    if (!m_arguments.Empty())
    {
        std::cout << "[args] ";
    }

    if (!m_options.Empty())
    {
        std::cout << "[options] ";
    }

    std::cout << '\n';

    constexpr auto argColumnWidth = 25;

    if (!m_positional.Empty())
    {
        std::cout << "\nPositional arguments: \n";
    }

    for (const auto &arg : m_positional)
    {
        std::cout << std::left << std::setw(argColumnWidth) << arg.first << std::right << std::setw(10) << arg.second
                  << '\n';
    }

    if (!m_arguments.Empty())
    {
        std::cout << "\nArguments: \n";
    }

    for (const auto &arg : m_arguments)
    {
        auto argStr = arg.first + " value";
        std::cout << std::left << std::setw(argColumnWidth) << argStr << std::right << std::setw(10) << arg.second
                  << '\n';
    }

    if (!m_options.Empty())
    {
        std::cout << "\nOptions: \n";
    }

    for (const auto &arg : m_options)
    {
        std::cout << std::left << std::setw(argColumnWidth) << arg.first << std::right << std::setw(10) << arg.second
                  << '\n';
    }
}

auto CommandlineParser::IsOption(const StringView arg) const noexcept -> bool
{
    return m_options.Contains(String{arg});
}

auto CommandlineParser::IsArgument(const StringView arg) const noexcept -> bool
{
    return m_arguments.Contains(String{arg});
}

} // namespace aeon::Common
