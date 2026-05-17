//! @file Text/Test_CharacterAnalyser.cpp
//! @brief The definition of unit tests for the CharacterAnalyser class — the
//! moving-window code-point reader with commit/rollback semantics.
//! @author GiantRobotLemur@na-se.co.uk and Claude Opus 4.7.
//! @date 2026
//! @copyright This file is part of the Silver (Ag) project which is released
//! under LGPL 3 license. See LICENSE file at the repository root or go to
//! https://github.com/GiantRobotLemur/Ag for full license details.
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Header File Includes
////////////////////////////////////////////////////////////////////////////////
#include <gtest/gtest.h>

#include "Ag/Text/CharacterAnalyser.hpp"
#include "Ag/Text/CharacterSource.hpp"

namespace Ag {
namespace Text {

namespace {

////////////////////////////////////////////////////////////////////////////////
// Local Data — sample text "A \u00E9 \u20AC \U0001D11E"
//   Code points: U+0041 U+0020 U+00E9 U+0020 U+20AC U+0020 U+1D11E
////////////////////////////////////////////////////////////////////////////////
constexpr char32_t kSampleUtf32[] = {
    U'A', U' ', U'\u00E9', U' ', U'\u20AC', U' ', U'\U0001D11E'
};

constexpr size_t kSampleCodePointCount = std::size(kSampleUtf32);

//! @brief Builds a long sequence ("ABABAB…") long enough to span the
//! analyser's internal buffer multiple times.
std::vector<char32_t> makeLongAlphabet(size_t count)
{
    std::vector<char32_t> v;
    v.reserve(count);
    for (size_t i = 0; i < count; ++i)
        v.push_back(U'A' + (i % 26));
    return v;
}

////////////////////////////////////////////////////////////////////////////////
// CharacterAnalyser — construction & accessors
////////////////////////////////////////////////////////////////////////////////
GTEST_TEST(CharacterAnalyser, NewAnalyserHasZeroRollbackLimit)
{
    String text(kSampleUtf32, kSampleCodePointCount);
    StringCharacterSource src(text);
    CharacterAnalyser analyser(&src);

    EXPECT_EQ(analyser.getRollbackLimit(), 0u);
}

GTEST_TEST(CharacterAnalyser, EmptySourceReturnsNoCharacters)
{
    String empty;
    StringCharacterSource src(empty);
    CharacterAnalyser analyser(&src);

    char32_t next = 0xDEADBEEF;
    EXPECT_FALSE(analyser.tryGetNextCharacter(next));
    EXPECT_EQ(next, U'\0');
    EXPECT_EQ(analyser.getRollbackLimit(), 0u);
}

////////////////////////////////////////////////////////////////////////////////
// CharacterAnalyser — reading & rollback limit
////////////////////////////////////////////////////////////////////////////////
GTEST_TEST(CharacterAnalyser, ReadsCharactersInOrder)
{
    String text(kSampleUtf32, kSampleCodePointCount);
    StringCharacterSource src(text);
    CharacterAnalyser analyser(&src);

    for (size_t i = 0; i < kSampleCodePointCount; ++i)
    {
        char32_t next = 0;
        ASSERT_TRUE(analyser.tryGetNextCharacter(next))
            << "stalled at index " << i;
        EXPECT_EQ(next, kSampleUtf32[i]) << "wrong char at index " << i;
    }

    char32_t trailing = 0;
    EXPECT_FALSE(analyser.tryGetNextCharacter(trailing));
}

GTEST_TEST(CharacterAnalyser, SupplementaryPlaneCharIsOneCodePoint)
{
    // U+1D11E (musical G clef) is a surrogate pair in UTF-16, but the analyser
    // walks UTF-32 code points so it must appear as exactly one character.
    constexpr char32_t single[] = { U'\U0001D11E' };
    String text(single, std::size(single));
    StringCharacterSource src(text);
    CharacterAnalyser analyser(&src);

    char32_t next = 0;
    ASSERT_TRUE(analyser.tryGetNextCharacter(next));
    EXPECT_EQ(next, U'\U0001D11E');

    char32_t trailing = 0;
    EXPECT_FALSE(analyser.tryGetNextCharacter(trailing));
}

GTEST_TEST(CharacterAnalyser, RollbackLimitGrowsWithUncommittedReads)
{
    String text(kSampleUtf32, kSampleCodePointCount);
    StringCharacterSource src(text);
    CharacterAnalyser analyser(&src);

    char32_t next = 0;
    for (size_t i = 0; i < 3; ++i)
    {
        ASSERT_TRUE(analyser.tryGetNextCharacter(next));
        EXPECT_EQ(analyser.getRollbackLimit(), i + 1);
    }
}

GTEST_TEST(CharacterAnalyser, CommitClearsRollbackLimit)
{
    String text(kSampleUtf32, kSampleCodePointCount);
    StringCharacterSource src(text);
    CharacterAnalyser analyser(&src);

    char32_t next = 0;
    ASSERT_TRUE(analyser.tryGetNextCharacter(next));
    ASSERT_TRUE(analyser.tryGetNextCharacter(next));
    EXPECT_EQ(analyser.getRollbackLimit(), 2u);

    analyser.commit();
    EXPECT_EQ(analyser.getRollbackLimit(), 0u);

    // Reading must continue from the position established before the commit.
    ASSERT_TRUE(analyser.tryGetNextCharacter(next));
    EXPECT_EQ(next, kSampleUtf32[2]);
}

////////////////////////////////////////////////////////////////////////////////
// CharacterAnalyser — rollback semantics
////////////////////////////////////////////////////////////////////////////////
GTEST_TEST(CharacterAnalyser, RollbackRestoresPriorPosition)
{
    String text(kSampleUtf32, kSampleCodePointCount);
    StringCharacterSource src(text);
    CharacterAnalyser analyser(&src);

    char32_t next = 0;
    ASSERT_TRUE(analyser.tryGetNextCharacter(next));   // kSampleUtf32[0]
    ASSERT_TRUE(analyser.tryGetNextCharacter(next));   // kSampleUtf32[1]
    ASSERT_TRUE(analyser.tryGetNextCharacter(next));   // kSampleUtf32[2]

    analyser.rollback(2);
    EXPECT_EQ(analyser.getRollbackLimit(), 1u);

    ASSERT_TRUE(analyser.tryGetNextCharacter(next));
    EXPECT_EQ(next, kSampleUtf32[1]);
    ASSERT_TRUE(analyser.tryGetNextCharacter(next));
    EXPECT_EQ(next, kSampleUtf32[2]);
}

GTEST_TEST(CharacterAnalyser, RollbackZeroIsNoOp)
{
    String text(kSampleUtf32, kSampleCodePointCount);
    StringCharacterSource src(text);
    CharacterAnalyser analyser(&src);

    char32_t next = 0;
    ASSERT_TRUE(analyser.tryGetNextCharacter(next));
    ASSERT_TRUE(analyser.tryGetNextCharacter(next));
    size_t before = analyser.getRollbackLimit();

    analyser.rollback(0);
    EXPECT_EQ(analyser.getRollbackLimit(), before);

    ASSERT_TRUE(analyser.tryGetNextCharacter(next));
    EXPECT_EQ(next, kSampleUtf32[2]);
}

GTEST_TEST(CharacterAnalyser, RollbackBeyondLimitThrows)
{
    String text(kSampleUtf32, kSampleCodePointCount);
    StringCharacterSource src(text);
    CharacterAnalyser analyser(&src);

    char32_t next = 0;
    ASSERT_TRUE(analyser.tryGetNextCharacter(next));
    EXPECT_EQ(analyser.getRollbackLimit(), 1u);

    EXPECT_THROW(analyser.rollback(2), OperationException);
}

GTEST_TEST(CharacterAnalyser, RollbackPastCommitThrows)
{
    String text(kSampleUtf32, kSampleCodePointCount);
    StringCharacterSource src(text);
    CharacterAnalyser analyser(&src);

    char32_t next = 0;
    ASSERT_TRUE(analyser.tryGetNextCharacter(next));   // [0]
    ASSERT_TRUE(analyser.tryGetNextCharacter(next));   // [1]
    analyser.commit();                                 // commit [0..1]
    ASSERT_TRUE(analyser.tryGetNextCharacter(next));   // [2]

    EXPECT_EQ(analyser.getRollbackLimit(), 1u);
    EXPECT_THROW(analyser.rollback(2), OperationException);
}

////////////////////////////////////////////////////////////////////////////////
// CharacterAnalyser — tryEnsureNextCharacter
////////////////////////////////////////////////////////////////////////////////
GTEST_TEST(CharacterAnalyser, EnsureNextMatchesAdvances)
{
    String text(kSampleUtf32, kSampleCodePointCount);
    StringCharacterSource src(text);
    CharacterAnalyser analyser(&src);

    EXPECT_TRUE(analyser.tryEnsureNextCharacter(U'A'));
    EXPECT_EQ(analyser.getRollbackLimit(), 1u);

    char32_t next = 0;
    ASSERT_TRUE(analyser.tryGetNextCharacter(next));
    EXPECT_EQ(next, kSampleUtf32[1]);   // the space after 'A'
}

GTEST_TEST(CharacterAnalyser, EnsureNextMismatchDoesNotAdvance)
{
    String text(kSampleUtf32, kSampleCodePointCount);
    StringCharacterSource src(text);
    CharacterAnalyser analyser(&src);

    EXPECT_FALSE(analyser.tryEnsureNextCharacter(U'Z'));
    EXPECT_EQ(analyser.getRollbackLimit(), 0u);

    // The position is unchanged — the next read still yields 'A'.
    char32_t next = 0;
    ASSERT_TRUE(analyser.tryGetNextCharacter(next));
    EXPECT_EQ(next, U'A');
}

GTEST_TEST(CharacterAnalyser, EnsureNextAtEofReturnsFalse)
{
    String empty;
    StringCharacterSource src(empty);
    CharacterAnalyser analyser(&src);

    EXPECT_FALSE(analyser.tryEnsureNextCharacter(U'X'));
    EXPECT_EQ(analyser.getRollbackLimit(), 0u);
}

GTEST_TEST(CharacterAnalyser, EnsureNextMatchesSupplementaryCharacter)
{
    constexpr char32_t single[] = { U'\U0001D11E' };
    String text(single, std::size(single));
    StringCharacterSource src(text);
    CharacterAnalyser analyser(&src);

    EXPECT_TRUE(analyser.tryEnsureNextCharacter(U'\U0001D11E'));
    EXPECT_EQ(analyser.getRollbackLimit(), 1u);
}

////////////////////////////////////////////////////////////////////////////////
// CharacterAnalyser — buffer refill across long input
////////////////////////////////////////////////////////////////////////////////
GTEST_TEST(CharacterAnalyser, ReadsAcrossBufferRefill)
{
    // Internal buffer minimum is 256 chars; use ~3x that to force several
    // refill cycles.
    constexpr size_t kLength = 800;
    auto long_ = makeLongAlphabet(kLength);

    String text(long_.data(), long_.size());
    StringCharacterSource src(text);
    CharacterAnalyser analyser(&src);

    analyser.setBufferSize(256);

    for (size_t i = 0; i < kLength; ++i)
    {
        char32_t next = 0;
        ASSERT_TRUE(analyser.tryGetNextCharacter(next))
            << "stalled at index " << i;
        EXPECT_EQ(next, long_[i]) << "wrong char at index " << i;

        // Commit periodically so the rollback buffer doesn't grow without
        // bound; this also exercises the "erase committed, refill" branch.
        if ((i % 100) == 99)
            analyser.commit();
    }

    char32_t trailing = 0;
    EXPECT_FALSE(analyser.tryGetNextCharacter(trailing));
}

GTEST_TEST(CharacterAnalyser, RollbackAfterRefillBoundary)
{
    // Use a string long enough that the analyser will have refilled at least
    // once. After a commit + further reads, rollback within the remaining
    // uncommitted window must still hand back the right characters.
    constexpr size_t kLength = 400;
    auto long_ = makeLongAlphabet(kLength);

    String text(long_.data(), long_.size());
    StringCharacterSource src(text);
    CharacterAnalyser analyser(&src);

    // Consume 300 chars, committing the first 250 so the rollback window
    // tracks 50 uncommitted chars across an internal refill.
    analyser.setBufferSize(300);

    char32_t next = 0;
    for (size_t i = 0; i < 250; ++i)
        ASSERT_TRUE(analyser.tryGetNextCharacter(next));
    analyser.commit();

    for (size_t i = 250; i < 300; ++i)
        ASSERT_TRUE(analyser.tryGetNextCharacter(next));

    EXPECT_EQ(analyser.getRollbackLimit(), 50u);

    analyser.rollback(50);
    EXPECT_EQ(analyser.getRollbackLimit(), 0u);

    // After rollback the next read must be the first uncommitted char (index 250).
    ASSERT_TRUE(analyser.tryGetNextCharacter(next));
    EXPECT_EQ(next, long_[250]);
}

} // Anonymous namespace

}} // namespace Ag::Text
////////////////////////////////////////////////////////////////////////////////
