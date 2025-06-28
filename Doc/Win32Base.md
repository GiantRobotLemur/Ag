# Win32Base - A Low-Level Windows Interop Library
---
This library provides a useful wrapper on the lowest levels of the Win32 API.
That includes:
* Kernel file objects
* Runtime linking
* COM object wrappers
* Wrappers for Windows GDI
* GDI resources management tools
* A wrapper for User32 windows
* Windows dialog wrappers
* Tool for Windows event processing
* UI thread management tools
* Windows EXE resource management tools
* DPI scaling support

The intention is for this to ease the user of the Win32 API for low level tasks.
The use of GUI controls is beyond the scope of this library, but maybe
implemented elsewhere, along with appropriate layout management.

Although the aim of the Ag library is to be cross-platform, this component exists
to allow the creation of internal Windows-only utilities which have a primitive UI.
Applications with a more complex UI should use Qt to be properly platform agnostic.