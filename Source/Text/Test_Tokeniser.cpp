//! @file Text/Test_Tokeniser.cpp
//! @brief The definition of unit tests for the TokenSource template class and
//! the classes which support it.
//! @author GiantRobotLemur@na-se.co.uk
//! @date 2026
//! @copyright This file is part of the Silver (Ag) project which is released
//! under LGPL 3 license. See LICENSE file at the repository root or go to
//! https://github.com/GiantRobotLemur/Ag for full license details.
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Header File Includes
////////////////////////////////////////////////////////////////////////////////
#include <gtest/gtest.h>

#include "Ag/GTest_Core.hpp"
#include "Ag/Text/Tokeniser.hpp"
#include "Test_ExampleParser.hpp"

namespace Ag {
namespace Text {
namespace Test {

namespace {

////////////////////////////////////////////////////////////////////////////////
// Unit Tests
////////////////////////////////////////////////////////////////////////////////
GTEST_TEST(TokenStream, NoTokensFromEmptyStream)
{
    ICharacterSourceUPtr sourceStream = std::make_unique<StringCharacterSource>(String::Empty);
    ExprInput::ITokeniserCPtr initialTokeniser = &StatementTokeniser::Instance;
    ExprInput::TokenStream specimen(initialTokeniser, "(anon)",
                                    std::move(sourceStream));

    ExprInput::Token next;

    EXPECT_FALSE(specimen.tryGetNextToken(next));
}

GTEST_TEST(TokenStream, NoTokensFromWhiteSpaceStream)
{
    String source = "   \t\t\n\t  \r\n\t  ";
    ICharacterSourceUPtr sourceStream = std::make_unique<StringCharacterSource>(source);
    ExprInput::ITokeniserCPtr initialTokeniser = &StatementTokeniser::Instance;
    ExprInput::TokenStream specimen(initialTokeniser, "(anon)",
                                    std::move(sourceStream));

    ExprInput::Token next;

    EXPECT_FALSE(specimen.tryGetNextToken(next));
}

GTEST_TEST(TokenStream, LiteralTokenFromStream)
{
    String source = "\t 12345\n  ";
    ICharacterSourceUPtr sourceStream = std::make_unique<StringCharacterSource>(source);
    ExprInput::ITokeniserCPtr initialTokeniser = &ExpressionTokeniser::Instance;
    ExprInput::TokenStream specimen(initialTokeniser, "(anon)",
                                    std::move(sourceStream));

    ExprInput::Token next;

    ASSERT_TRUE(specimen.tryGetNextToken(next));
    EXPECT_EQ(next.getClass(), ExprTokenClass::IntegerLiteral);
    EXPECT_EQ(next.getLocation().getLine(), 1);
    EXPECT_EQ(next.getLocation().getColumn(), 3);
    EXPECT_STRINGEQC(next.getValue(), "12345");
}

GTEST_TEST(TokenStream, SymbolTokenOnNewLine)
{
    String source = "\t  \n   \r\n   HelloWorld\n  ";
    ICharacterSourceUPtr sourceStream = std::make_unique<StringCharacterSource>(source);
    ExprInput::ITokeniserCPtr initialTokeniser = &ExpressionTokeniser::Instance;
    ExprInput::TokenStream specimen(initialTokeniser, "(anon)",
                                    std::move(sourceStream));

    ExprInput::Token next;

    ASSERT_TRUE(specimen.tryGetNextToken(next));
    EXPECT_EQ(next.getClass(), ExprTokenClass::Symbol);
    EXPECT_EQ(next.getLocation().getLine(), 3);
    EXPECT_EQ(next.getLocation().getColumn(), 4);
    EXPECT_STRINGEQC(next.getValue(), "HelloWorld");
}



GTEST_TEST(TokenStream, SingleCharacterTokens)
{
    String source = "\t  ;\n +  \r\n  * \n /";
    ICharacterSourceUPtr sourceStream = std::make_unique<StringCharacterSource>(source);
    ExprInput::ITokeniserCPtr initialTokeniser = &ExpressionTokeniser::Instance;
    ExprInput::TokenStream specimen(initialTokeniser, "(anon)",
                                    std::move(sourceStream));

    ExprInput::Token next;

    ASSERT_TRUE(specimen.tryGetNextToken(next));
    EXPECT_EQ(next.getClass(), ExprTokenClass::EndOfStatement);
    EXPECT_EQ(next.getLocation().getLine(), 1);
    EXPECT_EQ(next.getLocation().getColumn(), 4);
    EXPECT_TRUE(next.getValue().isEmpty());

    ASSERT_TRUE(specimen.tryGetNextToken(next));
    EXPECT_EQ(next.getClass(), ExprTokenClass::OperatorPlus);
    EXPECT_EQ(next.getLocation().getLine(), 2);
    EXPECT_EQ(next.getLocation().getColumn(), 2);
    EXPECT_TRUE(next.getValue().isEmpty());

    ASSERT_TRUE(specimen.tryGetNextToken(next));
    EXPECT_EQ(next.getClass(), ExprTokenClass::OperatorMultiply);
    EXPECT_EQ(next.getLocation().getLine(), 3);
    EXPECT_EQ(next.getLocation().getColumn(), 3);
    EXPECT_TRUE(next.getValue().isEmpty());

    ASSERT_TRUE(specimen.tryGetNextToken(next));
    EXPECT_EQ(next.getClass(), ExprTokenClass::OperatorDivide);
    EXPECT_EQ(next.getLocation().getLine(), 4);
    EXPECT_EQ(next.getLocation().getColumn(), 2);
    EXPECT_TRUE(next.getValue().isEmpty());

    specimen.rewind(2);

    ASSERT_TRUE(specimen.tryGetNextToken(next));
    EXPECT_EQ(next.getClass(), ExprTokenClass::OperatorMultiply);
    EXPECT_EQ(next.getLocation().getLine(), 3);
    EXPECT_EQ(next.getLocation().getColumn(), 3);
    EXPECT_TRUE(next.getValue().isEmpty());
}

GTEST_TEST(TokenStream, ConstructorAcceptsInputStream)
{
    // Verify the four-argument constructor (which also takes ownership of an
    // underlying binary stream) functions equivalently when no binary stream
    // is supplied.
    String source = "x";
    ICharacterSourceUPtr sourceStream = std::make_unique<StringCharacterSource>(source);
    IStreamUPtr noStream;
    ExprInput::ITokeniserCPtr initialTokeniser = &ExpressionTokeniser::Instance;
    ExprInput::TokenStream specimen(initialTokeniser, "(anon)",
                                    std::move(sourceStream),
                                    std::move(noStream));

    ExprInput::Token next;

    ASSERT_TRUE(specimen.tryGetNextToken(next));
    EXPECT_EQ(next.getClass(), ExprTokenClass::Symbol);
    EXPECT_STRINGEQC(next.getValue(), "x");
    EXPECT_FALSE(specimen.tryGetNextToken(next));
}

GTEST_TEST(TokenStream, MoveConstructionPreservesPosition)
{
    String source = "alpha beta gamma";
    ICharacterSourceUPtr sourceStream = std::make_unique<StringCharacterSource>(source);
    ExprInput::ITokeniserCPtr initialTokeniser = &ExpressionTokeniser::Instance;
    ExprInput::TokenStream original(initialTokeniser, "(anon)",
                                    std::move(sourceStream));

    ExprInput::Token next;

    ASSERT_TRUE(original.tryGetNextToken(next));
    EXPECT_STRINGEQC(next.getValue(), "alpha");

    // Move-construct from the partially consumed stream.
    ExprInput::TokenStream moved(std::move(original));

    ASSERT_TRUE(moved.tryGetNextToken(next));
    EXPECT_EQ(next.getClass(), ExprTokenClass::Symbol);
    EXPECT_STRINGEQC(next.getValue(), "beta");

    ASSERT_TRUE(moved.tryGetNextToken(next));
    EXPECT_EQ(next.getClass(), ExprTokenClass::Symbol);
    EXPECT_STRINGEQC(next.getValue(), "gamma");

    EXPECT_FALSE(moved.tryGetNextToken(next));
}

GTEST_TEST(TokenStream, LocationCarriesSourceIdentifier)
{
    String source = "value";
    ICharacterSourceUPtr sourceStream = std::make_unique<StringCharacterSource>(source);
    ExprInput::ITokeniserCPtr initialTokeniser = &ExpressionTokeniser::Instance;
    ExprInput::TokenStream specimen(initialTokeniser, "my-source.txt",
                                    std::move(sourceStream));

    ExprInput::Token next;

    ASSERT_TRUE(specimen.tryGetNextToken(next));
    EXPECT_STRINGEQC(next.getLocation().getIdentifier(), "my-source.txt");
}

GTEST_TEST(TokenStream, EndOfStreamRemainsExhausted)
{
    String source = "only";
    ICharacterSourceUPtr sourceStream = std::make_unique<StringCharacterSource>(source);
    ExprInput::ITokeniserCPtr initialTokeniser = &ExpressionTokeniser::Instance;
    ExprInput::TokenStream specimen(initialTokeniser, "(anon)",
                                    std::move(sourceStream));

    ExprInput::Token next;

    ASSERT_TRUE(specimen.tryGetNextToken(next));
    EXPECT_STRINGEQC(next.getValue(), "only");

    // Subsequent reads after exhaustion should consistently return false.
    EXPECT_FALSE(specimen.tryGetNextToken(next));
    EXPECT_FALSE(specimen.tryGetNextToken(next));
    EXPECT_FALSE(specimen.tryGetNextToken(next));
}

GTEST_TEST(TokenStream, RecognisesMixedExpressionTokens)
{
    String source = "result = 1.5 + 'A' - \"hi\";";
    ICharacterSourceUPtr sourceStream = std::make_unique<StringCharacterSource>(source);
    ExprInput::ITokeniserCPtr initialTokeniser = &ExpressionTokeniser::Instance;
    ExprInput::TokenStream specimen(initialTokeniser, "(anon)",
                                    std::move(sourceStream));

    ExprInput::Token next;

    ASSERT_TRUE(specimen.tryGetNextToken(next));
    EXPECT_EQ(next.getClass(), ExprTokenClass::Symbol);
    EXPECT_STRINGEQC(next.getValue(), "result");

    ASSERT_TRUE(specimen.tryGetNextToken(next));
    EXPECT_EQ(next.getClass(), ExprTokenClass::OperatorAssignment);

    // Use the expression tokeniser from here on.
    size_t tokenState = specimen.pushTokeniser(&ExpressionTokeniser::Instance);
    ASSERT_TRUE(specimen.tryGetNextToken(next));
    EXPECT_EQ(next.getClass(), ExprTokenClass::RealLiteral);
    EXPECT_STRINGEQC(next.getValue(), "1.5");

    ASSERT_TRUE(specimen.tryGetNextToken(next));
    EXPECT_EQ(next.getClass(), ExprTokenClass::OperatorPlus);

    ASSERT_TRUE(specimen.tryGetNextToken(next));
    EXPECT_EQ(next.getClass(), ExprTokenClass::CharacterLiteral);
    EXPECT_STRINGEQC(next.getValue(), "A");

    ASSERT_TRUE(specimen.tryGetNextToken(next));
    EXPECT_EQ(next.getClass(), ExprTokenClass::OperatorMinus);

    ASSERT_TRUE(specimen.tryGetNextToken(next));
    EXPECT_EQ(next.getClass(), ExprTokenClass::StringLiteral);
    EXPECT_STRINGEQC(next.getValue(), "hi");

    ASSERT_TRUE(specimen.tryGetNextToken(next));
    EXPECT_EQ(next.getClass(), ExprTokenClass::EndOfStatement);

    // Restore to the statement tokeniser.
    specimen.restoreTokeniser(tokenState);

    EXPECT_FALSE(specimen.tryGetNextToken(next));
}

GTEST_TEST(TokenStream, RecognisesParentheses)
{
    String source = "(a)";
    ICharacterSourceUPtr sourceStream = std::make_unique<StringCharacterSource>(source);
    ExprInput::ITokeniserCPtr initialTokeniser = &ExpressionTokeniser::Instance;
    ExprInput::TokenStream specimen(initialTokeniser, "(anon)",
                                    std::move(sourceStream));

    ExprInput::Token next;

    ASSERT_TRUE(specimen.tryGetNextToken(next));
    EXPECT_EQ(next.getClass(), ExprTokenClass::OpenParenthesis);

    ASSERT_TRUE(specimen.tryGetNextToken(next));
    EXPECT_EQ(next.getClass(), ExprTokenClass::Symbol);
    EXPECT_STRINGEQC(next.getValue(), "a");

    ASSERT_TRUE(specimen.tryGetNextToken(next));
    EXPECT_EQ(next.getClass(), ExprTokenClass::CloseParenthesis);

    EXPECT_FALSE(specimen.tryGetNextToken(next));
}

GTEST_TEST(TokenStream, ProducesErrorTokenForUnterminatedString)
{
    String source = "\"never closed";
    ICharacterSourceUPtr sourceStream = std::make_unique<StringCharacterSource>(source);
    ExprInput::ITokeniserCPtr initialTokeniser = &ExpressionTokeniser::Instance;
    ExprInput::TokenStream specimen(initialTokeniser, "(anon)",
                                    std::move(sourceStream));

    ExprInput::Token next;

    ASSERT_TRUE(specimen.tryGetNextToken(next));
    EXPECT_EQ(next.getClass(), ExprTokenClass::Error);
}

GTEST_TEST(TokenStream, RewindZeroIsNoOp)
{
    String source = "first second";
    ICharacterSourceUPtr sourceStream = std::make_unique<StringCharacterSource>(source);
    ExprInput::ITokeniserCPtr initialTokeniser = &ExpressionTokeniser::Instance;
    ExprInput::TokenStream specimen(initialTokeniser, "(anon)",
                                    std::move(sourceStream));

    ExprInput::Token next;

    ASSERT_TRUE(specimen.tryGetNextToken(next));
    EXPECT_STRINGEQC(next.getValue(), "first");

    EXPECT_NO_THROW(specimen.rewind(0));

    ASSERT_TRUE(specimen.tryGetNextToken(next));
    EXPECT_STRINGEQC(next.getValue(), "second");
}

GTEST_TEST(TokenStream, RewindOnFreshStreamThrowsForPositiveCount)
{
    String source = "anything";
    ICharacterSourceUPtr sourceStream = std::make_unique<StringCharacterSource>(source);
    ExprInput::ITokeniserCPtr initialTokeniser = &ExpressionTokeniser::Instance;
    ExprInput::TokenStream specimen(initialTokeniser, "(anon)",
                                    std::move(sourceStream));

    EXPECT_THROW(specimen.rewind(1), OperationException);
}

GTEST_TEST(TokenStream, RewindBeyondReadCountThrows)
{
    String source = "one two";
    ICharacterSourceUPtr sourceStream = std::make_unique<StringCharacterSource>(source);
    ExprInput::ITokeniserCPtr initialTokeniser = &ExpressionTokeniser::Instance;
    ExprInput::TokenStream specimen(initialTokeniser, "(anon)",
                                    std::move(sourceStream));

    ExprInput::Token next;

    ASSERT_TRUE(specimen.tryGetNextToken(next));
    ASSERT_TRUE(specimen.tryGetNextToken(next));

    EXPECT_THROW(specimen.rewind(3), OperationException);
}

GTEST_TEST(TokenStream, RewindReReadsCachedTokens)
{
    String source = "alpha beta gamma";
    ICharacterSourceUPtr sourceStream = std::make_unique<StringCharacterSource>(source);
    ExprInput::ITokeniserCPtr initialTokeniser = &ExpressionTokeniser::Instance;
    ExprInput::TokenStream specimen(initialTokeniser, "(anon)",
                                    std::move(sourceStream));

    ExprInput::Token next;

    // Read three tokens.
    ASSERT_TRUE(specimen.tryGetNextToken(next));
    EXPECT_STRINGEQC(next.getValue(), "alpha");
    ASSERT_TRUE(specimen.tryGetNextToken(next));
    EXPECT_STRINGEQC(next.getValue(), "beta");
    ASSERT_TRUE(specimen.tryGetNextToken(next));
    EXPECT_STRINGEQC(next.getValue(), "gamma");

    // Rewind back to the start; expect to re-read the same three tokens.
    specimen.rewind(3);

    ASSERT_TRUE(specimen.tryGetNextToken(next));
    EXPECT_EQ(next.getClass(), ExprTokenClass::Symbol);
    EXPECT_STRINGEQC(next.getValue(), "alpha");

    ASSERT_TRUE(specimen.tryGetNextToken(next));
    EXPECT_EQ(next.getClass(), ExprTokenClass::Symbol);
    EXPECT_STRINGEQC(next.getValue(), "beta");

    ASSERT_TRUE(specimen.tryGetNextToken(next));
    EXPECT_EQ(next.getClass(), ExprTokenClass::Symbol);
    EXPECT_STRINGEQC(next.getValue(), "gamma");

    EXPECT_FALSE(specimen.tryGetNextToken(next));
}

GTEST_TEST(TokenStream, RewindThenAdvanceMixesCachedAndNew)
{
    String source = "one two three four";
    ICharacterSourceUPtr sourceStream = std::make_unique<StringCharacterSource>(source);
    ExprInput::ITokeniserCPtr initialTokeniser = &ExpressionTokeniser::Instance;
    ExprInput::TokenStream specimen(initialTokeniser, "(anon)",
                                    std::move(sourceStream));

    ExprInput::Token next;

    ASSERT_TRUE(specimen.tryGetNextToken(next));
    EXPECT_STRINGEQC(next.getValue(), "one");
    ASSERT_TRUE(specimen.tryGetNextToken(next));
    EXPECT_STRINGEQC(next.getValue(), "two");
    ASSERT_TRUE(specimen.tryGetNextToken(next));
    EXPECT_STRINGEQC(next.getValue(), "three");

    // Rewind two; subsequent reads return cached "two", "three", then new "four".
    specimen.rewind(2);

    ASSERT_TRUE(specimen.tryGetNextToken(next));
    EXPECT_STRINGEQC(next.getValue(), "two");

    ASSERT_TRUE(specimen.tryGetNextToken(next));
    EXPECT_STRINGEQC(next.getValue(), "three");

    ASSERT_TRUE(specimen.tryGetNextToken(next));
    EXPECT_STRINGEQC(next.getValue(), "four");

    EXPECT_FALSE(specimen.tryGetNextToken(next));
}

GTEST_TEST(TokenStream, RewindRestoresLocationInformation)
{
    String source = "x\n  yy";
    ICharacterSourceUPtr sourceStream = std::make_unique<StringCharacterSource>(source);
    ExprInput::ITokeniserCPtr initialTokeniser = &ExpressionTokeniser::Instance;
    ExprInput::TokenStream specimen(initialTokeniser, "src",
                                    std::move(sourceStream));

    ExprInput::Token next;

    ASSERT_TRUE(specimen.tryGetNextToken(next));
    ASSERT_TRUE(specimen.tryGetNextToken(next));
    EXPECT_EQ(next.getLocation().getLine(), 2);
    EXPECT_EQ(next.getLocation().getColumn(), 3);

    specimen.rewind(1);

    ASSERT_TRUE(specimen.tryGetNextToken(next));
    EXPECT_STRINGEQC(next.getValue(), "yy");
    EXPECT_EQ(next.getLocation().getLine(), 2);
    EXPECT_EQ(next.getLocation().getColumn(), 3);
    EXPECT_STRINGEQC(next.getLocation().getIdentifier(), "src");
}

GTEST_TEST(TokenStream, CommitPreventsRewindOverCommittedTokens)
{
    String source = "alpha beta gamma";
    ICharacterSourceUPtr sourceStream = std::make_unique<StringCharacterSource>(source);
    ExprInput::ITokeniserCPtr initialTokeniser = &ExpressionTokeniser::Instance;
    ExprInput::TokenStream specimen(initialTokeniser, "(anon)",
                                    std::move(sourceStream));

    ExprInput::Token next;

    ASSERT_TRUE(specimen.tryGetNextToken(next));
    ASSERT_TRUE(specimen.tryGetNextToken(next));

    specimen.commit();

    // After committing all read tokens, none may be rewound over.
    EXPECT_THROW(specimen.rewind(1), OperationException);
    EXPECT_THROW(specimen.rewind(2), OperationException);
    EXPECT_NO_THROW(specimen.rewind(0));
}

GTEST_TEST(TokenStream, CommitAllowsContinuedReading)
{
    String source = "a b c d";
    ICharacterSourceUPtr sourceStream = std::make_unique<StringCharacterSource>(source);
    ExprInput::ITokeniserCPtr initialTokeniser = &ExpressionTokeniser::Instance;
    ExprInput::TokenStream specimen(initialTokeniser, "(anon)",
                                    std::move(sourceStream));

    ExprInput::Token next;

    ASSERT_TRUE(specimen.tryGetNextToken(next));
    EXPECT_STRINGEQC(next.getValue(), "a");
    ASSERT_TRUE(specimen.tryGetNextToken(next));
    EXPECT_STRINGEQC(next.getValue(), "b");

    specimen.commit();

    ASSERT_TRUE(specimen.tryGetNextToken(next));
    EXPECT_STRINGEQC(next.getValue(), "c");
    ASSERT_TRUE(specimen.tryGetNextToken(next));
    EXPECT_STRINGEQC(next.getValue(), "d");

    EXPECT_FALSE(specimen.tryGetNextToken(next));
}

GTEST_TEST(TokenStream, CommitOnFreshStreamIsNoOp)
{
    String source = "alpha";
    ICharacterSourceUPtr sourceStream = std::make_unique<StringCharacterSource>(source);
    ExprInput::ITokeniserCPtr initialTokeniser = &ExpressionTokeniser::Instance;
    ExprInput::TokenStream specimen(initialTokeniser, "(anon)",
                                    std::move(sourceStream));

    EXPECT_NO_THROW(specimen.commit());

    ExprInput::Token next;

    ASSERT_TRUE(specimen.tryGetNextToken(next));
    EXPECT_STRINGEQC(next.getValue(), "alpha");
}

GTEST_TEST(TokenStream, CommitAfterRewindKeepsUnreadCachedTokens)
{
    String source = "one two three";
    ICharacterSourceUPtr sourceStream = std::make_unique<StringCharacterSource>(source);
    ExprInput::ITokeniserCPtr initialTokeniser = &ExpressionTokeniser::Instance;
    ExprInput::TokenStream specimen(initialTokeniser, "(anon)",
                                    std::move(sourceStream));

    ExprInput::Token next;

    ASSERT_TRUE(specimen.tryGetNextToken(next));
    ASSERT_TRUE(specimen.tryGetNextToken(next));
    ASSERT_TRUE(specimen.tryGetNextToken(next));
    EXPECT_STRINGEQC(next.getValue(), "three");

    // Rewind one, commit the first two, then continue reading.
    specimen.rewind(1);
    specimen.commit();

    // The uncommitted token "three" must still be available to read.
    ASSERT_TRUE(specimen.tryGetNextToken(next));
    EXPECT_STRINGEQC(next.getValue(), "three");

    // But once read and not yet committed, rewinding past it is forbidden.
    EXPECT_THROW(specimen.rewind(2), OperationException);

    EXPECT_FALSE(specimen.tryGetNextToken(next));
}

GTEST_TEST(TokenStream, CommitClearsCacheWhenFullyConsumed)
{
    // After commit() with everything read, the implementation is expected to
    // release the rewind buffer; that should not affect the ability to read
    // further tokens but does prevent rewinding back into the cleared range.
    String source = "a b c";
    ICharacterSourceUPtr sourceStream = std::make_unique<StringCharacterSource>(source);
    ExprInput::ITokeniserCPtr initialTokeniser = &ExpressionTokeniser::Instance;
    ExprInput::TokenStream specimen(initialTokeniser, "(anon)",
                                    std::move(sourceStream));

    ExprInput::Token next;

    ASSERT_TRUE(specimen.tryGetNextToken(next));
    ASSERT_TRUE(specimen.tryGetNextToken(next));
    specimen.commit();

    EXPECT_THROW(specimen.rewind(1), OperationException);

    ASSERT_TRUE(specimen.tryGetNextToken(next));
    EXPECT_STRINGEQC(next.getValue(), "c");

    // Rewinding back to the just-read token must still be permitted.
    specimen.rewind(1);
    ASSERT_TRUE(specimen.tryGetNextToken(next));
    EXPECT_STRINGEQC(next.getValue(), "c");
}

GTEST_TEST(TokenStream, StatementTokeniserOnlyRecognisesAssignmentAndTerminator)
{
    // The StatementTokeniser variant from Test_ExampleParser only recognises
    // '=', ';' and symbols. Verify TokenStream forwards to it correctly.
    String source = "name = ;";
    ICharacterSourceUPtr sourceStream = std::make_unique<StringCharacterSource>(source);
    ExprInput::ITokeniserCPtr initialTokeniser = &StatementTokeniser::Instance;
    ExprInput::TokenStream specimen(initialTokeniser, "(anon)",
                                    std::move(sourceStream));

    ExprInput::Token next;

    ASSERT_TRUE(specimen.tryGetNextToken(next));
    EXPECT_EQ(next.getClass(), ExprTokenClass::Symbol);
    EXPECT_STRINGEQC(next.getValue(), "name");

    ASSERT_TRUE(specimen.tryGetNextToken(next));
    EXPECT_EQ(next.getClass(), ExprTokenClass::OperatorAssignment);

    ASSERT_TRUE(specimen.tryGetNextToken(next));
    EXPECT_EQ(next.getClass(), ExprTokenClass::EndOfStatement);

    EXPECT_FALSE(specimen.tryGetNextToken(next));
}

GTEST_TEST(TokenStream, PushTokenStreamReadsFromNewSource)
{
    String firstSource = "outer";
    String secondSource = "inner";
    ICharacterSourceUPtr firstStream = std::make_unique<StringCharacterSource>(firstSource);
    ICharacterSourceUPtr secondStream = std::make_unique<StringCharacterSource>(secondSource);
    ExprInput::ITokeniserCPtr initialTokeniser = &ExpressionTokeniser::Instance;
    ExprInput::TokenStream specimen(initialTokeniser, "outer.src",
                                    std::move(firstStream));

    ExprInput::Token next;
    ASSERT_TRUE(specimen.tryGetNextToken(next));
    EXPECT_STRINGEQC(next.getValue(), "outer");

    specimen.pushTokenStream(initialTokeniser, "inner.src",
                             std::move(secondStream));

    ASSERT_TRUE(specimen.tryGetNextToken(next));
    EXPECT_STRINGEQC(next.getValue(), "inner");
    EXPECT_STRINGEQC(next.getLocation().getIdentifier(), "inner.src");
}

GTEST_TEST(TokenStream, PopTokenStreamReturnsToPriorSource)
{
    String firstSource = "outerOne outerTwo";
    String secondSource = "inner";
    ICharacterSourceUPtr firstStream = std::make_unique<StringCharacterSource>(firstSource);
    ICharacterSourceUPtr secondStream = std::make_unique<StringCharacterSource>(secondSource);
    ExprInput::ITokeniserCPtr initialTokeniser = &ExpressionTokeniser::Instance;
    ExprInput::TokenStream specimen(initialTokeniser, "outer.src",
                                    std::move(firstStream));

    ExprInput::Token next;
    ASSERT_TRUE(specimen.tryGetNextToken(next));
    EXPECT_STRINGEQC(next.getValue(), "outerOne");

    specimen.pushTokenStream(initialTokeniser, "inner.src",
                             std::move(secondStream));

    ASSERT_TRUE(specimen.tryGetNextToken(next));
    EXPECT_STRINGEQC(next.getValue(), "inner");

    // The inner stream is exhausted; popping should resume the outer stream.
    specimen.popTokenStream();

    ASSERT_TRUE(specimen.tryGetNextToken(next));
    EXPECT_STRINGEQC(next.getValue(), "outerTwo");
    EXPECT_STRINGEQC(next.getLocation().getIdentifier(), "outer.src");
}

GTEST_TEST(TokenStream, RestoreTokenStreamPopsToRecordedState)
{
    String outerSource = "outer";
    String middleSource = "middle";
    String innerSource = "inner";
    ICharacterSourceUPtr outerStream = std::make_unique<StringCharacterSource>(outerSource);
    ICharacterSourceUPtr middleStream = std::make_unique<StringCharacterSource>(middleSource);
    ICharacterSourceUPtr innerStream = std::make_unique<StringCharacterSource>(innerSource);
    ExprInput::ITokeniserCPtr initialTokeniser = &ExpressionTokeniser::Instance;
    ExprInput::TokenStream specimen(initialTokeniser, "outer.src",
                                    std::move(outerStream));

    size_t restorePoint = specimen.pushTokenStream(initialTokeniser, "middle.src",
                                                   std::move(middleStream));
    specimen.pushTokenStream(initialTokeniser, "inner.src",
                             std::move(innerStream));

    specimen.restoreTokenStream(restorePoint);

    ExprInput::Token next;
    ASSERT_TRUE(specimen.tryGetNextToken(next));
    EXPECT_STRINGEQC(next.getValue(), "outer");
}

GTEST_TEST(TokenStream, PushTokeniserChangesRecognitionWithinSource)
{
    // StatementTokeniser does not recognise '+'; ExpressionTokeniser does.
    String source = "+";
    ICharacterSourceUPtr sourceStream = std::make_unique<StringCharacterSource>(source);
    ExprInput::ITokeniserCPtr initialTokeniser = &StatementTokeniser::Instance;
    ExprInput::TokenStream specimen(initialTokeniser, "(anon)",
                                    std::move(sourceStream));

    ExprInput::Token next;

    // With StatementTokeniser, '+' is not recognised at all.
    EXPECT_FALSE(specimen.tryGetNextToken(next));

    specimen.pushTokeniser(&ExpressionTokeniser::Instance);

    ASSERT_TRUE(specimen.tryGetNextToken(next));
    EXPECT_EQ(next.getClass(), ExprTokenClass::OperatorPlus);
}

GTEST_TEST(TokenStream, RestoreTokeniserRevertsToPriorRecogniser)
{
    String source = "a + b ;";
    ICharacterSourceUPtr sourceStream = std::make_unique<StringCharacterSource>(source);
    ExprInput::ITokeniserCPtr initialTokeniser = &StatementTokeniser::Instance;
    ExprInput::TokenStream specimen(initialTokeniser, "(anon)",
                                    std::move(sourceStream));

    ExprInput::Token next;

    ASSERT_TRUE(specimen.tryGetNextToken(next));
    EXPECT_STRINGEQC(next.getValue(), "a");

    size_t restorePoint = specimen.pushTokeniser(&ExpressionTokeniser::Instance);

    ASSERT_TRUE(specimen.tryGetNextToken(next));
    EXPECT_EQ(next.getClass(), ExprTokenClass::OperatorPlus);

    specimen.restoreTokeniser(restorePoint);

    ASSERT_TRUE(specimen.tryGetNextToken(next));
    EXPECT_EQ(next.getClass(), ExprTokenClass::Symbol);
    EXPECT_STRINGEQC(next.getValue(), "b");

    ASSERT_TRUE(specimen.tryGetNextToken(next));
    EXPECT_EQ(next.getClass(), ExprTokenClass::EndOfStatement);
}

GTEST_TEST(TokenStream, RestoreTokeniserRejectsZero)
{
    String source = "x";
    ICharacterSourceUPtr sourceStream = std::make_unique<StringCharacterSource>(source);
    ExprInput::ITokeniserCPtr initialTokeniser = &ExpressionTokeniser::Instance;
    ExprInput::TokenStream specimen(initialTokeniser, "(anon)",
                                    std::move(sourceStream));

    EXPECT_THROW(specimen.restoreTokeniser(0), ArgumentException);
}

} // Anonymous namespace

}}} // namespace Ag::Text::Test
////////////////////////////////////////////////////////////////////////////////

