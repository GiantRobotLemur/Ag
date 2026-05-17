//! @file Ag/Text/CharacterAnalyser.hpp
//! @brief The declaration of an object which allows a program to analyse a
//! stream of Unicode characters.
//! @author GiantRobotLemur@na-se.co.uk
//! @date 2026
//! @copyright This file is part of the Silver (Ag) project which is released
//! under LGPL 3 license. See LICENSE file at the repository root or go to
//! https://github.com/GiantRobotLemur/Ag for full license details.
////////////////////////////////////////////////////////////////////////////////

#ifndef _AG_TEXT_CHARACTER_ANALYSER_HPP__
#define _AG_TEXT_CHARACTER_ANALYSER_HPP__

////////////////////////////////////////////////////////////////////////////////
// Dependent Header Files
////////////////////////////////////////////////////////////////////////////////
#include "CharacterSource.hpp"

namespace Ag {
namespace Text {

////////////////////////////////////////////////////////////////////////////////
// Data Type Declarations
////////////////////////////////////////////////////////////////////////////////
//! @brief An alias for a vector of Unicode code points.
using CodePointBuffer = std::vector<char32_t>;

////////////////////////////////////////////////////////////////////////////////
// Class Declarations
////////////////////////////////////////////////////////////////////////////////
//! @brief An object which represents a reference to source text being parsed.
class SourceReference
{
private:
    // Internal Fields
    String _identifier;
    int32_t _line;
    int32_t _column;
public:
    // Construction/Destruction
    SourceReference();
    SourceReference(string_cref_t identifier, int32_t line = -1, int32_t column = -1);
    ~SourceReference() = default;

    // Accessors
    string_cref_t getIdentifier() const;

    //! @brief Gets the 1-based index of the line within the source text.
    constexpr int32_t getLine() const { return _line; }

    //! @brief Gets the 1-based index of the column within the specified line.
    constexpr int32_t getColumn() const { return _column; }
};

//! @brief An object which allows a program to analyse a stream of Unicode
//! characters.
//! @remarks
//! The object represents a moving window used to analyse a stream of Unicode
//! code points. Code points are buffered. They can be read by a caller and the
//! read pointer rolled back. When rollback is no longer required, all characters
//! read up to the current point can be committed, preventing rollback until
//! more characters are read.
//! 
//! @note The object collapses CR+ LF combinations down to a single LF ('\n')
//! code point.
class CharacterAnalyser
{
public:
    // Construction/Destruction
    CharacterAnalyser(ICharacterSource *input);
    CharacterAnalyser(ICharacterSource *input, string_cref_t sourceIdentifier);
    ~CharacterAnalyser() = default;

    // Accessors
    size_t getRollbackLimit() const;
    void setBufferSize(size_t characterCount);
    SourceReference getPosition() const;

    // Operations
    void commit();
    void rollback(size_t count);
    bool tryGetNextCharacter(char32_t &next);
    bool tryEnsureNextCharacter(char32_t expectedNext);
    bool skipWhiteSpaceCharacters();
    bool skipBlankCharacters();
private:
    // Internal Functions
    bool tryRefillBuffer();
    void compactLineBreaks(size_t start, size_t length);

    // Internal Fields
    ICharacterSource *_source;
    String _sourceIdentifier;
    CodePointBuffer _buffer;
    size_t _committed;
    size_t _read;
    int32_t _line;
    int32_t _column;
    bool _isInLinebreakSequence;
};

}} // namespace Ag::Text

#endif // Header guard
////////////////////////////////////////////////////////////////////////////////
