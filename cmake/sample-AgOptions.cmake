# An optional CMake file used to preset which Ag projects should be configured.

if(DEFINED WIN32)
    set(AG_CONFIG_WIN32 OFF CACHE "BOOL" "Use Win32" FORCE)
endif()

set(AG_EXT_SYMBOL_PACKAGER "" CACHE FILEPATH "Symbol package path" FORCE)
set(AG_STATIC_RUNTIME ON CACHE "BOOL" "Static link" FORCE)
set(AG_CONFIG_QT OFF CACHE "BOOL" "Use Qt" FORCE)
set(AG_CONFIG_GFX OFF CACHE "BOOL" "Use Gfx" FORCE)
set(AG_CONFIG_OPEN_GL OFF CACHE "BOOL" "Use GL" FORCE)
set(AG_CONFIG_SDL2 OFF CACHE "BOOL" "Use SDL2" FORCE)
set(AG_CONFIG_SDL3 OFF CACHE "BOOL" "Use SDL3" FORCE)

set(AG_ENABLE_X64_V1 ON CACHE "BOOL" "Uses the capabilities of the x86-64 v1 architecture - SSE2" FORCE)
set(AG_ENABLE_X64_V2 ON CACHE "BOOL" "Uses the capabilities of the x86-64 v2 architecture - SSE4, POPCNT, CMPXCHG16B" FORCE)
set(AG_ENABLE_X64_V3 ON CACHE "BOOL" "Uses the capabilities of the x86-64 v3 architecture - AVX, AVX2, FMA, LZCNT" FORCE)
set(AG_ENABLE_X64_V4 OFF CACHE "BOOL" "Uses the capabilities of the x86-64 v4 architecture - AVX512F/BW/CD/DQ/VL" FORCE)