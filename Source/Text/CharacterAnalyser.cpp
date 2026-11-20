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
//! @brief Constructs an empty source reference.
SourceReference::SourceReference() :
    _line(-1),
    _column(-1)
{
}

//! @brief Constructs an initialised source reference.
//! @param[in] identifier Text describing the source, such as a file path of URI.
//! @param[in] line The 1-based index of the line within the source text.
//! @param[in] column The 1-based index of the column within the specified line.
SourceReference::SourceReference(string_cref_t identifier, int32_t line /*= -1*/,
                                 int32_t column /*= -1*/) :
    _identifier(identifier),
    _line(line),
    _column(column)
{
}

//! @brief Gets text describing the source, such as a file path of URI.
string_cref_t SourceReference::getIdentifier() const
{
    return _identifier;
}

////////////////////////////////////////////////////////////////////////////////
// CharacterAnalyser Member Definitions
////////////////////////////////////////////////////////////////////////////////
//! @brief Constructs an object to create a moving window on a stream of
//! Unicode characters being analysed.
//! @param[in] input The source of characters to analyse.
CharacterAnalyser::CharacterAnalyser(IO::TextInputStream *input) :
    _source(input)
{
    _buffer.reserve(MinBufferSize);
}

//! @brief Constructs an object to create a moving window on a stream of
//! Unicode characters being analysed.
//! @param[in] input The source of characters to analyse.
//! @param[in] sourceIdentifier A text identifier for the input source, such as
//! a file path or URI.
CharacterAnalyser::CharacterAnalyser(IO::TextInputStream *input,
                                     string_cref_t sourceIdentifier) :
    _source(input),
    _sourceIdentifier(sourceIdentifier)
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

//! @brief Gets the position of the next character to be read.
SourceReference CharacterAnalyser::getPosition() const
{
    return SourceReference(_sourceIdentifier, _line, _column);
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

    // Decrement the line count for line breaks we uncommitted.
    for (size_t i = _committed; i < _read; ++i)
    {
        if (_buffer.at(i) == U'\n')
        {
            --_line;
            _column = 0;
        }
        else
        {
            --_column;
        }
    }

    _read -= count;
}

//! @brief Attempts to get the next character from the input stream.
//! @param[in] next Receives the next Unicode code point from the input stream.
//! @retval true A character was available and returned in @p next.
//! @retval false There were no more characters to read.
bool CharacterAnalyser::tryGetNextCharacter(char32_t &next)
{
    bool hasCodePoint = false;

    if (_read < _buffer.size())
    {
        next = _buffer.at(_read++);
        hasCodePoint = true;
    }
    else if (tryRefillBuffer())
    {
        next = _buffer.at(_read++);
        hasCodePoint = true;
    }
    else
    {
        // We couldn't read any more characters.
        next = U'\0';
    }

    if (hasCodePoint)
    {
        // Process the code point obtained.
        ++_column;

        if (next == U'\n')
        {
            ++_line;
            _column = 1;
        }
    }

    return hasCodePoint;
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

//! @brief Skips discards white space characters until the first non-white-space
//! character or the end of the stream is encountered.
//! @retval true A non-white-space character was encountered.
//! @retval false There were no non-white-space characters before the end of
//! the stream.
//! @remarks All skipped characters are committed, i.e. they cannot be
//! rolled back.
bool CharacterAnalyser::skipWhiteSpaceCharacters()
{
    char32_t next;
    bool hasNonWhiteSpace = false;

    // We don't care about any previous characters.
    commit();

    while (!hasNonWhiteSpace && tryGetNextCharacter(next))
    {
        hasNonWhiteSpace = (CodePoint::isWhiteSpace(next) == false);

        if (hasNonWhiteSpace)
        {
            // We found a non-white-space character. Put it back to be
            // read later.
            rollback(1);
        }

        // We don't care about previously read white space.
        commit();
    }

    return hasNonWhiteSpace;
}

//! @brief Skips discards word-separator characters until the first word
//! character or the end of the stream is encountered.
//! @retval true A non-word-separator character was encountered.
//! @retval false There were no non-word separator characters before the end of
//! the stream.
//! @remarks All skipped characters are committed, i.e. they cannot be
//! rolled back.
bool CharacterAnalyser::skipBlankCharacters()
{
    char32_t next;
    bool hasNonBlank = false;

    // We don't care about any previous characters.
    commit();

    while (!hasNonBlank && tryGetNextCharacter(next))
    {
        hasNonBlank = CodePoint::isBlank(next);

        if (!hasNonBlank)
        {
            // We found a non-blank character. Put it back to be
            // read later.
            rollback(1);
        }

        // We don't care about previously read white space.
        commit();
    }

    return hasNonBlank;
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

        size_t charsRead = _source->read(_buffer.data(), _buffer.size());

        // Compact line breaks and truncate the buffer to only the characters read.
        truncateBuffer(charsRead);

        return charsRead > 0;
    }
    else if (uncommittedChars >= preferredSize)
    {
        throw OperationException("Too many uncommitted characters to be able to read more.");
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
        size_t charsRead = _source->read(_buffer.data() + _read, bufferLeft);

        // Compact line breaks and truncate the buffer to only the characters read.
        truncateBuffer(charsRead + _read);

        return charsRead > 0;
    }
}

//! @brief Truncates the character input buffer to its proper size.
//! @param[in] length The count of code points read into the buffer.
void CharacterAnalyser::truncateBuffer(size_t length)
{
    if (length > 0)
    {
        _buffer.erase(_buffer.begin() + length, _buffer.end());
    }
    else
    {
        _buffer.clear();
    }
}

}} // namespace Ag::Text
////////////////////////////////////////////////////////////////////////////////

