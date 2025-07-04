# CMakeLists configuration for the Ag::Core library

# Define the library.
ag_add_library(AgCore SOURCES   PreCompiledHeader.hpp
                                CoreInternal.hpp
                                CoreInternal.cpp
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
                                ${AG_INCLUDE_DIR}/Ag/Core/Configuration.hpp
                                ${AG_INCLUDE_DIR}/Ag/Core/Platform.hpp
                                ${AG_INCLUDE_DIR}/Ag/Core/EnumInfo.hpp
                                ${AG_INCLUDE_DIR}/Ag/Core/Math.hpp
                                ${AG_INCLUDE_DIR}/Ag/Core/Utils.hpp
                                ${AG_INCLUDE_DIR}/Ag/Core/CollectionTools.hpp
                                ${AG_INCLUDE_DIR}/Ag/Core/LinearSortedSet.hpp
                                ${AG_INCLUDE_DIR}/Ag/Core/LinearSortedMap.hpp
                                ${AG_INCLUDE_DIR}/Ag/Core/Binary.hpp
                                ${AG_INCLUDE_DIR}/Ag/Core/ByteOrder.hpp
                                ${AG_INCLUDE_DIR}/Ag/Core/CodePoint.hpp
                                ${AG_INCLUDE_DIR}/Ag/Core/Utf.hpp
                                ${AG_INCLUDE_DIR}/Ag/Core/Memory.hpp
                                ${AG_INCLUDE_DIR}/Ag/Core/InlineMemory.hpp
                                ${AG_INCLUDE_DIR}/Ag/Core/StackTrace.hpp
                                ${AG_INCLUDE_DIR}/Ag/Core/Exception.hpp
                                ${AG_INCLUDE_DIR}/Ag/Core/ErrorGuard.hpp
                                ${AG_INCLUDE_DIR}/Ag/Core/Trace.hpp
                                ${AG_INCLUDE_DIR}/Ag/Core/ScalarParser.hpp
                                ${AG_INCLUDE_DIR}/Ag/Core/String.hpp
                                ${AG_INCLUDE_DIR}/Ag/Core/Stream.hpp
                                ${AG_INCLUDE_DIR}/Ag/Core/VariantType.hpp
                                ${AG_INCLUDE_DIR}/Ag/Core/VariantTypes.hpp
                                ${AG_INCLUDE_DIR}/Ag/Core/Variant.hpp
                                ${AG_INCLUDE_DIR}/Ag/Core/Format.hpp
                                ${AG_INCLUDE_DIR}/Ag/Core/CommandLineSchema.hpp
                                ${AG_INCLUDE_DIR}/Ag/Core/ProgramArguments.hpp
                                ${AG_INCLUDE_DIR}/Ag/Core/App.hpp
                                ${AG_INCLUDE_DIR}/Ag/Core/FsPath.hpp
                                ${AG_INCLUDE_DIR}/Ag/Core/FsSearchPathList.hpp
                                ${AG_INCLUDE_DIR}/Ag/Core/FsDirectory.hpp
                                ${AG_INCLUDE_DIR}/Ag/Core/Uri.hpp
                                ${AG_INCLUDE_DIR}/Ag/Core/Timer.hpp
                                ${AG_INCLUDE_DIR}/Ag/Core/Version.hpp
                    WIN_SOURCES Win32API.hpp
                                Win32API.cpp
                                Core.natvis
                                cpp.hint
                    POSIX_SOURCES PosixAPI.hpp
                                  PosixAPI.cpp
                    HEADERS     ${AG_INCLUDE_DIR}/Ag/Core.hpp
                                ${AG_INCLUDE_DIR}/Ag/GTest_Core.hpp
                    FOLDER      Core)

target_precompile_headers(AgCore PRIVATE [["PreCompiledHeader.hpp"]])
target_include_directories(AgCore PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}")
target_include_directories(AgCore PUBLIC "${AG_INCLUDE_DIR}")

list(APPEND DOC_SRCS "${CMAKE_CURRENT_SOURCE_DIR}"
                     "${AG_INCLUDE_DIR}/Ag/Core.hpp"
                     "${AG_INCLUDE_DIR}/Ag/Core")

source_group("Build" FILES
    PreCompiledHeader.hpp
    CoreInternal.hpp
    CoreInternal.cpp
    ${AG_INCLUDE_DIR}/Ag/Core/Configuration.hpp
    Core.natvis
    cpp.hint
    ${AG_INCLUDE_DIR}/Ag/Core.hpp
    ${AG_INCLUDE_DIR}/Ag/GTest_Core.hpp
)
source_group("Platform" FILES
    ${AG_INCLUDE_DIR}/Ag/Core/Platform.hpp
    StackTrace.cpp
    ${AG_INCLUDE_DIR}/Ag/Core/StackTrace.hpp
    Timer.cpp
    ${AG_INCLUDE_DIR}/Ag/Core/Timer.hpp
    Win32API.hpp
    Win32API.cpp
    PosixAPI.hpp
    PosixAPI.cpp
)
source_group("Basics" FILES
    Binary.cpp
    ${AG_INCLUDE_DIR}/Ag/Core/Binary.hpp
    ByteOrder.cpp
    ${AG_INCLUDE_DIR}/Ag/Core/ByteOrder.hpp
    Memory.cpp
    ${AG_INCLUDE_DIR}/Ag/Core/Memory.hpp
    InlineMemory.cpp
    ${AG_INCLUDE_DIR}/Ag/Core/InlineMemory.hpp
    ${AG_INCLUDE_DIR}/Ag/Core/Math.hpp
    ${AG_INCLUDE_DIR}/Ag/Core/Utils.hpp
)

source_group("Data Types" FILES
    Variant.cpp
    ${AG_INCLUDE_DIR}/Ag/Core/Variant.hpp
    VariantType.cpp
    ${AG_INCLUDE_DIR}/Ag/Core/VariantType.hpp
    VariantTypes.cpp
    ${AG_INCLUDE_DIR}/Ag/Core/VariantTypes.hpp
    Version.cpp
    ${AG_INCLUDE_DIR}/Ag/Core/Version.hpp
    ${AG_INCLUDE_DIR}/Ag/Core/EnumInfo.hpp
    ${AG_INCLUDE_DIR}/Ag/Core/CollectionTools.hpp
    ${AG_INCLUDE_DIR}/Ag/Core/LinearSortedSet.hpp
    ${AG_INCLUDE_DIR}/Ag/Core/LinearSortedMap.hpp
)

source_group("Text" FILES
    CodePoint.cpp
    ${AG_INCLUDE_DIR}/Ag/Core/CodePoint.hpp
    Utf.cpp
    ${AG_INCLUDE_DIR}/Ag/Core/Utf.hpp
    ScalarParser.cpp
    ${AG_INCLUDE_DIR}/Ag/Core/ScalarParser.hpp
    StringPrivate.cpp
    StringPrivate.hpp
    String.cpp
    ${AG_INCLUDE_DIR}/Ag/Core/String.hpp
    Format.cpp
    ${AG_INCLUDE_DIR}/Ag/Core/Format.hpp
)

source_group("Error Handling" FILES
    Exception.cpp
    ${AG_INCLUDE_DIR}/Ag/Core/Exception.hpp
    ErrorGuard.cpp
    ${AG_INCLUDE_DIR}/Ag/Core/ErrorGuard.hpp
    Trace.cpp
    ${AG_INCLUDE_DIR}/Ag/Core/Trace.hpp
)

source_group("IO" FILES
    Stream.cpp
    ${AG_INCLUDE_DIR}/Ag/Core/Stream.hpp
    FsPathSchema.cpp
    FsPathSchema.hpp
    FsPath.cpp
    ${AG_INCLUDE_DIR}/Ag/Core/FsPath.hpp
    FsSearchPathList.cpp
    ${AG_INCLUDE_DIR}/Ag/Core/FsSearchPathList.hpp
    FsDirectory.cpp
    ${AG_INCLUDE_DIR}/Ag/Core/FsDirectory.hpp
    Uri.cpp
    ${AG_INCLUDE_DIR}/Ag/Core/Uri.hpp
)

source_group("Framework" FILES
    CommandLineSchema.cpp
    ${AG_INCLUDE_DIR}/Ag/Core/CommandLineSchema.hpp
    ProgramArguments.cpp
    ${AG_INCLUDE_DIR}/Ag/Core/ProgramArguments.hpp
    App.cpp
    ${AG_INCLUDE_DIR}/Ag/Core/App.hpp
)


# Define the unit test harness.
ag_add_test_app(Core_Tests TEST_LIB AgCore
                           SOURCES  Test_Binary.cpp
                                    Test_Utils.cpp
                                    Test_EnumInfo.cpp
                                    Test_LinearSortedSet.cpp
                                    Test_LinearSortedMap.cpp
                                    Test_Utf.cpp
                                    Test_String.cpp
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
target_include_directories(Core_Tests PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}")
