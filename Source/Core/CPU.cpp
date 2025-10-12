//! @file Core/CPU.cpp
//! @brief The definition of functions to verify the CPU architecture and
//! features available to the application.
//! @author GiantRobotLemur@na-se.co.uk
//! @date 2025
//! @copyright This file is part of the Silver (Ag) project which is released
//! under LGPL 3 license. See LICENSE file at the repository root or go to
//! https://github.com/GiantRobotLemur/Ag for full license details.
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Header File Includes
////////////////////////////////////////////////////////////////////////////////
#include <algorithm>

#ifdef _MSC_VER
#include <intrin.h>
#else
#error CPU detection code needs a g++ alternative.
#endif

#include "Ag/Core/CPU.hpp"

namespace Ag {

////////////////////////////////////////////////////////////////////////////////
// Global Function Definitions
////////////////////////////////////////////////////////////////////////////////
//! @brief Detects what version, if any, of the x86-64 architecture the current
//! CPU implements.
//! @return An integer version giving the architecture version, or 0 if not
//! running on an x64 processor.
//! @remarks See https://en.wikipedia.org/wiki/X86-64#Microarchitecture_levels
int getX86_64ArchVersion()
{
    int version = 0;

#ifdef _M_AMD64
#ifdef _MSC_VER
    // MSVC-specific x64 feature detection code.
    int featureInfo[4];

    // Determine the highest extended feature register available.
    __cpuid(featureInfo, 1);

    // V1 = { CMOV, CX8, FPU, FXSR, MMX, OSFXSR, SCE, SSE, SSE2 }
    // https://en.wikipedia.org/wiki/CPUID#EAX=1:_Processor_Info_and_Feature_Bits
    constexpr int EDX_FPU  = 0x0000001;
    constexpr int EDX_CX8  = 0x0000100;
    constexpr int EDX_CMOV = 0x0008000;
    constexpr int EDX_MMX  = 0x0800000;
    constexpr int EDX_SSE  = 0x2000000;
    constexpr int EDX_SSE2 = 0x4000000;

    constexpr int V1_EDX = EDX_CMOV | EDX_CX8 | EDX_FPU |
                           EDX_MMX | EDX_SSE | EDX_SSE2;

    if ((featureInfo[3] & V1_EDX) == V1_EDX)
    {
        ++version;

        // V2 = { CMPXCHG16B, LAHF-SAHF, POPCNT, SSE3, SSE4.1, SSE4.2, SSSE3 }
        constexpr int ECX_SSE3       = 0x000001;
        constexpr int ECX_SSSE3      = 0x000200;
        constexpr int ECX_CMPXCHG16B = 0x002000;
        constexpr int ECX_SSE4_1     = 0x080000;
        constexpr int ECX_SSE4_2     = 0x100000;
        constexpr int ECX_POPCNT     = 0x800000;

        const int V2_ECX = ECX_SSE3 | ECX_SSSE3 | ECX_SSE4_1 |
                           ECX_SSE4_2 | ECX_POPCNT | ECX_CMPXCHG16B;

        if ((featureInfo[2] & V2_ECX) == V2_ECX)
        {
            ++version;
            int extendedInfo[4];

            __cpuidex(extendedInfo, 7, 0);

            // V3 = { AVX, AVX2, BMI1, BMI2, F16C, FMA, LZCNT, MOVBE, OSXSAVE }
            constexpr int ECX_FMA   = 0x00001000;
            constexpr int ECX_MOVBE = 0x00400000;
            constexpr int ECX_AVX   = 0x10000000;
            constexpr int ECX_F16C  = 0x20000000;
            constexpr int EBX_AVX2 = 0x020;
            constexpr int EBX_BMI1 = 0x008;
            constexpr int EBX_BMI2 = 0x100;
            //constexpr int LZCNT = 0;

            constexpr int V3_ECX = ECX_AVX | ECX_F16C | ECX_FMA | ECX_MOVBE;
            constexpr int V3_EBX = EBX_AVX2 | EBX_BMI1 | EBX_BMI2;

            if (((featureInfo[2] & V3_ECX) == V3_ECX) &&
                ((extendedInfo[1] & V3_EBX) == V3_EBX))
            {
                ++version;

                // V4 = { AVX512F, AVX512BW, AVX512CD, AVX512DQ, AVX512VL }
                constexpr int EBX_AVX512F  = 0x00010000;
                constexpr int EBX_AVX512DQ = 0x00020000;
                constexpr int EBX_AVX512CD = 0x10000000;
                constexpr int EBX_AVX512BW = 0x40000000;
                constexpr int EBX_AVX512VL = 0x80000000;

                constexpr int EBX_V4 = EBX_AVX512F | EBX_AVX512DQ | EBX_AVX512CD |
                                       EBX_AVX512BW | EBX_AVX512VL;

                if ((extendedInfo[1] & EBX_V4) == EBX_V4)
                {
                    ++version;
                }
            }
        }
    }

    return version;
}

#endif
#endif

} // namespace Ag
////////////////////////////////////////////////////////////////////////////////

