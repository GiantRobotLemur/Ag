//! @file ObjectGL/Extensions/Sun.cpp
//! @brief The definition of Sun Microsystems-specific extensions to the
//! OpenGL API.
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
#include "Ag/ObjectGL/Extensions/Sun.hpp"

namespace gl {

namespace {

////////////////////////////////////////////////////////////////////////////////
// Local Data
////////////////////////////////////////////////////////////////////////////////
static const EntryOffset __SUNXConstantDataEntryPoints[] = {
    { offsetof(SUNXConstantData, glFinishTexture), "glFinishTextureSUNX" },
};

static const EntryOffset __SUNGlobalAlphaEntryPoints[] = {
    { offsetof(SUNGlobalAlpha, glGlobalAlphaFactorb), "glGlobalAlphaFactorbSUN" },
    { offsetof(SUNGlobalAlpha, glGlobalAlphaFactord), "glGlobalAlphaFactordSUN" },
    { offsetof(SUNGlobalAlpha, glGlobalAlphaFactorf), "glGlobalAlphaFactorfSUN" },
    { offsetof(SUNGlobalAlpha, glGlobalAlphaFactori), "glGlobalAlphaFactoriSUN" },
    { offsetof(SUNGlobalAlpha, glGlobalAlphaFactors), "glGlobalAlphaFactorsSUN" },
    { offsetof(SUNGlobalAlpha, glGlobalAlphaFactorub), "glGlobalAlphaFactorubSUN" },
    { offsetof(SUNGlobalAlpha, glGlobalAlphaFactorui), "glGlobalAlphaFactoruiSUN" },
    { offsetof(SUNGlobalAlpha, glGlobalAlphaFactorus), "glGlobalAlphaFactorusSUN" },
};

static const EntryOffset __SUNMeshArrayEntryPoints[] = {
    { offsetof(SUNMeshArray, glDrawMeshArrays), "glDrawMeshArraysSUN" },
};

static const EntryOffset __SUNTriangleListEntryPoints[] = {
    { offsetof(SUNTriangleList, glReplacementCodePointer), "glReplacementCodePointerSUN" },
    { offsetof(SUNTriangleList, glReplacementCodeub), "glReplacementCodeubSUN" },
    { offsetof(SUNTriangleList, glReplacementCodeubv), "glReplacementCodeubvSUN" },
    { offsetof(SUNTriangleList, glReplacementCodeui), "glReplacementCodeuiSUN" },
    { offsetof(SUNTriangleList, glReplacementCodeuiv), "glReplacementCodeuivSUN" },
    { offsetof(SUNTriangleList, glReplacementCodeus), "glReplacementCodeusSUN" },
    { offsetof(SUNTriangleList, glReplacementCodeusv), "glReplacementCodeusvSUN" },
};

static const EntryOffset __SUNVertexEntryPoints[] = {
    { offsetof(SUNVertex, glColor3fVertex3f), "glColor3fVertex3fSUN" },
    { offsetof(SUNVertex, glColor3fVertex3fv), "glColor3fVertex3fvSUN" },
    { offsetof(SUNVertex, glColor4fNormal3fVertex3f), "glColor4fNormal3fVertex3fSUN" },
    { offsetof(SUNVertex, glColor4fNormal3fVertex3fv), "glColor4fNormal3fVertex3fvSUN" },
    { offsetof(SUNVertex, glColor4ubVertex2f), "glColor4ubVertex2fSUN" },
    { offsetof(SUNVertex, glColor4ubVertex2fv), "glColor4ubVertex2fvSUN" },
    { offsetof(SUNVertex, glColor4ubVertex3f), "glColor4ubVertex3fSUN" },
    { offsetof(SUNVertex, glColor4ubVertex3fv), "glColor4ubVertex3fvSUN" },
    { offsetof(SUNVertex, glNormal3fVertex3f), "glNormal3fVertex3fSUN" },
    { offsetof(SUNVertex, glNormal3fVertex3fv), "glNormal3fVertex3fvSUN" },
    { offsetof(SUNVertex, glReplacementCodeuiColor3fVertex3f), "glReplacementCodeuiColor3fVertex3fSUN" },
    { offsetof(SUNVertex, glReplacementCodeuiColor3fVertex3fv), "glReplacementCodeuiColor3fVertex3fvSUN" },
    { offsetof(SUNVertex, glReplacementCodeuiColor4fNormal3fVertex3f), "glReplacementCodeuiColor4fNormal3fVertex3fSUN" },
    { offsetof(SUNVertex, glReplacementCodeuiColor4fNormal3fVertex3fv), "glReplacementCodeuiColor4fNormal3fVertex3fvSUN" },
    { offsetof(SUNVertex, glReplacementCodeuiColor4ubVertex3f), "glReplacementCodeuiColor4ubVertex3fSUN" },
    { offsetof(SUNVertex, glReplacementCodeuiColor4ubVertex3fv), "glReplacementCodeuiColor4ubVertex3fvSUN" },
    { offsetof(SUNVertex, glReplacementCodeuiNormal3fVertex3f), "glReplacementCodeuiNormal3fVertex3fSUN" },
    { offsetof(SUNVertex, glReplacementCodeuiNormal3fVertex3fv), "glReplacementCodeuiNormal3fVertex3fvSUN" },
    { offsetof(SUNVertex, glReplacementCodeuiTexCoord2fColor4fNormal3fVertex3f), "glReplacementCodeuiTexCoord2fColor4fNormal3fVertex3fSUN" },
    { offsetof(SUNVertex, glReplacementCodeuiTexCoord2fColor4fNormal3fVertex3fv), "glReplacementCodeuiTexCoord2fColor4fNormal3fVertex3fvSUN" },
    { offsetof(SUNVertex, glReplacementCodeuiTexCoord2fNormal3fVertex3f), "glReplacementCodeuiTexCoord2fNormal3fVertex3fSUN" },
    { offsetof(SUNVertex, glReplacementCodeuiTexCoord2fNormal3fVertex3fv), "glReplacementCodeuiTexCoord2fNormal3fVertex3fvSUN" },
    { offsetof(SUNVertex, glReplacementCodeuiTexCoord2fVertex3f), "glReplacementCodeuiTexCoord2fVertex3fSUN" },
    { offsetof(SUNVertex, glReplacementCodeuiTexCoord2fVertex3fv), "glReplacementCodeuiTexCoord2fVertex3fvSUN" },
    { offsetof(SUNVertex, glReplacementCodeuiVertex3f), "glReplacementCodeuiVertex3fSUN" },
    { offsetof(SUNVertex, glReplacementCodeuiVertex3fv), "glReplacementCodeuiVertex3fvSUN" },
    { offsetof(SUNVertex, glTexCoord2fColor3fVertex3f), "glTexCoord2fColor3fVertex3fSUN" },
    { offsetof(SUNVertex, glTexCoord2fColor3fVertex3fv), "glTexCoord2fColor3fVertex3fvSUN" },
    { offsetof(SUNVertex, glTexCoord2fColor4fNormal3fVertex3f), "glTexCoord2fColor4fNormal3fVertex3fSUN" },
    { offsetof(SUNVertex, glTexCoord2fColor4fNormal3fVertex3fv), "glTexCoord2fColor4fNormal3fVertex3fvSUN" },
    { offsetof(SUNVertex, glTexCoord2fColor4ubVertex3f), "glTexCoord2fColor4ubVertex3fSUN" },
    { offsetof(SUNVertex, glTexCoord2fColor4ubVertex3fv), "glTexCoord2fColor4ubVertex3fvSUN" },
    { offsetof(SUNVertex, glTexCoord2fNormal3fVertex3f), "glTexCoord2fNormal3fVertex3fSUN" },
    { offsetof(SUNVertex, glTexCoord2fNormal3fVertex3fv), "glTexCoord2fNormal3fVertex3fvSUN" },
    { offsetof(SUNVertex, glTexCoord2fVertex3f), "glTexCoord2fVertex3fSUN" },
    { offsetof(SUNVertex, glTexCoord2fVertex3fv), "glTexCoord2fVertex3fvSUN" },
    { offsetof(SUNVertex, glTexCoord4fColor4fNormal3fVertex4f), "glTexCoord4fColor4fNormal3fVertex4fSUN" },
    { offsetof(SUNVertex, glTexCoord4fColor4fNormal3fVertex4fv), "glTexCoord4fColor4fNormal3fVertex4fvSUN" },
    { offsetof(SUNVertex, glTexCoord4fVertex4f), "glTexCoord4fVertex4fSUN" },
    { offsetof(SUNVertex, glTexCoord4fVertex4fv), "glTexCoord4fVertex4fvSUN" },
};

} // Anonymous namespace

////////////////////////////////////////////////////////////////////////////////
// SUNXConstantData Member Definitions
////////////////////////////////////////////////////////////////////////////////
SUNXConstantData::SUNXConstantData()
{
    std::for_each_n(__SUNXConstantDataEntryPoints,
                    std::size(__SUNXConstantDataEntryPoints),
                    ClearEntryPoint(this));
}

bool SUNXConstantData::isPresent(const APIResolver *resolver) const
{
    return resolver->isExtensionPresent("GL_SUNX_constant_data");
}

void SUNXConstantData::resolveEntryPoints(const APIResolver *resolver)
{
    std::for_each_n(__SUNXConstantDataEntryPoints,
                    std::size(__SUNXConstantDataEntryPoints),
                    ResolveEntryPoint(this, resolver));
}

////////////////////////////////////////////////////////////////////////////////
// SUNGlobalAlpha Member Definitions
////////////////////////////////////////////////////////////////////////////////
SUNGlobalAlpha::SUNGlobalAlpha()
{
    std::for_each_n(__SUNGlobalAlphaEntryPoints,
                    std::size(__SUNGlobalAlphaEntryPoints),
                    ClearEntryPoint(this));
}

bool SUNGlobalAlpha::isPresent(const APIResolver *resolver) const
{
    return resolver->isExtensionPresent("GL_SUN_global_alpha");
}

void SUNGlobalAlpha::resolveEntryPoints(const APIResolver *resolver)
{
    std::for_each_n(__SUNGlobalAlphaEntryPoints,
                    std::size(__SUNGlobalAlphaEntryPoints),
                    ResolveEntryPoint(this, resolver));
}

////////////////////////////////////////////////////////////////////////////////
// SUNMeshArray Member Definitions
////////////////////////////////////////////////////////////////////////////////
SUNMeshArray::SUNMeshArray()
{
    std::for_each_n(__SUNMeshArrayEntryPoints,
                    std::size(__SUNMeshArrayEntryPoints),
                    ClearEntryPoint(this));
}

bool SUNMeshArray::isPresent(const APIResolver *resolver) const
{
    return resolver->isExtensionPresent("GL_SUN_mesh_array");
}

void SUNMeshArray::resolveEntryPoints(const APIResolver *resolver)
{
    std::for_each_n(__SUNMeshArrayEntryPoints,
                    std::size(__SUNMeshArrayEntryPoints),
                    ResolveEntryPoint(this, resolver));
}

////////////////////////////////////////////////////////////////////////////////
// SUNTriangleList Member Definitions
////////////////////////////////////////////////////////////////////////////////
SUNTriangleList::SUNTriangleList()
{
    std::for_each_n(__SUNTriangleListEntryPoints,
                    std::size(__SUNTriangleListEntryPoints),
                    ClearEntryPoint(this));
}

bool SUNTriangleList::isPresent(const APIResolver *resolver) const
{
    return resolver->isExtensionPresent("GL_SUN_triangle_list");
}

void SUNTriangleList::resolveEntryPoints(const APIResolver *resolver)
{
    std::for_each_n(__SUNTriangleListEntryPoints,
                    std::size(__SUNTriangleListEntryPoints),
                    ResolveEntryPoint(this, resolver));
}

////////////////////////////////////////////////////////////////////////////////
// SUNVertex Member Definitions
////////////////////////////////////////////////////////////////////////////////
SUNVertex::SUNVertex()
{
    std::for_each_n(__SUNVertexEntryPoints,
                    std::size(__SUNVertexEntryPoints),
                    ClearEntryPoint(this));
}

bool SUNVertex::isPresent(const APIResolver *resolver) const
{
    return resolver->isExtensionPresent("GL_SUN_vertex");
}

void SUNVertex::resolveEntryPoints(const APIResolver *resolver)
{
    std::for_each_n(__SUNVertexEntryPoints,
                    std::size(__SUNVertexEntryPoints),
                    ResolveEntryPoint(this, resolver));
}

} // namespace gl


#ifdef _USES_GLX
namespace glx {
namespace {

static const gl::EntryOffset __SUNGetTransparentIndexEntryPoints[] = {
    { offsetof(SUNGetTransparentIndex, glXGetTransparentIndex), "glXGetTransparentIndexSUN" },
};

} // Anonymous namespace

////////////////////////////////////////////////////////////////////////////////
// SUNGetTransparentIndex Member Definitions
////////////////////////////////////////////////////////////////////////////////
SUNGetTransparentIndex::SUNGetTransparentIndex()
{
    std::for_each_n(__SUNGetTransparentIndexEntryPoints,
                    std::size(__SUNGetTransparentIndexEntryPoints),
                    gl::ClearEntryPoint(this));
}

bool SUNGetTransparentIndex::isPresent(const APIResolver *resolver) const
{
    return resolver->isExtensionPresent("GLX_SUN_get_transparent_index");
}

void SUNGetTransparentIndex::resolveEntryPoints(const APIResolver *resolver)
{
    std::for_each_n(__SUNGetTransparentIndexEntryPoints,
                    std::size(__SUNGetTransparentIndexEntryPoints),
                    gl::ResolveEntryPoint(this, resolver));
}

} // namespace glx
#endif // ifdef _USES_GLX
////////////////////////////////////////////////////////////////////////////////

