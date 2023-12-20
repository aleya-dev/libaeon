# Distributed under the BSD 2-Clause License - Copyright 2012-2023 Robin Degen

if (NOT AEON_ENABLE_SUBMODULE_DEPENDENCIES)
    find_package(ZLIB CONFIG)
endif ()

file(GLOB_RECURSE
    SOURCES
    CONFIGURE_DEPENDS
    "private/*"
    "public/*"
)

source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${SOURCES})

add_library(aeon_compression STATIC
    ${SOURCES}
)

set_target_properties(aeon_compression PROPERTIES
    FOLDER dep/libaeon
)

target_include_directories(aeon_compression
    PUBLIC
        public
)

target_link_libraries(aeon_compression
    aeon_common
    aeon_streams
)

if (NOT AEON_ENABLE_SUBMODULE_DEPENDENCIES)
    target_link_libraries(aeon_compression
        ZLIB::ZLIB
    )
else ()
    target_link_libraries(aeon_compression
        zlibstatic
    )
endif ()

install(
    DIRECTORY public/aeon
    DESTINATION include
)

if (AEON_ENABLE_TESTING)
    add_subdirectory(tests)
endif ()
