# BinaryTree
In order to remove slavery terms the stable branch it's called main instead of ~~master~~, to know more about this initiative please consider referring to this [thread](https://twitter.com/mislav/status/1270388510684598272). 

This repo intends to expose binary tree creation through Rest API using modern C++.

## Dependencies

> [!IMPORTANT]
> To get the dependencies installed, I used [vcpkg](https://aka.ms/vcpkg) and set the environment variable `VCPKG_ROOT`, this helps me to do not add the `CMAKE_TOOLCHAIN_FILE` parameter into the project build.

- [Microsoft C++ Rest SDK](https://github.com/Microsoft/cpprestsdk).
- [SQLite](https://sqlite.org/index.html).
    > [!TIP]
    > vcpkg have a [recipe](https://github.com/microsoft/vcpkg/blob/master/docs/examples/installing-and-using-packages.md) to get SQLite instaled, you should consider using it.

## Construction
Written using CMake and Modern C++, using VSCode and MS C++ compiler.