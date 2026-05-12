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
// Class Declarations
////////////////////////////////////////////////////////////////////////////////
//! @brief An object which allows a program to analyse a stream of Unicode
//! characters.
//! @remarks
//! The object represents a moving window used to analyse a stream of Unicode
//! code points. Code points are buffered. They can be read and the read pointer
//! rolled back. When rollback is no longer required, all characters read up to
//! the current point can be committed, preventing rollback until more characters
//! are read.
class CharacterAnalyser
{
public:
    // Construction/Destruction
    CharacterAnalyser(ICharacterSource *input);
    ~CharacterAnalyser() = default;

    // Accessors
    size_t getRollbackLimit() const;
    void setBufferSize(size_t characterCount);

    // Operations
    void commit();
    void rollback(size_t count);
    bool tryGetNextCharacter(char32_t &next);
    bool tryEnsureNextCharacter(char32_t expectedNext);
private:
    // Internal Functions
    bool tryRefillBuffer();

    // Internal Fields
    ICharacterSource *_source;
    std::vector<char32_t> _buffer;
    size_t _committed;
    size_t _read;
};

}} // namespace Ag::Text

#endif // Header guard
////////////////////////////////////////////////////////////////////////////////
