from conan import ConanFile
from conan.tools.cmake import cmake_layout


class SfmlSplines(ConanFile):
    settings = "os", "compiler", "build_type", "arch"
    generators = "CMakeDeps", "CMakeToolchain"

    def requirements(self):
        self.requires("sfml/3.0.2")
        self.requires("portable-file-dialogs/0.1.0")

    def layout(self):
        cmake_layout(self)
