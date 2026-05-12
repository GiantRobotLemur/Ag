# CMakeLists configuration for an text processing library

set(TEXT_INCLUDE_DIR "${AG_INCLUDE_DIR}/Ag/Text")

# Define the library.
ag_add_library(Text FOLDER      Core
                    SOURCES     PreCompiledHeader.hpp
                                CharacterSource.cpp
                                ${TEXT_INCLUDE_DIR}/CharacterSource.hpp
                                CharacterSink.cpp
                                ${TEXT_INCLUDE_DIR}/CharacterSink.hpp
                                CharacterAnalyser.cpp
                                ${TEXT_INCLUDE_DIR}/CharacterAnalyser.hpp
                                Json.cpp
                                ${TEXT_INCLUDE_DIR}/Json.hpp
                    HEADERS     ${AG_INCLUDE_DIR}/Ag/Text.hpp
                    PUBLIC_LIBS AgCore)

target_precompile_headers(Text PRIVATE [["PreCompiledHeader.hpp"]])
target_include_directories(Text PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}")

list(APPEND DOC_SRCS "${CMAKE_CURRENT_SOURCE_DIR}"
                     "${AG_INCLUDE_DIR}/Ag/Text.hpp"
                     "${TEXT_INCLUDE_DIR}")


source_group("Build" FILES  PreCompiledHeader.hpp
                            ${AG_INCLUDE_DIR}/Ag/Text.hpp
)

# Define the unit test harness.
ag_add_test_app(Text_Tests TEST_LIB   Text
                           SOURCES    Test_MemoryStream.hpp
                                      Test_MemoryStream.cpp
                                      Test_CharacterSource.cpp
                                      Test_CharacterSink.cpp
                                      Test_CharacterAnalyser.cpp)

target_precompile_headers(Text_Tests PRIVATE <gtest/gtest.h>
                                             [["PreCompiledHeader.hpp"]])
target_include_directories(Text_Tests PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}")