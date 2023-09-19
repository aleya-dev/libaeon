from conan import ConanFile
from conan.tools.cmake import CMake, CMakeToolchain, CMakeDeps
from conan.tools.files import rmdir
import os

required_conan_version = ">=2.0"


class LibAeonConan(ConanFile):
    name = 'libaeon'
    description = 'A general purpose C++20 support library.'
    license = 'BSD-2-Clause'
    homepage = 'https://git.aeons.dev/aeon-engine/libaeon'
    url = 'https://git.aeons.dev/aeon-engine/libaeon'
    settings = "os", "compiler", "build_type", "arch"

    options = {
        'shared': [True, False],
        'fPIC': [True, False],
        'libaeon_enable_unittests': [True, False],
        'libaeon_enable_benchmarks': [True, False],
        'libaeon_with_common': [True, False],
        'libaeon_with_compression': [True, False],
        'libaeon_with_crypto': [True, False],
        'libaeon_with_file_container': [True, False],
        'libaeon_with_fonts': [True, False],
        'libaeon_with_imaging': [True, False],
        'libaeon_with_logger': [True, False],
        'libaeon_with_math': [True, False],
        'libaeon_with_platform': [True, False],
        'libaeon_with_platform_glfw': [True, False],
        'libaeon_with_platform_sdl2': [True, False],
        'libaeon_with_plugins': [True, False],
        'libaeon_with_ptree': [True, False],
        'libaeon_with_rdp': [True, False],
        'libaeon_with_reflection': [True, False],
        'libaeon_with_serial': [True, False],
        'libaeon_with_sockets': [True, False],
        'libaeon_with_streams': [True, False],
        'libaeon_with_testing': [True, False],
        'libaeon_with_tracelog': [True, False],
        'libaeon_with_unicode': [True, False],
        'libaeon_with_variant': [True, False],
        'libaeon_with_vulkan': [True, False],
        'libaeon_with_web': [True, False]
    }

    default_options = {
        'shared': False,
        'fPIC': True,
        'libaeon_enable_unittests': True,
        'libaeon_enable_benchmarks': True,
        'libaeon_with_common': True,
        'libaeon_with_compression': True,
        'libaeon_with_crypto': True,
        'libaeon_with_file_container': True,
        'libaeon_with_fonts': True,
        'libaeon_with_imaging': True,
        'libaeon_with_logger': True,
        'libaeon_with_math': True,
        'libaeon_with_platform': True,
        'libaeon_with_platform_glfw': True,
        'libaeon_with_platform_sdl2': True,
        'libaeon_with_plugins': True,
        'libaeon_with_ptree': True,
        'libaeon_with_rdp': True,
        'libaeon_with_reflection': True,
        'libaeon_with_serial': True,
        'libaeon_with_sockets': True,
        'libaeon_with_streams': True,
        'libaeon_with_testing': True,
        'libaeon_with_tracelog': True,
        'libaeon_with_unicode': True,
        'libaeon_with_variant': True,
        'libaeon_with_vulkan': True,
        'libaeon_with_web': True
    }

    def configure(self):
        if self.options.shared:
            del self.options.fPIC

        if not self.options.libaeon_with_platform:
            del self.options.libaeon_with_platform_glfw
            del self.options.libaeon_with_platform_sdl2

    def config_options(self):
        if self.settings.os == 'Windows':
            del self.options.fPIC

        if self.settings.os == 'Macos' or self.settings.os == 'iOS':
            del self.options.libaeon_with_serial
            del self.options.libaeon_with_vulkan

    def requirements(self):
        if self.options.get_safe('libaeon_enable_unittests', False):
            self.requires('gtest/1.13.0')

        if self.options.get_safe('libaeon_enable_benchmarks', False):
            self.requires('benchmark/1.8.3')

        if self.options.get_safe('libaeon_with_compression', False):
            self.requires('zlib/1.2.13')

        if self.options.get_safe('libaeon_with_fonts', False):
            self.requires('freetype/2.13.0')

        if self.options.get_safe('libaeon_with_imaging', False):
            self.requires('libpng/1.6.40')
            self.requires('libjpeg-turbo/2.1.91')

        if self.options.get_safe('libaeon_with_platform', False) and self.options.get_safe('libaeon_with_platform_glfw',
                                                                                           False):
            self.requires('glfw/3.3.8')

        if self.options.get_safe('libaeon_with_platform', False) and self.options.get_safe('libaeon_with_platform_sdl2',
                                                                                           False):
            self.requires('sdl/2.28.3')

        if self.options.get_safe('libaeon_with_sockets', False):
            self.requires('asio/1.28.0')

        if self.options.get_safe('libaeon_with_vulkan', False):
            self.requires('vulkan-memory-allocator/3.0.1')

    def generate(self):
        tc = CMakeToolchain(self)
        tc.variables['BUILD_SHARED_LIBS'] = self.options.shared
        tc.variables['CMAKE_POSITION_INDEPENDENT_CODE'] = \
            self.options.get_safe('fPIC', default=False) or self.options.shared

        tc.variables['AEON_libaeon_enable_TESTING'] = self.options.libaeon_enable_unittests
        tc.variables['AEON_libaeon_enable_BENCHMARK'] = self.options.libaeon_enable_benchmarks

        tc.variables['AEON_COMPONENT_COMMON'] = self.options.get_safe('libaeon_with_common', default=False)
        tc.variables['AEON_COMPONENT_COMPRESSION'] = self.options.get_safe('libaeon_with_compression', default=False)
        tc.variables['AEON_COMPONENT_CRYPTO'] = self.options.get_safe('libaeon_with_crypto', default=False)
        tc.variables['AEON_COMPONENT_FILE_CONTAINER'] = self.options.get_safe('libaeon_with_file_container',
                                                                              default=False)
        tc.variables['AEON_COMPONENT_FONTS'] = self.options.get_safe('libaeon_with_fonts', default=False)
        tc.variables['AEON_COMPONENT_IMAGING'] = self.options.get_safe('libaeon_with_imaging', default=False)
        tc.variables['AEON_COMPONENT_LOGGER'] = self.options.get_safe('libaeon_with_logger', default=False)
        tc.variables['AEON_COMPONENT_MATH'] = self.options.get_safe('libaeon_with_math', default=False)
        tc.variables['AEON_COMPONENT_PLATFORM'] = self.options.get_safe('libaeon_with_platform', default=False)
        tc.variables['AEON_COMPONENT_PLUGINS'] = self.options.get_safe('libaeon_with_plugins', default=False)
        tc.variables['AEON_COMPONENT_PTREE'] = self.options.get_safe('libaeon_with_ptree', default=False)
        tc.variables['AEON_COMPONENT_RDP'] = self.options.get_safe('libaeon_with_rdp', default=False)
        tc.variables['AEON_COMPONENT_REFLECTION'] = self.options.get_safe('libaeon_with_reflection', default=False)
        tc.variables['AEON_COMPONENT_SERIAL'] = self.options.get_safe('libaeon_with_serial', default=False)
        tc.variables['AEON_COMPONENT_SOCKETS'] = self.options.get_safe('libaeon_with_sockets', default=False)
        tc.variables['AEON_COMPONENT_STREAMS'] = self.options.get_safe('libaeon_with_streams', default=False)
        tc.variables['AEON_COMPONENT_TESTING'] = self.options.get_safe('libaeon_with_testing', default=False)
        tc.variables['AEON_COMPONENT_TRACELOG'] = self.options.get_safe('libaeon_with_tracelog', default=False)
        tc.variables['AEON_COMPONENT_UNICODE'] = self.options.get_safe('libaeon_with_unicode', default=False)
        tc.variables['AEON_COMPONENT_VARIANT'] = self.options.get_safe('libaeon_with_variant', default=False)
        tc.variables['AEON_COMPONENT_VULKAN'] = self.options.get_safe('libaeon_with_vulkan', default=False)
        tc.variables['AEON_COMPONENT_WEB'] = self.options.get_safe('libaeon_with_web', default=False)

        tc.variables['AEON_PLATFORM_BACKEND_GLFW'] = self.options.get_safe('libaeon_with_platform_glfw', default=False)
        tc.variables['AEON_PLATFORM_BACKEND_SDL2'] = self.options.get_safe('libaeon_with_platform_sdl2', default=False)

        tc.generate()
        deps = CMakeDeps(self)
        deps.generate()

    def build(self):
        cmake = CMake(self)
        cmake.configure()
        cmake.build()

    def package(self):
        cmake = CMake(self)
        cmake.install()

        tools.remove_files_by_mask(self.package_folder, "*.pdb")
        tools.remove_files_by_mask(self.package_folder, "*.exe")
