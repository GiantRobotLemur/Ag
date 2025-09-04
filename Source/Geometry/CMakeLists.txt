# CMakeLists configuration for the 2-dimensional geometry library

set(GEOM_INCLUDE_DIR "${AG_INCLUDE_DIR}/Ag/Geometry")

# Define the library.
ag_add_library(Geometry FOLDER      Geometry
                        SOURCES     PreCompiledHeader.hpp
                                    Exceptions.cpp
                                    ${GEOM_INCLUDE_DIR}/Exceptions.hpp
                                    NumericDomain.cpp
                                    ${GEOM_INCLUDE_DIR}/NumericDomain.hpp
                                    Angle.cpp
                                    ${GEOM_INCLUDE_DIR}/Angle.hpp
                                    Point2I.cpp
                                    ${GEOM_INCLUDE_DIR}/Point2I.hpp
                                    Point2ICollectionView.cpp
                                    ${GEOM_INCLUDE_DIR}/Point2ICollectionView.hpp
                                    Size2I.cpp
                                    ${GEOM_INCLUDE_DIR}/Size2I.hpp
                                    Rect2I.cpp
                                    ${GEOM_INCLUDE_DIR}/Rect2I.hpp
                                    Point2D.cpp
                                    ${GEOM_INCLUDE_DIR}/Point2D.hpp
                                    Point2DCollectionView.cpp
                                    ${GEOM_INCLUDE_DIR}/Point2DCollectionView.hpp
                                    Size2D.cpp
                                    ${GEOM_INCLUDE_DIR}/Size2D.hpp
                                    Rect2D.cpp
                                    ${GEOM_INCLUDE_DIR}/Rect2D.hpp
                                    ${GEOM_INCLUDE_DIR}/LineHelpers.hpp
                                    LineSeg2D.cpp
                                    ${GEOM_INCLUDE_DIR}/LineSeg2D.hpp
                                    Line2D.cpp
                                    ${GEOM_INCLUDE_DIR}/Line2D.hpp
                                    LineEq2D.cpp
                                    ${GEOM_INCLUDE_DIR}/LineEq2D.hpp
                                    Triangle2D.cpp
                                    ${GEOM_INCLUDE_DIR}/Triangle2D.hpp
                                    SnapPoint.cpp
                                    ${GEOM_INCLUDE_DIR}/SnapPoint.hpp
                                    SnapContext.cpp
                                    ${GEOM_INCLUDE_DIR}/SnapContext.hpp
                                    QuadBezierCurve2D.cpp
                                    ${GEOM_INCLUDE_DIR}/QuadBezierCurve2D.hpp
                                    CubicBezierCurve2D.cpp
                                    ${GEOM_INCLUDE_DIR}/CubicBezierCurve2D.hpp
                                    Arc2D.cpp
                                    ${GEOM_INCLUDE_DIR}/Arc2D.hpp
                                    DCEL.cpp
                                    ${GEOM_INCLUDE_DIR}/DCEL.hpp
                                    DCEL_Sweep.cpp
                                    ${GEOM_INCLUDE_DIR}/DCEL_Sweep.hpp
                                    DCEL_RingTracer.cpp
                                    DCEL_RingTracer.hpp
                                    DCEL_Triangulate.cpp
                                    DCEL_Triangulate.hpp
                                    DCEL_Algorithms.cpp
                                    ${GEOM_INCLUDE_DIR}/DCEL_Algorithms.hpp
                        WIN_SOURCES Geometry.natvis
                        HEADERS     ${AG_INCLUDE_DIR}/Ag/Geometry.hpp
                        #PRIVATE_LIBS glm::glm
                        PUBLIC_LIBS AgCore)


target_precompile_headers(Geometry PRIVATE [["PreCompiledHeader.hpp"]])
target_include_directories(Geometry PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}")

# Define the unit test harness.
ag_add_test_app(Geometry_Tests  TEST_LIB    Geometry
                                SOURCES     Geometry_TestsPCH.hpp
                                            GtestHelpers.cpp
                                            GtestHelpers.hpp
                                            Test_NumericDomain.cpp
                                            Test_Angle.cpp
                                            Test_Point2I.cpp
                                            Test_Point2D.cpp
                                            Test_Line2D.cpp
                                            Test_LineEq2D.cpp
                                            Test_LineSeg2D.cpp
                                            Test_QuadBezierCurve2D.cpp
                                            Test_CubicBezierCurve2D.cpp
                                            Test_Arc2D.cpp
                                            Test_DCEL_Tools.cpp
                                            Test_DCEL_Tools.hpp
                                            Test_DCEL.cpp
                                            Test_DCEL_Sweep.cpp
                                            Test_Glyphs.txt
                                            Test_DCEL_Algorithms.cpp)

embed_glyph_geometry(Geometry_Tests
                     DEST "Test_GlyphData.hpp"
                     FONT "Arial"
                     SOURCE "Test_Glyphs.txt")

target_precompile_headers(Geometry_Tests PRIVATE [["Geometry_TestsPCH.hpp"]])
target_include_directories(Geometry_Tests PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}")
target_include_directories(Geometry_Tests PRIVATE "${CMAKE_CURRENT_BINARY_DIR}")