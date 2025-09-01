//! @file Geometry/Test_Angle.cpp
//! @brief The definition of unit tests for the Angle class.
//! @author GiantRobotLemur@na-se.co.uk
//! @date 2023-2025
//! @copyright This file is part of the Silver (Ag) project which is released
//! under LGPL 3 license. See LICENSE file at the repository root or go to
//! https://github.com/GiantRobotLemur/Ag for full license details.
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Header File Includes
////////////////////////////////////////////////////////////////////////////////
#include <gtest/gtest.h>

#include "Ag/GTest_Core.hpp"
#include "Ag/Geometry/Angle.hpp"

#include "GtestHelpers.hpp"

namespace Ag {
namespace Geom {

namespace {
////////////////////////////////////////////////////////////////////////////////
// Local Data Types
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Unit Tests
////////////////////////////////////////////////////////////////////////////////
GTEST_TEST(Angle, DefaultConstruct)
{
    Angle specimen;

    EXPECT_EQ(specimen.toRadians(), 0.0);
    EXPECT_EQ(specimen.toDegrees(), 0.0);

    EXPECT_EQ(specimen, Angle(0.0));
}

GTEST_TEST(Angle, Plus90Degrees)
{
    NumericDomain degrees(-180.0, 180.0);
    Angle specimen = Angle::fromDegrees(90.0);
    double radTol = Angle::Domain.getTolerance() * 2;
    double degTol = degrees.getTolerance() * 2;

    EXPECT_NEAREQ(specimen.toDegrees(), 90, degTol);

    Angle delta(specimen.getOffsetTo(Angle::fromDegrees(180)));

    EXPECT_NEAREQ(specimen.toDegrees(), 90, degTol);

    delta = specimen.getOffsetTo(Angle(Angle::Pi + radTol));

    EXPECT_NEAREQ(delta.toDegrees(), 90, degTol);
}

GTEST_TEST(Angle, ConvertLikeToLike)
{
    Angle specimen = Angle::fromDegrees(10);
    AngleOrientation defaultOrientation;
    AngleOrientation lhClockwiseFromY(Orientation::Clockwise,
                                      AngleAnchor::PositiveYAxis);

    EXPECT_EQ(defaultOrientation, AngleOrientation());
    EXPECT_NE(defaultOrientation, lhClockwiseFromY);
    EXPECT_EQ(lhClockwiseFromY, lhClockwiseFromY);

    Angle result = convertOrientation(defaultOrientation, defaultOrientation, specimen);

    EXPECT_EQ(result, specimen);

    result = convertOrientation(lhClockwiseFromY, lhClockwiseFromY, specimen);

    EXPECT_EQ(result, specimen);
}

GTEST_TEST(Angle, ConvertBetweenCWAndCCW)
{
    Angle specimen1 = Angle::fromDegrees(10);
    Angle specimen2 = Angle::fromDegrees(100);

    AngleOrientation CwFromX(Orientation::Clockwise,
                               AngleAnchor::PositiveXAxis);

    AngleOrientation CcwFromX(Orientation::CounterClockwise,
                              AngleAnchor::PositiveXAxis);

    ASSERT_NE(CwFromX, CcwFromX);

    Angle result1 = convertOrientation(CwFromX, CcwFromX, specimen1);
    EXPECT_EQ(result1, Angle::fromDegrees(-10));

    result1 = convertOrientation(CcwFromX, CwFromX, specimen1);
    EXPECT_EQ(result1, Angle::fromDegrees(-10));

    Angle result2 = convertOrientation(CwFromX, CcwFromX, specimen2);
    EXPECT_EQ(result2, Angle::fromDegrees(-100));

    result2 = convertOrientation(CcwFromX, CwFromX, specimen2);
    EXPECT_EQ(result2, Angle::fromDegrees(-100));
}

GTEST_TEST(Angle, ConvertBetweenAnchorXAndY)
{
    Angle specimen1 = Angle::fromDegrees(10);
    Angle specimen2 = Angle::fromDegrees(135);

    AngleOrientation CwFromX(Orientation::Clockwise,
                             AngleAnchor::PositiveXAxis);

    AngleOrientation CwFromY(Orientation::Clockwise,
                             AngleAnchor::PositiveYAxis);

    AngleOrientation CcwFromX(Orientation::CounterClockwise,
                             AngleAnchor::PositiveXAxis);

    AngleOrientation CcwFromY(Orientation::CounterClockwise,
                              AngleAnchor::PositiveYAxis);

    ASSERT_NE(CwFromX, CwFromY);

    Angle result1 = convertOrientation(CwFromX, CwFromY, specimen1);
    EXPECT_EQ(result1, Angle::fromDegrees(100));

    result1 = convertOrientation(CwFromY, CwFromX, specimen1);
    EXPECT_EQ(result1, Angle::fromDegrees(-80));

    Angle result2 = convertOrientation(CwFromX, CwFromY, specimen2);
    EXPECT_EQ(result2, Angle::fromDegrees(225));

    result2 = convertOrientation(CwFromY, CwFromX, specimen2);
    EXPECT_EQ(result2, Angle::fromDegrees(45));


    ASSERT_NE(CcwFromX, CcwFromY);

    result1 = convertOrientation(CcwFromX, CcwFromY, specimen1);
    EXPECT_EQ(result1, Angle::fromDegrees(-80));

    result1 = convertOrientation(CcwFromY, CcwFromX, specimen1);
    EXPECT_EQ(result1, Angle::fromDegrees(100));

    result2 = convertOrientation(CcwFromX, CcwFromY, specimen2);
    EXPECT_EQ(result2, Angle::fromDegrees(45));

    result2 = convertOrientation(CcwFromY, CcwFromX, specimen2);
    EXPECT_EQ(result2, Angle::fromDegrees(225));
}

GTEST_TEST(Angle, ConvertBetweenAnchorAndOrient)
{
    Angle specimen1 = Angle::fromDegrees(10);
    Angle specimen2 = Angle::fromDegrees(135);

    AngleOrientation CwFromX(Orientation::Clockwise,
                             AngleAnchor::PositiveXAxis);

    AngleOrientation CcwFromX(Orientation::CounterClockwise,
                              AngleAnchor::PositiveXAxis);

    AngleOrientation CwFromY(Orientation::Clockwise,
                             AngleAnchor::PositiveYAxis);

    AngleOrientation CcwFromY(Orientation::CounterClockwise,
                              AngleAnchor::PositiveYAxis);

    ASSERT_NE(CwFromX, CcwFromY);

    Angle result1 = convertOrientation(CwFromX, CcwFromY, specimen1);
    EXPECT_EQ(result1, Angle::fromDegrees(-100));

    result1 = convertOrientation(CcwFromY, CwFromX, specimen1);
    EXPECT_EQ(result1, Angle::fromDegrees(-100));

    Angle result2 = convertOrientation(CwFromX, CcwFromY, specimen2);
    EXPECT_EQ(result2, Angle::fromDegrees(-225));

    result2 = convertOrientation(CcwFromY, CwFromX, specimen2);
    EXPECT_EQ(result2, Angle::fromDegrees(-225));

    ASSERT_NE(CcwFromX, CwFromY);

    result1 = convertOrientation(CcwFromX, CwFromY, specimen1);
    EXPECT_EQ(result1, Angle::fromDegrees(80));

    result1 = convertOrientation(CwFromY, CcwFromX, specimen1);
    EXPECT_EQ(result1, Angle::fromDegrees(80));

    result2 = convertOrientation(CcwFromX, CwFromY, specimen2);
    EXPECT_EQ(result2, Angle::fromDegrees(-45));

    result2 = convertOrientation(CwFromY, CcwFromX, specimen2);
    EXPECT_EQ(result2, Angle::fromDegrees(-45));
}

GTEST_TEST(Angle, GetOffsetAngle)
{
    Angle xAxis(0.0);

    EXPECT_NEAR(xAxis.getOffsetTo(Angle::fromDegrees(90)), Angle::Pi_2,
                Angle::Domain.getTolerance());

    EXPECT_NEAR(Angle::fromDegrees(179.0).getOffsetTo(Angle::fromDegrees(-179)),
                Angle::fromDegrees(2.0).toRadians(),
                Angle::Domain.getTolerance());

    EXPECT_NEAR(Angle::fromDegrees(-179.0).getOffsetTo(Angle::fromDegrees(179)),
                Angle::fromDegrees(-2.0).toRadians(),
                Angle::Domain.getTolerance());

}

} // Anonymous

}} // namespace Ag::Geom
////////////////////////////////////////////////////////////////////////////////

