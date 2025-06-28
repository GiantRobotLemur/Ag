# CMakeLists file for the SymbolPackager tool.

# Fix up difference between CMAKE system ID and generator platform.
if ("${CMAKE_GENERATOR_PLATFORM}" STREQUAL "x64")
    set (TARGET_ARCH "AMD64")
else()
    set(TARGET_ARCH "${CMAKE_HOST_SYSTEM_PROCESSOR}")
endif()


if ("${TARGET_ARCH}" STREQUAL "${CMAKE_HOST_SYSTEM_PROCESSOR}")
    # Only build the symbol packager if it can be run on the host platform.
    add_executable(SymbolPackager
                   Main.cpp
                   Utils.hpp
                   Utils.cpp
                   LineTokeniser.cpp
                   LineTokeniser.hpp
                   CommandLine.hpp
                   CommandLine.cpp
                   SymbolDb.cpp
                   SymbolDb.hpp
                   MsMapFileReader.cpp
                   MsMapFileReader.hpp
                   GnuMapFileReader.cpp
                   GnuMapFileReader.hpp
                   GnuNmFileReader.cpp
                   GnuNmFileReader.hpp
                   PdbFileReader.cpp
                   PdbFileReader.hpp
                   SymbolFileReader.cpp
                   SymbolFileReader.hpp
                   ${AG_INCLUDE_DIR}/Ag/Private/SymbolEncoding.hpp)

    target_include_directories(SymbolPackager PRIVATE "${AG_INCLUDE_DIR}")

    set_target_properties(SymbolPackager PROPERTIES FOLDER Tools)
endif()

if (DEFINED AG_EXT_SYMBOL_PACKAGER AND NOT "${AG_EXT_SYMBOL_PACKAGER}" STREQUAL "")
    message(STATUS "Creating symbol files via external tool: ${AG_EXT_SYMBOL_PACKAGER}")
endif()

