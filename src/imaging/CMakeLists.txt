# Distributed under the BSD 2-Clause License - Copyright 2012-2023 Robin Degen

if (NOT AEON_ENABLE_SUBMODULE_DEPENDENCIES)
    find_package(PNG CONFIG)
    find_package(libjpeg-turbo CONFIG)
endif ()

file(GLOB_RECURSE
    SOURCES
    CONFIGURE_DEPENDS
    "private/*"
    "public/*"
)

source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${SOURCES})

add_library(aeon_imaging STATIC
    ${SOURCES}
)

set_target_properties(aeon_imaging PROPERTIES
    FOLDER dep/libaeon
    LINKER_LANGUAGE CXX
)

target_include_directories(aeon_imaging
    PUBLIC
        public
)

target_link_libraries(aeon_imaging
    aeon_common
    aeon_math
    aeon_streams
)

if (NOT AEON_ENABLE_SUBMODULE_DEPENDENCIES)
    target_link_libraries(aeon_imaging
        PNG::PNG
        libjpeg-turbo::libjpeg-turbo
    )
else ()
    target_link_libraries(aeon_imaging
        png_static
        turbojpeg-static
    )
endif ()

install(
    DIRECTORY public/aeon
    DESTINATION include
)

install(
    TARGETS aeon_imaging
    RUNTIME DESTINATION bin
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib
)

if (AEON_ENABLE_TESTING)
    add_subdirectory(tests)
endif ()
