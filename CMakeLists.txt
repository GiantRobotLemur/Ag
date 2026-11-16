# The CMake configuration for the Silver (Ag) runtime utility library.
cmake_minimum_required(VERSION 4.4)
set(AG_VERSION "0.0.1.0")

if ("${CMAKE_SOURCE_DIR}" STREQUAL "${CMAKE_CURRENT_LIST_DIR}")
    set(AG_IS_ROOT 1)
endif()

if (DEFINED AG_IS_ROOT)
    project(Silver
            VERSION "${AG_VERSION}"
            DESCRIPTION "An cross platform runtime library."
            HOMEPAGE_URL "https://github.com/GiantRobotLemur/Ag"
            LANGUAGES CXX)
endif()

include("${CMAKE_CURRENT_LIST_DIR}/cmake/ConfigureBuild.cmake")
include("${CMAKE_CURRENT_LIST_DIR}/cmake/Utilities.cmake")

if (DEFINED AG_IS_ROOT)
    # Set build settings compatible with the Ag libraries.
    ag_configure_build()

    # Load external presets, if any.
    set(presetFile "AgOptions.cmake")

    cmake_path(ABSOLUTE_PATH presetFile
               BASE_DIRECTORY "${CMAKE_CURRENT_LIST_DIR}/../"
               NORMALIZE OUTPUT_VARIABLE presetPath)

    if(EXISTS "${presetPath}")
        message(STATUS "Preconfiguring Ag from ${presetPath}...")

        include("${presetPath}")
    endif()

    # Get bzip2 - Always needed for AgCore
    ag_configure_bzip2()

    # Get Google Test
    ag_configure_gtest()

    if(AG_CONFIG_GFX OR AG_CONFIG_OPEN_GL)
        # Get GLM.
        ag_configure_glm()
    endif()

    if (AG_CONFIG_SDL2)
        ag_configure_sdl2()
    endif()

    if (AG_CONFIG_SDL3)
        ag_configure_sdl3()
    endif()

    if (AG_CONFIG_QT)
        find_package(Qt6 QUIET COMPONENTS Core Widgets Concurrent)

        if (${Qt6_FOUND})
            set(AG_CONFIG_QT ON CACHE "BOOL" "Use Qt" FORCE)
            message(STATUS "Qt6: Found (Version ${Qt6_VERSION})")

            # Perform Qt initialisation once other 3rd party libraries are configured.
            qt_standard_project_setup()
        else()
            set(AG_CONFIG_QT OFF CACHE "BOOL" "Use Qt" FORCE)
            message(STATUS "Qt6: Not Found (Add Qt6 path to CMAKE_PREFIX_PATH)")
        endif()
    endif()
else()
    # Promote AG_CMAKE_UTILS_DIR for use in sibling sub-directories.
    set(AG_CMAKE_UTILS_DIR "${AG_CMAKE_UTILS_DIR}" PARENT_SCOPE)

    # Set build settings compatible with the Ag libraries.
    ag_configure_build()

    # Get bzip2 - Always needed for AgCore
    ag_configure_bzip2()

    # Get Google Test
    ag_configure_gtest()

    if (AG_CONFIG_QT)
        # Attempt to find the Qt6 package if it hasn't previously been found.
        if (NOT ${Qt6_FOUND})
            find_package(Qt6 QUIET COMPONENTS Core Widgets Concurrent)
        endif()

        # Deal with the existence of Qt whether we just found it or it was
        # found previously.
        if (${Qt6_FOUND})
            set(AG_CONFIG_QT ON CACHE "BOOL" "Use Qt" FORCE)
            message(STATUS "Qt6: Found (Version ${Qt6_VERSION})")

            # Perform Qt initialisation once other 3rd party libraries are configured.
            qt_standard_project_setup()
        else()
            set(AG_CONFIG_QT OFF CACHE "BOOL" "Use Qt" FORCE)
            message(STATUS "Qt6: Not Found (Add Qt6 path to CMAKE_PREFIX_PATH)")
        endif()
    endif()
endif()

add_subdirectory(Source)