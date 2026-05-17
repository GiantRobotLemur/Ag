//! @file Text/Test_ExampleParser.hpp
//! @brief The declaration of a specialisation of template classes implementing
//! lexical analysis and parsing, for testing purposes.
//! @author GiantRobotLemur@na-se.co.uk
//! @date 2026
//! @copyright This file is part of the Silver (Ag) project which is released
//! under LGPL 3 license. See LICENSE file at the repository root or go to
//! https://github.com/GiantRobotLemur/Ag for full license details.
////////////////////////////////////////////////////////////////////////////////

#ifndef _AG_TEXT_EXAMPLE_PARSER_HPP__
#define _AG_TEXT_EXAMPLE_PARSER_HPP__

////////////////////////////////////////////////////////////////////////////////
// Dependent Header Files
////////////////////////////////////////////////////////////////////////////////
#include "Ag/Text/Parser.hpp"

namespace Ag {
namespace Text {
namespace Test {

////////////////////////////////////////////////////////////////////////////////
// Data Type Declarations
////////////////////////////////////////////////////////////////////////////////
// The following define a simple assignment language where each statement is
// an expression assigned to a symbol. Expresses are defined using a small
// subset of arithmetic operators. Statements are terminated with a semi-colon
// character (;).

//! @brief Expresses the set of tokens used to test the Parser infrastructure.
enum class ExprTokenClass : uint8_t
{
    UnknownToken,
    IntegerLiteral,
    RealLiteral,
    CharacterLiteral,
    StringLiteral,
    Symbol,
    OpenParenthesis,
    CloseParenthesis,
    OperatorPlus,
    OperatorMinus,
    OperatorMultiply,
    OperatorDivide,
    OperatorAssignment,
    EndOfStatement,
    EndOfStream,
    Error,
};

using ExprInput = TokenPipelineTraits<ExprTokenClass>;

//! @brief An object which recognises tokens which form part of a statement.
class StatementTokeniser : public ExprInput::ITokeniser
{
protected:
    // Construction/Destruction
    StatementTokeniser() = default;
public:
    virtual ~StatementTokeniser() = default;

    // Public Data
    static const StatementTokeniser Instance;

    // Overrides
    virtual bool tryRecogniseToken(CharacterAnalyser &analyser,
                                   CodePointBuffer &scratchBuffer,
                                   ExprInput::Token &nextToken) const override;
};

//! @brief An object which recognises tokens which form part of an expression.
class ExpressionTokeniser : public ExprInput::ITokeniser
{
protected:
    // Construction/Destruction
    ExpressionTokeniser() = default;
public:
    virtual ~ExpressionTokeniser() = default;

    // Public Data
    static const ExpressionTokeniser Instance;

    // Overrides
    virtual bool tryRecogniseToken(CharacterAnalyser &analyser,
                                   CodePointBuffer &scratchBuffer,
                                   ExprInput::Token &nextToken) const override;
};

////////////////////////////////////////////////////////////////////////////////
// Class Declarations
////////////////////////////////////////////////////////////////////////////////
//! @brief
//class XXX
//{
//public:
//    // Construction/Destruction
//
//    // Accessors
//
//    // Operations
//
//private:
//    // Internal Types
//
//    // Internal Functions
//
//    // Internal Fields
//};

////////////////////////////////////////////////////////////////////////////////
// Function Declarations
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Templates
////////////////////////////////////////////////////////////////////////////////

}}} // namespace Ag::Text::Test

#endif // Header guard
////////////////////////////////////////////////////////////////////////////////
