//! @file Text/Test_ExampleParser.cpp
//! @brief The definition of a specialisation of template classes implementing
//! lexical analysis and parsing, for testing purposes.
//! @author GiantRobotLemur@na-se.co.uk
//! @date 2026
//! @copyright This file is part of the Silver (Ag) project which is released
//! under LGPL 3 license. See LICENSE file at the repository root or go to
//! https://github.com/GiantRobotLemur/Ag for full license details.
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Header File Includes
////////////////////////////////////////////////////////////////////////////////
#include "Test_ExampleParser.hpp"

namespace Ag {
namespace Text {
namespace Test {

namespace {
////////////////////////////////////////////////////////////////////////////////
// Local Data
////////////////////////////////////////////////////////////////////////////////
using CharacterTokenClassMap = Ag::StaticMap<char32_t, ExprTokenClass>;

} // Anonymous namespace

////////////////////////////////////////////////////////////////////////////////
// StatementTokeniser Member Definitions
////////////////////////////////////////////////////////////////////////////////
//! @brief A singleton stateless implementation of the tokeniser type.
const StatementTokeniser StatementTokeniser::Instance;

// Inherited from ITokeniser<ExprTokenClass>
bool StatementTokeniser::tryRecogniseToken(CharacterAnalyser &analyser,
                                           CodePointBuffer &scratchBuffer,
                                           ExprInput::Token &nextToken) const
{
    // Skip characters we don't care about.
    if (!analyser.skipWhiteSpaceCharacters())
        return false;

    // Create a static mapping of single code points to token classes.
    static CharacterTokenClassMap::MappingType mappings[] = {
        { U'=', ExprTokenClass::OperatorAssignment },
        { U';', ExprTokenClass::EndOfStatement },
    };

    static const CharacterTokenClassMap singleCharTokens(mappings);

    // Note the current position within the input stream.
    SourceReference location = analyser.getPosition();
    char32_t next;

    if (analyser.tryGetNextCharacter(next))
    {
        size_t mappingIndex;

        if (singleCharTokens.tryFindValue(next, mappingIndex))
        {
            nextToken = ExprInput::Token(location, singleCharTokens.getValue(mappingIndex));
            return true;
        }
        else if ((next == U'_') || CodePoint::isLetter(next))
        {
            // It's the start of a symbol.
            scratchBuffer.push_back(next);

            // Accumulate symbol characters using the supplied scratch buffer.
            while (analyser.tryGetNextCharacter(next))
            {
                if ((next == U'_') || CodePoint::isAlphaNumeric(next))
                {
                    scratchBuffer.push_back(next);
                }
                else
                {
                    analyser.rollback(1);
                    break;
                }
            }

            nextToken = ExprInput::Token(location, ExprTokenClass::Symbol,
                                         scratchBuffer);
            return true;
        }
        else
        {
            // Put the character back in the input stream.
            analyser.rollback(1);
        }
    }

    return false;
}

////////////////////////////////////////////////////////////////////////////////
// StatementTokeniser Member Definitions
////////////////////////////////////////////////////////////////////////////////
//! @brief A singleton stateless implementation of the tokeniser type.
const ExpressionTokeniser ExpressionTokeniser::Instance;

// Inherited from ITokeniser<ExprTokenClass>
bool ExpressionTokeniser::tryRecogniseToken(CharacterAnalyser &analyser,
                                            CodePointBuffer &scratchBuffer,
                                            ExprInput::Token &nextToken) const
{
    // Skip characters we don't care about.
    if (!analyser.skipWhiteSpaceCharacters())
        return false;

    // Create a static mapping of single code points to token classes.
    static CharacterTokenClassMap::MappingType mappings[] = {
        { U'(', ExprTokenClass::OpenParenthesis },
        { U')', ExprTokenClass::CloseParenthesis },
        { U'+', ExprTokenClass::OperatorPlus },
        { U'-', ExprTokenClass::OperatorMinus },
        { U'*', ExprTokenClass::OperatorMultiply },
        { U'/', ExprTokenClass::OperatorDivide },
        { U'=', ExprTokenClass::OperatorAssignment },
        { U';', ExprTokenClass::EndOfStatement },
    };

    static const CharacterTokenClassMap singleCharTokens(mappings);

    // Note the current position within the input stream.
    SourceReference location = analyser.getPosition();
    char32_t next;

    if (analyser.tryGetNextCharacter(next))
    {
        size_t mappingIndex;

        if (singleCharTokens.tryFindValue(next, mappingIndex))
        {
            nextToken = ExprInput::Token(location, singleCharTokens.getValue(mappingIndex));
            analyser.commit();
            return true;
        }
        else if (next == '"')
        {
            while (analyser.tryGetNextCharacter(next))
            {
                if (next == U'"')
                {
                    nextToken = ExprInput::Token(location,
                                                 ExprTokenClass::StringLiteral,
                                                 scratchBuffer);
                    analyser.commit();
                    return true;
                }
                else if (next == U'\n')
                {
                    break;
                }
                else
                {
                    scratchBuffer.push_back(next);
                }
            }

            // We either reached the end of the line or stream without a
            // closing quote.
            nextToken = ExprInput::Token(location,
                                         ExprTokenClass::Error,
                                         "Un-terminated string literal.");
            analyser.commit();
            return true;
        }
        else if (next == U'\'')
        {
            if (analyser.tryGetNextCharacter(next) &&
                (next != U'\'') &&
                analyser.tryEnsureNextCharacter(U'\''))
            {
                scratchBuffer.push_back(next);

                nextToken = ExprInput::Token(location,
                                             ExprTokenClass::CharacterLiteral,
                                             scratchBuffer);
            }
            else
            {
                nextToken = ExprInput::Token(location,
                                             ExprTokenClass::Error,
                                             "Un-terminated character literal.");
            }

            analyser.commit();
            return true;
        }
        else if (CodePoint::isNumeric(next))
        {
            ScalarParser valueParser;
            valueParser.enableLeadingWhiteSpace(false);
            valueParser.enableTrailingWhiteSpace(false);

            if (valueParser.tryProcessCharacter(next))
            {
                scratchBuffer.push_back(next);

                while (analyser.tryGetNextCharacter(next))
                {
                    if (valueParser.tryProcessCharacter(next))
                    {
                        scratchBuffer.push_back(next);
                    }
                    else
                    {
                        // Put the character back and see what we have.
                        analyser.rollback(1);
                        break;
                    }
                }
            }

            if (valueParser.isComplete())
            {
                // Create an appropriate token class.
                ExprTokenClass valueClass = ExprTokenClass::UnknownToken;

                if (valueParser.hasFraction() || valueParser.hasExponent())
                {
                    valueClass = ExprTokenClass::RealLiteral;
                }
                else
                {
                    valueClass = ExprTokenClass::IntegerLiteral;
                }

                nextToken = ExprInput::Token(location, valueClass, scratchBuffer);
                analyser.commit();
                return true;
            }
            else
            {
                // Error: return an error token.
                std::string error;
                error.assign("Invalid numeric literal '");
                Utf::appendUTF32(error, scratchBuffer.data(), scratchBuffer.size());
                error.append("'.");

                nextToken = ExprInput::Token(location, ExprTokenClass::Error,
                                             error.c_str());
                analyser.commit();
                return true;
            }
        }
        else if ((next == U'_') || CodePoint::isLetter(next))
        {
            // It's the start of a symbol.
            scratchBuffer.push_back(next);

            // Accumulate symbol characters using the supplied scratch buffer.
            while (analyser.tryGetNextCharacter(next))
            {
                if ((next == U'_') || CodePoint::isAlphaNumeric(next))
                {
                    scratchBuffer.push_back(next);
                }
                else
                {
                    analyser.rollback(1);
                    break;
                }
            }

            nextToken = ExprInput::Token(location, ExprTokenClass::Symbol,
                                         scratchBuffer);
            analyser.commit();
            return true;
        }
        else
        {
            // Put the character back in the input stream.
            analyser.rollback(1);
        }
    }

    return false;
}

}}} // namespace Ag::Text::Test
////////////////////////////////////////////////////////////////////////////////

