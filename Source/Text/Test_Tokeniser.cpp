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
// Local Data Types
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Local Data
////////////////////////////////////////////////////////////////////////////////

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

} // Anonymous namespace

}}} // namespace Ag::Text::Test
////////////////////////////////////////////////////////////////////////////////

