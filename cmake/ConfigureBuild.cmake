# A standard CMake configuration for C++ which can be used by all consuming projects.

if (NOT DEFINED AG_BUILD_CONFIGURED)
    set(AG_BUILD_CONFIGURED 1)

    macro(ag_configure_build)
        set_property(GLOBAL PROPERTY USE_FOLDERS ON)

        set(CMAKE_CXX_STANDARD          17)
        set(CMAKE_CXX_STANDARD_REQUIRED ON)
        set(CMAKE_CXX_EXTENSIONS        ON)

        get_property(isMultiConfig GLOBAL PROPERTY GENERATOR_IS_MULTI_CONFIG)

        if(isMultiConfig)
            # Limit build configurations to Release with Debug Info and Debug.
            set(CMAKE_CONFIGURATION_TYPES "Debug;RelWithDebInfo")
            message(STATUS "Configuring multi-configuration build...")
        endif()

        # Configure global compiler options.
        if (DEFINED MSVC)
            add_compile_options("/W4")
        else()
            add_compile_options(-Wall -Wextra -pedantic -Wshadow)

            # Ensure _DEBUG is defined for debug builds, this is done automatically
            # for MSVC.
            add_compile_definitions($<$<CONFIG:Debug>:_DEBUG>)
        endif()

        if(DEFINED WIN32)
            option(AG_CONFIG_WIN32 "Indicates whether Win32-specific components should be configured." OFF)
        endif()

        set(AG_EXT_SYMBOL_PACKAGER "" CACHE FILEPATH "The path to a pre-built Symbol Packager tool (usefull in cross compilation).")

        option(AG_STATIC_RUNTIME "Indicates whether libraries should link to static C/C++ runtime libraries" OFF)
        option(AG_CONFIG_QT "Indicates whether Qt-dependent components should be configured." OFF)
        option(AG_CONFIG_GFX "Indicates whether Graphics-related components should be configured." OFF)
        option(AG_CONFIG_GL "Indicates whether OpenGL-dependent components should be configured." OFF)
        option(AG_CONFIG_SDL "Indicates whether lib SDL-dependent components should be configured." OFF)

        include(FetchContent)

        if (AG_STATIC_RUNTIME)
            message(STATUS "Linking to static runtime libraries")
            set(_GTEST_ARGS "-Dgtest_force_shared_crt:BOOL=OFF -DBUILD_GMOCK:BOOL=OFF -DINSTALL_GTEST:BOOL=OFF")
            if(MSVC)
                # Tell MSVC to link to static runtime libraries.
                set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")
            endif()
        else()
            set(_GTEST_ARGS "-Dgtest_force_shared_crt:BOOL=ON -DBUILD_GMOCK:BOOL=OFF -DINSTALL_GTEST:BOOL=OFF")
        endif()

        FetchContent_Declare(googletest
                             GIT_REPOSITORY https://github.com/google/googletest.git
                             GIT_TAG release-1.12.1
                             CMAKE_CACHE_ARGS "${_GTEST_ARGS}"
                             FIND_PACKAGE_ARGS NAMES GTest)

        FetchContent_Declare(glm
                             GIT_REPOSITORY https://github.com/g-truc/glm.git
                             GIT_TAG 1.0.1
                             CMAKE_CACHE_ARGS -DGLM_BUILD_TESTS:BOOL=OFF -DBUILD_SHARED_LIBS:BOOL=OFF
                             FIND_PACKAGE_ARGS NAMES glm)

        # Define the name of folder used for fetched content projects.
        set(AG_EXT_PROJ_FOLDER "3rdParty")
    endmacro()

    macro(ag_configure_gtest)
        enable_testing()

        message(STATUS "Obtaining Google Test...")
        FetchContent_MakeAvailable(googletest)
        include(GoogleTest)
        set_target_properties(gtest PROPERTIES FOLDER "${AG_EXT_PROJ_FOLDER}")
        set_target_properties(gtest_main PROPERTIES FOLDER "${AG_EXT_PROJ_FOLDER}")
        set_target_properties(gmock PROPERTIES FOLDER "${AG_EXT_PROJ_FOLDER}")
        set_target_properties(gmock_main PROPERTIES FOLDER "${AG_EXT_PROJ_FOLDER}")
    endmacro()

    macro(ag_configure_glm)
        message(STATUS "Obtaining glm...")
        FetchContent_MakeAvailable(glm)
        set_target_properties(glm PROPERTIES FOLDER "${AG_EXT_PROJ_FOLDER}")
        # target_link_libraries(${myTarget} PRIVATE glm::glm)
    endmacro()
endif()