# Distributed under the BSD 2-Clause License - Copyright 2012-2023 Robin Degen

file(GLOB_RECURSE
    SOURCES
    CONFIGURE_DEPENDS
    "private/*"
    "public/*"
)

source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${SOURCES})

add_library(aeon_reflection STATIC
    ${SOURCES}
)

set_target_properties(aeon_reflection PROPERTIES
    FOLDER dep/libaeon
    LINKER_LANGUAGE CXX
)

target_include_directories(aeon_reflection
    PUBLIC
        public
        ${CMAKE_CURRENT_BINARY_DIR}
    PRIVATE
        private
)

target_link_libraries(aeon_reflection
    PRIVATE
        aeon_common
)

install(
    DIRECTORY public/aeon
    DESTINATION include
)

install(
    TARGETS aeon_reflection
    RUNTIME DESTINATION bin
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib
)

set(AEON_REFLECTION_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/public/)
configure_file(reflection_path.h.in reflection_path.h @ONLY)

if (AEON_ENABLE_TESTING)
    add_subdirectory(tests)
endif ()
