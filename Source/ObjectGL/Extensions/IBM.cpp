//! @file ObjectGL/Extensions/IBM.cpp
//! @brief The definition of IBM-specific extensions to the OpenGL API.
//! @author GiantRobotLemur@na-se.co.uk
//! @date 2025
//! @copyright This file is part of the Silver (Ag) project which is released
//! under LGPL 3 license. See LICENSE file at the repository root or go to
//! https://github.com/GiantRobotLemur/Ag for full license details.
//!
//! @note This contents of this file was generated from the Khronos XML API
//! definition using a bespoke code generation tool.
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Header File Includes
////////////////////////////////////////////////////////////////////////////////
#include "Ag/ObjectGL/Extensions/IBM.hpp"

namespace gl {

namespace {

////////////////////////////////////////////////////////////////////////////////
// Local Data
////////////////////////////////////////////////////////////////////////////////
static const EntryOffset __IBMMultimodeDrawArraysEntryPoints[] = {
    { offsetof(IBMMultimodeDrawArrays, glMultiModeDrawArrays), "glMultiModeDrawArraysIBM" },
    { offsetof(IBMMultimodeDrawArrays, glMultiModeDrawElements), "glMultiModeDrawElementsIBM" },
};

static const EntryOffset __IBMStaticDataEntryPoints[] = {
    { offsetof(IBMStaticData, glFlushStaticData), "glFlushStaticDataIBM" },
};

static const EntryOffset __IBMVertexArrayListsEntryPoints[] = {
    { offsetof(IBMVertexArrayLists, glColorPointerList), "glColorPointerListIBM" },
    { offsetof(IBMVertexArrayLists, glEdgeFlagPointerList), "glEdgeFlagPointerListIBM" },
    { offsetof(IBMVertexArrayLists, glFogCoordPointerList), "glFogCoordPointerListIBM" },
    { offsetof(IBMVertexArrayLists, glIndexPointerList), "glIndexPointerListIBM" },
    { offsetof(IBMVertexArrayLists, glNormalPointerList), "glNormalPointerListIBM" },
    { offsetof(IBMVertexArrayLists, glSecondaryColorPointerList), "glSecondaryColorPointerListIBM" },
    { offsetof(IBMVertexArrayLists, glTexCoordPointerList), "glTexCoordPointerListIBM" },
    { offsetof(IBMVertexArrayLists, glVertexPointerList), "glVertexPointerListIBM" },
};

} // Anonymous namespace

////////////////////////////////////////////////////////////////////////////////
// IBMMultimodeDrawArrays Member Definitions
////////////////////////////////////////////////////////////////////////////////
IBMMultimodeDrawArrays::IBMMultimodeDrawArrays()
{
    std::for_each_n(__IBMMultimodeDrawArraysEntryPoints,
                    std::size(__IBMMultimodeDrawArraysEntryPoints),
                    ClearEntryPoint(this));
}

bool IBMMultimodeDrawArrays::isPresent(const APIResolver *resolver) const
{
    return resolver->isExtensionPresent("GL_IBM_multimode_draw_arrays");
}

void IBMMultimodeDrawArrays::resolveEntryPoints(const APIResolver *resolver)
{
    std::for_each_n(__IBMMultimodeDrawArraysEntryPoints,
                    std::size(__IBMMultimodeDrawArraysEntryPoints),
                    ResolveEntryPoint(this, resolver));
}

////////////////////////////////////////////////////////////////////////////////
// IBMStaticData Member Definitions
////////////////////////////////////////////////////////////////////////////////
IBMStaticData::IBMStaticData()
{
    std::for_each_n(__IBMStaticDataEntryPoints,
                    std::size(__IBMStaticDataEntryPoints),
                    ClearEntryPoint(this));
}

bool IBMStaticData::isPresent(const APIResolver *resolver) const
{
    return resolver->isExtensionPresent("GL_IBM_static_data");
}

void IBMStaticData::resolveEntryPoints(const APIResolver *resolver)
{
    std::for_each_n(__IBMStaticDataEntryPoints,
                    std::size(__IBMStaticDataEntryPoints),
                    ResolveEntryPoint(this, resolver));
}

////////////////////////////////////////////////////////////////////////////////
// IBMVertexArrayLists Member Definitions
////////////////////////////////////////////////////////////////////////////////
IBMVertexArrayLists::IBMVertexArrayLists()
{
    std::for_each_n(__IBMVertexArrayListsEntryPoints,
                    std::size(__IBMVertexArrayListsEntryPoints),
                    ClearEntryPoint(this));
}

bool IBMVertexArrayLists::isPresent(const APIResolver *resolver) const
{
    return resolver->isExtensionPresent("GL_IBM_vertex_array_lists");
}

void IBMVertexArrayLists::resolveEntryPoints(const APIResolver *resolver)
{
    std::for_each_n(__IBMVertexArrayListsEntryPoints,
                    std::size(__IBMVertexArrayListsEntryPoints),
                    ResolveEntryPoint(this, resolver));
}

} // namespace gl
////////////////////////////////////////////////////////////////////////////////

