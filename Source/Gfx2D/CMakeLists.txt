# CMakeLists configuration for the 2-dimensional graphics library

set(GFX2D_INCLUDE_DIR "${AG_INCLUDE_DIR}/Ag/Gfx2D")

# Define the library.
ag_add_library(Gfx2D FOLDER         Graphics
                     SOURCES        PreCompiledHeader.hpp
                                    Operations.hpp
                                    Operations_Base.hpp
                                    Operations_x64v1.hpp
                                    Colour.cpp
                                    ${GFX2D_INCLUDE_DIR}/Colour.hpp
                                    Colours.cpp
                                    ${GFX2D_INCLUDE_DIR}/Colours.hpp
                                    GraphicArtefact.cpp
                                    ${GFX2D_INCLUDE_DIR}/GraphicArtefact.hpp
                                    Pen.cpp
                                    ${GFX2D_INCLUDE_DIR}/Pen.hpp
                                    Brush.cpp
                                    ${GFX2D_INCLUDE_DIR}/Brush.hpp
                                    Brushes.cpp
                                    ${GFX2D_INCLUDE_DIR}/Brushes.hpp
                                    Font.cpp
                                    ${GFX2D_INCLUDE_DIR}/Font.hpp
                                    Path.cpp
                                    ${GFX2D_INCLUDE_DIR}/Path.hpp
                                    StrokeHelper.cpp
                                    StrokeHelper.hpp
                                    Gfx2D_Internal.cpp
                                    Gfx2D_Internal.hpp
                                    Graphic.cpp
                                    ${GFX2D_INCLUDE_DIR}/Graphic.hpp
                                    PartitionedPolygon.cpp
                                    ${GFX2D_INCLUDE_DIR}/PartitionedPolygon.hpp
                                    DecompositionContext.cpp
                                    DecompositionContext.hpp
                                    GraphicDecomposition.cpp
                                    ${GFX2D_INCLUDE_DIR}/GraphicDecomposition.hpp

                     HEADERS        ${AG_INCLUDE_DIR}/Ag/Gfx2D.hpp
                     PUBLIC_LIBS    Geometry AgCore)


target_precompile_headers(Gfx2D PRIVATE [["PreCompiledHeader.hpp"]])
target_compile_definitions(Gfx2D PUBLIC AG_GFX_2D)
target_include_directories(Gfx2D PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}")

# if (AG_CONFIG_OPEN_GL)
# TODO: Add ObjectGL-specific drivers here.
# endif()

# if (AG_CONFIG_SDL3)
# TODO: Add SDL3-specific drivers here, perhaps for GPU?
# endif()

list(APPEND DOC_SRCS "${CMAKE_CURRENT_SOURCE_DIR}"
                     "${AG_INCLUDE_DIR}/Ag/Gfx2D.hpp"
                     "${AG_INCLUDE_DIR}/Ag/Gfx2D")

# Define the unit test harness.
ag_add_test_app(Gfx2D_Tests TEST_LIB    Gfx2D
                            SOURCES     Gfx2D_TestPCH.hpp
                                        Test_Operations.cpp
                                        Test_Colours.cpp
                                        Test_StrokeHelper.cpp)

target_precompile_headers(Gfx2D_Tests PRIVATE [["Gfx2D_TestPCH.hpp"]])
target_include_directories(Gfx2D_Tests PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}")