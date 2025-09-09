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

        set(AG_EXT_SYMBOL_PACKAGER "" CACHE FILEPATH "The path to a pre-built Symbol Packager tool (useful in cross compilation).")

        option(AG_STATIC_RUNTIME "Indicates whether libraries should link to static C/C++ runtime libraries" OFF)
        option(AG_CONFIG_QT "Indicates whether Qt-dependent components should be configured." OFF)
        option(AG_CONFIG_GFX "Indicates whether Graphics-related components should be configured." OFF)
        #option(AG_CONFIG_GL "Indicates whether OpenGL-dependent components should be configured." OFF)
        option(AG_CONFIG_SDL3 "Indicates whether lib SDL3-dependent components should be configured." OFF)

        include(FetchContent)

        if (AG_STATIC_RUNTIME)
            message(STATUS "Linking to static runtime libraries")

            if(MSVC)
                # Tell MSVC to link to static runtime libraries.
                set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")
            endif()
        endif()


        # Configure the bzip2 compression library needed by SymbolPackager and AgCore
        # Note: Only the master branch (and none of the tags) seems to have
        #   CMake integration.
        FetchContent_Declare(bzip2
                             GIT_REPOSITORY https://github.com/libarchive/bzip2.git
                             GIT_TAG master)

        FetchContent_Declare(googletest
                             GIT_REPOSITORY https://github.com/google/googletest.git
                             GIT_TAG release-1.12.1)

        FetchContent_Declare(glm
                             GIT_REPOSITORY https://github.com/g-truc/glm.git
                             GIT_TAG 1.0.1)

        FetchContent_Declare(SDL3
                             GIT_REPOSITORY https://github.com/libsdl-org/SDL.git
                             GIT_TAG release-3.2.10)

        # Define the name of folder used for fetched content projects.
        set(AG_EXT_PROJ_FOLDER "3rdParty")
    endmacro()

    function(ag_config_external_projects)
        foreach(target IN LISTS ARGN)
            if (TARGET ${target})
                set_target_properties("${target}" PROPERTIES FOLDER "${AG_EXT_PROJ_FOLDER}")

                # This is only good for CMake 3.25+ :-(
                set_target_properties("${target}" PROPERTIES SYSTEM ON)
            endif()
        endforeach()
    endfunction()

    macro(ag_configure_bzip2)
        message(STATUS "Obtaining bzip2...")
        option(ENABLE_LIB_ONLY "Bzip2 libs only" on)
        option(ENABLE_STATIC_LIB "Build bzip2 static lib" on)
        option(ENABLE_SHARED_LIB "Build bzip2 shared lib" off)
        FetchContent_MakeAvailable(bzip2)

        if (bzip2_POPULATED)
            set(BZIP2_INCLUDE_DIRECTORY "${bzip2_SOURCE_DIR}")
        else()
            message(FATAL "Failed to obtain bzip2 source code.")
        endif()

        ag_config_external_projects(bz2_ObjLib bz2_static check)
    endmacro()

    macro(ag_configure_gtest)
        enable_testing()

        message(STATUS "Obtaining Google Test...")

        # Set Google Test configuration options here as
        #   FetchContent_Declare(CMAKE_CACHE_ARGS) has no effect.
        option(BUILD_GMOCK "Build GMock" OFF)
        option(INSTALL_GTEST "Install GTest" OFF)

        if (AG_STATIC_RUNTIME)
            option(gtest_force_shared_crt "Static CRT" OFF)
        else()
            option(gtest_force_shared_crt "Static CRT" ON)
        endif()

        FetchContent_MakeAvailable(googletest)
        include(GoogleTest)

        ag_config_external_projects(gtest gtest_main gmock gmock_main)
    endmacro()

    macro(ag_configure_glm)
        message(STATUS "Obtaining glm...")

        # Set GLM configuration options here as
        #   FetchContent_Declare(CMAKE_CACHE_ARGS) has no effect.
        option(GLM_BUILD_TESTS "Build Tests" OFF)
        option(BUILD_SHARED_LIBS "Build Shared" OFF)

        FetchContent_MakeAvailable(glm)
        ag_config_external_projects(glm)
        # target_link_libraries(${myTarget} PRIVATE glm::glm)

        # Adds the .natvis file to MSVC projects, but only to the final binary.
        function(GLM_Link target)
            if(DEFINED MSVC)
                # Include the .natvis file packaged with GLM.
                get_target_property(glm_inc_dirs glm::glm INTERFACE_INCLUDE_DIRECTORIES)
                list(GET glm_inc_dirs 0 glm_inc_dir)

                if (EXISTS "${glm_inc_dir}/glm.natvis")
                    message(STATUS "${target}: Adding ${glm_inc_dir}/glm.natvis")
                    target_sources("${target}" PRIVATE "${glm_inc_dir}/glm.natvis")
                endif()
            endif()
        endfunction()
    endmacro()

    macro(ag_configure_sdl3)
        message(STATUS "Obtaining SDL 3...")

        # Set SDL2 configuration options here as
        #   FetchContent_Declare(CMAKE_CACHE_ARGS) has no effect.
        if (AG_STATIC_RUNTIME)
            option(SDL_FORCE_STATIC_VCRT "Use Static MSVCRT" ON)
            option(SDL_STATIC "Build Static" ON)
        else()
            option(SDL_FORCE_STATIC_VCRT "Use Static MSVCRT" OFF)
        endif()

        option(SDL_TEST_LIBRARY "Build the SDL3_test library" OFF)
        option(SDL_DISABLE_UNINSTALL  "Disable uninstallation of SDL3" ON)

        FetchContent_MakeAvailable(SDL3)

        ag_config_external_projects(SDL3_test SDL3-shared SDL3-static SDL_uclibc unintall)
    endmacro()
endif()