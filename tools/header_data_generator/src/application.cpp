// Distributed under the BSD 2-Clause License - Copyright 2012-2023 Robin Degen

#include "application.h"
#include <aeon/streams/devices/file_device.h>
#include <aeon/streams/stream_reader.h>
#include <aeon/streams/stream_writer.h>
#include <aeon/common/commandline_parser.h>
#include <aeon/common/string_utils.h>
#include <filesystem>
#include <iostream>

namespace aeon::header_data_generator
{

constexpr auto exe_name = "aeon_reflection_generator";
constexpr auto default_namespace_name = "aeon::data";
constexpr auto default_data_type = "std::uint8_t";

constexpr auto max_hex_bytes_per_line = 16;

[[nodiscard]] auto parse_arguments(Common::CommandlineParser &parser, int argc, char *argv[])
{
    parser.AddPositional("source_file", "The source header file for which to generate reflection data.");
    parser.AddPositional("dest_file", "The destination for the generated reflection data.");
    parser.AddOption("v", "Verbose.");
    parser.AddOption("h", "Show help text.");
    parser.AddArgument("n", "Set a custom name for the namespace. The default is aeon::data");
    parser.AddArgument(
        "d", "Set a custom name for the data variable. The default is to base this on the source file name.");
    parser.AddArgument("t", "Override the std::uint8_t type with a custom one (must be 8 bits)");

    return parser.Parse(argc, argv);
}

[[nodiscard]] auto generate_variable_name(const std::filesystem::path &path)
{
    auto filename = Common::String{path.filename().string()};
    Common::StringUtils::Trim(filename);
    Common::StringUtils::Replace(filename, " ", "-");
    Common::StringUtils::Replace(filename, ".", "_");
    Common::StringUtils::ToLower(filename);
    return filename;
}

[[nodiscard]] auto read_source_data(const std::filesystem::path &source)
{
    streams::file_source_device src_device{source};
    const streams::stream_reader src_reader{src_device};
    return src_reader.read_to_vector<std::uint8_t>();
}

void generate(const std::filesystem::path &source, const std::filesystem::path &destination,
              const Common::StringView namespace_name, const Common::StringView data_name, const Common::StringView data_type,
              const bool verbose)
{
    if (verbose)
        std::cout << "Reading source file.\n";

    const auto data = read_source_data(source);

    if (verbose)
        std::cout << "Opening destination file for writing.\n";

    streams::file_sink_device dst_device{destination};
    streams::stream_writer dst_writer{dst_device};

    if (verbose)
        std::cout << "Generating header...\n";

    dst_writer << "// This is a generated file. Do not modify.\n\n";
    dst_writer << "#pragma once\n\n";
    dst_writer << "#include <cstdint>\n\n";
    dst_writer << "namespace " << namespace_name << "\n";
    dst_writer << "{\n\n";

    dst_writer << "constexpr static " << data_type << " " << data_name << "[] =\n";
    dst_writer << "{\n";

    dst_writer << "    ";

    auto hex_bytes_per_line = 0;
    for (const auto b : data)
    {
        dst_writer << "0x" << Common::StringUtils::Uint8ToHexString(b) << ", ";

        if (++hex_bytes_per_line >= max_hex_bytes_per_line)
        {
            dst_writer << "\n    ";
            hex_bytes_per_line = 0;
        }
    }

    dst_writer << "\n};\n\n";

    dst_writer << "} // namespace " << namespace_name << "\n";

    dst_device.flush();

    if (verbose)
        std::cout << "Done.\n";
}

auto application::main(const int argc, char *argv[]) noexcept -> int // NOLINT(bugprone-exception-escape)
{
    Common::CommandlineParser CommandlineParser;
    auto args = parse_arguments(CommandlineParser, argc, argv);

    if (!args)
    {
        std::cerr << "Invalid arguments.\n";
        CommandlineParser.PrintHelpText(exe_name);
        return 1;
    }

    if (args.HasOption("h"))
    {
        CommandlineParser.PrintHelpText(exe_name);
        return 0;
    }

    const auto source_file = std::filesystem::path{args.Positional(0).AsStdStringView()};
    const auto destination_file = std::filesystem::path{args.Positional(1).AsStdStringView()};

    if (!std::filesystem::exists(source_file))
    {
        std::cerr << "Source file does not exist.\n";
        return 1;
    }

    const auto namespace_name = args.GetArgument("n", default_namespace_name);
    const auto generated_variable_name = generate_variable_name(source_file);
    const auto data_name = args.GetArgument("d", generated_variable_name.AsStdStringView());
    const auto data_type = args.GetArgument("t", default_data_type);
    const auto verbose = args.HasOption("v");

    generate(source_file, destination_file, namespace_name, data_name, data_type, verbose);

    return 0;
}

} // namespace aeon::header_data_generator
