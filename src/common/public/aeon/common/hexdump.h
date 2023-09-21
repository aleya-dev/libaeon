// Distributed under the BSD 2-Clause License - Copyright 2012-2023 Robin Degen

#pragma once

#include <cstdio>

namespace aeon::Common::HexDump
{

void PrettyPrint(FILE *dest, const void *src, const std::size_t len) noexcept;
void CppArray(FILE *dest, const char *const arrayName, const void *src, const std::size_t len) noexcept;

} // namespace aeon::Common::HexDump
