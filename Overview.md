# Ag (Silver) - Project Overview

## Identity

**Ag** (the periodic table symbol for Silver) is a cross-platform C++17 runtime
utility library suite. It underpins the
[Mighty Oak](https://github.com/GiantRobotLemur/MightyOak) project and serves
as a reusable foundation for other C++ projects by the same author.

- **License:** LGPL 3
- **Author:** GiantRobotLemur (GiantRobotLemur@na-se.co.uk)
- **Repository:** https://github.com/GiantRobotLemur/Ag
- **Designed as:** a git submodule consumed by parent projects
- **Build system:** CMake >= 3.21, C++17, multi-config (Debug / RelWithDebInfo)
- **Primary platform:** Windows (MSVC), with POSIX / Linux support

---

## Architecture & Library Hierarchy

```
AgCore  (foundation - no external deps beyond CRT/STL/bzip2)
  |
  +-- Geometry       (2D geometry primitives, DCEL, sweep-line, triangulation)
  |     |
  |     +-- Gfx2D    (abstract 2D scene graph, decomposes to GPU-ready triangles)
  |
  +-- Win32Base      (native Win32 GUI framework, GDI resources, COM wrappers)
  |
  +-- QtInterop      (bridges Core with Qt6)
  |
  +-- ObjectGL       (C++ OpenGL wrappers, entry point resolution, error checking)
  |
  +-- Sdl3Tools      (C++ wrappers for SDL3, GPU framework, event processing)

SymbolPackager       (standalone CLI tool - extracts symbols for stack traces)
WriteGlyphGeometry   (Win32 tool - extracts font glyph geometry for tests)
```

**Dependency graph (simplified):**
- `Gfx2D` -> `Geometry` -> `AgCore`
- `ObjectGL` -> `AgCore` (optionally SDL2/SDL3 drivers)
- `Sdl3Tools` -> `AgCore`
- `Win32Base` -> `AgCore`

Libraries are conditionally compiled via CMake options:
`AG_CONFIG_WIN32`, `AG_CONFIG_QT`, `AG_CONFIG_GFX`, `AG_CONFIG_OPEN_GL`,
`AG_CONFIG_SDL3`, etc.

---

## Directory Structure

```
Ag/
  CMakeLists.txt              Root build config
  cmake/
    ConfigureBuild.cmake      Compiler settings, FetchContent deps, SIMD options
    Utilities.cmake           ag_add_library(), ag_add_test_app(), ag_add_cli_app(), etc.
    Version.hpp.in            Version template
    Win32Version.rc.in        Win32 resource template
  Doc/                        Per-library markdown documentation
  Source/
    CMakeLists.txt            Orchestrates subdirectory inclusion
    Include/Ag/              Public headers (one folder per library)
      Core/                   Core public headers
      Geometry/               Geometry public headers
      Gfx2D/                  Gfx2D public headers
      ObjectGL/               OpenGL public headers (incl. Extensions/)
      Sdl3Tools/              SDL3 public headers
      Win32Base/              Win32 public headers
      Private/                Internal shared headers (Bz2Stream, SymbolEncoding)
    Core/                     Core implementation + tests (Test_*.cpp)
    Geometry/                 Geometry implementation + tests
    Gfx2D/                   Gfx2D implementation + tests
    ObjectGL/                 OpenGL implementation (Extensions/ subfolder)
    Sdl3Tools/                SDL3 implementation + tests
    Win32Base/                Win32 implementation
    QtInterop/                Qt6 interop
    SymbolPackager/           CLI tool
    WriteGlyphGeometry/       Font glyph extraction tool
    Template.cpp/.hpp         File templates for new modules
  Build/                      CMake build output (gitignored via build* pattern)
```

---

## Coding Style & Conventions

### File Layout
Every `.cpp` and `.hpp` follows a rigid template structure:
```cpp
//! @file <path>
//! @brief <description>
//! @author GiantRobotLemur@na-se.co.uk
//! @date <year range>
//! @copyright ... LGPL 3 ...
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Header File Includes (or "Dependent Header Files" in .hpp)
////////////////////////////////////////////////////////////////////////////////

namespace Ag {
namespace <SubLib> {  // e.g. Geom, Gfx2D

namespace {
////////////////////////////////////////////////////////////////////////////////
// Local Data Types
////////////////////////////////////////////////////////////////////////////////
// Local Data
// Local Functions
} // Anonymous namespace

////////////////////////////////////////////////////////////////////////////////
// <ClassName> Member Definitions
////////////////////////////////////////////////////////////////////////////////

}} // namespace Ag::<SubLib>
```
- Banner-style section separators using `////////////////////////////////////////////////////////////////////////////////`
- Template files (`Template.cpp`, `Template.hpp`) exist in each library for creating new files

### Naming
- **Namespaces:** `Ag`, `Ag::Geom`, `Ag::Gfx2D`, `Ag::GL`, `Ag::SDL`
- **Classes:** PascalCase (`String`, `AffineTransform2D`, `DecompositionContext`)
- **Methods:** camelCase with get/set/is/try prefixes (`getUtf8Length()`, `isEmpty()`, `tryGetNextByte()`)
- **Member fields:** `_camelCase` underscore-prefixed (`_encoded`, `_encodingLength`)
- **Constants:** PascalCase or UPPER_CASE (`NullID`, `EndIndex`, `MaxUTF8EncodingLength`)
- **Typedefs:** PascalCase with suffix conventions (`SPtr` = shared_ptr, `CPtr` = const pointer)
- **Header guards:** `__AG_<MODULE>_<FILE>_HPP__` style (double underscore, all caps)

### Code Patterns
- **Doxygen comments** on all public declarations (`//!` style)
- **Precompiled headers** per library (`PreCompiledHeader.hpp`)
- **Platform abstraction:** `Win32API.hpp` / `PosixAPI.hpp` paired source files
- **Immutable/frozen pattern:** objects can be made immutable after construction (Brush, Pen via GraphicArtefact)
- **PIMPL-like patterns:** `StringPrivate`, `DisplayContextPrivate`, `RenderContextPrivate`
- **Smart pointers:** `std::shared_ptr` used extensively for internal data sharing
- **SIMD dispatch:** `Operations.hpp` pattern with `Operations_Base.hpp`, `Operations_x64v1.hpp`, `Operations_x64v2.hpp` for architecture-specific optimisations
- **Custom string type:** `Ag::String` is an immutable UTF-8 string (not `std::string`)
- **Google Test** for unit testing, tests co-located in library source folders as `Test_<Feature>.cpp`
- **`.natvis` files** for MSVC debugger visualisation (Core, Geometry)

### Build System
- Custom CMake functions: `ag_add_library()`, `ag_add_test_app()`, `ag_add_gui_app()`, `ag_add_cli_app()`
- External dependencies via `FetchContent`: bzip2, Google Test, GLM, SDL2, SDL3
- SIMD/architecture levels: `AG_ENABLE_X64_V1` through `AG_ENABLE_X64_V4`
- Static runtime option: `AG_STATIC_RUNTIME`
- `Source/Extra/` directory for temporary projects (gitignored)
- `AgOptions.cmake` in parent directory for external preset configuration

---

## Current State & Outstanding Work

### Active Branch: `Gfx2D_Decomposition`
The current branch is focused on implementing the graphic decomposition pipeline
in the Gfx2D library - converting the abstract scene graph into GPU-ready
triangle data.

### Libraries by Maturity

| Library | Status | Notes |
|---------|--------|-------|
| **Core** | Mature | Comprehensive test suite (20+ test files), stable API |
| **Geometry** | Mature | Extensive: DCEL, sweep-line, boolean ops, triangulation, Bezier curves, SIMD |
| **ObjectGL** | Mature | Complete OpenGL wrapper with all vendor extensions |
| **Win32Base** | Mature | Full Win32 GUI framework |
| **Sdl3Tools** | Active | SDL3 wrappers, event processing, recently added polling events |
| **Gfx2D** | In Progress | Scene graph skeleton exists; decomposition pipeline is WIP |
| **QtInterop** | Minimal | Just CommandLineWrangler and Conversion |
| **SymbolPackager** | Mature | PDB, GNU map, nm file readers |

### Outstanding Work / TODOs Found in Code
- **Gfx2D:** `Graphic` class has a TODO about deriving from `GraphicArtefact` for freezeability
- **Gfx2D:** Commented-out `decompose()` virtual method on `Graphic` - the decomposition interface is being designed
- **Gfx2D:** CMakeLists.txt has TODOs for ObjectGL-specific and SDL3-specific GPU drivers
- **Gfx2D:** `GraphicDecomposition.cpp` is essentially empty (template-only)
- **Gfx2D:** Missing tests for most components (only `Test_Operations.cpp` and `Test_Colours.cpp`)
- **ConfigureBuild.cmake:** TODO to auto-detect x86-64 architecture level via `try_run()`
- **Geometry:** `Grahpics.uxf` appears to be a typo (should be `Graphics.uxf`)

### Potential Issues / Flaws
1. **Header guards use reserved identifiers:** Double-underscore prefixed names (`__AG_CORE_STRING_HPP__`) are reserved by the C++ standard. Should use single-underscore or `#pragma once`.
2. **Self-inclusion in String.hpp:** Line 23 includes `"String.hpp"` from within `String.hpp` itself - likely meant to include a different header or is a copy-paste error.
3. **Build directory in repo:** The `Build/` directory contains `.cmake` API reply files that appear to be checked in, despite `build*` being in `.gitignore` (the capital `B` may not match the pattern on case-sensitive systems).
4. **`FATAL` vs `FATAL_ERROR`:** In `ConfigureBuild.cmake` line 112, `message(FATAL ...)` should be `message(FATAL_ERROR ...)` - `FATAL` alone is not a valid CMake message mode.
5. **Duplicate SSE4.1/4.2 config:** In `ag_configure_sdl3()`, `SDL_SSE4_2` is set twice per branch (once with "SSE4.2" comment, once with "SSE4.1" comment) - the `SDL_SSE4_1` variable is never set.
6. **SDL2 still declared:** `FetchContent_Declare(SDL2 ...)` and `ag_configure_sdl2()` exist but SDL2 support appears vestigial since the move to SDL3.
7. **Posix code paths use `${targetName}` instead of `${destTargetName}`:** In `ag_enable_proxy_stacktrace()`, the Linux branch references `${targetName}` which is the old parameter name, but the function signature uses `destTargetName`/`symbolTargetName`.

---

## External Dependencies

| Dependency | Version | Purpose |
|-----------|---------|---------|
| bzip2 | master | Compression for symbol data (compiled in) |
| Google Test | 1.12.1 | Unit testing |
| GLM | 1.0.1 | Math library (when GFX or OpenGL enabled) |
| SDL3 | 3.2.10 | Windowing, events, GPU framework |
| SDL2 | 2.32.10 | Legacy (still declared) |
| Qt6 | (external) | Optional Qt integration |

---

## Key Concepts for Working in This Codebase

1. **Public headers live separately** from implementation - always in `Source/Include/Ag/<Library>/`
2. **Each library has a convenience header** (e.g., `Ag/Core.hpp`, `Ag/Geometry.hpp`) that includes all public headers for that library
3. **Tests are in the same directory** as the library source, prefixed with `Test_`
4. **New files should be based on `Template.cpp`/`Template.hpp`** in each library directory
5. **The project is designed as a submodule** - build configuration must work both standalone and as part of a parent project (`AG_IS_ROOT` check)
6. **SIMD code uses a dispatch pattern** - a common `Operations.hpp` includes architecture-specific headers based on compile definitions
