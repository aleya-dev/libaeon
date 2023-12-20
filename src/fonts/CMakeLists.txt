# Distributed under the BSD 2-Clause License - Copyright 2012-2023 Robin Degen

if (NOT AEON_ENABLE_SUBMODULE_DEPENDENCIES)
    find_package(freetype CONFIG)
endif ()

file(GLOB_RECURSE
    SOURCES
    CONFIGURE_DEPENDS
    "private/*"
    "public/*"
)

source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${SOURCES})

add_library(aeon_fonts STATIC
    ${SOURCES}
)

set_target_properties(aeon_fonts PROPERTIES
    FOLDER dep/libaeon
    LINKER_LANGUAGE CXX
)

target_include_directories(aeon_fonts
    PUBLIC
        public
)

target_link_libraries(aeon_fonts
    aeon_common
    aeon_imaging
    aeon_streams
)

if (NOT AEON_ENABLE_SUBMODULE_DEPENDENCIES)
    target_link_libraries(aeon_fonts
        Freetype::Freetype
    )
else ()
    target_link_libraries(aeon_fonts
        freetype
    )
endif ()

install(
    DIRECTORY public/aeon
    DESTINATION include
)

install(
    TARGETS aeon_fonts
    RUNTIME DESTINATION bin
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib
)

if (AEON_ENABLE_TESTING)
    add_subdirectory(tests)
endif ()
