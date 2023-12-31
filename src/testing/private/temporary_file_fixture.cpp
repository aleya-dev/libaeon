// Distributed under the BSD 2-Clause License - Copyright 2012-2023 Robin Degen

#include <aeon/testing/temporary_file_fixture.h>
#include <aeon/common/tempfile.h>
#include <filesystem>

namespace aeon::testutils
{

temporary_file::temporary_file()
    : path_(common::generate_temporary_file_path())
{
}

temporary_file::temporary_file(const common::string &extension)
    : path_(common::generate_temporary_file_path())
{
    path_.replace_extension(extension.str());
}

temporary_file::~temporary_file()
{
    [[maybe_unused]] std::error_code ec;
    if (std::filesystem::exists(path_, ec))
        delete_temporary_file();
}

[[nodiscard]] auto temporary_file::get_temporary_file_path() const -> std::filesystem::path
{
    return path_;
}

[[nodiscard]] auto temporary_file::assert_temporary_file_present() const -> bool
{
    return std::filesystem::exists(path_);
}

void temporary_file::delete_temporary_file() const noexcept
{
    [[maybe_unused]] std::error_code ec;
    std::filesystem::remove(path_, ec);
}

} // namespace aeon::testutils
