//! @file Text/CharacterAnalyser.cpp
//! @brief The definition of an object which allows a program to analyse a
//! stream of Unicode characters.
//! @author GiantRobotLemur@na-se.co.uk
//! @date 2026
//! @copyright This file is part of the Silver (Ag) project which is released
//! under LGPL 3 license. See LICENSE file at the repository root or go to
//! https://github.com/GiantRobotLemur/Ag for full license details.
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Header File Includes
////////////////////////////////////////////////////////////////////////////////
#include "Ag/Text/CharacterAnalyser.hpp"

namespace Ag {
namespace Text {

namespace {

////////////////////////////////////////////////////////////////////////////////
// Local Data
////////////////////////////////////////////////////////////////////////////////
static constexpr size_t MinBufferSize = 256;

} // Anonymous namespace

////////////////////////////////////////////////////////////////////////////////
// CharacterAnalyser Member Definitions
////////////////////////////////////////////////////////////////////////////////
//! @brief Constructs an object to create a moving window on a stream of
//! Unicode characters being analysed.
//! @param[in] input The source of characters to analyse.
CharacterAnalyser::CharacterAnalyser(ICharacterSource *input) :
    _source(input),
    _committed(0),
    _read(0)
{
    _buffer.reserve(MinBufferSize);
}

//! @brief Gets the maximum number of already read characters which can be
//! rolled back.
size_t CharacterAnalyser::getRollbackLimit() const
{
    return _read - _committed;
}

//! @brief Sets the preferred buffer size.
//! @param[in] characterCount The preferred count of characters to buffer.
void CharacterAnalyser::setBufferSize(size_t characterCount)
{
    _buffer.reserve(std::max(MinBufferSize, characterCount));
}

//! @brief Commits all characters read up to this point.
//! @remarks Committed characters cannot be rolled back.
void CharacterAnalyser::commit()
{
    // Commit all characters up to the read pointer.
    _committed = _read;

    if (_committed == _buffer.size())
    {
        // We have committed the entire buffer, empty it.
        _committed = _read = 0;
        _buffer.clear();
    }
}

//! @brief Rolls back the buffer across some previously read characters.
//! @param[in] count The count of previously read characters to "unread".
//! @throws OperationException If @p count is greater than the count of
//! characters read since the last call to commit(). This limit is returned
//! by getRollbackLimit().
void CharacterAnalyser::rollback(size_t count)
{
    size_t maxRollback = _read - _committed;

    if (count > maxRollback)
        throw OperationException("Cannot rollback that many characters.");

    _read -= count;
}

//! @brief Attempts to get the next character from the input stream.
//! @param[in] next Receives the next Unicode code point from the input stream.
//! @retval true A character was available and returned in @p next.
//! @retval false There were no more characters to read.
bool CharacterAnalyser::tryGetNextCharacter(char32_t &next)
{
    if (_read < _buffer.size())
    {
        next = _buffer.at(_read++);

        return true;
    }

    if (tryRefillBuffer())
    {
        next = _buffer.at(_read++);

        return true;
    }

    // We couldn't read any more characters.
    next = U'\0';
    return false;
}

//! @brief Attempts to ensure the next character has a specified value.
//! @param[in] expectedNext The expected next character value.
//! @retval true Another character was available and it was equal
//! to @p expectedNext.
//! @retval false Either there were no more characters, or the next character
//! was not equal to @p expectedNext. In the latter case, the character is
//! NOT marked as read and does not need to be rolled back.
bool CharacterAnalyser::tryEnsureNextCharacter(char32_t expectedNext)
{
    char32_t next;

    if (tryGetNextCharacter(next))
    {
        if (expectedNext == next)
            return true;

        // Unread the character if it didn't match what was expected.
        --_read;
    }

    return false;
}

//! @brief Attempts to add more characters to the internal buffer, preserving
//! any uncommitted characters in the buffer.
//! @retval true At least one more character was added to the buffer.
//! @retval false No more characters could be read.
//! @throws OperationException If there was insufficient space in the buffer to
//! add new characters as the buffer is full of uncommitted characters.
bool CharacterAnalyser::tryRefillBuffer()
{
    size_t preferredSize = _buffer.capacity();
    size_t uncommittedChars = _read - _committed;

    if (uncommittedChars == 0)
    {
        // The buffer is empty, fill as much as possible.
        _buffer.resize(preferredSize);
        _committed = _read = 0;

        size_t charsRead = _source->readUtf32(_buffer.data(), _buffer.size());

        // Truncate the buffer to only the characters read.
        _buffer.erase(_buffer.begin() + charsRead, _buffer.end());

        return charsRead > 0;
    }
    else if (uncommittedChars >= preferredSize)
    {
        throw OperationException("To many uncommitted characters to be able to read more.");
    }
    else // if (uncommittedChars < preferredSize)
    {
        if (_committed > 0)
        {
            // Erase committed characters.
            _buffer.erase(_buffer.begin(), _buffer.begin() + _committed);
            _read -= _committed;
            _committed = 0;
        }

        // Maximize the buffer size without reallocating.
        _buffer.resize(preferredSize);
        size_t bufferLeft = _buffer.size() - _read;

        // Read as much as we can into the buffer.
        size_t charsRead = _source->readUtf32(_buffer.data() + _read, bufferLeft);

        // Truncate the buffer to remaining uncommitted characters.
        _buffer.erase(_buffer.begin() + _read + charsRead, _buffer.end());

        return charsRead > 0;
    }
}

}} // namespace Ag::Text
////////////////////////////////////////////////////////////////////////////////

