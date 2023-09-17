# Distributed under the BSD 2-Clause License - Copyright 2012-2023 Robin Degen

option(AEON_PLATFORM_BACKEND_GLFW "Use GLFW as backing library for Platform" ON)

if (NOT AEON_ENABLE_SUBMODULE_DEPENDENCIES)
    if (AEON_PLATFORM_BACKEND_GLFW)
        find_package(glfw3 CONFIG)
    endif ()
endif ()

message(STATUS "Platform backends:")

if (AEON_PLATFORM_BACKEND_GLFW)
    message(STATUS " - GLFW")
endif ()

include(GenerateExportHeader)

set(SOURCES
    private/base_context.cpp
    private/base_context.h
    private/base_window.cpp
    private/base_window.h
    public/aeon/platform/context.h
    public/aeon/platform/exception.h
    public/aeon/platform/input_events.h
    public/aeon/platform/keyboard_key.h
    public/aeon/platform/keyboard_key_state.h
    public/aeon/platform/mouse_button.h
    public/aeon/platform/mouse_button_state.h
    public/aeon/platform/native_handles.h
    public/aeon/platform/window.h
    public/aeon/platform/window_create_info.h
    public/aeon/platform/window_events.h
    public/aeon/platform/window_iconification_state.h
)

if (AEON_PLATFORM_BACKEND_GLFW)
    set(PLATFORM_SOURCES
        private/platforms/glfw/glfw_context.cpp
        private/platforms/glfw/glfw_context.h
        private/platforms/glfw/glfw_exception.h
        private/platforms/glfw/glfw_init.h
        private/platforms/glfw/glfw_scoped_window.h
        private/platforms/glfw/glfw_window.cpp
        private/platforms/glfw/glfw_window.h
    )
endif ()


source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${SOURCES} ${PLATFORM_SOURCES})

add_library(aeon_platform
    ${SOURCES}
    ${PLATFORM_SOURCES}
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
else ()
    if (AEON_PLATFORM_BACKEND_GLFW)
        target_link_libraries(aeon_platform
            glfw3
        )
    endif ()
endif ()

install(
    DIRECTORY public/aeon
    DESTINATION include
)

add_subdirectory(example)

configure_file(platform_config.h.in public/aeon/platform/platform_config.h @ONLY)
