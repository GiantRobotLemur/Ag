//! @file Ag/ObjectGL.hpp
//! @brief Imports all public header files for the ObjectGL library.
//! @author GiantRobotLemur@na-se.co.uk
//! @date 2022-2025
//! @copyright This file is part of the Silver (Ag) project which is released
//! under LGPL 3 license. See LICENSE file at the repository root or go to
//! https://github.com/GiantRobotLemur/Ag for full license details.
////////////////////////////////////////////////////////////////////////////////

#ifndef __AG_OBJECT_GL_HPP__
#define __AG_OBJECT_GL_HPP__

////////////////////////////////////////////////////////////////////////////////
// Dependant Header Files
////////////////////////////////////////////////////////////////////////////////
#include "ObjectGL/Platform.hpp"

// Header files based on code generated from the Khronos OpenGL API registry.
#include "ObjectGL/BaseTypes.hpp"
#include "ObjectGL/EnumTypes.hpp"
#include "ObjectGL/APIs.hpp"

#include "ObjectGL/Extensions/3DFX.hpp"
#include "ObjectGL/Extensions/AMD.hpp"
#include "ObjectGL/Extensions/Apple.hpp"
#include "ObjectGL/Extensions/ARB.hpp"
#include "ObjectGL/Extensions/ATI.hpp"
#include "ObjectGL/Extensions/Ext.hpp"
#include "ObjectGL/Extensions/Gremedy.hpp"
#include "ObjectGL/Extensions/HP.hpp"
#include "ObjectGL/Extensions/IBM.hpp"
#include "ObjectGL/Extensions/Ingr.hpp"
#include "ObjectGL/Extensions/Intel.hpp"
#include "ObjectGL/Extensions/Khr.hpp"
#include "ObjectGL/Extensions/Mesa.hpp"
#include "ObjectGL/Extensions/NVidia.hpp"
#include "ObjectGL/Extensions/OES.hpp"
#include "ObjectGL/Extensions/OML.hpp"
#include "ObjectGL/Extensions/Ovr.hpp"
#include "ObjectGL/Extensions/PGI.hpp"
#include "ObjectGL/Extensions/SGI.hpp"
#include "ObjectGL/Extensions/Sun.hpp"

#include "ObjectGL/Identifiers.hpp"
#include "ObjectGL/CommandSets.hpp"

#include "ObjectGL/Extensions/3DFXCommands.hpp"
#include "ObjectGL/Extensions/AMDCommands.hpp"
#include "ObjectGL/Extensions/AppleCommands.hpp"
#include "ObjectGL/Extensions/ARBCommands.hpp"
#include "ObjectGL/Extensions/ATICommands.hpp"
#include "ObjectGL/Extensions/ExtCommands.hpp"
#include "ObjectGL/Extensions/GremedyCommands.hpp"
#include "ObjectGL/Extensions/HPCommands.hpp"
#include "ObjectGL/Extensions/IBMCommands.hpp"
#include "ObjectGL/Extensions/IngrCommands.hpp"
#include "ObjectGL/Extensions/IntelCommands.hpp"
#include "ObjectGL/Extensions/KhrCommands.hpp"
#include "ObjectGL/Extensions/MesaCommands.hpp"
#include "ObjectGL/Extensions/NVidiaCommands.hpp"
#include "ObjectGL/Extensions/OESCommands.hpp"
#include "ObjectGL/Extensions/OMLCommands.hpp"
#include "ObjectGL/Extensions/OvrCommands.hpp"
#include "ObjectGL/Extensions/PGICommands.hpp"
#include "ObjectGL/Extensions/SGICommands.hpp"
#include "ObjectGL/Extensions/SunCommands.hpp"

#ifdef _WIN32
#include "ObjectGL/WGL_API.hpp"
#include "ObjectGL/Extensions/3DLabs.hpp"
#include "ObjectGL/Extensions/Intense3D.hpp"
#include "ObjectGL/WGL_CommandSets.hpp"
#include "ObjectGL/Extensions/3DLabsCommands.hpp"
#include "ObjectGL/Extensions/Intense3DCommands.hpp"
#endif // ifdef _WIN32

// TODO: Replace this macro with the correct one throughout the
// library, when you figure out what it is.
#ifdef _USES_GLX
#include "ObjectGL/GLX_API.hpp"
#include "ObjectGL/GLX_CommandSets.hpp"
#endif // ifdef _USES_GLX

// Further headers which build on the generated API.
#include "ObjectGL/ExtensionSet.hpp"
#include "ObjectGL/APIResolvers.hpp"
#include "ObjectGL/OpenGLException.hpp"

#include "ObjectGL/ContextOptions.hpp"
#include "ObjectGL/DisplayFormat.hpp"
#include "ObjectGL/DisplayContext.hpp"
#include "ObjectGL/RenderContext.hpp"
#include "ObjectGL/Driver.hpp"

#ifdef _WIN32
#include "ObjectGL/WGLDriver.hpp"
#endif

#include "ObjectGL/ProgramBuilder.hpp"
#include "ObjectGL/Program.hpp"
#include "ObjectGL/BufferSchema.hpp"
#include "ObjectGL/Buffer.hpp"
#include "ObjectGL/Shader.hpp"


#endif // Header guard
////////////////////////////////////////////////////////////////////////////////
