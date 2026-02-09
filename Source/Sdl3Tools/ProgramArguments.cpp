//! @file Sdl3Tools/ProgramArguments.cpp
//! @brief The definition of standard tools for defining and interpreting
//! command line options to enumerate and select SDL3 devices.
//! @author GiantRobotLemur@na-se.co.uk
//! @date 2025-2026
//! @copyright This file is part of the Silver (Ag) project which is released
//! under LGPL 3 license. See LICENSE file at the repository root or go to
//! https://github.com/GiantRobotLemur/Ag for full license details.
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Header File Includes
////////////////////////////////////////////////////////////////////////////////
#include "Ag/Sdl3Tools/ProgramArguments.hpp"

namespace Ag {
namespace SDL3 {

namespace {
////////////////////////////////////////////////////////////////////////////////
// Local Data Types
////////////////////////////////////////////////////////////////////////////////
using SdlObjectTypeEnum = Ag::EnumInfo<SdlObjectType>;

////////////////////////////////////////////////////////////////////////////////
// Local Functions
////////////////////////////////////////////////////////////////////////////////
//! @brief Gets static metadata for the SdlObjectType enumeration.
const SdlObjectTypeEnum &getSdlObjectTypeMetadata()
{
    static SdlObjectTypeEnum metadata({
        STATIC_SCALAR_CLASS_DEF(SdlObjectType, System),
        STATIC_SCALAR_CLASS_DEF(SdlObjectType, VideoDrivers),
        STATIC_SCALAR_CLASS_DEF(SdlObjectType, RenderDrivers),
        STATIC_SCALAR_CLASS_DEF(SdlObjectType, GPUDrivers),
        STATIC_SCALAR_CLASS_DEF(SdlObjectType, Displays),
    });

    return metadata;
}

void appendPropertyTitle(std::string &buffer, const std::string_view &name,
                        size_t maxNameLength)
{
    size_t padding = (name.length() < maxNameLength) ? (maxNameLength - name.length()) : 0;

    buffer.append(name);
    buffer.push_back(':');
    buffer.append(padding, ' ');
}

void appendPropertyValue(std::string &buffer, const std::string_view &name,
                         const char *value, size_t maxNameLength)
{
    appendPropertyTitle(buffer, name, maxNameLength);
    buffer.append(Ag::Utf::isNullOrEmpty(value) ? "(none)" : value);
    buffer.push_back('\n');
}

template<typename T> 
void appendPropertyScalar(std::string &buffer, const std::string_view &name,
                          T value, size_t maxNameLength)
{
    appendPropertyTitle(buffer, name, maxNameLength);

    FormatInfo format(LocaleInfo::getNeutral());
    appendValue(format, buffer, value);
    buffer.push_back('\n');
}

void appendPropertyFileSize(std::string &buffer, const std::string_view &name,
                            uint64_t value, size_t maxNameLength)
{
    appendPropertyTitle(buffer, name, maxNameLength);

    FormatInfo format(LocaleInfo::getNeutral());
    format.setRequiredFractionDigits(0);
    appendFileSize(format, buffer, value);
    buffer.push_back('\n');
}

void appendPropertyBool(std::string &buffer, const std::string_view &name,
                        bool value, size_t maxNameLength)
{
    appendPropertyValue(buffer, name, value ? "true" : "false", maxNameLength);
}

void appendPropertyFormatted(std::string &buffer, const std::string_view &name,
                             size_t maxNameLength, const std::string_view &format,
                             const VariantList &items)
{
    appendPropertyTitle(buffer, name, maxNameLength);
    FormatInfo formatOptions(LocaleInfo::getNeutral());

    Ag::appendFormat(formatOptions, format, buffer, items);
    buffer.push_back('\n');
}

void appendListItem(std::string &buffer, const std::string_view &item, bool isPresent, bool &isFirst)
{
    if (isPresent == false)
        return;

    if (isFirst == false)
    {
        buffer.push_back(',');
        buffer.push_back(' ');
    }

    buffer.append(item);
    isFirst = false;
}

void appendListEnd(std::string &buffer, bool isFirst)
{
    if (isFirst)
        buffer.append("(none)");

    buffer.push_back('\n');
}

void appendTitle(std::string &buffer, const std::string_view &title)
{
    buffer.append(title);
    buffer.push_back('\n');
    buffer.append(title.length(), '-');
    buffer.append(2, '\n');
}

void listSystemProperties(std::string &buffer)
{
    appendTitle(buffer, "SDL System Properties");

    constexpr size_t MaxNameLength = 22;

    appendPropertyValue(buffer, "Platform", SDL_GetPlatform(), MaxNameLength);
    appendPropertyScalar(buffer, "Logical CPU Count", SDL_GetNumLogicalCPUCores(), MaxNameLength);
    appendPropertyFileSize(buffer, "System RAM", static_cast<uint64_t>(SDL_GetSystemRAM()) << 20, MaxNameLength);
    appendPropertyScalar(buffer, "SIMD Alignment", SDL_GetSIMDAlignment(), MaxNameLength);
    appendPropertyScalar(buffer, "CPU Cache Line Length", SDL_GetCPUCacheLineSize(), MaxNameLength);

    bool isFirst = true;
    appendPropertyTitle(buffer, "CPU Extensions", MaxNameLength);
    appendListItem(buffer, "AltiVec", SDL_HasAltiVec(), isFirst);
    appendListItem(buffer, "MMX", SDL_HasMMX(), isFirst);
    appendListItem(buffer, "SSE", SDL_HasSSE(), isFirst);
    appendListItem(buffer, "SSE 2", SDL_HasSSE2(), isFirst);
    appendListItem(buffer, "SSE 3", SDL_HasSSE3(), isFirst);
    appendListItem(buffer, "SSE 4.1", SDL_HasSSE41(), isFirst);
    appendListItem(buffer, "SSE 4.2", SDL_HasSSE42(), isFirst);
    appendListItem(buffer, "AVX", SDL_HasAVX(), isFirst);
    appendListItem(buffer, "AVX 2", SDL_HasAVX2(), isFirst);
    appendListItem(buffer, "AVX 512F", SDL_HasAVX512F(), isFirst);
    appendListItem(buffer, "ARM SIMD", SDL_HasARMSIMD(), isFirst);
    appendListItem(buffer, "LASX", SDL_HasLASX(), isFirst);
    appendListItem(buffer, "LSX", SDL_HasLSX(), isFirst);
    appendListItem(buffer, "NEON", SDL_HasNEON(), isFirst);
    appendListEnd(buffer, isFirst);

    int itemCount = 0;
    SDL_Locale **preferredLocales = SDL_GetPreferredLocales(&itemCount);

    if (preferredLocales != nullptr)
    {
        // Ensure the locales are freed.
        AtScopeExit1 freeLocales(SDL_free, preferredLocales);

        appendPropertyTitle(buffer, "Preferred Locales", MaxNameLength);

        for (int i = 0; i < itemCount; ++i)
        {
            if (i > 0)
            {
                buffer.push_back(',');
                buffer.push_back(' ');
            }

            buffer.append(preferredLocales[i]->language);
            buffer.push_back('-');
            buffer.append(preferredLocales[i]->country);
        }

        appendListEnd(buffer, itemCount == 0);
    }
}

void listVideoDrivers(std::string &buffer)
{
    appendTitle(buffer, "SDL Video Drivers");

    int count = SDL_GetNumVideoDrivers();

    for (int i = 0; i < count; ++i)
    {
        buffer.push_back('-');
        buffer.push_back(' ');
        buffer.append(SDL_GetVideoDriver(i));
        buffer.push_back('\n');
    }
}

void listRenderDrivers(std::string &buffer)
{
    appendTitle(buffer, "SDL Render Drivers");

    int count = SDL_GetNumRenderDrivers();

    for (int i = 0; i < count; ++i)
    {
        buffer.push_back('-');
        buffer.push_back(' ');
        buffer.append(SDL_GetRenderDriver(i));
        buffer.push_back('\n');
    }
}

void listGPUDrivers(std::string &buffer)
{
    appendTitle(buffer, "SDL GPU Drivers");

    int count = SDL_GetNumGPUDrivers();

    for (int i = 0; i < count; ++i)
    {
        buffer.push_back('-');
        buffer.push_back(' ');
        buffer.append(SDL_GetGPUDriver(i));
        buffer.push_back('\n');
    }
}

void listDisplays(std::string &buffer)
{
    appendTitle(buffer, "SDL Displays");

    constexpr size_t MaxNameLength = 15;

    int count = 0;
    SDL_DisplayID *displays = SDL_GetDisplays(&count);

    if (displays == nullptr)
    {
        appendListEnd(buffer, true);
        return;
    }

    AtScopeExit1 deleteDisplays(SDL_free, displays);
    SDL_DisplayID primaryID = SDL_GetPrimaryDisplay();

    for (int i = 0; i < count; ++i)
    {
        SDL_DisplayID id = displays[i];

        if (id == primaryID)
            appendPropertyFormatted(buffer, "ID", MaxNameLength, "{0} (primary)", { id });
        else
            appendPropertyScalar(buffer, "ID", id, MaxNameLength);

        appendPropertyValue(buffer, "  Name", SDL_GetDisplayName(id), MaxNameLength);

        Rect bounds;
        if (SDL_GetDisplayBounds(id, &bounds))
        {
            appendPropertyFormatted(buffer, "  Origin", MaxNameLength,
                                    "({0}, {1})", { bounds.x, bounds.y });
        }

        const SDL_DisplayMode *currentMode = SDL_GetCurrentDisplayMode(id);

        if (currentMode != nullptr)
        {
            appendPropertyFormatted(buffer, "  Size", MaxNameLength,
                                    "{0} x {1}", { currentMode->w, currentMode->h });
            appendPropertyFormatted(buffer, "  Refresh Rate", MaxNameLength,
                                    "{0:F0} Hz", { currentMode->refresh_rate });
        }

        int modeCount = 0;
        SDL_DisplayMode **modes = SDL_GetFullscreenDisplayModes(id, &modeCount);

        if (modes != nullptr)
        {
            // Ensure the modes list is disposed of.
            AtScopeExit1 deleteModes(SDL_free, modes);

            for (int j = 0; j < modeCount; ++j)
            {
                const SDL_DisplayMode *mode = modes[j];
                const auto *pixelFormat = SDL_GetPixelFormatDetails(mode->format);

                appendPropertyFormatted(buffer, "  Mode", MaxNameLength,
                                        "{0} x {1}, {2} bpp, {3:F0} Hz",
                                        { mode->w, mode->h,
                                          pixelFormat->bits_per_pixel,
                                          mode->refresh_rate });
            }
        }
    }
}

} // Anonymous namespace

////////////////////////////////////////////////////////////////////////////////
// ProgramArguments Member Definitions
////////////////////////////////////////////////////////////////////////////////
//! @brief Constructs an object to interpret program arguments including some
//! to support use of the SDL3 library.
ProgramArguments::ProgramArguments() :
    _objectToList(SdlObjectType::None)
{
    Ag::Cli::SchemaBuilder builder;

    defineSDLSchema(builder);

    // Update the schema with new options.
    setSchema(builder);
}

//! @brief Constructs an object to interpret program arguments including some
//! to support use of the SDL3 library.
//! @param[in] schema An object containing application command line argument
//! definitions to add SDL3-specific definitions to on order to fully define
//! the command line argument schema.
ProgramArguments::ProgramArguments(const Ag::Cli::SchemaBuilder &schema) :
    _objectToList(SdlObjectType::None)
{
    Ag::Cli::SchemaBuilder builder(schema);

    defineSDLSchema(builder);

    // Update the schema with new options.
    setSchema(builder);
}

//! @brief Determines if a built-in SDL command was selected.
//! @retval true A built-in SDL command was selected in command line arguments.
//! @retval false Some other command was selected in command line arguments.
bool ProgramArguments::hasSDLCommand() const
{
    return (getCommand() >= toScalar(SdlCommand::ListObjects)) &&
           (getCommand() < toScalar(SdlCommand::LastSdlCommand));
}

//! @brief Determines if command line options imply that the user wanted
//! a full-screen application window.
//! @retval true A specific display name or mode was requested, perhaps both.
//! @retval false The command line options did not include any exclusive
//! display-specific arguments.
bool ProgramArguments::isFullScreenPreferred() const
{
    return (_displayName.isEmpty() == false) ||
        (_displayMode.isEmpty() == false);
}

//! @brief Gets the type of object to be listed.
//! @return An object type or SdlObjectType::None if none was specified.
SdlObjectType ProgramArguments::getSDLListObjectType() const
{
    return _objectToList;
}

//! @brief Gets the name of the display specified on the command line.
//! @return The name of an SDL display, or an empty string if none was specified.
string_cref_t ProgramArguments::getDisplayName() const
{
    return _displayName;
}

//! @brief Gets the name of the display driver specified on the command line.
//! @return The name of a render or GPU driver or an empty string if no
//! display driver was specified.
string_cref_t ProgramArguments::getDisplayDriverName() const
{
    return _displayDriverName;
}

//! @brief Gets the specification of a display mode specified on the
//! command line.
//! @return An object describing the preferred display mode, in an
//! empty state if none was specified.
const DisplayModeSpec &ProgramArguments::getDisplayMode() const
{
    return _displayMode;
}

//! @brief Attempts to obtain the identifier of a display specified in
//! command line options.
//! @param[out] displayID The identifier of the selected display, if one
//! was specified, the identifier of the primary display, if not.
//! @retval true A display was specified and found, its ID returned.
//! @retval false No display was specified, or it could not be found, the
//! identifier of the primary display was returned.
bool ProgramArguments::tryFindDisplay(SDL_DisplayID &displayID) const
{
    displayID = SDL_GetPrimaryDisplay();

    if (_displayName.isEmpty())
        return false;

    int count;
    SDL_DisplayID *displays = SDL_GetDisplays(&count);

    if (displays == nullptr)
        return false;

    AtScopeExit1 deleteDisplays(SDL_free, displays);
    for (int i = 0; i < count; ++i)
    {
        SDL_DisplayID id = displays[i];
        String name = SDL_GetDisplayName(id);

        if (_displayName == name)
        {
            displayID = id;
            return true;
        }
    }

    return false;
}

//! @brief Attempts to find the display mode specified on the command line, if any.
//! @param[in] displayID The identifier of the display the mode is specific to.
//! @param[out] mode Receives details of the preferred display mode, if possible.
//! @retval true A mode was specified and found, @p mode was updated to describe
//! the selection.
//! @retval false Either no mode was specified or was but wasn't matched. @p mode
//! was updated with details of the desktop display mode.
bool ProgramArguments::tryFindDisplayMode(SDL_DisplayID displayID,
                                              SDL_DisplayMode &mode) const
{
    const SDL_DisplayMode *selectedMode = nullptr;

    if (_displayMode.isEmpty())
    {
        selectedMode = SDL_GetCurrentDisplayMode(displayID);

        if (selectedMode == nullptr)
            throw ApiException("SDL_GetCurrentDisplayMode()");

        mode = *selectedMode;
        return true;
    }

    int modeCount = 0;
    SDL_DisplayMode **modes = SDL_GetFullscreenDisplayModes(displayID, &modeCount);

    if (modes != nullptr)
    {
        // Ensure the modes list is disposed of.
        AtScopeExit1 deleteModes(SDL_free, modes);
        int bestBpp = -1;

        for (int j = 0; j < modeCount; ++j)
        {
            const SDL_DisplayMode *modeInfo = modes[j];

            if ((modeInfo->w != _displayMode.getWidth()) ||
                (modeInfo->h != _displayMode.getHeight()))
                continue;

            if ((_displayMode.hasRefreshRate() == false) ||
                (_displayMode.getRefreshRate() != static_cast<int>(std::rint(modeInfo->refresh_rate))))
                continue;

            const auto *pixelFormat = SDL_GetPixelFormatDetails(modeInfo->format);

            if (_displayMode.hasBpp())
            {
                if (_displayMode.getBpp() != pixelFormat->bits_per_pixel)
                    continue;
            }
            else if (pixelFormat->bits_per_pixel < bestBpp)
            {
                continue;
            }

            bestBpp = pixelFormat->bits_per_pixel;
            selectedMode = modeInfo;
        }

        if (bestBpp >= 0)
        {
            mode = *selectedMode;
            return true;
        }
    }

    // If we get this far, we didn't find a matching mode.
    selectedMode = SDL_GetDesktopDisplayMode(displayID);

    if (selectedMode == nullptr)
        throw ApiException("SDL_GetDesktopDisplayMode(ID=0x{0:X2})", { displayID });

    return false;
}

//! @brief Attempts to create a renderer for a window based on command line
//! options specified.
//! @param[in] window The window to be rendered to.
//! @param[out] renderer Receives a pointer to the newly created renderer.
//! @retval true A render driver was specified and successfully created.
//! @retval false No renderer was specified or creation failed.
bool ProgramArguments::tryCreatePreferredRenderer(SDL_Window *window,
                                                      SDL_Renderer *&renderer) const
{
    renderer = nullptr;

    if (_displayDriverName.isEmpty())
        return false;

    int count = SDL_GetNumRenderDrivers();

    for (int i = 0; i < count; ++i)
    {
        const char *driverName = SDL_GetRenderDriver(i);

        if (_displayDriverName == driverName)
        {
            // We found a driver which matches the name.
            renderer = SDL_CreateRenderer(window, driverName);

            return renderer != nullptr;
        }
    }

    return false;
}

//! @brief Attempts to create a GPU device using the driver named in
//! command line options.
//! @param[in] possibleFormats The set of shader format which could be used.
//! @param[in] enableDebugMode True to enable debug mode properties and
//! validations.
//! @param[out] device Receives the newly created device or nullptr.
//! @retval true A GPU driver was specified on the command line and
//! successfully used to instantiate a device.
//! @retval false Either no GPU driver was specified, or the device could
//! not be instantiated.
bool ProgramArguments::tryCreatePreferredGPUDevice(
    SDL_GPUShaderFormat possibleFormats,
    bool enableDebugMode,
    SDL_GPUDevice *&device) const
{
    device = nullptr;

    if (_displayDriverName.isEmpty())
        return false;

    int count = SDL_GetNumGPUDrivers();

    for (int i = 0; i < count; ++i)
    {
        const char *driverName = SDL_GetGPUDriver(i);

        if (_displayDriverName == driverName)
        {
            device = SDL_CreateGPUDevice(possibleFormats, enableDebugMode,
                                         driverName);

            return device != nullptr;
        }
    }

    return false;
}

//! @brief Generates text listing a set of available SDL objects.
//! @param[in] objectType The type of object to list.
//! @return Text listing and describing the specific types of object specified.
String ProgramArguments::listSdlObjects(SdlObjectType objectType) const
{
    std::string buffer;
    String initError;

    // We might need to temporarily initialise SDL components to enumerate
    // objects while processing this command.
    Initialiser initialiser;

    switch (objectType)
    {
    case SdlObjectType::System:
        listSystemProperties(buffer);
        break;

    case SdlObjectType::VideoDrivers:
        if (initialiser.tryInitialise(initError))
            listVideoDrivers(buffer);
        break;

    case SdlObjectType::RenderDrivers:
        if (initialiser.tryInitialise(initError))
            listRenderDrivers(buffer);
        break;

    case SdlObjectType::GPUDrivers:
        if (initialiser.tryInitialise(initError))
            listGPUDrivers(buffer);
        break;

    case SdlObjectType::Displays:
        if (initialiser.tryInitialise(initError))
            listDisplays(buffer);
        break;

    case SdlObjectType::None:
        break;
    }

    if (!initError.isEmpty())
    {
        // An error occurred while initialising SDL3 before enumerating
        // objects.
        buffer.assign("Failed to initialise SDL3: ");
        appendAgString(buffer, initError);
    }

    return String(buffer);
}

//! @brief Performs the SDL-specific command encoded in the last set of
//! command line arguments processed, if any.
//! @retval true A command was performed, the application should exit.
//! @retval false No command was performed, the application should continue
//! with normal execution.
bool ProgramArguments::tryProcessStandardCommand() const
{
    // Call the base class for standard commands.
    if (Cli::ProgramArguments::tryProcessStandardCommand())
        return true;

    if (getCommand() != toScalar(SdlCommand::ListObjects))
        return false;

    // Generate the list as text.
    String output = listSdlObjects(_objectToList);

    if (output.isEmpty())
        return false;

    // Output the text.
#ifdef _WIN32
    if (::IsDebuggerPresent())
    {
        std::wstring wideText;

        Utf::appendToWide(wideText, output.getUtf8Bytes(),
                          output.getUtf8Length(),
                          output.getWideLength() + 1);
        wideText.push_back(L'\n');
        ::OutputDebugStringW(wideText.c_str());
    }
#endif

    if (FILE *stdOut = App::getConsoleOutputStream())
    {
        fputc('\n', stdOut);
        fputs(output.getUtf8Bytes(), stdOut);
        fputc('\n', stdOut);
    }

    return true;
}

// Inherited from Ag::Cli::ProgramArguments
bool ProgramArguments::processOption(uint32_t id, const String &original,
                                     const String &value, String &error)
{
    bool isOK = true;

    switch (id)
    {
    case SdlOptions::SdlList:
        if (_objectToList != SdlObjectType::None)
        {
            error = "Only one type of SDL object can be specified for listing.";
            isOK = false;
        }
        else
        {
            SdlObjectType objType;

            if (getSdlObjectTypeMetadata().tryParse(value.toUtf8View(), objType))
            {
                setCommand(toScalar(SdlCommand::ListObjects));
                _objectToList = objType;
            }
            else
            {
                error = String::format("Unknown SDL object type '{0}' specified with {1} option.",
                                       { value, original });
                isOK = false;
            }
        }
        break;

    case SdlOptions::SdlDisplayName:
        if (_displayName.isEmpty())
        {
            _displayName = value;
        }
        else
        {
            error = "A display name has already been specified.";
            isOK = false;
        }
        break;

    case SdlOptions::SdlDisplayMode:
        if (_displayMode.isEmpty())
        {
            if (_displayMode.tryParse(value.toUtf8View()) == false)
            {
                std::string message;
                message.assign("The value '");
                message.append(value.toUtf8View());
                message.append("' did not represent a valid display mode specification.");
                error = message;
                isOK = false;
            }
        }
        else
        {
            error = "A display mode has already been specified.";
            isOK = false;
        }
        break;

    case SdlOptions::SdlDisplayDriver:
        if (_displayDriverName.isEmpty())
        {
            _displayDriverName = value;
        }
        else
        {
            error = "A display driver name has already been specified.";
            isOK = false;
        }
        break;

    default:
        // Have the base class try to process the option.
        isOK = Cli::ProgramArguments::processOption(id, original, value, error);
        break;
    }

    return isOK;
}

//! @brief Defines the standard command line options for an SDL3-based application.
//! @param[in] builder The object used to create a command line option schema.
void ProgramArguments::defineSDLSchema(Cli::SchemaBuilder &builder)
{
    // Generate help text to define what object types can be listed.
    std::string buffer;
    buffer.assign("List SDL runtime objects (");
    const auto &types = getSdlObjectTypeMetadata();
    bool isFirst = true;

    for (const auto &symbol : types.getSymbols())
    {
        if (isFirst)
        {
            isFirst = false;
        }
        else
        {
            buffer.push_back(',');
            buffer.push_back(' ');
        }

        buffer.append(symbol.getSymbol());
    }

    buffer.push_back(')');

    // Define SDL-specific operations.
    builder.defineOption(SdlList, buffer.c_str(), Cli::OptionValue::Mandatory,
                         "object type");

    builder.defineAlias(SdlList, "sdl_list");

    builder.defineOption(SdlDisplayName, "The name of the display to use.",
                         Cli::OptionValue::Mandatory, "display name");
    builder.defineAlias(SdlDisplayName, "sdl_display_name");

    builder.defineOption(SdlDisplayMode,
                         "The resolution of the display in the form "
                         "<w>x<h>[@<bpp>][:<refesh rate>].",
                         Cli::OptionValue::Mandatory, "mode spec");
    builder.defineAlias(SdlDisplayMode, "sdl_display_mode");

    builder.defineOption(SdlDisplayDriver,
                         "The display subsystem driver to use.",
                         Cli::OptionValue::Mandatory, "driver name");
    builder.defineAlias(SdlDisplayDriver, "sdl_display_driver");
}

}} // namespace Ag::SDL3
////////////////////////////////////////////////////////////////////////////////

