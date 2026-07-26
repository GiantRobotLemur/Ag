//! @file TestTools.hpp
//! @brief The declaration of tools shared between various IO unit tests.
//! @author GiantRobotLemur@na-se.co.uk
//! @date 2026
//! @copyright This file is part of the Silver (Ag) project which is released
//! under LGPL 3 license. See LICENSE file at the repository root or go to
//! https://github.com/GiantRobotLemur/Ag for full license details.
////////////////////////////////////////////////////////////////////////////////

#ifndef HEADER_IO_TEST_TOOLS_HPP_
#define HEADER_IO_TEST_TOOLS_HPP_

////////////////////////////////////////////////////////////////////////////////
// Dependent Header Files
////////////////////////////////////////////////////////////////////////////////
#include <type_traits>
#include <random>

#include <Ag/Core.hpp>

namespace Ag {
namespace IO {

////////////////////////////////////////////////////////////////////////////////
// Class Declarations
////////////////////////////////////////////////////////////////////////////////
//! @brief An object which can produce random bytes.
class RandomByteGenerator
{
public:
    using Engine = std::ranlux48;
    using RootScalar = Engine::result_type;
private:
    // Allow the state to be copied between instances so that it persists
    // when passed to STL functions like std::generate().
    struct InnerState : public std::enable_shared_from_this<InnerState>
    {
        Engine _engine;
        RootScalar _seed;
        RootScalar _latest;
        uint8_t _bytesUsed;

        InnerState(RootScalar seed);
        void reset();
        uint8_t generate();
        void skip(size_t count);
    };

    std::shared_ptr<InnerState> _state;

public:
    RandomByteGenerator(RootScalar seed);

    void reset();
    void skip(size_t count);
    uint8_t operator()();

    template<typename T, std::enable_if_t<std::is_integral_v<T>, bool> = true>
    T nextValue()
    {
        using Limits = std::numeric_limits<T>;
        T value = Limits::lowest();
        size_t count = sizeof(T);

        for (size_t i = 0; i < count; ++i)
        {
            value = (value << 8) | static_cast<T>(_state->generate());
        }

        return value;
    }

    template<typename T, std::enable_if_t<std::is_floating_point_v<T>, bool> = true>
    T nextValue()
    {
        using Limits = std::numeric_limits<T>;
        constexpr T Zero = static_cast<T>(0);
        constexpr T Two = static_cast<T>(2);

        // Generate a random number of steps.
        uint8_t opCount = _state->generate() >> 4;
        T value;

        do
        {
            // Generate a random start point.
            value = static_cast<T>(static_cast<int8_t>(_state->generate()));

            for (uint8_t i = 0; i < opCount; ++i)
            {
                // Generate a new value at each step to apply a random operator
                // based on a random value.
                uint8_t next = _state->generate();

                T nextValue = static_cast<T>(static_cast<int8_t>(next >> 3));

                switch (next & 0x07)
                {
                case 0:
                    value += nextValue;
                    break;

                case 1:
                    value -= nextValue;
                    break;

                case 2:
                    value *= nextValue;
                    break;

                case 3:
                    // Prevent division by zero.
                    if (std::abs(nextValue) > Limits::lowest())
                        value /= nextValue;
                    break;

                case 4:
                    if (std::abs(nextValue) > Limits::lowest())
                        value = std::fmod(value, static_cast<T>(nextValue));
                    break;

                case 5:
                    value = std::pow(value, nextValue);
                    break;

                case 6:
                    value = (value + nextValue) / Two;
                    break;

                case 7:
                    value = (value - nextValue) * 2;
                    break;
                }
            }

            // Continue generating values until we get a valid one.
        } while (std::isnan(value));

        // Filter out values of -0.0 as they cause problems with comparisons.
        return (value == Zero) ? Zero : value;
    }

    String nextString(size_t preferredSize = 0);
};

struct FileDeleter
{
private:
    Fs::Entry _fileToDelete;
public:
    FileDeleter(const Fs::Path &fileToDelete);
    ~FileDeleter();

    const Fs::Path &getPath() const;
};

////////////////////////////////////////////////////////////////////////////////
// Function Declarations
////////////////////////////////////////////////////////////////////////////////
size_t writeRandomBytes(RandomByteGenerator &generator,
                        IStream *stream, size_t byteCount);
ByteBlock fillRandomData(RandomByteGenerator &generator, size_t byteCount);
Fs::Path generateTempFileName();
void createRandomDataFile(RandomByteGenerator &entropySource,
                          const Fs::Path &fileName, size_t fileSize);

}} // namespace Ag::IO

#endif // Header guard
////////////////////////////////////////////////////////////////////////////////
