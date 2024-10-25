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

    set(ExtFolderName "3rdParty")

    message(STATUS "Obtaining Google Test...")
    FetchContent_MakeAvailable(googletest)
    include(GoogleTest)
    set_target_properties(gtest PROPERTIES FOLDER "${ExtFolderName}")
    set_target_properties(gtest_main PROPERTIES FOLDER "${ExtFolderName}")
    set_target_properties(gmock PROPERTIES FOLDER "${ExtFolderName}")
    set_target_properties(gmock_main PROPERTIES FOLDER "${ExtFolderName}")

    # message(STATUS "Obtaining glm...")
    # FetchContent_MakeAvailable(glm)
    # set_target_properties(glm PROPERTIES FOLDER "${ExtFolderName}")
    # target_link_libraries(${myTarget} PRIVATE glm::glm)
endif()

add_subdirectory(Source)