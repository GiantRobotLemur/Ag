# Symbol Packager

The `SymbolPackager` tool can be built as part of the Ag repository, or if
being cross-compiled, can be provided as an external pre-built binary.

The `SymbolPackager` tool creates a .sym file with the same base name as
the target binary. For a shared object or executable binary, it can be
created using the CMake function `ag_enable_stacktrace(target)`. The
symbols within the file are compressed so that its size is a fraction of
the corresponding PDB file or binary symbol section.

If a binary is accompanied by its .sym file, the file will be read at
runtime to resolve symbols in stack traces. Stack traces are always
present in `Ag::Exception` derived objects.

If no symbols can be obtained, a stack trace will contain numeric
offsets. If the `SymbolPackager` tool is not available at build-time
(perhaps due to cross compilation), a warning is issued, but the build
can be configured as normal.

The CMake cache variable `AG_EXT_SYMBOL_PACKAGER` can be set to the path to a
pre-built `SymbolPackager` binary if building for another platform, such
as building for ARM64 Windows on x64 Windows.