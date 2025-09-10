//! @file ObjectGL/Extensions/IBMCommands.cpp
//! @brief The definition of IBM-specific extensions to the OpenGL Command
//! set wrappers.
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
#include "Ag/ObjectGL/Extensions/IBMCommands.hpp"
#include "CommandSetTools.hpp"

namespace gl {

////////////////////////////////////////////////////////////////////////////////
// IBMMultimodeDrawArraysAPI Member Function Definitions
////////////////////////////////////////////////////////////////////////////////
// Construct an unresolved command set for the GL_IBM_multimode_draw_arrays extension.
IBMMultimodeDrawArraysAPI::IBMMultimodeDrawArraysAPI() :
    BaseExtension("GL_IBM_multimode_draw_arrays")
{
}

// Grant read-only access to the underlying function pointers.
const IBMMultimodeDrawArrays &IBMMultimodeDrawArraysAPI::getRawAPI() const
{
    return _api;
}

// Resolve the GL_IBM_multimode_draw_arrays entry points.
void IBMMultimodeDrawArraysAPI::resolve(const APIResolver *resolver)
{
    if (resolver != nullptr)
    {
        _api.resolveEntryPoints(resolver);

        // Call the base class.
        BaseExtension::resolve(resolver);
    }
}

// Calls glMultiModeDrawArraysIBM().
void IBMMultimodeDrawArraysAPI::multiModeDrawArrays(const PrimitiveType *mode,
                                                    const GLint *first,
                                                    const GLsizei *count,
                                                    GLsizei primcount,
                                                    GLint modestride) const
{
    static const char *fnName = "glMultiModeDrawArraysIBM";

    beforeCommand(fnName, _api.glMultiModeDrawArrays);
    _api.glMultiModeDrawArrays(toScalarPtr(mode), first, count, primcount,
                               modestride);
    afterCommand(fnName);
}

// Calls glMultiModeDrawElementsIBM().
void IBMMultimodeDrawArraysAPI::multiModeDrawElements(const PrimitiveType *mode,
                                                      const GLsizei *count,
                                                      DrawElementsType type,
                                                      const void *const *indices,
                                                      GLsizei primcount,
                                                      GLint modestride) const
{
    static const char *fnName = "glMultiModeDrawElementsIBM";

    beforeCommand(fnName, _api.glMultiModeDrawElements);
    _api.glMultiModeDrawElements(toScalarPtr(mode), count, toScalar(type),
                                 indices, primcount, modestride);
    afterCommand(fnName);
}

////////////////////////////////////////////////////////////////////////////////
// IBMStaticDataAPI Member Function Definitions
////////////////////////////////////////////////////////////////////////////////
// Construct an unresolved command set for the GL_IBM_static_data extension.
IBMStaticDataAPI::IBMStaticDataAPI() :
    BaseExtension("GL_IBM_static_data")
{
}

// Grant read-only access to the underlying function pointers.
const IBMStaticData &IBMStaticDataAPI::getRawAPI() const
{
    return _api;
}

// Resolve the GL_IBM_static_data entry points.
void IBMStaticDataAPI::resolve(const APIResolver *resolver)
{
    if (resolver != nullptr)
    {
        _api.resolveEntryPoints(resolver);

        // Call the base class.
        BaseExtension::resolve(resolver);
    }
}

// Calls glFlushStaticDataIBM().
void IBMStaticDataAPI::flushStaticData(GLenum target) const
{
    static const char *fnName = "glFlushStaticDataIBM";

    beforeCommand(fnName, _api.glFlushStaticData);
    _api.glFlushStaticData(target);
    afterCommand(fnName);
}

////////////////////////////////////////////////////////////////////////////////
// IBMVertexArrayListsAPI Member Function Definitions
////////////////////////////////////////////////////////////////////////////////
// Construct an unresolved command set for the GL_IBM_vertex_array_lists extension.
IBMVertexArrayListsAPI::IBMVertexArrayListsAPI() :
    BaseExtension("GL_IBM_vertex_array_lists")
{
}

// Grant read-only access to the underlying function pointers.
const IBMVertexArrayLists &IBMVertexArrayListsAPI::getRawAPI() const
{
    return _api;
}

// Resolve the GL_IBM_vertex_array_lists entry points.
void IBMVertexArrayListsAPI::resolve(const APIResolver *resolver)
{
    if (resolver != nullptr)
    {
        _api.resolveEntryPoints(resolver);

        // Call the base class.
        BaseExtension::resolve(resolver);
    }
}

// Calls glColorPointerListIBM().
void IBMVertexArrayListsAPI::colorPointerList(GLint size, ColorPointerType type,
                                              GLint stride, const void **pointer,
                                              GLint ptrstride) const
{
    static const char *fnName = "glColorPointerListIBM";

    beforeCommand(fnName, _api.glColorPointerList);
    _api.glColorPointerList(size, toScalar(type), stride, pointer, ptrstride);
    afterCommand(fnName);
}

// Calls glEdgeFlagPointerListIBM().
void IBMVertexArrayListsAPI::edgeFlagPointerList(GLint stride,
                                                 const GLboolean **pointer,
                                                 GLint ptrstride) const
{
    static const char *fnName = "glEdgeFlagPointerListIBM";

    beforeCommand(fnName, _api.glEdgeFlagPointerList);
    _api.glEdgeFlagPointerList(stride, pointer, ptrstride);
    afterCommand(fnName);
}

// Calls glFogCoordPointerListIBM().
void IBMVertexArrayListsAPI::fogCoordPointerList(FogPointerTypeIBM type,
                                                 GLint stride,
                                                 const void **pointer,
                                                 GLint ptrstride) const
{
    static const char *fnName = "glFogCoordPointerListIBM";

    beforeCommand(fnName, _api.glFogCoordPointerList);
    _api.glFogCoordPointerList(toScalar(type), stride, pointer, ptrstride);
    afterCommand(fnName);
}

// Calls glIndexPointerListIBM().
void IBMVertexArrayListsAPI::indexPointerList(IndexPointerType type,
                                              GLint stride, const void **pointer,
                                              GLint ptrstride) const
{
    static const char *fnName = "glIndexPointerListIBM";

    beforeCommand(fnName, _api.glIndexPointerList);
    _api.glIndexPointerList(toScalar(type), stride, pointer, ptrstride);
    afterCommand(fnName);
}

// Calls glNormalPointerListIBM().
void IBMVertexArrayListsAPI::normalPointerList(NormalPointerType type,
                                               GLint stride,
                                               const void **pointer,
                                               GLint ptrstride) const
{
    static const char *fnName = "glNormalPointerListIBM";

    beforeCommand(fnName, _api.glNormalPointerList);
    _api.glNormalPointerList(toScalar(type), stride, pointer, ptrstride);
    afterCommand(fnName);
}

// Calls glSecondaryColorPointerListIBM().
void IBMVertexArrayListsAPI::secondaryColorPointerList(GLint size,
                                                       SecondaryColorPointerTypeIBM type,
                                                       GLint stride,
                                                       const void **pointer,
                                                       GLint ptrstride) const
{
    static const char *fnName = "glSecondaryColorPointerListIBM";

    beforeCommand(fnName, _api.glSecondaryColorPointerList);
    _api.glSecondaryColorPointerList(size, toScalar(type), stride, pointer,
                                     ptrstride);
    afterCommand(fnName);
}

// Calls glTexCoordPointerListIBM().
void IBMVertexArrayListsAPI::texCoordPointerList(GLint size,
                                                 TexCoordPointerType type,
                                                 GLint stride,
                                                 const void **pointer,
                                                 GLint ptrstride) const
{
    static const char *fnName = "glTexCoordPointerListIBM";

    beforeCommand(fnName, _api.glTexCoordPointerList);
    _api.glTexCoordPointerList(size, toScalar(type), stride, pointer, ptrstride);
    afterCommand(fnName);
}

// Calls glVertexPointerListIBM().
void IBMVertexArrayListsAPI::vertexPointerList(GLint size,
                                               VertexPointerType type,
                                               GLint stride,
                                               const void **pointer,
                                               GLint ptrstride) const
{
    static const char *fnName = "glVertexPointerListIBM";

    beforeCommand(fnName, _api.glVertexPointerList);
    _api.glVertexPointerList(size, toScalar(type), stride, pointer, ptrstride);
    afterCommand(fnName);
}

} // namespace gl
////////////////////////////////////////////////////////////////////////////////

