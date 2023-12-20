# Distributed under the BSD 2-Clause License - Copyright 2012-2023 Robin Degen

option(AEON_PLATFORM_BACKEND_GLFW "Use GLFW as backing library for Platform" ON)
option(AEON_PLATFORM_BACKEND_SDL2 "Use SDL2 as backing library for Platform" ON)

if (NOT AEON_ENABLE_SUBMODULE_DEPENDENCIES)
    if (AEON_PLATFORM_BACKEND_GLFW)
        find_package(glfw3 CONFIG)
    endif ()

    if (AEON_PLATFORM_BACKEND_SDL2)
        find_package(SDL2 CONFIG)
    endif ()
endif ()

message(STATUS "Platform backends:")

if (AEON_PLATFORM_BACKEND_GLFW)
    message(STATUS " - GLFW")
endif ()

if (AEON_PLATFORM_BACKEND_SDL2)
    message(STATUS " - SDL2")
endif ()

include(GenerateExportHeader)

file(GLOB_RECURSE
    SOURCES
    CONFIGURE_DEPENDS
    "private/common/*"
    "public/*"
)

if (AEON_PLATFORM_BACKEND_GLFW)
    file(GLOB_RECURSE
        GLFW_PLATFORM_SOURCES
        CONFIGURE_DEPENDS
        "private/platforms/glfw/*"
    )
endif ()

if (AEON_PLATFORM_BACKEND_SDL2)
    file(GLOB_RECURSE
        SDL2_PLATFORM_SOURCES
        CONFIGURE_DEPENDS
        "private/platforms/sdl2/*"
    )
endif ()

source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES
    ${SOURCES}
    ${GLFW_PLATFORM_SOURCES}
    ${SDL2_PLATFORM_SOURCES}
)

add_library(aeon_platform
    ${SOURCES}
    ${GLFW_PLATFORM_SOURCES}
    ${SDL2_PLATFORM_SOURCES}
)

generate_export_header(aeon_platform
    EXPORT_FILE_NAME public/aeon/platform/platform_export.h
)

set_target_properties(aeon_platform PROPERTIES
    FOLDER dep/libaeon
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
)

target_include_directories(aeon_platform
    PUBLIC
        public
        ${CMAKE_CURRENT_BINARY_DIR}/public
    PRIVATE
        private
)

target_link_libraries(aeon_platform
    aeon_common
    aeon_math
)

if (NOT AEON_ENABLE_SUBMODULE_DEPENDENCIES)
    if (AEON_PLATFORM_BACKEND_GLFW)
        target_link_libraries(aeon_platform
            glfw::glfw
        )
    endif ()

    if (AEON_PLATFORM_BACKEND_SDL2)
        target_link_libraries(aeon_platform
            SDL2::SDL2
        )
    endif ()
else ()
    if (AEON_PLATFORM_BACKEND_GLFW)
        target_link_libraries(aeon_platform
            glfw3
        )
    endif ()

    if (AEON_PLATFORM_BACKEND_SDL2)
        target_link_libraries(aeon_platform
            sdl
        )
    endif ()
endif ()

install(
    DIRECTORY public/aeon
    DESTINATION include
)

add_subdirectory(example)

configure_file(platform_config.h.in public/aeon/platform/platform_config.h @ONLY)
