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

#include <aeon/common/dll_loader.h>
#include <aeon/common/platform.h>
#include <cassert>

#if (defined(AEON_PLATFORM_OS_WINDOWS))
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
static const std::string dll_extension = ".dll";
#elif (defined(AEON_PLATFORM_OS_LINUX))
#include <dlfcn.h>
static const std::string dll_extension = ".so";
#elif (defined(AEON_PLATFORM_OS_MACOS))
#include <dlfcn.h>
static const std::string dll_extension = ".dylib";
#endif

namespace aeon::common::dll_loader
{

#if (defined(AEON_PLATFORM_OS_WINDOWS))
dll_handle get_dll_handle(const char *filename)
{
    const auto real_filename = filename + dll_extension;
    return LoadLibrary(real_filename.c_str());
}

void free_dll_handle(const dll_handle handle)
{
    if (handle)
        FreeLibrary(static_cast<HMODULE>(handle));
}

void *get_dll_proc_address(const dll_handle handle, const char *proc)
{
    return GetProcAddress(static_cast<HMODULE>(handle), proc);
}

#elif (defined(AEON_PLATFORM_OS_LINUX) || defined(AEON_PLATFORM_OS_MACOS))
dll_handle get_dll_handle(const char *filename)
{
#if (defined(AEON_PLATFORM_OS_LINUX))
    // On linux, the given path must be prepended by "./", otherwise
    // the .so file will not get loaded as expected.
    //
    // From the documentation (https://linux.die.net/man/3/dlopen):
    // "If filename contains a slash ("/"), then it is interpreted as a
    // (relative or absolute) pathname. Otherwise, the dynamic linker searches
    // for the library (...)"
    const auto real_filename = std::string("./") + filename + dll_extension;
#else
    const auto real_filename = filename + dll_extension;
#endif
    return dlopen(real_filename.c_str(), RTLD_LAZY);
}

void free_dll_handle(const dll_handle handle)
{
    if (handle)
        dlclose(handle);
}

void *get_dll_proc_address(const dll_handle handle, const char *proc)
{
    return dlsym(handle, proc);
}
#endif

} // namespace aeon::common::dll_loader