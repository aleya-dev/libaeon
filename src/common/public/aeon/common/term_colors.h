// Distributed under the BSD 2-Clause License - Copyright 2012-2023 Robin Degen

#pragma once

/* Color codes for colored console output. Can be used like this:
 * std::cout << AEON_TERM_COLOR_BLUE << "Blue! "
 *     << AEON_TERM_COLOR_RESET << "Normal!" << std::endl;
 */

// TODO: Just checking for windows may not be sufficient.
#if (!AEON_PLATFORM_OS_WINDOWS)
#define AeonTermColorReset "\033[0m"
#define AeonTermColorBold "\033[1m"
#define AeonTermColorBlack "\033[30m"
#define AeonTermColorRed "\033[31m"
#define AeonTermColorGreen "\033[32m"
#define AeonTermColorYellow "\033[33m"
#define AeonTermColorBlue "\033[34m"
#define AeonTermColorMagenta "\033[35m"
#define AeonTermColorCyan "\033[36m"
#define AeonTermColorWhite "\033[37m"
#endif // AEON_PLATFORM_OS_WINDOWS
