# CMakeLists file for the SDL3 Tools library.

set(SDL3_TOOLS_INCLUDE_DIR "${AG_INCLUDE_DIR}/Ag/Sdl3Tools")

ag_add_library(Sdl3Tools FOLDER     "Core"
                         HEADERS    ${AG_INCLUDE_DIR}/Ag/Sdl3Tools.hpp
                         SOURCES    PreCompiledHeader.hpp
                                    ${SDL3_TOOLS_INCLUDE_DIR}/Primitives.hpp
                                    Primitives.cpp
                                    ${SDL3_TOOLS_INCLUDE_DIR}/WrapperTypes.hpp
                                    WrapperTypes.cpp
                                    ${SDL3_TOOLS_INCLUDE_DIR}/ApiException.hpp
                                    ApiException.cpp
                                    ${SDL3_TOOLS_INCLUDE_DIR}/Initialiser.hpp
                                    Initialiser.cpp
                                    ${SDL3_TOOLS_INCLUDE_DIR}/DisplayModeSpec.hpp
                                    DisplayModeSpec.cpp
                                    ${SDL3_TOOLS_INCLUDE_DIR}/ProgramArguments.hpp
                                    ProgramArguments.cpp
                                    ${SDL3_TOOLS_INCLUDE_DIR}/PropertySet.hpp
                                    PropertySet.cpp
                                    ${SDL3_TOOLS_INCLUDE_DIR}/EventProcessor.hpp
                                    EventProcessor.cpp
                                    ${SDL3_TOOLS_INCLUDE_DIR}/Window.hpp
                                    Window.cpp
                                    ${SDL3_TOOLS_INCLUDE_DIR}/Surface.hpp
                                    Surface.cpp
                                    ${SDL3_TOOLS_INCLUDE_DIR}/OpenGL.hpp
                                    OpenGL.cpp
                                    ${SDL3_TOOLS_INCLUDE_DIR}/GPUObjects.hpp
                                    GPUObjects.cpp
                        PUBLIC_LIBS AgCore SDL3::SDL3)

# Package symbols for libSDL3.
#ag_enable_proxy_stacktrace(Sdl3Tools SDL3-shared)

target_precompile_headers(Sdl3Tools PRIVATE [["PreCompiledHeader.hpp"]])
target_compile_definitions(Sdl3Tools PUBLIC AG_SDL3_TOOLS)
target_include_directories(Sdl3Tools PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}")

if (WIN32)
    get_filename_component(WIN_SDK_ROOT_PATH "[HKEY_LOCAL_MACHINE\\SOFTWARE\\Microsoft\\Windows Kits\\Installed Roots;KitsRoot10]"
                           ABSOLUTE CACHE)

    cmake_path(APPEND WIN_SDK_ROOT_PATH "bin"
               "${CMAKE_VS_WINDOWS_TARGET_PLATFORM_VERSION}"
               "${CMAKE_VS_PLATFORM_TOOLSET_HOST_ARCHITECTURE}"
               OUTPUT_VARIABLE SDK_TOOLS_PATH)

    find_program(DXC_PATH dxc
                 NO_CACHE
                 PATHS "${SDK_TOOLS_PATH}"
                 NO_DEFAULT_PATH
                 DOC "Direct3D Shader Compiler")
endif()

list(APPEND DOC_SRCS "${CMAKE_CURRENT_SOURCE_DIR}"
                     "${AG_INCLUDE_DIR}/Ag/Sdl3Tools.hpp"
                     "${AG_INCLUDE_DIR}/Ag/Sdl3Tools")

# Define the unit test harness.
ag_add_test_app(Sdl3Tools_Tests TEST_LIB Sdl3Tools
                                SOURCES  Test_DisplayModeSpec.cpp
                                         Test_ProgramArguments.cpp)

target_precompile_headers(Sdl3Tools_Tests PRIVATE <gtest/gtest.h>
                                                  [["PreCompiledHeader.hpp"]])
target_include_directories(Sdl3Tools_Tests PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}")