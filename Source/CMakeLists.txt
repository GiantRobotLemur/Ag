# The CMake configuration for Ag library source code and build targets

# Add the location of public header files.
set(AG_INCLUDE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/Include")

# Underlying runtime components.
add_subdirectory(SymbolPackager)
add_subdirectory(WriteGlyphGeometry)
add_subdirectory(Core)
add_subdirectory(Geometry)

if (WIN32 AND AG_CONFIG_WIN32)
    add_subdirectory(Win32Base)
endif()

if ("${Qt6_FOUND}" AND AG_CONFIG_QT)
    add_subdirectory(QtInterop)
endif()

if (AG_CONFIG_OPEN_GL)
    add_subdirectory(ObjectGL)
endif()

if (AG_CONFIG_SDL3)
    add_subdirectory(Sdl3Tools)
endif()

if (IS_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/Extra")
    # Allow temporary projects to be configured which aren't in source control.
    message(STATUS "Configuring 'Extra' projects...")
    add_subdirectory(Extra)
endif()