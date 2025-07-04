# Utilities for configuring the Ag library and suite of applications.

include(CMakePrintHelpers)

# This might be important when building for ARM64 on x64.
set(AG_EXT_SYMBOL_PACKAGER "" CACHE FILEPATH "The path to an external Symbol Packager tool binary.")

function(ag_enable_proxy_stacktrace destTargetName symbolTargetName)
    if (NOT TARGET ${destTargetName})
        message(SEND_ERROR "'${destTargetName}' is not a valid target.")
        return()
    endif()

    if (NOT TARGET ${symbolTargetName})
        message(SEND_ERROR "'${symbolTargetName}' is not a valid target.")
        return()
    endif()

    # Fix up difference between CMAKE system ID and generator platform.
    if ("${CMAKE_GENERATOR_PLATFORM}" STREQUAL "x64")
        set (TARGET_ARCH "AMD64")
    else()
        set(TARGET_ARCH "${CMAKE_HOST_SYSTEM_PROCESSOR}")
    endif()

    if (DEFINED AG_EXT_SYMBOL_PACKAGER AND NOT "${AG_EXT_SYMBOL_PACKAGER}" STREQUAL "")
        set(SymTool "${AG_EXT_SYMBOL_PACKAGER}")
    elseif (NOT "${TARGET_ARCH}" STREQUAL "${CMAKE_HOST_SYSTEM_PROCESSOR}")
        message(STATUS "${symbolTargetName} - Not generating symbols due to cross-compilation.")
        return()
    else()
        # Use the SymbolPackager target name.
        set(SymTool "SymbolPackager")
    endif()

    if (DEFINED WIN32)
        # Use the PDB file to extract function symbols.
        add_custom_command(TARGET ${destTargetName} POST_BUILD
                           COMMAND "${SymTool}" ARGS "$<TARGET_PDB_FILE:${symbolTargetName}>"
                                                  -o "$<TARGET_FILE_DIR:${destTargetName}>/$<TARGET_FILE_BASE_NAME:${symbolTargetName}>.sym"
                                                  --exe "$<TARGET_FILE:${symbolTargetName}>"
                           COMMAND "${SymTool}" ARGS "$<TARGET_FILE_DIR:${destTargetName}>/$<TARGET_FILE_BASE_NAME:${symbolTargetName}>.sym"
                                                  -o "$<TARGET_FILE_DIR:${destTargetName}>/$<TARGET_FILE_BASE_NAME:${symbolTargetName}>.txt"
                           WORKING_DIRECTORY "$<TARGET_FILE_DIR:${destTargetName}>"
                           COMMENT "Creating stack trace data for ${symbolTargetName}...")
    else()
        # Ensure the linker generates a .map file and use it to produce a stack
        # trace symbol file which sits alongside the binary.
        target_link_options(${targetName} PRIVATE "LINKER:-Map=${CMAKE_CURRENT_BINARY_DIR}/$<TARGET_FILE_BASE_NAME:${symbolTargetName}>.map")

        # install(TARGETS "${targetName}_Symbols" RUNTIME DESTINATION ${CMAKE_INSTALL_FULL_BINDIR})

        # EXPERIMENTAL Use nm to extract the symbols, even internal symbols.
        #add_custom_command(TARGET ${targetName} POST_BUILD
        #                   COMMAND nm ARGS -a --demangle "$<TARGET_FILE:${targetName}>" > "${CMAKE_CURRENT_BINARY_DIR}/$<TARGET_FILE_BASE_NAME:${targetName}>.nm"
        #                   COMMAND SymbolPackager ARGS "{CMAKE_CURRENT_BINARY_DIR}/$<TARGET_FILE_BASE_NAME:${targetName}>.nm"
        #                                          -o "$<TARGET_FILE_DIR:${targetName}>/$<TARGET_FILE_BASE_NAME:${targetName}>.sym"
        #                   COMMAND SymbolPackager ARGS "$<TARGET_FILE_DIR:${targetName}>/$<TARGET_FILE_BASE_NAME:${targetName}>.sym"
        #                                          -o "$<TARGET_FILE_DIR:${targetName}>/$<TARGET_FILE_BASE_NAME:${targetName}>.txt"
        #                   WORKING_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}"
        #                   COMMENT "Creating stack trace data for ${targetName}...")

        add_custom_command(TARGET ${targetName} POST_BUILD
                           COMMAND "${SymTool}" ARGS "${CMAKE_CURRENT_BINARY_DIR}/$<TARGET_FILE_BASE_NAME:${targetName}>.map"
                                                  -o "$<TARGET_FILE_DIR:${targetName}>/$<TARGET_FILE_BASE_NAME:${targetName}>.sym"
                           COMMAND "${SymTool}" ARGS "$<TARGET_FILE_DIR:${targetName}>/$<TARGET_FILE_BASE_NAME:${targetName}>.sym"
                                                  -o "$<TARGET_FILE_DIR:${targetName}>/$<TARGET_FILE_BASE_NAME:${targetName}>.txt"
                           WORKING_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}"
                           COMMENT "Creating stack trace data for ${targetName}...")
    endif()
endfunction()

function(ag_enable_stacktrace targetName)
    ag_enable_proxy_stacktrace("${targetName}" "${targetName}")
endfunction()

# Create a static library which is part of the Ag suite.
# Arguments: target                   - The mandatory target name
#            QT                       - Defines the target using qt_add_library().
#            FOLDER <folder name>     - The name of the project folder to add the item to.
#            NAME <output name>       - The base name of the output file.
#            SOURCES <files>          - Internal source and header files.
#            WIN_SOURCES <files>      - Win32-specific internal source and header files.
#            POSIX_SOURCES <files>    - Linux-specific internal source and header files.
#            HEADERS <files>          - Public interface header files.
#            WIN_HEADERS <files>      - Win32-specific public interface header files.
#            POSIX_HEADERS <files>    - Linux-specific public interface header files.
#            PUBLIC_LIBS <libraries>  - Libraries which the library and its clients should link to.
#            PRIVATE_LIBS <libraries> - Libraries which the library link to.
function(ag_add_library target)
    set(prefix LIB)
    set(noValues QT)
    set(singleValues "FOLDER" "NAME")
    set(multiValues SOURCES WIN_SOURCES POSIX_SOURCES HEADERS WIN_HEADERS POSIX_HEADERS PUBLIC_LIBS PRIVATE_LIBS)

    cmake_parse_arguments("${prefix}"
                          "${noValues}"
                          "${singleValues}"
                          "${multiValues}"
                          ${ARGN})

    #cmake_print_variables(LIB_SOURCES LIB_WIN_SOURCES LIB_POSIX_SOURCES LIB_HEADERS
    #                      LIB_WIN_HEADERS LIB_POSIX_HEADERS)

    if (LIB_QT)
        qt_add_library(${target} STATIC)
    else()
        add_library(${target} STATIC)
    endif()

    if (DEFINED LIB_FOLDER)
        set_target_properties(${target} PROPERTIES FOLDER ${LIB_FOLDER})
    endif()

    if (NOT DEFINED LIB_NAME)
        # Base the library name on the target name.
        string(REPLACE "::" "" LIB_NAME "${target}")
    endif()

    set_target_properties(${target} PROPERTIES OUTPUT_NAME "${LIB_NAME}")

    target_sources(${target} PRIVATE ${LIB_SOURCES})
    target_sources(${target} PUBLIC ${LIB_HEADERS})

    if(DEFINED WIN32)
        target_sources(${target} PRIVATE ${LIB_WIN_SOURCES})
        target_sources(${target} PUBLIC ${LIB_WIN_HEADERS})
    else()
        target_sources(${target} PRIVATE ${LIB_POSIX_SOURCES})
        target_sources(${target} PUBLIC ${LIB_POSIX_HEADERS})
    endif()

    if(DEFINED LIB_PUBLIC_LIBS)
        target_link_libraries(${target} PUBLIC ${LIB_PUBLIC_LIBS})
    endif()

    if(DEFINED LIB_PRIVATE_LIBS)
        target_link_libraries(${target} PRIVATE ${LIB_PRIVATE_LIBS})
    endif()
endfunction()

# Create a Google Test unit test harness application or an Ag library.
# Arguments: target - The mandatory target name
#            TEST_LIB <libName> - The Ag library to test.
#            SOURCES <files>    - The unit test source code files.
function(ag_add_test_app target)
    set(prefix TAPP)
    set(noValues "")
    set(singleValues "TEST_LIB")
    set(multiValues SOURCES)

    cmake_parse_arguments("${prefix}"
                          "${noValues}"
                          "${singleValues}"
                          "${multiValues}"
                          ${ARGN})

    add_executable(${target})

    target_link_libraries(${target} PRIVATE gtest gtest_main)

    if(DEFINED TAPP_TEST_LIB)
        # Link to the library under test.
        target_link_libraries(${target} PRIVATE ${TAPP_TEST_LIB})
    endif()

    # Put the test app in the same folder as the library under test.
    get_target_property(folder ${TAPP_TEST_LIB} FOLDER)

    if (DEFINED folder)
        set_target_properties(${target} PROPERTIES FOLDER ${folder})
    endif()

    if (DEFINED WIN32)
        # Define a macro indicating the app uses the wmain() entry point.
        target_compile_definitions(${target} PRIVATE "_CUI")
    endif()

    target_sources(${target} PRIVATE ${TAPP_SOURCES})
    gtest_discover_tests(${target})
    ag_enable_stacktrace(${target})
endfunction()

# Create a GUI application dependent upon the Ag suite of libraries.
# ag_add_gui_app(target ...)
# Arguments: target                  - The mandatory target name
#            QT                      - The application will be defined using qt_add_executable()
#            FOLDER <folder name>    - The name of the project folder to add the item to.
#            NAME <app name>         - The base name of the application program file.
#            DESCRIPTION <desc>      - A description of the application's purpose.
#            VERSION <version>       - The version to embed in the application.
#            SOURCES <files>         - Internal source and header files.
#            WIN_SOURCES <files>     - Win32-specific source and header files.
#            POSIX_SOURCES <files>   - Linux-specific source and header files.
#            LIBS                    - The libraries the application should link to.
function(ag_add_gui_app target)
    set(prefix APP)
    set(noValues QT)
    set(singleValues FOLDER NAME DESCRIPTION VERSION)
    set(multiValues SOURCES WIN_SOURCES POSIX_SOURCES LIBS)

    cmake_parse_arguments("${prefix}"
                          "${noValues}"
                          "${singleValues}"
                          "${multiValues}"
                          ${ARGN})

    if ("${APP_QT}")
        if (DEFINED WIN32)
            qt_add_executable("${target}" WIN32)
        else()
            qt_add_executable("${target}")
        endif()

        if (DEFINED MSVC)
            set_target_properties("${target}" PROPERTIES
                                  VS_DEBUGGER_ENVIRONMENT
                                  "PATH=$<TARGET_FILE_DIR:Qt6::Core>;%PATH%")
        endif()
    elseif (DEFINED WIN32)
        add_executable(${target} WIN32)

        # Define a macro indicating the use of the WinMain() entry point.
        target_compile_definitions(${target} PRIVATE "_GUI")
    else()
        add_executable(${target})
    endif()

    if (DEFINED WIN32)
        target_sources(${target} PRIVATE ${APP_WIN_SOURCES})
    else()
        target_sources(${target} PRIVATE ${APP_POSIX_SOURCES})
    endif()

    target_sources(${target} PRIVATE ${APP_SOURCES})

    if (NOT DEFINED APP_VERSION)
        set(APP_VERSION "${PROJECT_VERSION}")
    endif()

    if (NOT DEFINED APP_NAME)
        set(APP_NAME "${target}")
    endif()

    if (DEFINED APP_FOLDER)
        set_target_properties(${target} PROPERTIES FOLDER ${APP_FOLDER})
    endif()

    if(DEFINED APP_LIBS)
        target_link_libraries(${target} PUBLIC ${APP_LIBS})
    endif()

    if(DEFINED APP_NAME)
        set_target_properties(${target} PROPERTIES OUTPUT_NAME "${APP_NAME}")
    endif()

    # Write the header and possibly resource file with the version substituted into it.
    string(REGEX MATCHALL "^([0-9]+)" versionComponents "${APP_VERSION}")
    list(LENGTH versionComponents verComponentCount)

    if ("${verComponentCount}" GREATER 0)
        list(GET versionComponents 0 APP_VER_MAJOR)
    else()
        set(APP_VER_MAJOR "${PROJECT_VERSION_MAJOR}")
    endif()

    if ("${verComponentCount}" GREATER 1)
        list(GET versionComponents 1 APP_VER_MINOR)
    else()
        set(APP_VER_MINOR "${PROJECT_VERSION_MINOR}")
    endif()

    if ("${verComponentCount}" GREATER 2)
        list(GET versionComponents 2 APP_VER_PATCH)
    else()
        set(APP_VER_PATCH "${PROJECT_VERSION_PATCH}")
    endif()

    if ("${verComponentCount}" GREATER 3)
        list(GET versionComponents 3 APP_VER_TWEAK)
    else()
        set(APP_VER_TWEAK "${PROJECT_VERSION_TWEAK}")
    endif()

    if(WIN32)
        configure_file("${CMAKE_CURRENT_FUNCTION_LIST_DIR}/Win32Version.rc.in"
                       "Win32Version.rc" COPYONLY)
        configure_file("${CMAKE_CURRENT_FUNCTION_LIST_DIR}/Win32Version.h.in"
                       "Win32Version.h" @ONLY NEWLINE_STYLE WIN32)

        target_sources("${target}" PRIVATE
                       "${CMAKE_CURRENT_BINARY_DIR}/Win32Version.rc"
                       "${CMAKE_CURRENT_BINARY_DIR}/Win32Version.h")
    endif()

    configure_file("${CMAKE_CURRENT_FUNCTION_LIST_DIR}/Version.hpp.in"
                   "Version.hpp" @ONLY)

    target_sources("${target}" PRIVATE
                   "${CMAKE_CURRENT_BINARY_DIR}/Version.hpp")

    include_directories("${target}" PRIVATE "${CMAKE_CURRENT_BINARY_DIR}")

    ag_enable_stacktrace(${target})
endfunction()


# Create a console application dependent upon the Ag suite of libraries.
# ag_add_cli_app(target ...)
# Arguments: target                  - The mandatory target name
#            FOLDER <folder name>    - The name of the project folder to add the item to.
#            NAME <app name>         - The base name of the application program file.
#            DESCRIPTION <desc>      - A description of the application's purpose.
#            VERSION <version>       - The version to embed in the application.
#            SOURCES <files>         - Internal source and header files.
#            WIN_SOURCES <files>     - Win32-specific source and header files.
#            POSIX_SOURCES <files>   - Linux-specific source and header files.
#            LIBS                    - The libraries the application should link to.
function(ag_add_cli_app target)
    set(prefix APP)
    set(noValues "")
    set(singleValues FOLDER NAME DESCRIPTION VERSION)
    set(multiValues SOURCES WIN_SOURCES POSIX_SOURCES LIBS)

    cmake_parse_arguments("${prefix}"
                          "${noValues}"
                          "${singleValues}"
                          "${multiValues}"
                          ${ARGN})

    add_executable(${target})

    if(DEFINED WIN32)
        target_sources(${target} PRIVATE ${APP_WIN_SOURCES})

        # Define a macro indicating the use of the WinMain() entry point.
        target_compile_definitions(${target} PRIVATE "_CUI")
    else()
        target_sources(${target} PRIVATE ${APP_POSIX_SOURCES})
    endif()

    target_sources(${target} PRIVATE ${APP_SOURCES})

    if (DEFINED APP_FOLDER)
        set_target_properties(${target} PROPERTIES FOLDER ${APP_FOLDER})
    endif()

    if(DEFINED APP_LIBS)
        target_link_libraries(${target} PUBLIC ${APP_LIBS})
    endif()

    if(DEFINED APP_NAME)
        set_target_properties(${target} PROPERTIES OUTPUT_NAME "${APP_NAME}")
    endif()

    ag_enable_stacktrace(${target})
endfunction()

# ag_add_static_data(target, StaticData.hpp Input1.txt Input2.txt ...)
#
# Will produce StaticData.hpp containing function declarations like:
# const char *getInputText1();
# const char *getInputText2();
# ...
# and StaticData.cpp containing the definitions of the functions which
# return the content of the text files as static text.
#
# The source file is generated via a custom command, so post-configuration-time
# changes to the source text files will force a re-generation and recompilation
# of the generated code.
function(ag_add_static_data target headerName)
    set(prefix data)
    set(noValues BINARY)
    set(singleValues)
    set(multiValues SOURCES)

    cmake_parse_arguments("${prefix}"
                          "${noValues}"
                          "${singleValues}"
                          "${multiValues}"
                          ${ARGN})

    if (data_BINARY)
        string(APPEND declarations "#include <cstdint>\n\n")
    endif()

    foreach(dataFileName IN ITEMS ${data_SOURCES})
        get_filename_component(fullName ${dataFileName} ABSOLUTE BASE_DIR ${CMAKE_CURRENT_SOURCE_DIR})
        get_filename_component(baseName ${fullName} NAME_WLE)

        if (data_BINARY)
            string(APPEND declarations "const uint8_t *get${baseName}Data(size_t &byteCount);\n")
        else()
            string(APPEND declarations "const char *get${baseName}Text();\n")
        endif()

        list(APPEND inputFiles ${fullName})
    endforeach()

    get_filename_component(fullHeaderPath ${headerName}
                           ABSOLUTE BASE_DIR ${CMAKE_CURRENT_BINARY_DIR})
    get_filename_component(headerDir ${fullHeaderPath} DIRECTORY)
    get_filename_component(headerBaseName ${fullHeaderPath} NAME_WLE)
    set(fullSourceName "${headerDir}/${headerBaseName}.cpp")

    # Generate a UUID for the header guard macro.
    string(UUID headerGuardGuid
           NAMESPACE F54211FB-AC61-462A-B4A6-037E98FCB7CC
           NAME ${headerName}
           TYPE SHA1 UPPER)

    string(REPLACE "-" "_" headerGuard ${headerGuardGuid})

    configure_file("${CMAKE_CURRENT_FUNCTION_LIST_DIR}/StaticData.hpp.in"
                   "${fullHeaderPath}" @ONLY)

    # Schedule the source file to be generated at build time if any of
    # the data files are edited.
    set(buildTimeScript "${CMAKE_CURRENT_BINARY_DIR}/${headerBaseName}.cmake")

    if (data_BINARY)
        configure_file("${CMAKE_CURRENT_FUNCTION_LIST_DIR}/GenerateData.cmake.in" "${buildTimeScript}" @ONLY)
    else()
        configure_file("${CMAKE_CURRENT_FUNCTION_LIST_DIR}/GenerateText.cmake.in" "${buildTimeScript}" @ONLY)
    endif()

    add_custom_command(OUTPUT ${fullSourceName}
                       COMMAND ${CMAKE_COMMAND} ARGS -P ${buildTimeScript}
                       DEPENDS ${inputFiles}
                       WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
                       COMMENT "Regenerating ${fullSourceName}...")

    target_sources(${target} PRIVATE ${fullHeaderPath} ${fullSourceName} ${inputFiles})

    target_include_directories(${target} PRIVATE ${headerDir})
endfunction()

# ag_copy_shared_lib(<destTarget> <shared_lib_targets...>)
#
# Copies shared library binaries to the build output filder of destTarget.
#
function(ag_copy_shared_lib destTarget)
    foreach(targetName IN LISTS ARGN)
        if (TARGET ${targetName})
            # Add a command to copy the library binary to the
            add_custom_command(TARGET ${destTarget} POST_BUILD
                    COMMAND "${CMAKE_COMMAND}"
                    ARGS    -E copy_if_different
                            #"$<TARGET_PDB_FILE:${targetName}>"
                            #"$<TARGET_FILE_BASE_NAME:${targetName}>.pdb"
                            #"$<TARGET_FILE_BASE_NAME:${targetName}>.sym"
                            "$<TARGET_FILE:${targetName}>"
                            "$<TARGET_FILE_DIR:${destTarget}>"
                    COMMENT "Copying ${targetName} to ${destTarget} output directory...")
        else()
            message(SEND_ERROR "'${target}' is not a valid target.")
        endif()
    endforeach()
endfunction()