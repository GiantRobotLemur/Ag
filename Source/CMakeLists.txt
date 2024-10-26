# The CMake configuration for Ag library source code and build targets

# Add the location of public header files.
set(AG_INCLUDE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/Include")

# Underlying runtime components.
add_subdirectory(SymbolPackager)
add_subdirectory(Core)

if ("${Qt6_FOUND}" AND "${AG_CONFIG_QT}")
    add_subdirectory(QtInterop)
endif()