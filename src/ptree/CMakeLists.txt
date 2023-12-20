# Distributed under the BSD 2-Clause License - Copyright 2012-2023 Robin Degen

file(GLOB_RECURSE
    SOURCES
    CONFIGURE_DEPENDS
    "private/*"
    "public/*"
)

source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${SOURCES})

add_library(aeon_ptree
    STATIC
        ${SOURCES}
)

set_target_properties(aeon_ptree PROPERTIES
    FOLDER dep/libaeon
    LINKER_LANGUAGE CXX
)

target_include_directories(aeon_ptree
    PUBLIC
        public
)

target_link_libraries(aeon_ptree
    aeon_common
    aeon_rdp
    aeon_reflection
    aeon_streams
    aeon_unicode
    aeon_variant
)

install(
    DIRECTORY public/aeon
    DESTINATION include
)

if (AEON_ENABLE_TESTING)
    add_subdirectory(tests)
endif ()
