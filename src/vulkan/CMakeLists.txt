# Distributed under the BSD 2-Clause License - Copyright 2012-2023 Robin Degen

add_subdirectory(vma)

file(GLOB_RECURSE
    SOURCES
    CONFIGURE_DEPENDS
    "private/*"
    "public/*"
)

source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${SOURCES})

add_library(aeon_vulkan STATIC
    ${SOURCES}
)

set_target_properties(aeon_vulkan PROPERTIES
    FOLDER dep/libaeon
)

target_include_directories(aeon_vulkan
    PUBLIC
        public
    PRIVATE
        private
)

target_link_libraries(aeon_vulkan
    aeon_common
    aeon_streams
    aeon_math
    aeon_platform
    aeon_imaging
    aeon_vulkan_vma
    Vulkan::Vulkan
)

install(
    DIRECTORY public/aeon
    DESTINATION include
)

if (AEON_ENABLE_TESTING)
    add_subdirectory(tests)
endif ()

add_subdirectory(example)
