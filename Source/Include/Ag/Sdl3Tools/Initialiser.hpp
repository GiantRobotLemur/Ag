//! @file Ag/Sdl3Tools/Initialiser.hpp
//! @brief The declaration of an object which uses RAII to initialise and
//! properly shut down SDL sub-systems.
//! @author GiantRobotLemur@na-se.co.uk
//! @date 2023-2024
//! @copyright This file is part of the Silver (Ag) project which is released
//! under LGPL 3 license. See LICENSE file at the repository root or go to
//! https://github.com/GiantRobotLemur/Ag for full license details.
////////////////////////////////////////////////////////////////////////////////

#ifndef __AG_SDL3_TOOLS_INITIALISER_HPP__
#define __AG_SDL3_TOOLS_INITIALISER_HPP__

////////////////////////////////////////////////////////////////////////////////
// Dependent Header Files
////////////////////////////////////////////////////////////////////////////////
#include <cstdint>

#include <SDL3/SDL.h>

namespace Ag {

//! @brief A namespace which encapsulates utilities for operating with libSDL2
//! (Simple Direct Media Layer - version 3) library.
namespace SDL3 {

////////////////////////////////////////////////////////////////////////////////
// Class Declarations
////////////////////////////////////////////////////////////////////////////////
//! @brief An object which uses RAII to initialise and properly shut down SDL
//! sub-systems.
class Initialiser
{
public:
    // Construction/Destruction
    Initialiser(uint32_t subSysFlags = SDL_INIT_VIDEO | SDL_INIT_EVENTS);
    ~Initialiser();

    // Accessors
    bool isInitialised() const;

    // Operations
    void addSubSystems(uint32_t subSystemFlags);
    void initialise();
    void shutdown();
private:
    // Internal Fields
    uint32_t _subSystemFlags;
    bool _isInitialised;
};

}} // namespace Ag::SDL3

#endif // Header guard
////////////////////////////////////////////////////////////////////////////////
