//! @file Sdl3Tools/DisplayModeSpec.cpp
//! @brief The definition of an object used to specify a display mode.
//! @author GiantRobotLemur@na-se.co.uk
//! @date 2025
//! @copyright This file is part of the Silver (Ag) project which is released
//! under LGPL 3 license. See LICENSE file at the repository root or go to
//! https://github.com/GiantRobotLemur/Ag for full license details.
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Header File Includes
////////////////////////////////////////////////////////////////////////////////
#include "Ag/Sdl3Tools/DisplayModeSpec.hpp"

namespace Ag {
namespace SDL3 {

namespace {
////////////////////////////////////////////////////////////////////////////////
// Local Data Types
////////////////////////////////////////////////////////////////////////////////
enum class State
{
    BeforeWidth,
    AfterFirstWidthDigit,
    BeforeHeight,
    AfterFirstHeightDigit,
    BeforeBpp,
    AfterFirstBppDigit,
    BeforeRefresh,
    AfterFirstRefreshDigit,
    Complete,
};

////////////////////////////////////////////////////////////////////////////////
// Local Data
////////////////////////////////////////////////////////////////////////////////
constexpr char BppSeparator = '@';
constexpr char RefreshSeparator = ':';

} // Anonymous namespace

////////////////////////////////////////////////////////////////////////////////
// DisplayModeSpec Member Definitions
////////////////////////////////////////////////////////////////////////////////
//! @brief Constructs an display mode specification with not attributes specified.
DisplayModeSpec::DisplayModeSpec() :
    _width(-1),
    _height(-1),
    _bpp(-1),
    _refreshRate(-1)
{
}

//! @brief Constructs a display mode specification initialised with values.
//! @param[in] width The width of the display mode in pixels.
//! @param[in] height The height of the display mode in scan lines.
//! @param[in] bpp The count of bits per pixel, or a negative value if not specified.
//! @param[in] refreshRate The refresh rate in Hz, or negative if not specified.
DisplayModeSpec::DisplayModeSpec(int width, int height, int bpp /*= -1*/,
                                 int refreshRate /*= -1*/) :
    _width(width),
    _height(height),
    _bpp(bpp),
    _refreshRate(refreshRate)
{
}

//! @brief Sets the display mode width.
//! @param[in] widthInPixels The new required display mode width.
void DisplayModeSpec::setWidth(int widthInPixels) noexcept
{
    _width = widthInPixels;
}

//! @brief Sets the display mode height.
//! @param[in] heightInPixels The new display mode height in scan lines.
void DisplayModeSpec::setHeight(int heightInPixels) noexcept
{
    _height = heightInPixels;
}

//! @brief Sets the preferred count of bits per pixel.
//! @param[in] bitsPerPixel The new count of bits for each pixel or a negative
//! value to indicate no preference.
void DisplayModeSpec::setBpp(int bitsPerPixel) noexcept
{
    _bpp = bitsPerPixel;
}

//! @brief Sets the preferred display refresh rate.
//! @param[in] refreshRateInHz The preferred rate in Hz or a negative value to
//! indicate no preference.
void DisplayModeSpec::setRefreshRate(int refreshRateInHz) noexcept
{
    _refreshRate = refreshRateInHz;
}

//! @brief Attempts to initialise the object by parsing a string.
//! @param[in] text The text to parse.
//! @retval true If @p text represented a valid display mode specification and
//! the object values were updated.
//! @retval false If @p was not a valid display mode specification and the
//! object values remain unchanged.
bool DisplayModeSpec::tryParse(const std::string_view &text)
{
    int width, height, bpp, refresh;
    State state = State::BeforeWidth;
    bool isOK = false;

    // Set all values to an 'unset' value.
    width = height = bpp = refresh = -1;

    for (char next : text)
    {
        switch (state)
        {
        case State::BeforeWidth:
            if (std::isdigit(next))
            {
                width = next - '0';
                state = State::AfterFirstWidthDigit;
            }
            else if (std::isspace(next) == 0)
            {
                state = State::Complete;
            }
            break;

        case State::AfterFirstWidthDigit:
            if (std::isdigit(next))
            {
                int digit = next - '0';
                width = (width * 10) + digit;
            }
            else if ((next == 'X') || (next == 'x'))
            {
                state = State::BeforeHeight;
            }
            else
            {
                state = State::Complete;
            }
            break;

        case State::BeforeHeight:
            if (std::isdigit(next))
            {
                height = next - '0';
                state = State::AfterFirstHeightDigit;
                isOK = true;
            }
            else
            {
                state = State::Complete;
            }
            break;

        case State::AfterFirstHeightDigit:
            if (std::isdigit(next))
            {
                int digit = next - '0';
                height = (height * 10) + digit;
            }
            else if (next == BppSeparator)
            {
                state = State::BeforeBpp;
                isOK = false;
            }
            else if (next == RefreshSeparator)
            {
                state = State::BeforeRefresh;
                isOK = false;
            }
            else
            {
                state = State::Complete;
            }
            break;

        case State::BeforeBpp:
            if (std::isdigit(next))
            {
                bpp = next - '0';
                state = State::AfterFirstBppDigit;
                isOK = true;
            }
            else
            {
                state = State::Complete;
            }
            break;

        case State::AfterFirstBppDigit:
            if (std::isdigit(next))
            {
                int digit = next - '0';
                bpp = (bpp * 10) + digit;
            }
            else if (next == RefreshSeparator)
            {
                state = State::BeforeRefresh;
                isOK = false;
            }
            else
            {
                state = State::Complete;
            }
            break;

        case State::BeforeRefresh:
            if (std::isdigit(next))
            {
                refresh = next - '0';
                state = State::AfterFirstRefreshDigit;
                isOK = true;
            }
            else
            {
                state = State::Complete;
            }
            break;

        case State::AfterFirstRefreshDigit:
            if (std::isdigit(next))
            {
                int digit = next - '0';
                refresh = (refresh * 10) + digit;
            }
            else
            {
                state = State::Complete;
            }
            break;
        }

        if (state == State::Complete)
            break;
    }

    if (isOK)
    {
        _width = width;
        _height = height;
        _bpp = bpp;
        _refreshRate = refresh;
    }

    return isOK;
}

//! @brief Outputs the object value as a string.
//! @return A string representing the object value, empty if the object was
//! not initialised.
String DisplayModeSpec::toString() const
{
    if (isEmpty())
        return String::Empty;

    std::string buffer;
    buffer.reserve(24);

    FormatInfo format(LocaleInfo::getNeutral());

    appendValue(format, buffer, _width);
    buffer.push_back('x');
    appendValue(format, buffer, _height);

    if (_bpp > 0)
    {
        buffer.push_back(BppSeparator);
        appendValue(format, buffer, _bpp);
    }

    if (_refreshRate > 0)
    {
        buffer.push_back(RefreshSeparator);
        appendValue(format, buffer, _refreshRate);
    }

    return buffer;
}

}} // namespace Ag::SDL3
////////////////////////////////////////////////////////////////////////////////

