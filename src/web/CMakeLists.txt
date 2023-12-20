# Distributed under the BSD 2-Clause License - Copyright 2012-2023 Robin Degen

file(GLOB_RECURSE
    SOURCES
    CONFIGURE_DEPENDS
    "private/*"
    "public/*"
)

source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${SOURCES})

add_library(aeon_web STATIC
    ${SOURCES}
)

set_target_properties(aeon_web PROPERTIES
    FOLDER dep/libaeon
    LINKER_LANGUAGE CXX
)

target_include_directories(aeon_web
    PUBLIC
        public
)

target_link_libraries(aeon_web
    aeon_common
    aeon_streams
    aeon_sockets
    aeon_ptree
)

install(
    DIRECTORY public/aeon
    DESTINATION include
)

install(
    TARGETS aeon_web
    RUNTIME DESTINATION bin
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib
)

if (AEON_ENABLE_TESTING)
    add_subdirectory(tests)
endif ()

add_subdirectory(testapps)
