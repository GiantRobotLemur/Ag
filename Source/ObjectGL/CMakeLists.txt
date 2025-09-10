# CMakeLists configuration for a C++ 17+ OpenGL wrapper library

# Define the library.
ag_add_library(ObjectGL FOLDER      Graphics
                        SOURCES     PreCompiledHeader.hpp
                                    Platform.cpp
                                    ${AG_INCLUDE_DIR}/Ag/ObjectGL/Platform.hpp
                                    BaseTypes.cpp
                                    ${AG_INCLUDE_DIR}/Ag/ObjectGL/BaseTypes.hpp
                                    ${AG_INCLUDE_DIR}/Ag/ObjectGL/EnumTypes.hpp
                                    APIs.cpp
                                    ${AG_INCLUDE_DIR}/Ag/ObjectGL/APIs.hpp
                                    Identifiers.cpp
                                    ${AG_INCLUDE_DIR}/Ag/ObjectGL/Identifiers.hpp
                                    CommandSetTools.hpp
                                    CommandSets.cpp
                                    ${AG_INCLUDE_DIR}/Ag/ObjectGL/CommandSets.hpp
                                    ExtensionSet.cpp
                                    ${AG_INCLUDE_DIR}/Ag/ObjectGL/ExtensionSet.hpp
                                    APIResolvers.cpp
                                    ${AG_INCLUDE_DIR}/Ag/ObjectGL/APIResolvers.hpp
                                    OpenGLException.cpp
                                    ${AG_INCLUDE_DIR}/Ag/ObjectGL/OpenGLException.hpp
                                    DisplayFormat.cpp
                                    ${AG_INCLUDE_DIR}/Ag/ObjectGL/DisplayFormat.hpp
                                    ContextOptions.cpp
                                    ${AG_INCLUDE_DIR}/Ag/ObjectGL/ContextOptions.hpp
                                    ${AG_INCLUDE_DIR}/Ag/ObjectGL/Driver.hpp
                                    DisplayContextPrivate.cpp
                                    DisplayContextPrivate.hpp
                                    DisplayContext.cpp
                                    ${AG_INCLUDE_DIR}/Ag/ObjectGL/DisplayContext.hpp
                                    RenderContextPrivate.cpp
                                    RenderContextPrivate.hpp
                                    RenderContext.cpp
                                    ${AG_INCLUDE_DIR}/Ag/ObjectGL/RenderContext.hpp
                                    # SDL2Driver.cpp
                                    # ${AG_INCLUDE_DIR}/Ag/ObjectGL/SDL2Driver.hpp
                                    ResourceWrappers.hpp
                                    Shader.cpp
                                    ${AG_INCLUDE_DIR}/Ag/ObjectGL/Shader.hpp
                                    Program.cpp
                                    ${AG_INCLUDE_DIR}/Ag/ObjectGL/Program.hpp
                                    ProgramBuilder.cpp
                                    ${AG_INCLUDE_DIR}/Ag/ObjectGL/ProgramBuilder.hpp
                                    Buffer.cpp
                                    ${AG_INCLUDE_DIR}/Ag/ObjectGL/Buffer.hpp
                                    BufferSchema.cpp
                                    ${AG_INCLUDE_DIR}/Ag/ObjectGL/BufferSchema.hpp
                        WIN_SOURCES ${AG_INCLUDE_DIR}/Ag/ObjectGL/WGL_Types.hpp
                                    WGL_API.cpp
                                    ${AG_INCLUDE_DIR}/Ag/ObjectGL/WGL_API.hpp
                                    WGL_CommandSets.cpp
                                    ${AG_INCLUDE_DIR}/Ag/ObjectGL/WGL_CommandSets.hpp
                        #POSIX_SOURCES
                                    ${AG_INCLUDE_DIR}/Ag/ObjectGL/GLX_Types.hpp
                                    GLX_API.cpp
                                    ${AG_INCLUDE_DIR}/Ag/ObjectGL/GLX_API.hpp
                                    GLX_CommandSets.cpp
                                    ${AG_INCLUDE_DIR}/Ag/ObjectGL/GLX_CommandSets.hpp
                        HEADERS     ${AG_INCLUDE_DIR}/Ag/ObjectGL.hpp
                        PUBLIC_LIBS AgCore glm)

foreach(extName IN ITEMS 3DFX 3DLabs AMD Apple ARB ATI Ext
                         Gremedy HP IBM Ingr Intel Intense3D
                         Khr Mesa NVidia OES OML Ovr PGI
                         SGI Sun)
    target_sources(ObjectGL PRIVATE "Extensions/${extName}.cpp"
                                    "${AG_INCLUDE_DIR}/Ag/ObjectGL/Extensions/${extName}.hpp"
                                    "Extensions/${extName}Commands.cpp"
                                    "${AG_INCLUDE_DIR}/Ag/ObjectGL/Extensions/${extName}Commands.hpp")

    source_group("Extensions" FILES "Extensions/${extName}.cpp"
                                    "${AG_INCLUDE_DIR}/Ag/ObjectGL/Extensions/${extName}.hpp"
                                    "Extensions/${extName}Commands.cpp"
                                    "${AG_INCLUDE_DIR}/Ag/ObjectGL/Extensions/${extName}Commands.hpp")
endforeach()

target_precompile_headers(ObjectGL PRIVATE [["PreCompiledHeader.hpp"]])
target_include_directories(ObjectGL PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}")

if (AG_CONFIG_SDL3)
    # Define the SDL3 integration driver.
    target_compile_definitions(ObjectGL PUBLIC AG_OBJECT_GL_SDL3_DRIVER)
    target_link_libraries(ObjectGL PUBLIC SDL3::SDL3)

    target_sources(ObjectGL PRIVATE SDL3Driver.cpp
                                    ${AG_INCLUDE_DIR}/Ag/ObjectGL/SDL3Driver.hpp)
endif()

if (WIN32 AND AG_CONFIG_WIN32)
    # Define the WGL driver.
    target_compile_definitions(ObjectGL PUBLIC AG_OBJECT_GL_WGL_DRIVER)

    target_sources(ObjectGL PRIVATE WGL_Tools.cpp
                                    ${AG_INCLUDE_DIR}/Ag/ObjectGL/WGL_Tools.hpp
                                    WGLDriver.cpp
                                    ${AG_INCLUDE_DIR}/Ag/ObjectGL/WGLDriver.hpp)
endif()

list(APPEND DOC_SRCS "${CMAKE_CURRENT_SOURCE_DIR}"
                     "${AG_INCLUDE_DIR}/Ag/ObjectGL.hpp"
                     "${AG_INCLUDE_DIR}/Ag/ObjectGL")

source_group("Build" FILES
    ${AG_INCLUDE_DIR}/Ag/ObjectGL/Platform.hpp
    Platform.cpp
    ${AG_INCLUDE_DIR}/Ag/ObjectGL.hpp
    PreCompiledHeader.hpp
)

source_group("API" FILES
    BaseTypes.cpp
    ${AG_INCLUDE_DIR}/Ag/ObjectGL/BaseTypes.hpp
    ${AG_INCLUDE_DIR}/Ag/ObjectGL/EnumTypes.hpp
    APIs.cpp
    ${AG_INCLUDE_DIR}/Ag/ObjectGL/APIs.hpp
    Identifiers.cpp
    ${AG_INCLUDE_DIR}/Ag/ObjectGL/Identifiers.hpp
    CommandSetTools.hpp
    CommandSets.cpp
    ${AG_INCLUDE_DIR}/Ag/ObjectGL/CommandSets.hpp
    ${AG_INCLUDE_DIR}/Ag/ObjectGL/WGL_Types.hpp
    WGL_API.cpp
    ${AG_INCLUDE_DIR}/Ag/ObjectGL/WGL_API.hpp
    WGL_CommandSets.cpp
    ${AG_INCLUDE_DIR}/Ag/ObjectGL/WGL_CommandSets.hpp
    ${AG_INCLUDE_DIR}/Ag/ObjectGL/GLX_Types.hpp
    GLX_API.cpp
    ${AG_INCLUDE_DIR}/Ag/ObjectGL/GLX_API.hpp
    GLX_CommandSets.cpp
    ${AG_INCLUDE_DIR}/Ag/ObjectGL/GLX_CommandSets.hpp
)

source_group("Drivers" FILES
    #${AG_INCLUDE_DIR}/Ag/ObjectGL/Version.hpp
    #Version.cpp
    ExtensionSet.cpp
    ${AG_INCLUDE_DIR}/Ag/ObjectGL/ExtensionSet.hpp
    APIResolvers.cpp
    ${AG_INCLUDE_DIR}/Ag/ObjectGL/APIResolvers.hpp
    OpenGLException.cpp
    ${AG_INCLUDE_DIR}/Ag/ObjectGL/OpenGLException.hpp
    DisplayFormat.cpp
    ${AG_INCLUDE_DIR}/Ag/ObjectGL/DisplayFormat.hpp
    ContextOptions.cpp
    ${AG_INCLUDE_DIR}/Ag/ObjectGL/ContextOptions.hpp
    ${AG_INCLUDE_DIR}/Ag/ObjectGL/Driver.hpp
    DisplayContextPrivate.cpp
    DisplayContextPrivate.hpp
    DisplayContext.cpp
    ${AG_INCLUDE_DIR}/Ag/ObjectGL/DisplayContext.hpp
    RenderContextPrivate.cpp
    RenderContextPrivate.hpp
    RenderContext.cpp
    ${AG_INCLUDE_DIR}/Ag/ObjectGL/RenderContext.hpp
    # SDL2Driver.cpp
    # ${AG_INCLUDE_DIR}/Ag/ObjectGL/SDL2Driver.hpp
    SDL3Driver.cpp
    ${AG_INCLUDE_DIR}/Ag/ObjectGL/SDL3Driver.hpp
    WGL_Tools.cpp
    ${AG_INCLUDE_DIR}/Ag/ObjectGL/WGL_Tools.hpp
    WGLDriver.cpp
    ${AG_INCLUDE_DIR}/Ag/ObjectGL/WGLDriver.hpp
)

source_group("Resources" FILES
    ResourceWrappers.cpp
    ResourceWrappers.hpp
    Shader.cpp
    ${AG_INCLUDE_DIR}/Ag/ObjectGL/Shader.hpp
    Program.cpp
    ${AG_INCLUDE_DIR}/Ag/ObjectGL/Program.hpp
    ProgramBuilder.cpp
    ${AG_INCLUDE_DIR}/Ag/ObjectGL/ProgramBuilder.hpp
    Buffer.cpp
    ${AG_INCLUDE_DIR}/Ag/ObjectGL/Buffer.hpp
    BufferSchema.cpp
    ${AG_INCLUDE_DIR}/Ag/ObjectGL/BufferSchema.hpp
)