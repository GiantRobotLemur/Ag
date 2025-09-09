# CMakeLists file for the WriteGlyphGeometry tool.

if(WIN32 AND AG_CONFIG_WIN32)
    # The WriteGlyphGeometry tool extracts glyph geometry from fonts using
    # Windows GDI, hence is Win32-only.
    add_executable(WriteGlyphGeometry
                   PreCompiledHeader.hpp
                   Helpers.cpp
                   Helpers.hpp
                   Main.cpp
                   CommandLineOptions.cpp
                   CommandLineOptions.hpp
                   GlyphExtractor.cpp
                   GlyphExtractor.hpp
                   GlyphWriter.cpp
                   GlyphWriter.hpp)

    # Configure a pre-compiled header.
    target_precompile_headers(WriteGlyphGeometry PRIVATE [["PreCompiledHeader.hpp"]])
    target_include_directories(WriteGlyphGeometry PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}")

    # Tidy the app away into a folder.
    set_target_properties(WriteGlyphGeometry PROPERTIES FOLDER Tools)
endif()

# embed_glyph_geometry(target SOURCE <source file> DEST <cpp source file>)
#
# Reads a text file of <name>:<character> pairs which are used to create
# a C++ source file containing the geometry for the specified character
# in the target project.
#
# SOURCE    - The path to the source text file, resolved relative to
#             CMAKE_CURRENT_SOURCE_DIR.
# DEST      - The C++ source file to create from the source, resolved relative
#             to CMAKE_CURRENT_BINARY_DIR.
# FALLBACK  - The file to copy to DEST on non-Win32 platforms, or copy the
#             created file to on Win32 platforms.
# FONT      - The font read to obtain the glyph geometry of the specified
#             characters.
function(embed_glyph_geometry target)
    set(prefix GLYPH)
    set(noValues "")
    set(singleValues "SOURCE" "FALLBACK" "DEST" "FONT" "FOLDER")
    set(multiValues "")

    cmake_parse_arguments("${prefix}"
                          "${noValues}"
                          "${singleValues}"
                          "${multiValues}"
                          ${ARGN})

    if(NOT GLYPH_SOURCE)
        message(FATAL_ERROR "No source glyphs file specified.")
    endif()

    if (NOT GLYPH_DEST)
        message(FATAL_ERROR "No destination glyph source file specified.")
    endif()

    if (NOT WIN32 AND NOT GLYPH_SOURCE)
        message(FATAL_ERROR "No fallback glyph data specified.")
    endif()

    cmake_path(ABSOLUTE_PATH GLYPH_SOURCE
               BASE_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
               OUTPUT_VARIABLE sourcePath)

    cmake_path(ABSOLUTE_PATH GLYPH_DEST
               BASE_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}"
               OUTPUT_VARIABLE destPath)

    if (GLYPH_FALLBACK)
        # Resolve the absolute path to the fallback file.
        cmake_path(ABSOLUTE_PATH GLYPH_FALLBACK
                   BASE_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
                   OUTPUT_VARIABLE backupPath)
    else()
        # Define a default backup file name derived from the
        # destination file name.
        cmake_path(GET destPath STEM destName)
        set(backupName "${destName}_backup.txt")

        cmake_path(GET sourcePath PARENT_PATH sourceDir)

        cmake_path(APPEND sourceDir "${backupName}" OUTPUT_VARIABLE backupPath)
    endif()

    if (TARGET WriteGlyphGeometry)
        # Create a command to extract the glyph outlines from GDI fonts.
        if (NOT GLYPH_FONT)
            set(GLYPH_FONT "Arial")
        endif()

        # Create a command to re-generate the glyph outline and encode them
        # as literal C++ data.
        add_custom_command(OUTPUT "${destPath}"
                           MAIN_DEPENDENCY "${sourcePath}"
                           COMMAND WriteGlyphGeometry
                           ARGS "--source" "${destPath}"
                                "--font" "${GLYPH_FONT}"
                                "--glyphs" "${sourcePath}"
                           # Copy the output file back to the source folder
                           # for use on non-Win32 platforms.
                           COMMAND "${CMAKE_COMMAND}"
                           ARGS -E copy "${destPath}" "${backupPath}"
                           WORKING_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}"
                           COMMENT "Extract glyph outlines...")

        target_sources("${target}" PRIVATE "${destPath}")

        if (GLYPH_FOLDER)
            source_group("${GLYPH_FOLDER}" FILES "${destPath}")
        endif()
    else()
        target_sources("${target}" PRIVATE "${backupPath}")
        add_custom_command(OUTPUT "${destPath}"
                           MAIN_DEPENDENCY "${backupPath}"
                           # Copy the backup file to the output file
                           # for use on non-Win32 platforms.
                           COMMAND "${CMAKE_COMMAND}"
                           ARGS -E copy "${backupPath}" "${destPath}"
                           WORKING_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}"
                           COMMENT "Copying old glyph outlines...")
    endif()
endfunction()
