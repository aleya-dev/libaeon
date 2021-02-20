// Distributed under the BSD 2-Clause License - Copyright 2012-2021 Robin Degen

#include <aeon/streams/dynamic_stream.h>
#include <aeon/streams/devices/file_device.h>
#include <aeon/streams/stream_writer.h>
#include <aeon/common/string.h>
#include <aeon/common/timer.h>
#include "generator.h"

namespace aeon::gl::generator
{

namespace detail
{

[[nodiscard]] auto generate_proc_name(const std::string &name)
{
    return "PFN" + common::string::to_upper_copy(name) + "PROC";
}

} // namespace detail

generator::generator(const opengl_definition &definition)
    : definition_{definition}
{
}

void generator::write_header(const std::filesystem::path &path) const
{
    const common::timer timer;

    std::cout << "Writing header " << path.filename() << "... ";

    auto output_stream = streams::make_dynamic_stream(streams::file_sink_device{path});

    generate_header(output_stream);
    generate_header_additional_source_lines(output_stream);
    generate_header_enum_definitions(output_stream);
    generate_header_function_definitions(output_stream);
    generate_footer(output_stream);

    std::cout << " Took: " << std::fixed << timer.get_time_difference<double>() << " seconds.\n";
}

void generator::write_inline_header(const std::filesystem::path &path) const
{
    const common::timer timer;

    std::cout << "Writing inline header " << path.filename() << "... ";

    auto output_stream = streams::make_dynamic_stream(streams::file_sink_device{path});

    generate_header(output_stream);
    generate_inline_header_function_definitions(output_stream);
    generate_footer(output_stream);

    generate_inline_header_initialize_impl(output_stream);

    std::cout << " Took: " << std::fixed << timer.get_time_difference<double>() << " seconds.\n";
}

void generator::generate_header(streams::idynamic_stream &output_file) const
{
    streams::stream_writer writer{output_file};
    writer << "// This file is generated by the Aeon OpenGL Registry parser tool.\n\n";
    writer << "#pragma once\n\n";
    writer << "#include <aeon/gl/gl_export.h>\n\n";
    writer << "#ifndef KHRONOS_STATIC\n";
    writer << "#define KHRONOS_STATIC\n";
    writer << "#endif\n\n";
    writer << "#ifdef __cplusplus\n";
    writer << "extern \"C\" {\n";
    writer << "#endif\n\n";
}

void generator::generate_footer(streams::idynamic_stream &output_file) const
{
    streams::stream_writer writer{output_file};
    writer << "#ifdef __cplusplus\n";
    writer << "}\n";
    writer << "#endif\n";
}

void generator::generate_header_additional_source_lines(streams::idynamic_stream &output_file) const
{
    streams::stream_writer writer{output_file};

    for (const auto &line : definition_.additional_code())
    {
        writer << line << '\n';
    }

    writer << '\n';
}

void generator::generate_header_enum_definitions(streams::idynamic_stream &output_file) const
{
    streams::stream_writer writer{output_file};

    for (const auto &enum_value : definition_.enum_values())
    {
        writer << "#define " << enum_value.name << "    " << enum_value.value << '\n';
    }

    writer << '\n';
}

void generator::generate_header_function_definitions(streams::idynamic_stream &output_file) const
{
    streams::stream_writer writer{output_file};

    for (const auto &function : definition_.functions())
    {
        const auto proc_name = detail::generate_proc_name(function.name());
        const auto aeon_name = "aeon_" + function.name();

        writer << "using " << proc_name << " = " << function.return_type() << "(KHRONOS_APIENTRY)(";

        const auto &arguments = function.arguments();
        for (auto i = 0ull; i < std::size(arguments); ++i)
        {
            // Hack Workaround: If the type contains [], it has to be placed after the name.
            if (common::string::contains<char>(arguments[i].type, '['))
            {
                const auto split = common::string::split(arguments[i].type, '[');
                writer << split[0] << " " << arguments[i].name << '[' << split[1];
            }
            else
            {
                writer << arguments[i].type << " " << arguments[i].name;
            }

            if (i + 1ull < std::size(arguments))
                writer << ", ";
        }
        writer << ");\n";

        writer << "extern AEON_GL_EXPORT " << proc_name << "* " << aeon_name << ";\n";
        writer << "#undef " << function.name() << "\n";
        writer << "#define " << function.name() << " " << aeon_name << "\n";
        writer << "\n";
    }

    writer << "\n\n";
}

void generator::generate_inline_header_function_definitions(streams::idynamic_stream &output_file) const
{
    streams::stream_writer writer{output_file};

    for (const auto &function : definition_.functions())
    {
        const auto proc_name = detail::generate_proc_name(function.name());
        const auto aeon_name = "aeon_" + function.name();
        writer << proc_name << " *" << aeon_name << ";\n";
    }

    writer << "\n\n";
}

void generator::generate_inline_header_initialize_impl(streams::idynamic_stream &output_file) const
{
    streams::stream_writer writer{output_file};

    writer << "namespace aeon::gl::internal\n";
    writer << "{\n";
    writer << "template <typename T>\n";
    writer << "void initialize_" << definition_.definition_name() << "_impl(T &&get_proc_address)\n";
    writer << "{\n";

    for (const auto &function : definition_.functions())
    {
        const auto proc_name = detail::generate_proc_name(function.name());
        const auto aeon_name = "aeon_" + function.name();
        writer << "    " << aeon_name << " = (" << proc_name << "*) get_proc_address(\"" << function.name() << "\");\n";
    }

    writer << "}\n";
    writer << "} // aeon::gl::internal\n\n";
}

} // namespace aeon::gl::generator