How to build
--------------
### Conan
You must first install Conan 2.x. libAeon will pull in packages from a private repository.

The following remote must be added:
https://artifactory.aleya.dev/artifactory/api/conan/aleya-group-conan

### Windows (Visual Studio 2022)

libAeon is tested on the most recent version of Visual Studio 2022. It is best to just install the latest stable version when building.

1.  Make sure you have cloned the submodules

    ```git submodule update --init```

2.  Run `bootstrap.cmd`

    This will download all dependencies and generate the Visual Studio solution and project files in the `build` subfolder.

3.  Load the solution in Visual Studio and build

### Linux

libAeon requires at least GCC 12

1.  Make sure you have cloned the submodules

    ```git submodule update --init```

2.  Run `./bootstrap.sh`

    This will download all dependencies and generate a Makefile in the `build` subfolder.

3.  Enter the `build` folder and run make

### MacOS

libAeon requires at least XCode 14.3

1.  Make sure you have cloned the submodules

    ```git submodule update --init```

2.  Run `./bootstrap.sh`

    This will download all dependencies and generate a Makefile in the `build` subfolder.

3.  Enter the `build` folder and run make

Alternatively you can also generate an XCode project to build. For this you can use the `./bootstrap_xcode.sh` script.

### FreeBSD

libAeon requires Clang to build on FreeBSD. There is no official support for this platform and it is not tested regularly.
There are no prebuilt dependencies available for this platform so you must build them manually through Conan.