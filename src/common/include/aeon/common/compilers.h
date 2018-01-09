/*
 * Copyright (c) 2012-2018 Robin Degen
 *
 * Permission is hereby granted, free of charge, to any person
 * obtaining a copy of this software and associated documentation
 * files (the "Software"), to deal in the Software without
 * restriction, including without limitation the rights to use,
 * copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following
 * conditions:
 *
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
 * OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
 * HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
 * WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 */

#pragma once

#include <aeon/common/platform.h>

#if (AEON_PLATFORM_OS_WINDOWS)
#define AEON_IGNORE_VS_WARNING(nnn) __pragma(warning(disable : nnn))
#define AEON_IGNORE_VS_WARNING_PUSH(nnn) __pragma(warning(push)) __pragma(warning(disable : nnn))
#define AEON_IGNORE_VS_WARNING_POP() __pragma(warning(pop))
#else // (AEON_PLATFORM_OS_WINDOWS)
#define AEON_IGNORE_VS_WARNING(nnn)
#define AEON_IGNORE_VS_WARNING_PUSH(nnn)
#define AEON_IGNORE_VS_WARNING_POP()
#endif

#if (AEON_PLATFORM_OS_WINDOWS)
#define AEON_PACK_STRUCT_PUSH(nnn) __pragma(pack(push, nnn))
#define AEON_PACK_STRUCT_POP(nnn) __pragma(pack(pop))
#else
#define AEON_PACK_STRUCT_PUSH(nnn)
#define AEON_PACK_STRUCT_POP(nnn) __attribute__((aligned(nnn), packed))
#endif
