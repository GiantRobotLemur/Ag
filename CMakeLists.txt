# The CMake configuration for the Silver (Ag) runtime utility library.
cmake_minimum_required(VERSION 3.21)
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
    #set(AG_CONFIG_SDL3 ON)
    #set(AG_CONFIG_GLM ON)

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

    # Get Google Test
    ag_configure_gtest()

    if(AG_CONFIG_GFX)
        # Get GLM.
        ag_configure_glm()
    endif()

    if (AG_CONFIG_SDL3)
        ag_configure_sdl3()
    endif()
endif()

add_subdirectory(Source)