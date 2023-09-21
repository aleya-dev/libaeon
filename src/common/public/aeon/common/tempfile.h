// Distributed under the BSD 2-Clause License - Copyright 2012-2023 Robin Degen

#pragma once

#include <aeon/common/uuid.h>
#include <filesystem>

namespace aeon::Common
{

[[nodiscard]] inline auto GenerateTemporaryFilePath()
{
    const auto uuid = Uuid::Generate();
    return std::filesystem::temp_directory_path() / uuid.Str().Str();
}

} // namespace aeon::Common
