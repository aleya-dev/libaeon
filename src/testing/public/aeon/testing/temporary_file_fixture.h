// Distributed under the BSD 2-Clause License - Copyright 2012-2023 Robin Degen

#pragma once

#include <aeon/common/string.h>

#ifdef ENABLE_TEMPORARY_FILE_FIXTURE
#include <gtest/gtest.h>
#endif // ENABLE_TEMPORARY_FILE_FIXTURE

#include <filesystem>

namespace aeon::testutils
{

class temporary_file
{
public:
    temporary_file();
    explicit temporary_file(const common::string &extension);

    ~temporary_file();

    temporary_file(temporary_file &&) = delete;
    auto operator=(temporary_file &&) -> temporary_file & = delete;

    temporary_file(const temporary_file &) = delete;
    auto operator=(const temporary_file &) -> temporary_file & = delete;

    [[nodiscard]] auto get_temporary_file_path() const -> std::filesystem::path;

    [[nodiscard]] auto assert_temporary_file_present() const -> bool;

    void delete_temporary_file() const noexcept;

protected:
    std::filesystem::path path_;
};

// If gtest was included before this header, enable the test fixture code.
#ifdef ENABLE_TEMPORARY_FILE_FIXTURE
struct temporary_file_fixture : public temporary_file, public ::testing::Test
{
};
#endif // ENABLE_TEMPORARY_FILE_FIXTURE

} // namespace aeon::testutils
