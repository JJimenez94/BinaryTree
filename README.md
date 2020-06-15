# BinaryTree
 Binary Tree creation through Rest API using modern C++

## Dependencies

> [!IMPORTANT]
> In order to get the dependencies installed, I used [vcpkg](https://aka.ms/vcpkg) and set the environment variable `VCPKG_ROOT`, this helps me to do not add the `CMAKE_TOOLCHAIN_FILE` parameter into the project build.

- [Microsoft C++ Rest SDK](https://github.com/Microsoft/cpprestsdk).
- [SQLite](https://sqlite.org/index.html).
    > [!TIP]
    > vcpkg have a [recipe](https://github.com/microsoft/vcpkg/blob/master/docs/examples/installing-and-using-packages.md) to get SQLite instaled, you should consider using it.
