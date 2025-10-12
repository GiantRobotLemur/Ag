# CMakeLists configuration for the Ag::Core library

set(AGCORE_INCLUDE_DIR "${AG_INCLUDE_DIR}/Ag/Core")

# Define the library.
ag_add_library(AgCore SOURCES   PreCompiledHeader.hpp
                                CoreInternal.hpp
                                CoreInternal.cpp
                                CPU.cpp
                                Binary.cpp
                                ByteOrder.cpp
                                CodePoint.cpp
                                Utf.cpp
                                Memory.cpp
                                InlineMemory.cpp
                                StringPrivate.hpp
                                StringPrivate.cpp
                                String.cpp
                                StackTrace.cpp
                                Exception.cpp
                                ErrorGuard.cpp
                                Trace.cpp
                                ScalarParser.cpp
                                Stream.cpp
                                VariantType.cpp
                                VariantTypes.cpp
                                Variant.cpp
                                Format.cpp
                                CommandLineSchema.cpp
                                ProgramArguments.cpp
                                App.cpp
                                FsPathSchema.cpp
                                FsPathSchema.hpp
                                FsPath.cpp
                                FsSearchPathList.cpp
                                FsDirectory.cpp
                                Uri.cpp
                                Timer.cpp
                                Version.cpp
                                ${AGCORE_INCLUDE_DIR}/Configuration.hpp
                                ${AGCORE_INCLUDE_DIR}/Platform.hpp
                                ${AGCORE_INCLUDE_DIR}/CPU.hpp
                                ${AGCORE_INCLUDE_DIR}/AlignedTypes.hpp
                                ${AGCORE_INCLUDE_DIR}/EnumInfo.hpp
                                ${AGCORE_INCLUDE_DIR}/Math.hpp
                                ${AGCORE_INCLUDE_DIR}/Utils.hpp
                                ${AGCORE_INCLUDE_DIR}/CollectionTools.hpp
                                ${AGCORE_INCLUDE_DIR}/LinearSortedSet.hpp
                                ${AGCORE_INCLUDE_DIR}/LinearSortedMap.hpp
                                ${AGCORE_INCLUDE_DIR}/Binary.hpp
                                ${AGCORE_INCLUDE_DIR}/ByteOrder.hpp
                                ${AGCORE_INCLUDE_DIR}/CodePoint.hpp
                                ${AGCORE_INCLUDE_DIR}/Utf.hpp
                                ${AGCORE_INCLUDE_DIR}/Memory.hpp
                                ${AGCORE_INCLUDE_DIR}/InlineMemory.hpp
                                ${AGCORE_INCLUDE_DIR}/StackTrace.hpp
                                ${AGCORE_INCLUDE_DIR}/Exception.hpp
                                ${AGCORE_INCLUDE_DIR}/ErrorGuard.hpp
                                ${AGCORE_INCLUDE_DIR}/Trace.hpp
                                ${AGCORE_INCLUDE_DIR}/ScalarParser.hpp
                                ${AGCORE_INCLUDE_DIR}/String.hpp
                                ${AGCORE_INCLUDE_DIR}/Stream.hpp
                                ${AGCORE_INCLUDE_DIR}/VariantType.hpp
                                ${AGCORE_INCLUDE_DIR}/VariantTypes.hpp
                                ${AGCORE_INCLUDE_DIR}/Variant.hpp
                                ${AGCORE_INCLUDE_DIR}/Format.hpp
                                ${AGCORE_INCLUDE_DIR}/CommandLineSchema.hpp
                                ${AGCORE_INCLUDE_DIR}/ProgramArguments.hpp
                                ${AGCORE_INCLUDE_DIR}/App.hpp
                                ${AGCORE_INCLUDE_DIR}/FsPath.hpp
                                ${AGCORE_INCLUDE_DIR}/FsSearchPathList.hpp
                                ${AGCORE_INCLUDE_DIR}/FsDirectory.hpp
                                ${AGCORE_INCLUDE_DIR}/Uri.hpp
                                ${AGCORE_INCLUDE_DIR}/Timer.hpp
                                ${AGCORE_INCLUDE_DIR}/Version.hpp
                    WIN_SOURCES Win32API.hpp
                                Win32API.cpp
                                Core.natvis
                                cpp.hint
                    POSIX_SOURCES PosixAPI.hpp
                                  PosixAPI.cpp
                    PRIVATE_LIBS bz2_ObjLib
                    HEADERS     ${AG_INCLUDE_DIR}/Ag/Core.hpp
                                ${AG_INCLUDE_DIR}/Ag/GTest_Core.hpp
                    FOLDER      Core)

target_precompile_headers(AgCore PRIVATE [["PreCompiledHeader.hpp"]])

# It seems simply linking to bz_ObjLib does not bring through the include
# directories, so we have to do it manually here.
target_include_directories(AgCore PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}"
                                          "${BZIP2_INCLUDE_DIRECTORY}")
target_include_directories(AgCore PUBLIC "${AG_INCLUDE_DIR}")

# Embed configuration variables as public pre-processor macro defines in the
# library to be propagated down to all consumers.

if("${CMAKE_SYSTEM_PROCESSOR}" STREQUAL "AMD64")
    # See: https://en.wikipedia.org/wiki/X86-64#Microarchitecture_levels
    if (AG_ENABLE_X64_V4)
        target_compile_definitions(AgCore PUBLIC AG_X86_64_VER=4
                                                 AG_ENABLE_X64_V1
                                                 AG_ENABLE_X64_V2
                                                 AG_ENABLE_X64_V3
                                                 AG_ENABLE_X64_V4)
    elseif (AG_ENABLE_X64_V3)
        target_compile_definitions(AgCore PUBLIC AG_X86_64_VER=3
                                                 AG_ENABLE_X64_V1
                                                 AG_ENABLE_X64_V2
                                                 AG_ENABLE_X64_V3)
    elseif(AG_ENABLE_X64_V2)
        target_compile_definitions(AgCore PUBLIC AG_X86_64_VER=2
                                                 AG_ENABLE_X64_V1
                                                 AG_ENABLE_X64_V2)
    elseif(AG_ENABLE_X64_V1)
        target_compile_definitions(AgCore PUBLIC AG_X86_64_VER=1
                                                 AG_ENABLE_X64_V1)
    else()
        target_compile_definitions(AgCore PUBLIC AG_X86_64_VER=0)
    endif()
endif()

list(APPEND DOC_SRCS "${CMAKE_CURRENT_SOURCE_DIR}"
                     "${AG_INCLUDE_DIR}/Ag/Core.hpp"
                     "${AG_INCLUDE_DIR}/Ag/Core")

source_group("Build" FILES
    PreCompiledHeader.hpp
    CoreInternal.hpp
    CoreInternal.cpp
    ${AGCORE_INCLUDE_DIR}/Configuration.hpp
    Core.natvis
    cpp.hint
    ${AG_INCLUDE_DIR}/Ag/Core.hpp
    ${AG_INCLUDE_DIR}/Ag/GTest_Core.hpp
)
source_group("Platform" FILES
    ${AGCORE_INCLUDE_DIR}/Platform.hpp
    CPU.cpp
    ${AGCORE_INCLUDE_DIR}/CPU.hpp
    StackTrace.cpp
    ${AGCORE_INCLUDE_DIR}/StackTrace.hpp
    Timer.cpp
    ${AGCORE_INCLUDE_DIR}/Timer.hpp
    Win32API.hpp
    Win32API.cpp
    PosixAPI.hpp
    PosixAPI.cpp
)
source_group("Basics" FILES
    Binary.cpp
    ${AGCORE_INCLUDE_DIR}/Binary.hpp
    ByteOrder.cpp
    ${AGCORE_INCLUDE_DIR}/ByteOrder.hpp
    Memory.cpp
    ${AGCORE_INCLUDE_DIR}/Memory.hpp
    InlineMemory.cpp
    ${AGCORE_INCLUDE_DIR}/InlineMemory.hpp
    ${AGCORE_INCLUDE_DIR}/Math.hpp
    ${AGCORE_INCLUDE_DIR}/Utils.hpp
)

source_group("Data Types" FILES
    ${AGCORE_INCLUDE_DIR}/AlignedTypes.hpp
    Variant.cpp
    ${AGCORE_INCLUDE_DIR}/Variant.hpp
    VariantType.cpp
    ${AGCORE_INCLUDE_DIR}/VariantType.hpp
    VariantTypes.cpp
    ${AGCORE_INCLUDE_DIR}/VariantTypes.hpp
    Version.cpp
    ${AGCORE_INCLUDE_DIR}/Version.hpp
    ${AGCORE_INCLUDE_DIR}/EnumInfo.hpp
    ${AGCORE_INCLUDE_DIR}/CollectionTools.hpp
    ${AGCORE_INCLUDE_DIR}/LinearSortedSet.hpp
    ${AGCORE_INCLUDE_DIR}/LinearSortedMap.hpp
)

source_group("Text" FILES
    CodePoint.cpp
    ${AGCORE_INCLUDE_DIR}/CodePoint.hpp
    Utf.cpp
    ${AGCORE_INCLUDE_DIR}/Utf.hpp
    ScalarParser.cpp
    ${AGCORE_INCLUDE_DIR}/ScalarParser.hpp
    StringPrivate.cpp
    StringPrivate.hpp
    String.cpp
    ${AGCORE_INCLUDE_DIR}/String.hpp
    Format.cpp
    ${AGCORE_INCLUDE_DIR}/Format.hpp
)

source_group("Error Handling" FILES
    Exception.cpp
    ${AGCORE_INCLUDE_DIR}/Exception.hpp
    ErrorGuard.cpp
    ${AGCORE_INCLUDE_DIR}/ErrorGuard.hpp
    Trace.cpp
    ${AGCORE_INCLUDE_DIR}/Trace.hpp
)

source_group("IO" FILES
    Stream.cpp
    ${AGCORE_INCLUDE_DIR}/Stream.hpp
    FsPathSchema.cpp
    FsPathSchema.hpp
    FsPath.cpp
    ${AGCORE_INCLUDE_DIR}/FsPath.hpp
    FsSearchPathList.cpp
    ${AGCORE_INCLUDE_DIR}/FsSearchPathList.hpp
    FsDirectory.cpp
    ${AGCORE_INCLUDE_DIR}/FsDirectory.hpp
    Uri.cpp
    ${AGCORE_INCLUDE_DIR}/Uri.hpp
)

source_group("Framework" FILES
    CommandLineSchema.cpp
    ${AGCORE_INCLUDE_DIR}/CommandLineSchema.hpp
    ProgramArguments.cpp
    ${AGCORE_INCLUDE_DIR}/ProgramArguments.hpp
    App.cpp
    ${AGCORE_INCLUDE_DIR}/App.hpp
)

# Define the unit test harness.
ag_add_test_app(Core_Tests TEST_LIB AgCore
                           SOURCES  Test_Binary.cpp
                                    Test_Utils.cpp
                                    Test_CPU.cpp
                                    Test_EnumInfo.cpp
                                    Test_LinearSortedSet.cpp
                                    Test_LinearSortedMap.cpp
                                    Test_Utf.cpp
                                    Test_String.cpp
                                    Test_Bz2Stream.cpp
                                    Test_StackTrace.cpp
                                    Test_Exception.cpp
                                    Test_PackedFieldHelper.cpp
                                    Test_ErrorGuard.cpp
                                    Test_Variant.cpp
                                    Test_Format.cpp
                                    Test_ScalarParser.cpp
                                    Test_CommandLine.cpp
                                    Test_App.cpp
                                    Test_FileSystem.cpp
                                    Test_Uri.cpp
                                    Test_Timer.cpp
                                    Test_Version.cpp)

target_precompile_headers(Core_Tests PRIVATE <gtest/gtest.h>
                                             [["PreCompiledHeader.hpp"]])
target_include_directories(Core_Tests PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}"
                                              "${BZIP2_INCLUDE_DIRECTORY}")
