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
        'enable_unittests': [True, False],
        'enable_benchmarks': [True, False],
        'with_common': [True, False],
        'with_compression': [True, False],
        'with_crypto': [True, False],
        'with_file_container': [True, False],
        'with_fonts': [True, False],
        'with_imaging': [True, False],
        'with_logger': [True, False],
        'with_math': [True, False],
        'with_platform': [True, False],
        'with_platform_glfw': [True, False],
        'with_platform_sdl2': [True, False],
        'with_plugins': [True, False],
        'with_ptree': [True, False],
        'with_rdp': [True, False],
        'with_reflection': [True, False],
        'with_serial': [True, False],
        'with_sockets': [True, False],
        'with_streams': [True, False],
        'with_testing': [True, False],
        'with_tracelog': [True, False],
        'with_unicode': [True, False],
        'with_variant': [True, False],
        'with_vulkan': [True, False],
        'with_web': [True, False]
    }

    default_options = {
        'shared': False,
        'fPIC': True,
        'enable_unittests': True,
        'enable_benchmarks': True,
        'with_common': True,
        'with_compression': True,
        'with_crypto': True,
        'with_file_container': True,
        'with_fonts': True,
        'with_imaging': True,
        'with_logger': True,
        'with_math': True,
        'with_platform': True,
        'with_platform_glfw': True,
        'with_platform_sdl2': True,
        'with_plugins': True,
        'with_ptree': True,
        'with_rdp': True,
        'with_reflection': True,
        'with_serial': True,
        'with_sockets': True,
        'with_streams': True,
        'with_testing': True,
        'with_tracelog': True,
        'with_unicode': True,
        'with_variant': True,
        'with_vulkan': True,
        'with_web': True
    }

    def configure(self):
        if self.options.shared:
            del self.options.fPIC

        if not self.options.with_platform:
            del self.options.with_platform_glfw
            del self.options.with_platform_sdl2

    def config_options(self):
        if self.settings.os == 'Windows':
            del self.options.fPIC

    def requirements(self):
        if self.options.get_safe('enable_unittests', False):
            self.requires('gtest/1.13.0')

        if self.options.get_safe('enable_benchmarks', False):
            self.requires('benchmark/1.8.3')

        if self.options.get_safe('with_compression', False):
            self.requires('zlib/1.2.13')

        if self.options.get_safe('with_fonts', False):
            self.requires('freetype/2.13.0')

        if self.options.get_safe('with_imaging', False):
            self.requires('libpng/1.6.40')
            self.requires('libjpeg-turbo/2.1.91')

        if self.options.get_safe('with_platform', False) and self.options.get_safe('with_platform_glfw', False):
            self.requires('glfw/3.3.8')

        if self.options.get_safe('with_platform', False) and self.options.get_safe('with_platform_sdl2', False):
            self.requires('sdl/2.28.3')

        if self.options.get_safe('with_sockets', False):
            self.requires('asio/1.28.0')

        if self.options.get_safe('with_vulkan', False):
            self.requires('vulkan-memory-allocator/3.0.1')

    def generate(self):
        tc = CMakeToolchain(self)
        tc.variables['BUILD_SHARED_LIBS'] = self.options.shared
        tc.variables['CMAKE_POSITION_INDEPENDENT_CODE'] = \
            self.options.get_safe('fPIC', default=False) or self.options.shared

        tc.variables['AEON_ENABLE_TESTING'] = self.options.enable_unittests
        tc.variables['AEON_ENABLE_BENCHMARK'] = self.options.enable_benchmarks

        tc.variables['AEON_COMPONENT_COMMON'] = self.options.get_safe('with_common', default=False)
        tc.variables['AEON_COMPONENT_COMPRESSION'] = self.options.get_safe('with_compression', default=False)
        tc.variables['AEON_COMPONENT_CRYPTO'] = self.options.get_safe('with_crypto', default=False)
        tc.variables['AEON_COMPONENT_FILE_CONTAINER'] = self.options.get_safe('with_file_container', default=False)
        tc.variables['AEON_COMPONENT_FONTS'] = self.options.get_safe('with_fonts', default=False)
        tc.variables['AEON_COMPONENT_IMAGING'] = self.options.get_safe('with_imaging', default=False)
        tc.variables['AEON_COMPONENT_LOGGER'] = self.options.get_safe('with_logger', default=False)
        tc.variables['AEON_COMPONENT_MATH'] = self.options.get_safe('with_math', default=False)
        tc.variables['AEON_COMPONENT_PLATFORM'] = self.options.get_safe('with_platform', default=False)
        tc.variables['AEON_COMPONENT_PLUGINS'] = self.options.get_safe('with_plugins', default=False)
        tc.variables['AEON_COMPONENT_PTREE'] = self.options.get_safe('with_ptree', default=False)
        tc.variables['AEON_COMPONENT_RDP'] = self.options.get_safe('with_rdp', default=False)
        tc.variables['AEON_COMPONENT_REFLECTION'] = self.options.get_safe('with_reflection', default=False)
        tc.variables['AEON_COMPONENT_SERIAL'] = self.options.get_safe('with_serial', default=False)
        tc.variables['AEON_COMPONENT_SOCKETS'] = self.options.get_safe('with_sockets', default=False)
        tc.variables['AEON_COMPONENT_STREAMS'] = self.options.get_safe('with_streams', default=False)
        tc.variables['AEON_COMPONENT_TESTING'] = self.options.get_safe('with_testing', default=False)
        tc.variables['AEON_COMPONENT_TRACELOG'] = self.options.get_safe('with_tracelog', default=False)
        tc.variables['AEON_COMPONENT_UNICODE'] = self.options.get_safe('with_unicode', default=False)
        tc.variables['AEON_COMPONENT_VARIANT'] = self.options.get_safe('with_variant', default=False)
        tc.variables['AEON_COMPONENT_VULKAN'] = self.options.get_safe('with_vulkan', default=False)
        tc.variables['AEON_COMPONENT_WEB'] = self.options.get_safe('with_web', default=False)

        tc.variables['AEON_PLATFORM_BACKEND_GLFW'] = self.options.get_safe('with_platform_glfw', default=False)
        tc.variables['AEON_PLATFORM_BACKEND_SDL2'] = self.options.get_safe('with_platform_sdl2', default=False)

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
