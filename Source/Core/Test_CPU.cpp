//! @file Core/Test_CPU.cpp
//! @brief The definition of unit tests for CPU detection.
//! @author GiantRobotLemur@na-se.co.uk
//! @date 2025-2026
//! @copyright This file is part of the Silver (Ag) project which is released
//! under LGPL 3 license. See LICENSE file at the repository root or go to
//! https://github.com/GiantRobotLemur/Ag for full license details.
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Header File Includes
////////////////////////////////////////////////////////////////////////////////
#include <gtest/gtest.h>

#include "Ag/Core/Configuration.hpp"
#include "Ag/Core/CPU.hpp"

namespace Ag {

namespace {

////////////////////////////////////////////////////////////////////////////////
// Unit Tests
////////////////////////////////////////////////////////////////////////////////
GTEST_TEST(CPU, GetX86_64ArchVersion)
{
    int version = getX86_64ArchVersion();

#if defined(_MSC_VER) && defined(_M_AMD64)
    EXPECT_GE(version, 1);
#else
    EXPECT_EQ(version, 0);
#endif
}

GTEST_TEST(CPU, BigEndian)
{
#ifdef IS_BIG_ENDIAN
    constexpr bool CompileTime_IsBigEndian = true;
#else
    constexpr bool CompileTime_IsBigEndian = false;
#endif

    uint16_t value = 0x01;
    uint8_cptr_t bytes = reinterpret_cast<uint8_cptr_t>(&value);

    bool Runtime_IsBigEndian = (*bytes == 0);

    EXPECT_EQ(CompileTime_IsBigEndian, Runtime_IsBigEndian);
}

GTEST_TEST(CPU, LitteEndian)
{
#ifdef IS_LITTLE_ENDIAN
    constexpr bool CompileTime_IsLittleEndian = true;
#else
    constexpr bool CompileTime_IsLittleEndian = false;
#endif

    uint16_t value = 0x01;
    uint8_cptr_t bytes = reinterpret_cast<uint8_cptr_t>(&value);

    bool Runtime_IsLittleEndian = (*bytes == 1);

    EXPECT_EQ(CompileTime_IsLittleEndian, Runtime_IsLittleEndian);
}

} // Anonymous namespace

} // namespace Ag
////////////////////////////////////////////////////////////////////////////////

