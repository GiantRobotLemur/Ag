# The Ag Core Library

Ag Core is the lowest level library. It provides the most basic functionality
for up-stream code. It is dependent upon the platform C Runtime Library
(currently MSVC Runtime and glibc), the C++ Standard Template Library and, in
the case of Windows, the Win32 subsystem and shell. Currently Ag Core is not
dependent upon any third party libraries which are not available to the host
platform as standard, although testing does require
[Google Test](https://github.com/google/googletest.git).

Some notable features of the Core library are:
* Optimised low-level binary operations (bit scan, byte order, etc.).
* Tools for dynamic management of in-line memory blocks.
* Enumeration metadata tools.
* Support for Unicode conversions.
* Immutable UTF-8 strings.
* An Immutable exception class hierarchy with stack traces.
* Symbol use in stack traces.
* Try/Catch mechanism for hardware exceptions.
* A robust application framework including command line handling.
* Optimised sorted linear maps and sets.
* String formatting using type-safe variable arguments.
* URI management.
* File path management using both Win32 and POSIX-style paths.
* Platform agnostic file system integration.