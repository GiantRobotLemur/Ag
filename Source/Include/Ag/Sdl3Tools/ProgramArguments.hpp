//! @file Ag/Sdl3Tools/ProgramArguments.hpp
//! @brief The declaration of standard tools for defining and interpreting
//! command line options to enumerate and select SDL3 devices.
//! @author GiantRobotLemur@na-se.co.uk
//! @date 2025-2026
//! @copyright This file is part of the Silver (Ag) project which is released
//! under LGPL 3 license. See LICENSE file at the repository root or go to
//! https://github.com/GiantRobotLemur/Ag for full license details.
////////////////////////////////////////////////////////////////////////////////

#ifndef __AG_SDL3_TOOLS_COMMAND_LINE_HPP__
#define __AG_SDL3_TOOLS_COMMAND_LINE_HPP__

////////////////////////////////////////////////////////////////////////////////
// Dependent Header Files
////////////////////////////////////////////////////////////////////////////////
#include <Ag/Core.hpp>

#include "DisplayModeSpec.hpp"

namespace Ag {
namespace SDL3 {

////////////////////////////////////////////////////////////////////////////////
// Data Type Declarations
////////////////////////////////////////////////////////////////////////////////
//! @brief Lists commands inferred from SDL command line options.
enum class SdlCommand : uint32_t
{
    //! @brief List object enumerated by SDL.
    ListObjects = Cli::StandardCommands::LastStdCommand,

    //! @brief The command ID to base additional standard commands on.
    LastSdlCommand,
};

//! @brief Defines identifiers for standard SDL command line options.
enum SdlOptions : uint32_t
{
    SdlList = Cli::StandardOptions::LastStdOption,
    SdlDisplayName,
    SdlDisplayMode,
    SdlDisplayDriver,

    //! @brief The option to use to base additional option definitions upon.
    SdlLastOption,
};

//! @brief Defines the set of SDL objects which can be listed.
enum class SdlObjectType
{
    //! @brief No object type specified.
    None,

    //! @brief Global values for the overall system.
    System,

    //! @brief The available video drivers.
    VideoDrivers,

    //! @brief The available render drivers.
    RenderDrivers,

    //! @brief The available GPU drivers.
    GPUDrivers,

    //! @brief The available displays.
    Displays,
};

////////////////////////////////////////////////////////////////////////////////
// Class Declarations
////////////////////////////////////////////////////////////////////////////////
//! @brief An object which defines and parses standard command line arguments.
class ProgramArguments : public Ag::Cli::ProgramArguments
{
public:
    // Construction/Destruction
    ProgramArguments();
    ProgramArguments(const Ag::Cli::SchemaBuilder &schema);
    virtual ~ProgramArguments() = default;

    // Accessors
    bool hasSDLCommand() const;
    bool isFullScreenPreferred() const;
    SdlObjectType getSDLListObjectType() const;
    string_cref_t getDisplayName() const;
    string_cref_t getDisplayDriverName() const;
    const DisplayModeSpec &getDisplayMode() const;

    bool tryFindDisplay(SDL_DisplayID &displayID) const;
    bool tryFindDisplayMode(SDL_DisplayID displayID, SDL_DisplayMode &mode) const;
    bool tryCreatePreferredRenderer(SDL_Window *window,
                                    SDL_Renderer *&renderer) const;
    bool tryCreatePreferredGPUDevice(SDL_GPUShaderFormat possibleFormats,
                                     bool enableDebugMode,
                                     SDL_GPUDevice *&device) const;

    // Operations
    String listSdlObjects(SdlObjectType objectType) const;

    // Overrides
    virtual bool hasStandardCommand() const override;
    virtual bool tryProcessStandardCommand() const override;
protected:
    virtual bool processOption(uint32_t id, const String &original,
                               const String &value, String &error) override;

    // Internal Functions
    void defineSDLSchema(Cli::SchemaBuilder &builder);
private:
    // Internal Fields
    SdlObjectType _objectToList;
    String _displayName;
    String _displayDriverName;
    DisplayModeSpec _displayMode;
};

}} // namespace Ag::SDL3

#endif // Header guard
////////////////////////////////////////////////////////////////////////////////
