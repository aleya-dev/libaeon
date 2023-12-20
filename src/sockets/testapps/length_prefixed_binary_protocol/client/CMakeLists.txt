# Distributed under the BSD 2-Clause License - Copyright 2012-2023 Robin Degen

file(GLOB_RECURSE
    SOURCES
    CONFIGURE_DEPENDS
    "private/*"
)

source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${SOURCES})

add_executable(aeon_sockets_length_prefixed_binary_protocol_client
    ${SOURCES}
)

set_target_properties(aeon_sockets_length_prefixed_binary_protocol_client PROPERTIES
    FOLDER dep/libaeon
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
)

target_include_directories(aeon_sockets_length_prefixed_binary_protocol_client
    PRIVATE
        private
)

target_link_libraries(aeon_sockets_length_prefixed_binary_protocol_client
    aeon_sockets
)
