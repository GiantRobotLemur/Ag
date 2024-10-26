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
    ag_configure_build()

    ag_configure_gtest()

    ag_configure_glm()
endif()

add_subdirectory(Source)