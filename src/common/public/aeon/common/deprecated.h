// Distributed under the BSD 2-Clause License - Copyright 2012-2023 Robin Degen

#pragma once

#if (defined(AEON_IGNORE_DEPRECATED))
#define AEON_DEPRECATED(message)
#else
#define AEON_DEPRECATED(message) [[deprecated(message)]]
#endif
