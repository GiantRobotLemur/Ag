# CMakeLists file for the Ag IO library.

set(AG_IO_PATH "${AG_INCLUDE_DIR}/Ag/IO")

ag_add_library(AgIO FOLDER      "Core"
                    HEADERS     "${AG_INCLUDE_DIR}/Ag/IO.hpp"
                    SOURCES     "PreCompiledHeader.hpp"
                                "${AG_IO_PATH}/Exceptions.hpp"
                                "Exceptions.cpp"
                                "${AG_IO_PATH}/ISeekableStream.hpp"
                                "ISeekableStream.cpp"
                                "${AG_IO_PATH}/SeekableFileStream.hpp"
                                "SeekableFileStream.cpp"
                                "${AG_IO_PATH}/MemoryStream.hpp"
                                "MemoryStream.cpp"
                                "${AG_IO_PATH}/BufferedOutputStream.hpp"
                                "BufferedOutputStream.cpp"
                                "${AG_IO_PATH}/BufferedInputStream.hpp"
                                "BufferedInputStream.cpp"
                                "${AG_IO_PATH}/StreamTools.hpp"
                                "StreamTools.cpp"
                                "${AG_IO_PATH}/MemoryMappedFile.hpp"
                                "MemoryMappedFile.cpp"
                                "${AG_IO_PATH}/HierarchySerialization.hpp"
                                "HierarchySerialization.cpp"
                                "HierarchyInterfaces.hpp"
                                "OutOfOrderStream.cpp"
                                "OutOfOrderStream.hpp"
                                "ReadOnlyDataSource.cpp"
                                "ReadOnlyDataSource.hpp"
                                "BinaryReaderWriters.cpp"
                                "BinaryReaderWriters.hpp"
                                "BinaryHierarchyEncoding.cpp"
                                "BinaryHierarchyEncoding.hpp"
                    PUBLIC_LIBS AgCore)

target_precompile_headers(AgIO PRIVATE [["PreCompiledHeader.hpp"]])
target_include_directories(AgIO PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}")

list(APPEND DOC_SRCS "${CMAKE_CURRENT_SOURCE_DIR}"
                     "${AG_INCLUDE_DIR}/Ag/IO.hpp"
                     "${AG_INCLUDE_DIR}/Ag/IO")

source_group("Build" FILES
            "PreCompiledHeader.hpp"
            "${AG_INCLUDE_DIR}/Ag/IO.hpp"
            "${AG_INCLUDE_DIR}/Ag/Core.hpp"
            "${AG_INCLUDE_DIR}/Ag/GTest_Core.hpp"
)

source_group("Streams" FILES
            "${AG_IO_PATH}/Exceptions.hpp"
            "Exceptions.cpp"
            "${AG_IO_PATH}/ISeekableStream.hpp"
            "ISeekableStream.cpp"
            "${AG_IO_PATH}/SeekableFileStream.hpp"
            "SeekableFileStream.cpp"
            "${AG_IO_PATH}/MemoryStream.hpp"
            "MemoryStream.cpp"
            "${AG_IO_PATH}/BufferedOutputStream.hpp"
            "BufferedOutputStream.cpp"
            "${AG_IO_PATH}/BufferedInputStream.hpp"
            "BufferedInputStream.cpp"
            "${AG_IO_PATH}/MemoryMappedFile.hpp"
            "MemoryMappedFile.cpp"
            "${AG_IO_PATH}/StreamTools.hpp"
            "StreamTools.cpp"
)

source_group("Hierarchy" FILES
            "${AG_IO_PATH}/HierarchySerialization.hpp"
            "HierarchySerialization.cpp"
            "HierarchyInterfaces.hpp"
            "BinaryReaderWriters.cpp"
            "BinaryReaderWriters.hpp"
            "BinaryHierarchyEncoding.cpp"
            "BinaryHierarchyEncoding.hpp"
            "OutOfOrderStream.cpp"
            "OutOfOrderStream.hpp"
            "ReadOnlyDataSource.cpp"
            "ReadOnlyDataSource.hpp"
)

# Define the unit test harness.
ag_add_test_app(AgIO_Tests TEST_LIB AgIO
                           SOURCES  PreCompiledHeader.hpp
                                    TestTools.cpp
                                    TestTools.hpp
                                    Test_StreamRegion.cpp
                                    Test_SeekableStreams.cpp
                                    Test_BufferedOutputStream.cpp
                                    Test_BufferedInputStream.cpp
                                    Test_MemoryMappedFile.cpp
                                    Test_HierarchySerialization.cpp
)

target_precompile_headers(AgIO_Tests PRIVATE <gtest/gtest.h>
                                             [["PreCompiledHeader.hpp"]])
target_include_directories(AgIO_Tests PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}")