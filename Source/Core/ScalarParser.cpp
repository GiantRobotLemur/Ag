//! @file Core/ScalarParser.cpp
//! @brief The definition of an object which parses scalar values from text.
//! @author GiantRobotLemur@na-se.co.uk
//! @date 2021-2026
//! @copyright This file is part of the Silver (Ag) project which is released
//! under LGPL 3 license. See LICENSE file at the repository root or go to
//! https://github.com/GiantRobotLemur/Ag for full license details.
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Header File Includes
////////////////////////////////////////////////////////////////////////////////
#include <algorithm>
#include <cctype>

#include "Ag/Core/CodePoint.hpp"
#include "Ag/Core/ScalarParser.hpp"
#include "Ag/Core/Exception.hpp"
#include "Ag/Core/InlineMemory.hpp"
#include "Ag/Core/Utf.hpp"
#include "Ag/Core/Utils.hpp"

namespace Ag {

namespace {

////////////////////////////////////////////////////////////////////////////////
// Local Functions
////////////////////////////////////////////////////////////////////////////////
template<typename T> T raiseToPower(T value, int power)
{
    T result = static_cast<T>(0);

    using TypeInfo = std::numeric_limits<T>;
    static bool isInitialised = false;
    static T table[TypeInfo::digits10] = { static_cast<T>(0), };

    if (isInitialised == false)
    {
        table[0] = 0;
        table[1] = 1;

        for (int exp = 2; exp < TypeInfo::digits10; ++exp)
        {
            table[exp] = table[exp - 1] * 10;
        }

        isInitialised = true;
    }

    if (power >= 0)
    {
        if (power < TypeInfo::digits10)
        {
            result = value * table[power];
        }
        else
        {
            result = TypeInfo::max();
        }
    }

    return result;
}

} // Anonymous namespace

////////////////////////////////////////////////////////////////////////////////
// Class Method Definitions
////////////////////////////////////////////////////////////////////////////////
//! @brief Constructs an object which recognises scalar values encoded using
//! the neutral locale.
ScalarParser::ScalarParser() :
    _currentState(State_Start),
    _stateIndex(0),
    _preferredRadix(10),
    _radix(-1),
    _sign(1),
    _exponentSign(1),
    _flags(Flag_AllowRadixPrefix | Flag_AllowSign |
           Flag_AllowLeadingWhiteSpace | Flag_AllowTrailingWhiteSpace)
{
    initialise(LocaleInfo::getNeutral());
}

//! @brief Constructs an object to parse scalar values expressed as text.
//! @param[in] locale The locale parsed values will be expressed in.
ScalarParser::ScalarParser(const LocaleInfo &locale) :
    _currentState(State_Start),
    _stateIndex(0),
    _preferredRadix(10),
    _radix(-1),
    _sign(1),
    _exponentSign(1),
    _flags(Flag_AllowRadixPrefix | Flag_AllowSign |
           Flag_AllowLeadingWhiteSpace | Flag_AllowTrailingWhiteSpace)
{
    initialise(locale);
}

//! @brief Gets whether the radix can be detected by a '0x' (hex) or '0' (octal)
//! prefix to the value.
//! @retval true Radix will be detected from the prefix.
//! @retval false A radix prefix will not be expected.
bool ScalarParser::allowRadixPrefix() const
{
    return hasFlag(Flag_AllowRadixPrefix);
}

//! @brief Sets whether the radix can be detected by a '0x' (hex) or '0' (octal)
//! prefix to the value.
//! @param[in] isEnabled True if the radix will be detected from the prefix.
//! False if a radix prefix will not be expected.
void ScalarParser::enableRadixPrefix(bool isEnabled)
{
    setFlag(Flag_AllowRadixPrefix, isEnabled);
}

//! @brief Gets the preferred radix used if none is detected or detection is
//! disabled.
int ScalarParser::getPreferredRadix() const
{
    return _preferredRadix;
}

//! @brief Sets the preferred radix used if none is detected or detection is
//! disabled.
//! @param[in] radix The preferred radix, between 2 and 36.
void ScalarParser::setPreferredRadix(int radix)
{
    if ((radix < 2) || (radix > 36))
    {
        throw ArgumentException("radix");
    }

    _preferredRadix = radix;
}

//! @brief Gets whether a leading sign is expected.
//! @retval true An optional sign can proceed parsed values.
//! @retval false A sign will cause parsing to fail.
bool ScalarParser::allowSign() const
{
    return hasFlag(Flag_AllowSign);
}

//! @brief Sets whether a leading sign is expected.
//! @param[in] isEnabled True if an optional sign can proceed parsed values.
//! False to make a sign cause parsing to fail.
void ScalarParser::enableSign(bool isEnabled)
{
    setFlag(Flag_AllowSign, isEnabled);
}

//! @brief Gets whether an optional decimal point and fraction digits
//! are expected.
//! @retval true A fraction will be parsed.
//! @retval false A decimal point will end parsing.
bool ScalarParser::allowFraction() const
{
    return hasFlag(Flag_AllowFraction);
}

//! @brief Sets whether an optional decimal point and fraction digits
//! are expected.
//! @param[in] isEnabled True if a decimal point and following fraction digits
//! will be accepted. False to stop parsing at a decimal point.
void ScalarParser::enableFraction(bool isEnabled)
{
    setFlag(Flag_AllowFraction, isEnabled);
}

//! @brief Gets whether an optional exponential component will be recognised.
//! @retval true An exponent will be parsed.
//! @retval false An exponent will end parsing.
bool ScalarParser::allowExponent() const
{
    return hasFlag(Flag_AllowExponent);
}

//! @brief Sets whether an optional exponential component will be recognised.
//! @param[in] isEnabled True to parse an exponential component, false to cause
//! it to end parsing.
void ScalarParser::enableExponent(bool isEnabled)
{
    setFlag(Flag_AllowExponent, isEnabled);
}

//! @brief Gets whether leading white space will be consumed.
//! @retval true Any leading white space characters will be consumed.
//! @retval false Any leading white space characters will be rejected.
bool ScalarParser::allowLeadingWhiteSpace() const
{
    return hasFlag(Flag_AllowLeadingWhiteSpace);
}

//! @brief Sets whether an leading white space will be consumed.
//! @param[in] isEnabled True to consume leading white space characters, false
//! to cause it to end parsing.
void ScalarParser::enableLeadingWhiteSpace(bool isEnabled)
{
    setFlag(Flag_AllowLeadingWhiteSpace, isEnabled);
}

//! @brief Gets whether trailing white space will be consumed.
//! @retval true Any trailing white space characters will be consumed.
//! @retval false Any trailing white space characters will be rejected.
bool ScalarParser::allowTrailingWhiteSpace() const
{
    return hasFlag(Flag_AllowTrailingWhiteSpace);
}

//! @brief Sets whether an trailing white space will be consumed.
//! @param[in] isEnabled True to consume trailing white space characters, false
//! to cause it to end parsing.
void ScalarParser::enableTrailingWhiteSpace(bool isEnabled)
{
    setFlag(Flag_AllowTrailingWhiteSpace, isEnabled);
}

//! @brief Indicates whether any whole-number digits have been parsed.
bool ScalarParser::hasWholeDigits() const noexcept
{
    // We have to be careful with this one as we don't store leading zeros.
    return (_wholeDigits.empty() == false) ||
        (_currentState >= State_InWholeDigits);
}

//! @brief Indicates whether any fraction-component digits have been parsed.
bool ScalarParser::hasFraction() const noexcept
{
    return _fractionalDigits.empty() == false;
}

//! @brief Indicates whether any exponent digits have been parsed.
bool ScalarParser::hasExponent() const noexcept
{
    return _exponentDigits.empty() == false;
}

//! @brief Determines if enough characters have been processed to produce
//! a valid scalar value.
//! @retval true A valid scalar value has been parsed.
//! @retval false Either not enough digits have been parsed for a valid scalar
//! value, or the object is in an intermediate state, and needs to process more
//! characters to be valid (like after a decimal point).
bool ScalarParser::isComplete() const noexcept
{
    return isTerminalState(_currentState);
}

//! @brief Resets the parser back to the start state.
void ScalarParser::reset()
{
    _currentState = State_Start;
    _stateIndex = 0;
    _preferredRadix = 10;
    _radix = -1;
    _sign = 1;
    _exponentSign = 1;
    _wholeDigits.clear();
    _fractionalDigits.clear();
    _exponentDigits.clear();
}

//! @brief Attempts to process a UTF-8 character.
//! @param[in] character The character to process.
//! @retval true The character was processed successfully.
//! @retval false The character was unexpected given the previously parsed
//! characters. The parse state is not altered.
bool ScalarParser::tryProcessCharacter(char32_t character)
{
    // Re-direct parsing depending on the current state.
    static HandlerFnPtr handlerFunctions[] =
    {
        &ScalarParser::handleStart, // State_Start
        &ScalarParser::handleBeforePrefix, // State_BeforePrefix
        &ScalarParser::handleBeforeWholeDigits, // State_BeforeWholeDigits
        &ScalarParser::handleBeforeWholeHexDigits, // State_BeforeWholeHexDigits
        &ScalarParser::handleAfterZeroPrefix, // State_AfterZeroPrefix
        &ScalarParser::handleInWholeDigits, // State_InWholeDigits
        &ScalarParser::handleExpectingWholeDigit, // State_ExpectingWholeDigit
        &ScalarParser::handleInThousandSeparator, // State_InThousandSeparator
        &ScalarParser::handleInDecimalPoint, // State_InDecimalPoint
        &ScalarParser::handleBeforeFraction, // State_BeforeFraction
        &ScalarParser::handleInFraction, // State_InFraction
        &ScalarParser::handleAfterExponentSymbol, // State_AfterExponentSymbol
        &ScalarParser::handleBeforeExponentDigits, // State_BeforeExponentDigits
        &ScalarParser::handleInExponent, // State_InExponent
        &ScalarParser::handleInTrailingWhiteSpace, // State_InTrailingWhiteSpace
    };

    bool isProcessed = false;

    if (_currentState < std::size(handlerFunctions))
    {
        isProcessed = ((this)->*handlerFunctions[_currentState])(character);
    }

    return isProcessed;
}

//! @brief Attempts to process all characters in a string.
//! @param[in] str A view of the string to process.
//! @retval true All characters were successfully processed, a call to
//! tryGetValue() will yield the result.
//! @retval false An error was encountered during processing.
bool ScalarParser::tryProcessString(const std::string_view &str)
{
    reset();

    Utf::FromUtf8Converter converter;
    char32_t codePoint;
    bool isOK = true;
    bool hasError = false;

    for (auto pos = str.begin(); isOK && (pos != str.end()); ++pos)
    {
        if (converter.tryConvert(static_cast<uint8_t>(*pos),
                                 codePoint, hasError))
        {
            isOK &= tryProcessCharacter(codePoint);
        }
        else
        {
            isOK = (hasError == false);
        }
    }

    return isOK;
}

//! @brief Performs shared initialisation for the object.
//! @param[in] locale The locale used to define digit separators.
void ScalarParser::initialise(const LocaleInfo &locale)
{
    // Cache the separators as Unicode code points in a single buffer.
    string_cref_t thousandSep = locale.getThousandSeparator();
    string_cref_t decimalSep = locale.getDecimalSeparator();

    // Calculate the size of the buffer and position of elements within it.
    InlineAllocator allocator;

    // Allocate space for the fields.
    auto thousandField = allocator.allocateUTF32(thousandSep);
    auto decimalField = allocator.allocateUTF32(decimalSep);

    // Size the buffer accordingly.
    _source.resize(allocator.getSize());

    // Fill the buffer with field data.
    InlineInitialiser initialiser(_source.data(), _source.size());

    _thousandSeparator = initialiser.initialiseFieldUTF32(thousandField, thousandSep);
    _decimalPoint = initialiser.initialiseFieldUTF32(decimalField, decimalSep);
}

//! @brief Determines if one or more internal option flags are set.
//! @param[in] flag The flag(s) to query.
//! @retval true All flag bits were set.
//! @retval false Only some or none of the flags specified were set.
bool ScalarParser::hasFlag(uint32_t flag) const
{
    return (_flags & flag) == flag;
}

//! @brief Sets the value of a flag or flags.
//! @param[in] flag The flag(s) to set or clear.
//! @param[in] isSet True to set the flags, false to clear them.
void ScalarParser::setFlag(uint32_t flag, bool isSet)
{
    if (isSet)
    {
        _flags |= flag;
    }
    else
    {
        _flags &= ~flag;
    }
}

//! @brief Processes a character when in the State_Start state.
bool ScalarParser::handleStart(char32_t next)
{
    bool isProcessed = false;
    uint8_t digit = 0xFF;

    if (hasFlag(Flag_AllowLeadingWhiteSpace) && CodePoint::isWhiteSpace(next))
    {
        // Skip leading white space.
        isProcessed = true;
    }
    else if (next == U'-')
    {
        _sign = -1;
        isProcessed = hasFlag(Flag_AllowSign);

        _currentState = hasFlag(Flag_AllowRadixPrefix) ? State_BeforePrefix :
                                                         State_BeforeWholeDigits;
    }
    else if (next == U'+')
    {
        _sign = 1;
        isProcessed = hasFlag(Flag_AllowSign);

        _currentState = hasFlag(Flag_AllowRadixPrefix) ? State_BeforePrefix :
                                                         State_BeforeWholeDigits;
    }
    else if ((next == U'0') && hasFlag(Flag_AllowRadixPrefix))
    {
        isProcessed = true;
        _currentState = State_AfterZeroPrefix;
    }
    else
    {
        if ((next >= U'0') && (next <= U'9'))
        {
            digit = static_cast<uint8_t>(next - U'0');
        }
        else if ((next >= U'A') && (next <= U'Z'))
        {
            digit = static_cast<uint8_t>(next - U'A') + 10;
        }
        else if ((next >= U'a') && (next <= U'z'))
        {
            digit = static_cast<uint8_t>(next - U'a') + 10;
        }

        if (digit < _preferredRadix)
        {
            // Allow the character.
            isProcessed = true;
            _radix = _preferredRadix;

            if (digit != 0)
            {
                // Don't store leading zeros.
                _wholeDigits.push_back(digit);
            }

            _currentState = State_InWholeDigits;
        }
    }

    return isProcessed;
}

//! @brief Processes a character when in the State_BeforePrefix state.
bool ScalarParser::handleBeforePrefix(char32_t next)
{
    bool isProcessed = false;
    uint8_t digit = 0xFF;

    // We are only in this state because radix prefixes are enabled.
    if (next == U'0')
    {
        isProcessed = true;
        _currentState = State_AfterZeroPrefix;
    }
    else
    {
        if ((next >= U'1') && (next <= U'9'))
        {
            digit = static_cast<uint8_t>(next - U'0');
        }
        else if ((next >= U'A') && (next <= U'Z'))
        {
            digit = static_cast<uint8_t>(next - U'A') + 10;
        }
        else if ((next >= U'a') && (next <= U'z'))
        {
            digit = static_cast<uint8_t>(next - U'a') + 10;
        }

        if (digit < _preferredRadix)
        {
            // Allow the character.
            isProcessed = true;
            _radix = _preferredRadix;

            if (digit != 0)
            {
                // Don't store leading zeros.
                _wholeDigits.push_back(digit);
            }

            _currentState = State_InWholeDigits;
        }
    }

    return isProcessed;
}

//! @brief Processes a character when in the State_BeforeWholeDigits state.
bool ScalarParser::handleBeforeWholeDigits(char32_t next)
{
    bool isProcessed = false;
    uint8_t digit = 0xFF;

    // We are in this state is we are not detecting radix prefixes.
    if ((next >= U'0') && (next <= U'9'))
    {
        digit = static_cast<uint8_t>(next - U'0');
    }
    else if ((next >= U'A') && (next <= U'Z'))
    {
        digit = static_cast<uint8_t>(next - U'A') + 10;
    }
    else if ((next >= U'a') && (next <= U'z'))
    {
        digit = static_cast<uint8_t>(next - U'a') + 10;
    }

    if (digit < _preferredRadix)
    {
        // Allow the character.
        isProcessed = true;
        _radix = _preferredRadix;

        if (digit != 0)
        {
            // Don't store leading zeros.
            _wholeDigits.push_back(digit);
        }

        _currentState = State_InWholeDigits;
        isProcessed = true;
    }

    return isProcessed;
}

//! @brief Processes a character when in the State_AfterZeroPrefix state.
bool ScalarParser::handleBeforeWholeHexDigits(char32_t next)
{
    bool isProcessed = false;
    uint8_t digit = 0xFF;

    // The radix is set, but we haven't seen a digit yet.
    if ((next >= U'0') && (next <= U'9'))
    {
        digit = static_cast<uint8_t>(next - U'0');
    }
    else if ((next >= U'A') && (next <= U'F'))
    {
        digit = static_cast<uint8_t>(next - U'A') + 10;
    }
    else if ((next >= U'a') && (next <= U'f'))
    {
        digit = static_cast<uint8_t>(next - U'a') + 10;
    }

    if (digit < _radix)
    {
        isProcessed = true;

        // Don't store leading zeros.
        if (digit != '0')
        {
            _wholeDigits.push_back(digit);
        }

        _currentState = State_InWholeDigits;
    }

    return isProcessed;
}

//! @brief Processes a character when in the State_AfterZeroPrefix state.
bool ScalarParser::handleAfterZeroPrefix(char32_t next)
{
    bool isProcessed = false;
    uint8_t digit = 0xFF;

    if ((next == U'X') || (next == U'x'))
    {
        // Its hexadecimal.
        _radix = 16;
        isProcessed = true;
        _currentState = State_BeforeWholeHexDigits;
    }
    else if (hasFlag(Flag_AllowTrailingWhiteSpace) &&
             CodePoint::isWhiteSpace(next))
    {
        // The value was zero, the radix irrelevant.
        isProcessed = true;
        _radix = _preferredRadix;
        _currentState = State_InTrailingWhiteSpace;
    }
    else if ((next >= U'0') && (next <= U'7'))
    {
        // It's octal.
        _radix = 8;
        digit = static_cast<uint8_t>(next - U'0');
    }
    else if ((next == U'8') || (next == U'9'))
    {
        // The leading zero wasn't a prefix.
        digit = static_cast<uint8_t>(next - U'0');
        _radix = _preferredRadix;
    }
    else if ((next >= U'A') && (next <= U'Z'))
    {
        digit = static_cast<uint8_t>(next - U'A') + 10;
        _radix = _preferredRadix;
    }
    else if ((next >= U'a') && (next <= U'z'))
    {
        digit = static_cast<uint8_t>(next - U'a') + 10;
        _radix = _preferredRadix;
    }

    if (digit < _radix)
    {
        isProcessed = true;

        // Don't store leading zeros.
        if (digit != 0)
        {
            _wholeDigits.push_back(digit);
        }

        _currentState = State_InWholeDigits;
    }

    return isProcessed;
}

//! @brief Processes a character when in the State_InWholeDigits state.
bool ScalarParser::handleInWholeDigits(char32_t next)
{
    bool isProcessed = false;
    uint8_t digit = 0xFF;

    // If we are here, we have already encountered at least one digit character
    // and the radix is set.
    if ((_radix == 10) && hasFlag(Flag_AllowExponent) &&
        ((next == U'E') || (next == U'e')))
    {
        // We've reached the end of the whole number component.
        _currentState = State_AfterExponentSymbol;
        isProcessed = true;
    }
    else if ((_radix == 10) && hasFlag(Flag_AllowFraction) &&
             (_decimalPoint.empty() == false) &&
             (next == _decimalPoint.front()))
    {
        // We've found the start of a decimal point.
        isProcessed = true;

        if (_decimalPoint.length() > 1)
        {
            // We need to recognise the rest.
            _stateIndex = 1;

            _currentState = State_InDecimalPoint;
        }
        else
        {
            _currentState = State_BeforeFraction;
        }
    }
    else if ((_thousandSeparator.empty() == false) &&
             (_thousandSeparator.front() == next))
    {
        // We've found the beginning of a thousand separator.
        isProcessed = true;

        if (_thousandSeparator.length() > 1)
        {
            _stateIndex = 1;
            _currentState = State_InThousandSeparator;
        }
        else
        {
            _currentState = State_ExpectingWholeDigit;
        }
    }
    else if ((next >= U'0') && (next <= U'9'))
    {
        digit = static_cast<uint8_t>(next - U'0');
    }
    else if ((next >= U'A') && (next <= U'Z'))
    {
        digit = static_cast<uint8_t>(next - U'A') + 10;
    }
    else if ((next >= U'a') && (next <= U'z'))
    {
        digit = static_cast<uint8_t>(next - U'a') + 10;
    }
    else if (hasFlag(Flag_AllowTrailingWhiteSpace) &&
             CodePoint::isWhiteSpace(next))
    {
        isProcessed = true;
        _currentState = State_InTrailingWhiteSpace;
    }

    if (digit < _radix)
    {
        // The digit is valid, but the state doesn't change.
        isProcessed = true;

        // Don't store leading zeros.
        if ((_wholeDigits.empty() == false) || (digit != 0))
        {
            _wholeDigits.push_back(digit);
        }
    }

    return isProcessed;
}

//! @brief Processes a character when in the State_ExpectingWholeDigit state.
bool ScalarParser::handleExpectingWholeDigit(char32_t next)
{
    bool isProcessed = false;
    uint8_t digit = 0xFF;

    // If we get here, it is after a thousand separator. We need at least one
    // more digit before an exponent, decimal point or the end of the value.
    if ((next >= U'0') && (next <= U'9'))
    {
        digit = static_cast<uint8_t>(next - U'0');
    }
    else if ((next >= U'A') && (next <= U'Z'))
    {
        digit = static_cast<uint8_t>(next - U'A') + 10;
    }
    else if ((next >= U'a') && (next <= U'z'))
    {
        digit = static_cast<uint8_t>(next - U'a') + 10;
    }

    if (digit < _radix)
    {
        // The digit is valid, but the state doesn't change.
        isProcessed = true;

        // Don't store leading zeros.
        if ((_wholeDigits.empty() == false) || (digit != 0))
        {
            _wholeDigits.push_back(digit);
        }

        _currentState = State_InWholeDigits;
    }

    return isProcessed;
}

//! @brief Processes a character when in the State_InThousandSeparator state.
bool ScalarParser::handleInThousandSeparator(char32_t next)
{
    bool isProcessed = false;

    if (next == _thousandSeparator[_stateIndex])
    {
        isProcessed = true;
        ++_stateIndex;

        if (_stateIndex >= _thousandSeparator.length())
        {
            // We have recognised the entire string.
            _currentState = State_ExpectingWholeDigit;
            _stateIndex = 0;
        }
    }

    return isProcessed;
}

//! @brief Processes a character when in the State_InDecimalPoint state.
bool ScalarParser::handleInDecimalPoint(char32_t next)
{
    bool isProcessed = false;

    if (next == _decimalPoint[_stateIndex])
    {
        isProcessed = true;
        ++_stateIndex;

        if (_stateIndex >= _decimalPoint.length())
        {
            // We have recognised the entire string.
            _currentState = State_BeforeFraction;
            _stateIndex = 0;
        }
    }

    return isProcessed;
}

//! @brief Processes a character when in the State_BeforeFraction state.
bool ScalarParser::handleBeforeFraction(char32_t next)
{
    bool isProcessed = false;

    // If we get here, it is after a decimal point. We need at least one
    // more digit before an exponent or the end of the value.
    if ((next >= U'0') && (next <= U'9'))
    {
        // We only read fractions on decimal values.
        isProcessed = true;
        _fractionalDigits.push_back(static_cast<uint8_t>(next - U'0'));
        _currentState = State_InFraction;
    }

    return isProcessed;
}

//! @brief Processes a character when in the State_InFraction state.
bool ScalarParser::handleInFraction(char32_t next)
{
    bool isProcessed = false;

    // If we get here, it is after a decimal point. We need at least one
    // more digit before an exponent or the end of the value.
    if ((next >= U'0') && (next <= U'9'))
    {
        // We only read fractions on decimal values.
        isProcessed = true;
        _fractionalDigits.push_back(static_cast<uint8_t>(next - U'0'));
        _currentState = State_InFraction;
    }
    else if (hasFlag(Flag_AllowExponent) &&
             ((next == U'E') || (next == U'e')))
    {
        isProcessed = true;
        _currentState = State_AfterExponentSymbol;
    }
    else if (hasFlag(Flag_AllowTrailingWhiteSpace) &&
             CodePoint::isWhiteSpace(next))
    {
        isProcessed = true;
        _currentState = State_InTrailingWhiteSpace;
    }

    return isProcessed;
}

//! @brief Processes a character when in the State_AfterExponentSymbol state.
bool ScalarParser::handleAfterExponentSymbol(char32_t next)
{
    bool isProcessed = false;

    if (next == U'+')
    {
        isProcessed = true;
        _exponentSign = 1;
        _currentState = State_BeforeExponentDigits;
    }
    else if (next == U'-')
    {
        isProcessed = true;
        _exponentSign = -1;
        _currentState = State_BeforeExponentDigits;
    }
    else if ((next >= U'0') && (next <= U'9'))
    {
        // We only read exponents on decimal values.
        isProcessed = true;

        _exponentDigits.push_back(static_cast<uint8_t>(next - U'0'));
        _currentState = State_InExponent;
    }

    return isProcessed;
}

//! @brief Processes a character when in the State_AfterExponentSymbol state.
bool ScalarParser::handleBeforeExponentDigits(char32_t next)
{
    bool isProcessed = false;

    if ((next >= U'0') && (next <= U'9'))
    {
        // We only read fractions on decimal values.
        isProcessed = true;
        _exponentDigits.push_back(static_cast<uint8_t>(next - U'0'));
        _currentState = State_InExponent;
    }

    return isProcessed;
}

//! @brief Processes a character when in the State_AfterExponentSymbol state.
bool ScalarParser::handleInExponent(char32_t next)
{
    bool isProcessed = false;

    if ((next >= U'0') && (next <= U'9'))
    {
        // We only read fractions on decimal values.
        isProcessed = true;
        _exponentDigits.push_back(static_cast<uint8_t>(next - U'0'));
    }
    else if (hasFlag(Flag_AllowTrailingWhiteSpace) &&
             CodePoint::isWhiteSpace(next))
    {
        isProcessed = true;
        _currentState = State_InTrailingWhiteSpace;
    }

    return isProcessed;
}

//! @brief Processes a character when in the State_InTrailingWhiteSpace state.
bool ScalarParser::handleInTrailingWhiteSpace(char32_t next)
{
    return CodePoint::isWhiteSpace(next);
}

//! @brief Determines if the specified state is valid for producing a scalar
//! value from the information gathered.
bool ScalarParser::isTerminalState(ScalarParser::State state)
{
    // NOTE: These values should be sorted into ascending order.
    State terminals[] = {
        State_AfterZeroPrefix,
        State_InWholeDigits,
        State_InFraction,
        State_InExponent,
        State_InTrailingWhiteSpace,
    };

    return std::binary_search(terminals, terminals + std::size(terminals), state);
}

//! @brief Raises a value to a power of 10.
//! @param[in] value The value to raise.
//! @param[in] power The power to raise it to.
//! @returns The value raised to the power.
int8_t ScalarParser::pow(int8_t value, int power)
{
    return raiseToPower(value, power);
}

//! @brief Raises a value to a power of 10.
//! @param[in] value The value to raise.
//! @param[in] power The power to raise it to.
//! @returns The value raised to the power.
uint8_t ScalarParser::pow(uint8_t value, int power)
{
    return raiseToPower(value, power);
}

//! @brief Raises a value to a power of 10.
//! @param[in] value The value to raise.
//! @param[in] power The power to raise it to.
//! @returns The value raised to the power.
int16_t ScalarParser::pow(int16_t value, int power)
{
    return raiseToPower(value, power);
}

//! @brief Raises a value to a power of 10.
//! @param[in] value The value to raise.
//! @param[in] power The power to raise it to.
//! @returns The value raised to the power.
uint16_t ScalarParser::pow(uint16_t value, int power)
{
    return raiseToPower(value, power);
}

//! @brief Raises a value to a power of 10.
//! @param[in] value The value to raise.
//! @param[in] power The power to raise it to.
//! @returns The value raised to the power.
int32_t ScalarParser::pow(int32_t value, int power)
{
    return raiseToPower(value, power);
}

//! @brief Raises a value to a power of 10.
//! @param[in] value The value to raise.
//! @param[in] power The power to raise it to.
//! @returns The value raised to the power.
uint32_t ScalarParser::pow(uint32_t value, int power)
{
    return raiseToPower(value, power);
}

//! @brief Raises a value to a power of 10.
//! @param[in] value The value to raise.
//! @param[in] power The power to raise it to.
//! @returns The value raised to the power.
int64_t ScalarParser::pow(int64_t value, int power)
{
    return raiseToPower(value, power);
}

//! @brief Raises a value to a power of 10.
//! @param[in] value The value to raise.
//! @param[in] power The power to raise it to.
//! @returns The value raised to the power.
uint64_t ScalarParser::pow(uint64_t value, int power)
{
    return raiseToPower(value, power);
}

//! @brief Raises a value to a power of 10.
//! @param[in] value The value to raise.
//! @param[in] power The power to raise it to.
//! @returns The value raised to the power.
float ScalarParser::pow(float value, int power)
{
    return std::pow(value, static_cast<float>(power));
}

//! @brief Raises a value to a power of 10.
//! @param[in] value The value to raise.
//! @param[in] power The power to raise it to.
//! @returns The value raised to the power.
double ScalarParser::pow(double value, int power)
{
    return std::pow(value, static_cast<double>(power));
}

} // namespace Ag
////////////////////////////////////////////////////////////////////////////////

