# Distributed under the BSD 2-Clause License - Copyright 2012-2023 Robin Degen

file(GLOB_RECURSE
    SOURCES
    CONFIGURE_DEPENDS
    "private/*"
    "public/*"
)

source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${SOURCES})

add_library(aeon_common STATIC
    ${SOURCES}
)

set_target_properties(aeon_common PROPERTIES
    FOLDER dep/libaeon
    LINKER_LANGUAGE CXX
)

target_include_directories(aeon_common
    PUBLIC
        public
    PRIVATE
        ${CMAKE_BINARY_DIR}
)

# On linux, we must link with libdl to use dlopen, dlclose etc.
if (UNIX AND NOT APPLE)
    target_link_libraries(aeon_common dl)
endif ()

# On unix we must link to a threading library like pthread
if (UNIX)
    set(CMAKE_THREAD_PREFER_PTHREAD ON)
    find_package(Threads)

    target_link_libraries(aeon_common
        ${CMAKE_THREAD_LIBS_INIT}
    )
endif ()

install(
    DIRECTORY public/aeon
    DESTINATION include
)

install(
    TARGETS aeon_common
    RUNTIME DESTINATION bin
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib
)

if (AEON_ENABLE_TESTING)
    add_subdirectory(tests)
endif ()
