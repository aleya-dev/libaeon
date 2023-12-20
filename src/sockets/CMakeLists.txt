# Distributed under the BSD 2-Clause License - Copyright 2012-2023 Robin Degen

if (NOT AEON_ENABLE_SUBMODULE_DEPENDENCIES)
    find_package(asio CONFIG)
endif ()

file(GLOB_RECURSE
    SOURCES
    CONFIGURE_DEPENDS
    "private/*"
    "public/*"
)

source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${SOURCES})

add_library(aeon_sockets STATIC
    ${SOURCES}
)

set_target_properties(aeon_sockets PROPERTIES
    FOLDER dep/libaeon
    LINKER_LANGUAGE CXX
)

target_include_directories(aeon_sockets
    PUBLIC
        public
)

target_link_libraries(aeon_sockets
    aeon_common
    aeon_streams
)

if (NOT AEON_ENABLE_SUBMODULE_DEPENDENCIES)
    target_link_libraries(aeon_sockets
        asio::asio
    )
else ()
    target_link_libraries(aeon_sockets
        asio
    )
endif ()

target_compile_definitions(aeon_sockets
    PUBLIC
        ASIO_NO_DEPRECATED
        ASIO_STANDALONE
        ASIO_HEADER_ONLY
        # ASIO uses deprecated windows api calls which raise a warning when targetting Windows 10
        _WINSOCK_DEPRECATED_NO_WARNINGS
)

install(
    DIRECTORY public/aeon
    DESTINATION include
)

install(
    TARGETS aeon_sockets
    RUNTIME DESTINATION bin
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib
)

if (AEON_ENABLE_TESTING)
    add_subdirectory(tests)
endif ()

add_subdirectory(testapps)
