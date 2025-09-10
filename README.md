# Silver (Ag)
## A platform-independent library of runtime tools

Ag (inspired by the periodic table symbol for Silver) represents a set of
non-domain-specific libraries which underpin the
[Mighty Oak](https://github.com/GiantRobotLemur/MightyOak) project has gone
on to form the basis of other projects since.

The motivation here is that I'm fed up of creating everything from the ground
up in C++. There are so many common tools missing from the runtime libraries
or differences between platform runtime libraries which need to be written
around that I decided to invest in creating re-usable components which I
could use in my projects to be able to reduce the amount of set-up and boiler
plate code I had to write just to get going.

These libraries are intended mostly for internal use. They are completely
annotated with Doxygen comments, although could benefit from more detailed
explanation about various topics.

* [Core](Doc/Core.md) - A base runtime library providing components missing
  in C/C++ runtime.
* [Symbol Packager](Doc/SymbolPackager.md) - A stand-alone tools to extract
  symbols from binaries and packages them for use at runtime to create readable
  stack traces by the Core library.
* QtInterop - A library which integrates Core with Qt6.
* [Geometry](Doc/Geometry.md) - A 2D geometry library which implements
  primitives and low-complexity algorithms for line intersection, polygon/hole
  tracing and decomposition of polygons into triangle.
* WriteGlyphGeometry - A Win32 tool to extract the geometry of glyphs from
  a font to use in the unit tests for the Geometry library.
* [Win32Base](Doc/Win32Base.md) - A library which provides basic tools for
  creating a native Win32 GUI application and other low-level Win32 tools
  such as COM interface wrappers.
* [Sdl3Tools](Doc/Sdl3Tools.md) - C++ wrappers for the SDL 3 library, focusing
  on its GPU framework.
* [ObjectGL](Doc/ObjectGL.md) - C++ wrappers for the OpenGL API, including
  entry point resolution and built-in error checking.

This repository has been created so that it can be a git sub-module within
another. It provides not only C++ libraries, but also CMake utilities which
are available to the parent repository.