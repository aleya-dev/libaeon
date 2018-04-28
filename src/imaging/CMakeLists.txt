# Copyright (c) 2012-2018 Robin Degen
#
# Permission is hereby granted, free of charge, to any person
# obtaining a copy of this software and associated documentation
# files (the "Software"), to deal in the Software without
# restriction, including without limitation the rights to use,
# copy, modify, merge, publish, distribute, sublicense, and/or sell
# copies of the Software, and to permit persons to whom the
# Software is furnished to do so, subject to the following
# conditions:
#
# The above copyright notice and this permission notice shall be
# included in all copies or substantial portions of the Software.
#
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
# EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
# OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
# NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
# HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
# WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
# FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
# OTHER DEALINGS IN THE SOFTWARE.

add_subdirectory(${CMAKE_SOURCE_DIR}/dep/zlib dep/zlib)
add_subdirectory(${CMAKE_SOURCE_DIR}/dep/png dep/png)
add_subdirectory(${CMAKE_SOURCE_DIR}/dep/libjpeg_turbo dep/libjpeg_turbo)

set(LIB_AEON_IMAGING_SOURCE
    include/aeon/imaging/exceptions.h
    include/aeon/imaging/dimension.h
    include/aeon/imaging/iterator.h
    include/aeon/imaging/descriptor.h
    include/aeon/imaging/pixel_encoding.h
    include/aeon/imaging/pixel_iterator.h
    include/aeon/imaging/scanline_iterator.h
    include/aeon/imaging/image.h
    src/image.cpp
)

source_group(imaging FILES ${LIB_AEON_IMAGING_SOURCE})

set(LIB_AEON_IMAGING_FILE_SOURCE
    include/aeon/imaging/file/bmp_file.h
    src/file/bmp_file.cpp
    include/aeon/imaging/file/png_file.h
    src/file/png_file.cpp
    include/aeon/imaging/file/jpg_file.h
    src/file/jpg_file.cpp
    include/aeon/imaging/file/tjhandle_wrapper.h
    include/aeon/imaging/file/png_structs.h
    include/aeon/imaging/file/png_read_structs.h
    include/aeon/imaging/file/png_write_structs.h
)

source_group(imaging\\file FILES ${LIB_AEON_IMAGING_FILE_SOURCE})

set(LIB_AEON_IMAGING_GENERATORS_SOURCE
    include/aeon/imaging/generators/simplex_noise.h
)

source_group(imaging\\generators FILES ${LIB_AEON_IMAGING_GENERATORS_SOURCE})

set(LIB_AEON_IMAGING_CONVERTERS_SOURCE
    include/aeon/imaging/converters/convert_pixel.h
    include/aeon/imaging/converters/convert_encoding.h
    src/converters/convert_encoding.cpp
    include/aeon/imaging/converters/stride.h
    src/converters/stride.cpp
)

source_group(imaging\\converters FILES ${LIB_AEON_IMAGING_CONVERTERS_SOURCE})

set(LIB_AEON_IMAGING_FILTERS_SOURCE
    include/aeon/imaging/filters/invert.h
    src/filters/invert.cpp
)

source_group(imaging\\filters FILES ${LIB_AEON_IMAGING_FILTERS_SOURCE})

add_library(aeon_imaging STATIC
    ${LIB_AEON_IMAGING_SOURCE}
    ${LIB_AEON_IMAGING_FILE_SOURCE}
    ${LIB_AEON_IMAGING_GENERATORS_SOURCE}
    ${LIB_AEON_IMAGING_CONVERTERS_SOURCE}
    ${LIB_AEON_IMAGING_FILTERS_SOURCE}
)

set_target_properties(aeon_imaging PROPERTIES
    FOLDER dep/libaeon
    LINKER_LANGUAGE CXX
)

target_include_directories(aeon_imaging PUBLIC include)
target_link_libraries(aeon_imaging
    aeon_utility
    aeon_common
    aeon_math
    png_static
    turbojpeg-static
)

install(
    DIRECTORY include
    DESTINATION include
)

add_subdirectory(tests)