//! @file Ag/ObjectGL/Extensions/IBMCommands.hpp
//! @brief The declaration of IBM-specific extensions to the OpenGL Command set
//! wrappers.
//! @author GiantRobotLemur@na-se.co.uk
//! @date 2025
//! @copyright This file is part of the Silver (Ag) project which is released
//! under LGPL 3 license. See LICENSE file at the repository root or go to
//! https://github.com/GiantRobotLemur/Ag for full license details.
//!
//! @note This contents of this file was generated from the Khronos XML API
//! definition using a bespoke code generation tool.
////////////////////////////////////////////////////////////////////////////////

#ifndef __AG_OBJECT_GL_IBM_COMMANDS_EXTENSIONS_HPP__
#define __AG_OBJECT_GL_IBM_COMMANDS_EXTENSIONS_HPP__

////////////////////////////////////////////////////////////////////////////////
// Dependent Header Files
////////////////////////////////////////////////////////////////////////////////
#include "../BaseTypes.hpp"
#include "../EnumTypes.hpp"
#include "IBM.hpp"

namespace gl {

////////////////////////////////////////////////////////////////////////////////
// Class Declarations
////////////////////////////////////////////////////////////////////////////////
// Manages the entry points for the GL_IBM_multimode_draw_arrays extension API.
class IBMMultimodeDrawArraysAPI : public BaseExtension
{
public:
    // Construction
    IBMMultimodeDrawArraysAPI();

    // Accessors
    const IBMMultimodeDrawArrays &getRawAPI() const;

    // Operations
    void multiModeDrawArrays(const PrimitiveType *mode, const GLint *first,
                             const GLsizei *count, GLsizei primcount,
                             GLint modestride) const;
    void multiModeDrawElements(const PrimitiveType *mode, const GLsizei *count,
                               DrawElementsType type, const void *const *indices,
                               GLsizei primcount, GLint modestride) const;

    // Overrides
    virtual void resolve(const APIResolver *resolver) override;

private:
    IBMMultimodeDrawArrays _api;
};

// Manages the entry points for the GL_IBM_static_data extension API.
class IBMStaticDataAPI : public BaseExtension
{
public:
    // Construction
    IBMStaticDataAPI();

    // Accessors
    const IBMStaticData &getRawAPI() const;

    // Operations
    void flushStaticData(GLenum target) const;

    // Overrides
    virtual void resolve(const APIResolver *resolver) override;

private:
    IBMStaticData _api;
};

// Manages the entry points for the GL_IBM_vertex_array_lists extension API.
class IBMVertexArrayListsAPI : public BaseExtension
{
public:
    // Construction
    IBMVertexArrayListsAPI();

    // Accessors
    const IBMVertexArrayLists &getRawAPI() const;

    // Operations
    void colorPointerList(GLint size, ColorPointerType type, GLint stride,
                          const void **pointer, GLint ptrstride) const;
    void edgeFlagPointerList(GLint stride, const GLboolean **pointer,
                             GLint ptrstride) const;
    void fogCoordPointerList(FogPointerTypeIBM type, GLint stride,
                             const void **pointer, GLint ptrstride) const;
    void indexPointerList(IndexPointerType type, GLint stride,
                          const void **pointer, GLint ptrstride) const;
    void normalPointerList(NormalPointerType type, GLint stride,
                           const void **pointer, GLint ptrstride) const;
    void secondaryColorPointerList(GLint size, SecondaryColorPointerTypeIBM type,
                                   GLint stride, const void **pointer,
                                   GLint ptrstride) const;
    void texCoordPointerList(GLint size, TexCoordPointerType type, GLint stride,
                             const void **pointer, GLint ptrstride) const;
    void vertexPointerList(GLint size, VertexPointerType type, GLint stride,
                           const void **pointer, GLint ptrstride) const;

    // Overrides
    virtual void resolve(const APIResolver *resolver) override;

private:
    IBMVertexArrayLists _api;
};

} // namespace gl

#endif // Header guard
////////////////////////////////////////////////////////////////////////////////
