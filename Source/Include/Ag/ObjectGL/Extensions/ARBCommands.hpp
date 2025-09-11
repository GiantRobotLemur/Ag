//! @file Ag/ObjectGL/Extensions/ARBCommands.hpp
//! @brief The declaration of Architecture Review Board (ARB) -specific
//! extensions to the OpenGL Command set wrappers.
//! @author GiantRobotLemur@na-se.co.uk
//! @date 2025
//! @copyright This file is part of the Silver (Ag) project which is released
//! under LGPL 3 license. See LICENSE file at the repository root or go to
//! https://github.com/GiantRobotLemur/Ag for full license details.
//!
//! @note This contents of this file was generated from the Khronos XML API
//! definition using a bespoke code generation tool.
////////////////////////////////////////////////////////////////////////////////

#ifndef __AG_OBJECT_GL_ARB_COMMANDS_EXTENSIONS_HPP__
#define __AG_OBJECT_GL_ARB_COMMANDS_EXTENSIONS_HPP__

////////////////////////////////////////////////////////////////////////////////
// Dependent Header Files
////////////////////////////////////////////////////////////////////////////////
#include "../BaseTypes.hpp"
#include "../EnumTypes.hpp"
#include "../Identifiers.hpp"
#include "ARB.hpp"

namespace gl {

////////////////////////////////////////////////////////////////////////////////
// Class Declarations
////////////////////////////////////////////////////////////////////////////////
// Manages the entry points for the GL_ARB_ES3_2_compatibility extension API.
class ARBES32CompatibilityAPI : public BaseExtension
{
public:
    // Construction
    ARBES32CompatibilityAPI();

    // Accessors
    const ARBES32Compatibility &getRawAPI() const;

    // Operations
    void primitiveBoundingBox(GLfloat minX, GLfloat minY, GLfloat minZ,
                              GLfloat minW, GLfloat maxX, GLfloat maxY,
                              GLfloat maxZ, GLfloat maxW) const;

    // Overrides
    virtual void resolve(const APIResolver *resolver) override;

private:
    ARBES32Compatibility _api;
};

// Manages the entry points for the GL_ARB_bindless_texture extension API.
class ARBBindlessTextureAPI : public BaseExtension
{
public:
    // Construction
    ARBBindlessTextureAPI();

    // Accessors
    const ARBBindlessTexture &getRawAPI() const;

    // Operations
    GLuint64 getImageHandle(TextureName texture, GLint level, Boolean layered,
                            GLint layer, PixelFormat format) const;
    GLuint64 getTextureHandle(TextureName texture) const;
    GLuint64 getTextureSamplerHandle(TextureName texture, SamplerName sampler) const;
    void getVertexAttribLUI64(GLuint index, VertexAttribEnum pname,
                              GLuint64EXT *params) const;
    Boolean isImageHandleResident(GLuint64 handle) const;
    Boolean isTextureHandleResident(GLuint64 handle) const;
    void makeImageHandleNonResident(GLuint64 handle) const;
    void makeImageHandleResident(GLuint64 handle, GLenum access) const;
    void makeTextureHandleNonResident(GLuint64 handle) const;
    void makeTextureHandleResident(GLuint64 handle) const;
    void programUniformHandleUI64(ProgramName program, GLint location,
                                  GLuint64 value) const;
    void programUniformHandleUI64(ProgramName program, GLint location,
                                  GLsizei count, const GLuint64 *values) const;
    void uniformHandleUI64(GLint location, GLuint64 value) const;
    void uniformHandleUI64(GLint location, GLsizei count, const GLuint64 *value) const;
    void vertexAttribL1UI64(GLuint index, GLuint64EXT x) const;
    void vertexAttribL1UI64(GLuint index, const GLuint64EXT *v) const;

    // Overrides
    virtual void resolve(const APIResolver *resolver) override;

private:
    ARBBindlessTexture _api;
};

// Manages the entry points for the GL_ARB_cl_event extension API.
class ARBClEventAPI : public BaseExtension
{
public:
    // Construction
    ARBClEventAPI();

    // Accessors
    const ARBClEvent &getRawAPI() const;

    // Operations
    SyncName createSyncFromCLevent(struct _cl_context *context,
                                   struct _cl_event *event, GLbitfield flags) const;

    // Overrides
    virtual void resolve(const APIResolver *resolver) override;

private:
    ARBClEvent _api;
};

// Manages the entry points for the GL_ARB_color_buffer_float extension API.
class ARBColorBufferFloatAPI : public BaseExtension
{
public:
    // Construction
    ARBColorBufferFloatAPI();

    // Accessors
    const ARBColorBufferFloat &getRawAPI() const;

    // Operations
    void clampColor(ClampColorTargetARB target, ClampColorModeARB clamp) const;

    // Overrides
    virtual void resolve(const APIResolver *resolver) override;

private:
    ARBColorBufferFloat _api;
};

// Manages the entry points for the GL_ARB_compute_variable_group_size extension API.
class ARBComputeVariableGroupSizeAPI : public BaseExtension
{
public:
    // Construction
    ARBComputeVariableGroupSizeAPI();

    // Accessors
    const ARBComputeVariableGroupSize &getRawAPI() const;

    // Operations
    void dispatchComputeGroupSize(GLuint num_groups_x, GLuint num_groups_y,
                                  GLuint num_groups_z, GLuint group_size_x,
                                  GLuint group_size_y, GLuint group_size_z) const;

    // Overrides
    virtual void resolve(const APIResolver *resolver) override;

private:
    ARBComputeVariableGroupSize _api;
};

// Manages the entry points for the GL_ARB_debug_output extension API.
class ARBDebugOutputAPI : public BaseExtension
{
public:
    // Construction
    ARBDebugOutputAPI();

    // Accessors
    const ARBDebugOutput &getRawAPI() const;

    // Operations
    void debugMessageCallback(GLDEBUGPROCARB callback, const void *userParam) const;
    void debugMessageControl(DebugSource source, DebugType type,
                             DebugSeverity severity, GLsizei count,
                             const GLuint *ids, Boolean enabled) const;
    void debugMessageInsert(DebugSource source, DebugType type, GLuint id,
                            DebugSeverity severity, GLsizei length,
                            const GLchar *buf) const;
    GLuint getDebugMessageLog(GLuint count, GLsizei bufSize,
                              DebugSource *sources, DebugType *types,
                              GLuint *ids, DebugSeverity *severities,
                              GLsizei *lengths, GLchar *messageLog) const;

    // Overrides
    virtual void resolve(const APIResolver *resolver) override;

private:
    ARBDebugOutput _api;
};

// Manages the entry points for the GL_ARB_draw_buffers extension API.
class ARBDrawBuffersAPI : public BaseExtension
{
public:
    // Construction
    ARBDrawBuffersAPI();

    // Accessors
    const ARBDrawBuffers &getRawAPI() const;

    // Operations
    void drawBuffers(GLsizei n, const DrawBufferMode *bufs) const;

    // Overrides
    virtual void resolve(const APIResolver *resolver) override;

private:
    ARBDrawBuffers _api;
};

// Manages the entry points for the GL_ARB_draw_buffers_blend extension API.
class ARBDrawBuffersBlendAPI : public BaseExtension
{
public:
    // Construction
    ARBDrawBuffersBlendAPI();

    // Accessors
    const ARBDrawBuffersBlend &getRawAPI() const;

    // Operations
    void blendEquationSeparateI(GLuint buf, BlendEquationModeEXT modeRGB,
                                BlendEquationModeEXT modeAlpha) const;
    void blendEquationI(GLuint buf, BlendEquationModeEXT mode) const;
    void blendFuncSeparateI(GLuint buf, BlendingFactor srcRGB,
                            BlendingFactor dstRGB, BlendingFactor srcAlpha,
                            BlendingFactor dstAlpha) const;
    void blendFuncI(GLuint buf, BlendingFactor src, BlendingFactor dst) const;

    // Overrides
    virtual void resolve(const APIResolver *resolver) override;

private:
    ARBDrawBuffersBlend _api;
};

// Manages the entry points for the GL_ARB_draw_instanced extension API.
class ARBDrawInstancedAPI : public BaseExtension
{
public:
    // Construction
    ARBDrawInstancedAPI();

    // Accessors
    const ARBDrawInstanced &getRawAPI() const;

    // Operations
    void drawArraysInstanced(PrimitiveType mode, GLint first, GLsizei count,
                             GLsizei primcount) const;
    void drawElementsInstanced(PrimitiveType mode, GLsizei count,
                               DrawElementsType type, const void *indices,
                               GLsizei primcount) const;

    // Overrides
    virtual void resolve(const APIResolver *resolver) override;

private:
    ARBDrawInstanced _api;
};

// Manages the entry points for the GL_ARB_fragment_program extension API.
class ARBFragmentProgramAPI : public BaseExtension
{
public:
    // Construction
    ARBFragmentProgramAPI();

    // Accessors
    const ARBFragmentProgram &getRawAPI() const;

    // Operations
    void bindProgram(ProgramTarget target, ProgramName program) const;
    void deletePrograms(GLsizei n, const ProgramName *programs) const;
    void genPrograms(GLsizei n, ProgramName *programs) const;
    void getProgramEnvParameterDV(ProgramTarget target, GLuint index,
                                  GLdouble *params) const;
    void getProgramEnvParameterFV(ProgramTarget target, GLuint index,
                                  GLfloat *params) const;
    void getProgramLocalParameterDV(ProgramTarget target, GLuint index,
                                    GLdouble *params) const;
    void getProgramLocalParameterFV(ProgramTarget target, GLuint index,
                                    GLfloat *params) const;
    void getProgramString(ProgramTarget target, ProgramStringProperty pname,
                          void *string) const;
    void getProgramIV(ProgramTarget target, ProgramProperty pname,
                      GLint *params) const;
    Boolean isProgram(ProgramName program) const;
    void programEnvParameter4D(ProgramTarget target, GLuint index, GLdouble x,
                               GLdouble y, GLdouble z, GLdouble w) const;
    void programEnvParameter4DV(ProgramTarget target, GLuint index,
                                const GLdouble *params) const;
    void programEnvParameter4F(ProgramTarget target, GLuint index, GLfloat x,
                               GLfloat y, GLfloat z, GLfloat w) const;
    void programEnvParameter4FV(ProgramTarget target, GLuint index,
                                const GLfloat *params) const;
    void programLocalParameter4D(ProgramTarget target, GLuint index, GLdouble x,
                                 GLdouble y, GLdouble z, GLdouble w) const;
    void programLocalParameter4DV(ProgramTarget target, GLuint index,
                                  const GLdouble *params) const;
    void programLocalParameter4F(ProgramTarget target, GLuint index, GLfloat x,
                                 GLfloat y, GLfloat z, GLfloat w) const;
    void programLocalParameter4FV(ProgramTarget target, GLuint index,
                                  const GLfloat *params) const;
    void programString(ProgramTarget target, ProgramFormat format, GLsizei len,
                       const void *string) const;

    // Overrides
    virtual void resolve(const APIResolver *resolver) override;

private:
    ARBFragmentProgram _api;
};

// Manages the entry points for the GL_ARB_geometry_shader4 extension API.
class ARBGeometrySHADER4API : public BaseExtension
{
public:
    // Construction
    ARBGeometrySHADER4API();

    // Accessors
    const ARBGeometrySHADER4 &getRawAPI() const;

    // Operations
    void framebufferTexture(FrameBufferTarget target,
                            FramebufferAttachment attachment,
                            TextureName texture, GLint level) const;
    void framebufferTextureFace(FrameBufferTarget target,
                                FramebufferAttachment attachment,
                                TextureName texture, GLint level,
                                TextureTarget face) const;
    void framebufferTextureLayer(FrameBufferTarget target,
                                 FramebufferAttachment attachment,
                                 TextureName texture, GLint level, GLint layer) const;
    void programParameterI(ProgramName program, ProgramParameterPName pname,
                           GLint value) const;

    // Overrides
    virtual void resolve(const APIResolver *resolver) override;

private:
    ARBGeometrySHADER4 _api;
};

// Manages the entry points for the GL_ARB_gl_spirv extension API.
class ARBGlSpirvAPI : public BaseExtension
{
public:
    // Construction
    ARBGlSpirvAPI();

    // Accessors
    const ARBGlSpirv &getRawAPI() const;

    // Operations
    void specializeShader(ShaderName shader, const GLchar *pEntryPoint,
                          GLuint numSpecializationConstants,
                          const GLuint *pConstantIndex,
                          const GLuint *pConstantValue) const;

    // Overrides
    virtual void resolve(const APIResolver *resolver) override;

private:
    ARBGlSpirv _api;
};

// Manages the entry points for the GL_ARB_gpu_shader_int64 extension API.
class ARBGPUShaderInt64API : public BaseExtension
{
public:
    // Construction
    ARBGPUShaderInt64API();

    // Accessors
    const ARBGPUShaderInt64 &getRawAPI() const;

    // Operations
    void getUniformI64V(ProgramName program, GLint location, GLint64 *params) const;
    void getUniformUI64(ProgramName program, GLint location, GLuint64 *params) const;
    void getnUniformI64V(ProgramName program, GLint location, GLsizei bufSize,
                         GLint64 *params) const;
    void getnUniformUI64(ProgramName program, GLint location, GLsizei bufSize,
                         GLuint64 *params) const;
    void programUniform1I64(ProgramName program, GLint location, GLint64 x) const;
    void programUniform1I64V(ProgramName program, GLint location, GLsizei count,
                             const GLint64 *value) const;
    void programUniform1UI64(ProgramName program, GLint location, GLuint64 x) const;
    void programUniform1UI64(ProgramName program, GLint location, GLsizei count,
                             const GLuint64 *value) const;
    void programUniform2I64(ProgramName program, GLint location, GLint64 x,
                            GLint64 y) const;
    void programUniform2I64V(ProgramName program, GLint location, GLsizei count,
                             const GLint64 *value) const;
    void programUniform2UI64(ProgramName program, GLint location, GLuint64 x,
                             GLuint64 y) const;
    void programUniform2UI64(ProgramName program, GLint location, GLsizei count,
                             const GLuint64 *value) const;
    void programUniform3I64(ProgramName program, GLint location, GLint64 x,
                            GLint64 y, GLint64 z) const;
    void programUniform3I64V(ProgramName program, GLint location, GLsizei count,
                             const GLint64 *value) const;
    void programUniform3UI64(ProgramName program, GLint location, GLuint64 x,
                             GLuint64 y, GLuint64 z) const;
    void programUniform3UI64(ProgramName program, GLint location, GLsizei count,
                             const GLuint64 *value) const;
    void programUniform4I64(ProgramName program, GLint location, GLint64 x,
                            GLint64 y, GLint64 z, GLint64 w) const;
    void programUniform4I64V(ProgramName program, GLint location, GLsizei count,
                             const GLint64 *value) const;
    void programUniform4UI64(ProgramName program, GLint location, GLuint64 x,
                             GLuint64 y, GLuint64 z, GLuint64 w) const;
    void programUniform4UI64(ProgramName program, GLint location, GLsizei count,
                             const GLuint64 *value) const;
    void uniform1I64(GLint location, GLint64 x) const;
    void uniform1I64V(GLint location, GLsizei count, const GLint64 *value) const;
    void uniform1UI64(GLint location, GLuint64 x) const;
    void uniform1UI64(GLint location, GLsizei count, const GLuint64 *value) const;
    void uniform2I64(GLint location, GLint64 x, GLint64 y) const;
    void uniform2I64V(GLint location, GLsizei count, const GLint64 *value) const;
    void uniform2UI64(GLint location, GLuint64 x, GLuint64 y) const;
    void uniform2UI64(GLint location, GLsizei count, const GLuint64 *value) const;
    void uniform3I64(GLint location, GLint64 x, GLint64 y, GLint64 z) const;
    void uniform3I64V(GLint location, GLsizei count, const GLint64 *value) const;
    void uniform3UI64(GLint location, GLuint64 x, GLuint64 y, GLuint64 z) const;
    void uniform3UI64(GLint location, GLsizei count, const GLuint64 *value) const;
    void uniform4I64(GLint location, GLint64 x, GLint64 y, GLint64 z, GLint64 w) const;
    void uniform4I64V(GLint location, GLsizei count, const GLint64 *value) const;
    void uniform4UI64(GLint location, GLuint64 x, GLuint64 y, GLuint64 z,
                      GLuint64 w) const;
    void uniform4UI64(GLint location, GLsizei count, const GLuint64 *value) const;

    // Overrides
    virtual void resolve(const APIResolver *resolver) override;

private:
    ARBGPUShaderInt64 _api;
};

// Manages the entry points for the GL_ARB_indirect_parameters extension API.
class ARBIndirectParametersAPI : public BaseExtension
{
public:
    // Construction
    ARBIndirectParametersAPI();

    // Accessors
    const ARBIndirectParameters &getRawAPI() const;

    // Operations
    void multiDrawArraysIndirectCount(PrimitiveType mode, const void *indirect,
                                      GLintptr drawcount, GLsizei maxdrawcount,
                                      GLsizei stride) const;
    void multiDrawElementsIndirectCount(PrimitiveType mode,
                                        DrawElementsType type,
                                        const void *indirect, GLintptr drawcount,
                                        GLsizei maxdrawcount, GLsizei stride) const;

    // Overrides
    virtual void resolve(const APIResolver *resolver) override;

private:
    ARBIndirectParameters _api;
};

// Manages the entry points for the GL_ARB_instanced_arrays extension API.
class ARBInstancedArraysAPI : public BaseExtension
{
public:
    // Construction
    ARBInstancedArraysAPI();

    // Accessors
    const ARBInstancedArrays &getRawAPI() const;

    // Operations
    void vertexAttribDivisor(GLuint index, GLuint divisor) const;

    // Overrides
    virtual void resolve(const APIResolver *resolver) override;

private:
    ARBInstancedArrays _api;
};

// Manages the entry points for the GL_ARB_matrix_palette extension API.
class ARBMatrixPaletteAPI : public BaseExtension
{
public:
    // Construction
    ARBMatrixPaletteAPI();

    // Accessors
    const ARBMatrixPalette &getRawAPI() const;

    // Operations
    void currentPaletteMatrix(GLint index) const;
    void matrixIndexPointer(GLint size, MatrixIndexPointerTypeARB type,
                            GLsizei stride, const void *pointer) const;
    void matrixIndexUBV(GLint size, const GLubyte *indices) const;
    void matrixIndexUIV(GLint size, const GLuint *indices) const;
    void matrixIndexUSV(GLint size, const GLushort *indices) const;

    // Overrides
    virtual void resolve(const APIResolver *resolver) override;

private:
    ARBMatrixPalette _api;
};

// Manages the entry points for the GL_ARB_multisample extension API.
class ARBMultisampleAPI : public BaseExtension
{
public:
    // Construction
    ARBMultisampleAPI();

    // Accessors
    const ARBMultisample &getRawAPI() const;

    // Operations
    void sampleCoverage(GLfloat value, Boolean invert) const;

    // Overrides
    virtual void resolve(const APIResolver *resolver) override;

private:
    ARBMultisample _api;
};

// Manages the entry points for the GL_ARB_multitexture extension API.
class ARBMultitextureAPI : public BaseExtension
{
public:
    // Construction
    ARBMultitextureAPI();

    // Accessors
    const ARBMultitexture &getRawAPI() const;

    // Operations
    void activeTexture(TextureUnit texture) const;
    void clientActiveTexture(TextureUnit texture) const;
    void multiTexCoord1D(TextureUnit target, GLdouble s) const;
    void multiTexCoord1DV(TextureUnit target, const GLdouble *v) const;
    void multiTexCoord1F(TextureUnit target, GLfloat s) const;
    void multiTexCoord1FV(TextureUnit target, const GLfloat *v) const;
    void multiTexCoord1I(TextureUnit target, GLint s) const;
    void multiTexCoord1IV(TextureUnit target, const GLint *v) const;
    void multiTexCoord1S(TextureUnit target, GLshort s) const;
    void multiTexCoord1SV(TextureUnit target, const GLshort *v) const;
    void multiTexCoord2D(TextureUnit target, GLdouble s, GLdouble t) const;
    void multiTexCoord2DV(TextureUnit target, const GLdouble *v) const;
    void multiTexCoord2F(TextureUnit target, GLfloat s, GLfloat t) const;
    void multiTexCoord2FV(TextureUnit target, const GLfloat *v) const;
    void multiTexCoord2I(TextureUnit target, GLint s, GLint t) const;
    void multiTexCoord2IV(TextureUnit target, const GLint *v) const;
    void multiTexCoord2S(TextureUnit target, GLshort s, GLshort t) const;
    void multiTexCoord2SV(TextureUnit target, const GLshort *v) const;
    void multiTexCoord3D(TextureUnit target, GLdouble s, GLdouble t, GLdouble r) const;
    void multiTexCoord3DV(TextureUnit target, const GLdouble *v) const;
    void multiTexCoord3F(TextureUnit target, GLfloat s, GLfloat t, GLfloat r) const;
    void multiTexCoord3FV(TextureUnit target, const GLfloat *v) const;
    void multiTexCoord3I(TextureUnit target, GLint s, GLint t, GLint r) const;
    void multiTexCoord3IV(TextureUnit target, const GLint *v) const;
    void multiTexCoord3S(TextureUnit target, GLshort s, GLshort t, GLshort r) const;
    void multiTexCoord3SV(TextureUnit target, const GLshort *v) const;
    void multiTexCoord4D(TextureUnit target, GLdouble s, GLdouble t, GLdouble r,
                         GLdouble q) const;
    void multiTexCoord4DV(TextureUnit target, const GLdouble *v) const;
    void multiTexCoord4F(TextureUnit target, GLfloat s, GLfloat t, GLfloat r,
                         GLfloat q) const;
    void multiTexCoord4FV(TextureUnit target, const GLfloat *v) const;
    void multiTexCoord4I(TextureUnit target, GLint s, GLint t, GLint r, GLint q) const;
    void multiTexCoord4IV(TextureUnit target, const GLint *v) const;
    void multiTexCoord4S(TextureUnit target, GLshort s, GLshort t, GLshort r,
                         GLshort q) const;
    void multiTexCoord4SV(TextureUnit target, const GLshort *v) const;

    // Overrides
    virtual void resolve(const APIResolver *resolver) override;

private:
    ARBMultitexture _api;
};

// Manages the entry points for the GL_ARB_occlusion_query extension API.
class ARBOcclusionQueryAPI : public BaseExtension
{
public:
    // Construction
    ARBOcclusionQueryAPI();

    // Accessors
    const ARBOcclusionQuery &getRawAPI() const;

    // Operations
    void beginQuery(QueryTarget target, QueryName id) const;
    void deleteQueries(GLsizei n, const QueryName *ids) const;
    void endQuery(QueryTarget target) const;
    void genQueries(GLsizei n, QueryName *ids) const;
    void getQueryObjectIV(QueryName id, QueryObjectParameterName pname,
                          GLint *params) const;
    void getQueryObjectUIV(QueryName id, QueryObjectParameterName pname,
                           GLuint *params) const;
    void getQueryIV(QueryTarget target, QueryParameterName pname, GLint *params) const;
    Boolean isQuery(QueryName id) const;

    // Overrides
    virtual void resolve(const APIResolver *resolver) override;

private:
    ARBOcclusionQuery _api;
};

// Manages the entry points for the GL_ARB_parallel_shader_compile extension API.
class ARBParallelShaderCompileAPI : public BaseExtension
{
public:
    // Construction
    ARBParallelShaderCompileAPI();

    // Accessors
    const ARBParallelShaderCompile &getRawAPI() const;

    // Operations
    void maxShaderCompilerThreads(GLuint count) const;

    // Overrides
    virtual void resolve(const APIResolver *resolver) override;

private:
    ARBParallelShaderCompile _api;
};

// Manages the entry points for the GL_ARB_point_parameters extension API.
class ARBPointParametersAPI : public BaseExtension
{
public:
    // Construction
    ARBPointParametersAPI();

    // Accessors
    const ARBPointParameters &getRawAPI() const;

    // Operations
    void pointParameterF(PointParameterNameARB pname, GLfloat param) const;
    void pointParameterFV(PointParameterNameARB pname, const GLfloat *params) const;

    // Overrides
    virtual void resolve(const APIResolver *resolver) override;

private:
    ARBPointParameters _api;
};

// Manages the entry points for the GL_ARB_robustness extension API.
class ARBRobustnessAPI : public BaseExtension
{
public:
    // Construction
    ARBRobustnessAPI();

    // Accessors
    const ARBRobustness &getRawAPI() const;

    // Operations
    GraphicsResetStatus getGraphicsResetStatus() const;
    void getnCompressedTexImage(TextureTarget target, GLint lod, GLsizei bufSize,
                                void *img) const;
    void getnTexImage(TextureTarget target, GLint level, PixelFormat format,
                      PixelType type, GLsizei bufSize, void *img) const;
    void getnUniformDV(ProgramName program, GLint location, GLsizei bufSize,
                       GLdouble *params) const;
    void getnUniformFV(ProgramName program, GLint location, GLsizei bufSize,
                       GLfloat *params) const;
    void getnUniformIV(ProgramName program, GLint location, GLsizei bufSize,
                       GLint *params) const;
    void getnUniformUIV(ProgramName program, GLint location, GLsizei bufSize,
                        GLuint *params) const;
    void readnPixels(GLint x, GLint y, GLsizei width, GLsizei height,
                     PixelFormat format, PixelType type, GLsizei bufSize,
                     void *data) const;

    // Overrides
    virtual void resolve(const APIResolver *resolver) override;

private:
    ARBRobustness _api;
};

// Manages the entry points for the GL_ARB_sample_locations extension API.
class ARBSampleLocationsAPI : public BaseExtension
{
public:
    // Construction
    ARBSampleLocationsAPI();

    // Accessors
    const ARBSampleLocations &getRawAPI() const;

    // Operations
    void evaluateDepthValues() const;
    void framebufferSampleLocationsFV(FrameBufferTarget target, GLuint start,
                                      GLsizei count, const GLfloat *v) const;
    void namedFramebufferSampleLocationsFV(FrameBufferName framebuffer,
                                           GLuint start, GLsizei count,
                                           const GLfloat *v) const;

    // Overrides
    virtual void resolve(const APIResolver *resolver) override;

private:
    ARBSampleLocations _api;
};

// Manages the entry points for the GL_ARB_sample_shading extension API.
class ARBSampleShadingAPI : public BaseExtension
{
public:
    // Construction
    ARBSampleShadingAPI();

    // Accessors
    const ARBSampleShading &getRawAPI() const;

    // Operations
    void minSampleShading(GLfloat value) const;

    // Overrides
    virtual void resolve(const APIResolver *resolver) override;

private:
    ARBSampleShading _api;
};

// Manages the entry points for the GL_ARB_shader_objects extension API.
class ARBShaderObjectsAPI : public BaseExtension
{
public:
    // Construction
    ARBShaderObjectsAPI();

    // Accessors
    const ARBShaderObjects &getRawAPI() const;

    // Operations
    void attachObject(GLhandleARB containerObj, GLhandleARB obj) const;
    void compileShader(GLhandleARB shaderObj) const;
    GLhandleARB createProgramObject() const;
    GLhandleARB createShaderObject(ShaderType shaderType) const;
    void deleteObject(GLhandleARB obj) const;
    void detachObject(GLhandleARB containerObj, GLhandleARB attachedObj) const;
    void getActiveUniform(GLhandleARB programObj, GLuint index,
                          GLsizei maxLength, GLsizei *length, GLint *size,
                          UniformType *type, GLcharARB *name) const;
    void getAttachedObjects(GLhandleARB containerObj, GLsizei maxCount,
                            GLsizei *count, GLhandleARB *obj) const;
    GLhandleARB getHandle(GLenum pname) const;
    void getInfoLog(GLhandleARB obj, GLsizei maxLength, GLsizei *length,
                    GLcharARB *infoLog) const;
    void getObjectParameterFV(GLhandleARB obj, GLenum pname, GLfloat *params) const;
    void getObjectParameterIV(GLhandleARB obj, GLenum pname, GLint *params) const;
    void getShaderSource(GLhandleARB obj, GLsizei maxLength, GLsizei *length,
                         GLcharARB *source) const;
    GLint getUniformLocation(GLhandleARB programObj, const GLcharARB *name) const;
    void getUniformFV(GLhandleARB programObj, GLint location, GLfloat *params) const;
    void getUniformIV(GLhandleARB programObj, GLint location, GLint *params) const;
    void linkProgram(GLhandleARB programObj) const;
    void shaderSource(GLhandleARB shaderObj, GLsizei count,
                      const GLcharARB **string, const GLint *length) const;
    void uniform1F(GLint location, GLfloat v0) const;
    void uniform1FV(GLint location, GLsizei count, const GLfloat *value) const;
    void uniform1I(GLint location, GLint v0) const;
    void uniform1IV(GLint location, GLsizei count, const GLint *value) const;
    void uniform2F(GLint location, GLfloat v0, GLfloat v1) const;
    void uniform2FV(GLint location, GLsizei count, const GLfloat *value) const;
    void uniform2I(GLint location, GLint v0, GLint v1) const;
    void uniform2IV(GLint location, GLsizei count, const GLint *value) const;
    void uniform3F(GLint location, GLfloat v0, GLfloat v1, GLfloat v2) const;
    void uniform3FV(GLint location, GLsizei count, const GLfloat *value) const;
    void uniform3I(GLint location, GLint v0, GLint v1, GLint v2) const;
    void uniform3IV(GLint location, GLsizei count, const GLint *value) const;
    void uniform4F(GLint location, GLfloat v0, GLfloat v1, GLfloat v2,
                   GLfloat v3) const;
    void uniform4FV(GLint location, GLsizei count, const GLfloat *value) const;
    void uniform4I(GLint location, GLint v0, GLint v1, GLint v2, GLint v3) const;
    void uniform4IV(GLint location, GLsizei count, const GLint *value) const;
    void uniformMatrix2FV(GLint location, GLsizei count, Boolean transpose,
                          const GLfloat *value) const;
    void uniformMatrix3FV(GLint location, GLsizei count, Boolean transpose,
                          const GLfloat *value) const;
    void uniformMatrix4FV(GLint location, GLsizei count, Boolean transpose,
                          const GLfloat *value) const;
    void useProgramObject(GLhandleARB programObj) const;
    void validateProgram(GLhandleARB programObj) const;

    // Overrides
    virtual void resolve(const APIResolver *resolver) override;

private:
    ARBShaderObjects _api;
};

// Manages the entry points for the GL_ARB_shading_language_include extension API.
class ARBShadingLanguageIncludeAPI : public BaseExtension
{
public:
    // Construction
    ARBShadingLanguageIncludeAPI();

    // Accessors
    const ARBShadingLanguageInclude &getRawAPI() const;

    // Operations
    void compileShaderInclude(ShaderName shader, GLsizei count,
                              const GLchar *const *path, const GLint *length) const;
    void deleteNamedString(GLint namelen, const GLchar *name) const;
    void getNamedString(GLint namelen, const GLchar *name, GLsizei bufSize,
                        GLint *stringlen, GLchar *string) const;
    void getNamedStringIV(GLint namelen, const GLchar *name, GLenum pname,
                          GLint *params) const;
    Boolean isNamedString(GLint namelen, const GLchar *name) const;
    void namedString(GLenum type, GLint namelen, const GLchar *name,
                     GLint stringlen, const GLchar *string) const;

    // Overrides
    virtual void resolve(const APIResolver *resolver) override;

private:
    ARBShadingLanguageInclude _api;
};

// Manages the entry points for the GL_ARB_sparse_buffer extension API.
class ARBSparseBufferAPI : public BaseExtension
{
public:
    // Construction
    ARBSparseBufferAPI();

    // Accessors
    const ARBSparseBuffer &getRawAPI() const;

    // Operations
    void bufferPageCommitment(GLenum target, GLintptr offset, GLsizeiptr size,
                              Boolean commit) const;
    void namedBufferPageCommitmentARB(BufferName buffer, GLintptr offset,
                                      GLsizeiptr size, Boolean commit) const;
    void namedBufferPageCommitmentEXT(BufferName buffer, GLintptr offset,
                                      GLsizeiptr size, Boolean commit) const;

    // Overrides
    virtual void resolve(const APIResolver *resolver) override;

private:
    ARBSparseBuffer _api;
};

// Manages the entry points for the GL_ARB_sparse_texture extension API.
class ARBSparseTextureAPI : public BaseExtension
{
public:
    // Construction
    ARBSparseTextureAPI();

    // Accessors
    const ARBSparseTexture &getRawAPI() const;

    // Operations
    void texPageCommitment(GLenum target, GLint level, GLint xoffset,
                           GLint yoffset, GLint zoffset, GLsizei width,
                           GLsizei height, GLsizei depth, Boolean commit) const;

    // Overrides
    virtual void resolve(const APIResolver *resolver) override;

private:
    ARBSparseTexture _api;
};

// Manages the entry points for the GL_ARB_texture_buffer_object extension API.
class ARBTextureBufferObjectAPI : public BaseExtension
{
public:
    // Construction
    ARBTextureBufferObjectAPI();

    // Accessors
    const ARBTextureBufferObject &getRawAPI() const;

    // Operations
    void texBuffer(TextureTarget target, SizedInternalFormat internalformat,
                   BufferName buffer) const;

    // Overrides
    virtual void resolve(const APIResolver *resolver) override;

private:
    ARBTextureBufferObject _api;
};

// Manages the entry points for the GL_ARB_texture_compression extension API.
class ARBTextureCompressionAPI : public BaseExtension
{
public:
    // Construction
    ARBTextureCompressionAPI();

    // Accessors
    const ARBTextureCompression &getRawAPI() const;

    // Operations
    void compressedTexImage1D(TextureTarget target, GLint level,
                              InternalFormat internalformat, GLsizei width,
                              GLint border, GLsizei imageSize, const void *data) const;
    void compressedTexImage2D(TextureTarget target, GLint level,
                              InternalFormat internalformat, GLsizei width,
                              GLsizei height, GLint border, GLsizei imageSize,
                              const void *data) const;
    void compressedTexImage3D(TextureTarget target, GLint level,
                              InternalFormat internalformat, GLsizei width,
                              GLsizei height, GLsizei depth, GLint border,
                              GLsizei imageSize, const void *data) const;
    void compressedTexSubImage1D(TextureTarget target, GLint level,
                                 GLint xoffset, GLsizei width,
                                 InternalFormat format, GLsizei imageSize,
                                 const void *data) const;
    void compressedTexSubImage2D(TextureTarget target, GLint level,
                                 GLint xoffset, GLint yoffset, GLsizei width,
                                 GLsizei height, InternalFormat format,
                                 GLsizei imageSize, const void *data) const;
    void compressedTexSubImage3D(TextureTarget target, GLint level,
                                 GLint xoffset, GLint yoffset, GLint zoffset,
                                 GLsizei width, GLsizei height, GLsizei depth,
                                 InternalFormat format, GLsizei imageSize,
                                 const void *data) const;
    void getCompressedTexImage(TextureTarget target, GLint level, void *img) const;

    // Overrides
    virtual void resolve(const APIResolver *resolver) override;

private:
    ARBTextureCompression _api;
};

// Manages the entry points for the GL_ARB_transpose_matrix extension API.
class ARBTransposeMatrixAPI : public BaseExtension
{
public:
    // Construction
    ARBTransposeMatrixAPI();

    // Accessors
    const ARBTransposeMatrix &getRawAPI() const;

    // Operations
    void loadTransposeMatrixD(const GLdouble *m) const;
    void loadTransposeMatrixF(const GLfloat *m) const;
    void multTransposeMatrixD(const GLdouble *m) const;
    void multTransposeMatrixF(const GLfloat *m) const;

    // Overrides
    virtual void resolve(const APIResolver *resolver) override;

private:
    ARBTransposeMatrix _api;
};

// Manages the entry points for the GL_ARB_vertex_blend extension API.
class ARBVertexBlendAPI : public BaseExtension
{
public:
    // Construction
    ARBVertexBlendAPI();

    // Accessors
    const ARBVertexBlend &getRawAPI() const;

    // Operations
    void vertexBlend(GLint count) const;
    void weightPointer(GLint size, WeightPointerTypeARB type, GLsizei stride,
                       const void *pointer) const;
    void weightBV(GLint size, const GLbyte *weights) const;
    void weightDV(GLint size, const GLdouble *weights) const;
    void weightFV(GLint size, const GLfloat *weights) const;
    void weightIV(GLint size, const GLint *weights) const;
    void weightSV(GLint size, const GLshort *weights) const;
    void weightUBV(GLint size, const GLubyte *weights) const;
    void weightUIV(GLint size, const GLuint *weights) const;
    void weightUSV(GLint size, const GLushort *weights) const;

    // Overrides
    virtual void resolve(const APIResolver *resolver) override;

private:
    ARBVertexBlend _api;
};

// Manages the entry points for the GL_ARB_vertex_buffer_object extension API.
class ARBVertexBufferObjectAPI : public BaseExtension
{
public:
    // Construction
    ARBVertexBufferObjectAPI();

    // Accessors
    const ARBVertexBufferObject &getRawAPI() const;

    // Operations
    void bindBuffer(BufferTarget target, BufferName buffer) const;
    void bufferData(BufferTarget target, GLsizeiptrARB size, const void *data,
                    BufferUsage usage) const;
    void bufferSubData(BufferTarget target, GLintptrARB offset,
                       GLsizeiptrARB size, const void *data) const;
    void deleteBuffers(GLsizei n, const BufferName *buffers) const;
    void genBuffers(GLsizei n, BufferName *buffers) const;
    void getBufferParameterIV(BufferTarget target, BufferPName pname,
                              GLint *params) const;
    void getBufferPointerV(BufferTarget target, BufferPointerName pname,
                           void **params) const;
    void getBufferSubData(BufferTarget target, GLintptrARB offset,
                          GLsizeiptrARB size, void *data) const;
    Boolean isBuffer(BufferName buffer) const;
    void *mapBuffer(BufferTarget target, BufferAccess access) const;
    Boolean unmapBuffer(BufferTarget target) const;

    // Overrides
    virtual void resolve(const APIResolver *resolver) override;

private:
    ARBVertexBufferObject _api;
};

// Manages the entry points for the GL_ARB_vertex_program extension API.
class ARBVertexProgramAPI : public BaseExtension
{
public:
    // Construction
    ARBVertexProgramAPI();

    // Accessors
    const ARBVertexProgram &getRawAPI() const;

    // Operations
    void disableVertexAttribArray(GLuint index) const;
    void enableVertexAttribArray(GLuint index) const;
    void getVertexAttribPointerV(GLuint index,
                                 VertexAttribPointerPropertyARB pname,
                                 void **pointer) const;
    void getVertexAttribDV(GLuint index, VertexAttribPropertyARB pname,
                           GLdouble *params) const;
    void getVertexAttribFV(GLuint index, VertexAttribPropertyARB pname,
                           GLfloat *params) const;
    void getVertexAttribIV(GLuint index, VertexAttribPropertyARB pname,
                           GLint *params) const;
    void vertexAttrib1D(GLuint index, GLdouble x) const;
    void vertexAttrib1DV(GLuint index, const GLdouble *v) const;
    void vertexAttrib1F(GLuint index, GLfloat x) const;
    void vertexAttrib1FV(GLuint index, const GLfloat *v) const;
    void vertexAttrib1S(GLuint index, GLshort x) const;
    void vertexAttrib1SV(GLuint index, const GLshort *v) const;
    void vertexAttrib2D(GLuint index, GLdouble x, GLdouble y) const;
    void vertexAttrib2DV(GLuint index, const GLdouble *v) const;
    void vertexAttrib2F(GLuint index, GLfloat x, GLfloat y) const;
    void vertexAttrib2FV(GLuint index, const GLfloat *v) const;
    void vertexAttrib2S(GLuint index, GLshort x, GLshort y) const;
    void vertexAttrib2SV(GLuint index, const GLshort *v) const;
    void vertexAttrib3D(GLuint index, GLdouble x, GLdouble y, GLdouble z) const;
    void vertexAttrib3DV(GLuint index, const GLdouble *v) const;
    void vertexAttrib3F(GLuint index, GLfloat x, GLfloat y, GLfloat z) const;
    void vertexAttrib3FV(GLuint index, const GLfloat *v) const;
    void vertexAttrib3S(GLuint index, GLshort x, GLshort y, GLshort z) const;
    void vertexAttrib3SV(GLuint index, const GLshort *v) const;
    void vertexAttrib4NBV(GLuint index, const GLbyte *v) const;
    void vertexAttrib4NIV(GLuint index, const GLint *v) const;
    void vertexAttrib4NSV(GLuint index, const GLshort *v) const;
    void vertexAttrib4NUB(GLuint index, GLubyte x, GLubyte y, GLubyte z,
                          GLubyte w) const;
    void vertexAttrib4NUBV(GLuint index, const GLubyte *v) const;
    void vertexAttrib4NUIV(GLuint index, const GLuint *v) const;
    void vertexAttrib4NUSV(GLuint index, const GLushort *v) const;
    void vertexAttrib4BV(GLuint index, const GLbyte *v) const;
    void vertexAttrib4D(GLuint index, GLdouble x, GLdouble y, GLdouble z,
                        GLdouble w) const;
    void vertexAttrib4DV(GLuint index, const GLdouble *v) const;
    void vertexAttrib4F(GLuint index, GLfloat x, GLfloat y, GLfloat z, GLfloat w) const;
    void vertexAttrib4FV(GLuint index, const GLfloat *v) const;
    void vertexAttrib4IV(GLuint index, const GLint *v) const;
    void vertexAttrib4S(GLuint index, GLshort x, GLshort y, GLshort z, GLshort w) const;
    void vertexAttrib4SV(GLuint index, const GLshort *v) const;
    void vertexAttrib4UBV(GLuint index, const GLubyte *v) const;
    void vertexAttrib4UIV(GLuint index, const GLuint *v) const;
    void vertexAttrib4USV(GLuint index, const GLushort *v) const;
    void vertexAttribPointer(GLuint index, GLint size,
                             VertexAttribPointerType type, Boolean normalized,
                             GLsizei stride, const void *pointer) const;

    // Overrides
    virtual void resolve(const APIResolver *resolver) override;

private:
    ARBVertexProgram _api;
};

// Manages the entry points for the GL_ARB_vertex_shader extension API.
class ARBVertexShaderAPI : public BaseExtension
{
public:
    // Construction
    ARBVertexShaderAPI();

    // Accessors
    const ARBVertexShader &getRawAPI() const;

    // Operations
    void bindAttribLocation(GLhandleARB programObj, GLuint index,
                            const GLcharARB *name) const;
    void getActiveAttrib(GLhandleARB programObj, GLuint index, GLsizei maxLength,
                         GLsizei *length, GLint *size, AttributeType *type,
                         GLcharARB *name) const;
    GLint getAttribLocation(GLhandleARB programObj, const GLcharARB *name) const;

    // Overrides
    virtual void resolve(const APIResolver *resolver) override;

private:
    ARBVertexShader _api;
};

// Manages the entry points for the GL_ARB_viewport_array extension API.
class ARBViewportArrayAPI : public BaseExtension
{
public:
    // Construction
    ARBViewportArrayAPI();

    // Accessors
    const ARBViewportArray &getRawAPI() const;

    // Operations
    void depthRangeArrayDV(GLuint first, GLsizei count, const GLdouble *v) const;
    void depthRangeIndexedD(GLuint index, GLdouble n, GLdouble f) const;

    // Overrides
    virtual void resolve(const APIResolver *resolver) override;

private:
    ARBViewportArray _api;
};

// Manages the entry points for the GL_ARB_window_pos extension API.
class ARBWindowPosAPI : public BaseExtension
{
public:
    // Construction
    ARBWindowPosAPI();

    // Accessors
    const ARBWindowPos &getRawAPI() const;

    // Operations
    void windowPOS2D(GLdouble x, GLdouble y) const;
    void windowPOS2DV(const GLdouble *v) const;
    void windowPOS2F(GLfloat x, GLfloat y) const;
    void windowPOS2FV(const GLfloat *v) const;
    void windowPOS2I(GLint x, GLint y) const;
    void windowPOS2IV(const GLint *v) const;
    void windowPOS2S(GLshort x, GLshort y) const;
    void windowPOS2SV(const GLshort *v) const;
    void windowPOS3D(GLdouble x, GLdouble y, GLdouble z) const;
    void windowPOS3DV(const GLdouble *v) const;
    void windowPOS3F(GLfloat x, GLfloat y, GLfloat z) const;
    void windowPOS3FV(const GLfloat *v) const;
    void windowPOS3I(GLint x, GLint y, GLint z) const;
    void windowPOS3IV(const GLint *v) const;
    void windowPOS3S(GLshort x, GLshort y, GLshort z) const;
    void windowPOS3SV(const GLshort *v) const;

    // Overrides
    virtual void resolve(const APIResolver *resolver) override;

private:
    ARBWindowPos _api;
};


} // namespace gl


#ifdef _WIN32
namespace wgl {

// Manages the entry points for the WGL_ARB_buffer_region extension API.
class ARBBufferRegionAPI : public gl::BaseExtension
{
public:
    // Construction
    ARBBufferRegionAPI();

    // Accessors
    const ARBBufferRegion &getRawAPI() const;

    // Operations
    HANDLE createBufferRegion(HDC hDC, int iLayerPlane, UINT uType) const;
    VOID deleteBufferRegion(HANDLE hRegion) const;
    BOOL restoreBufferRegion(HANDLE hRegion, int x, int y, int width, int height,
                             int xSrc, int ySrc) const;
    BOOL saveBufferRegion(HANDLE hRegion, int x, int y, int width, int height) const;

    // Overrides
    virtual void resolve(const APIResolver *resolver) override;

private:
    ARBBufferRegion _api;
};

// Manages the entry points for the WGL_ARB_create_context extension API.
class ARBCreateContextAPI : public gl::BaseExtension
{
public:
    // Construction
    ARBCreateContextAPI();

    // Accessors
    const ARBCreateContext &getRawAPI() const;

    // Operations
    HGLRC createContextAttribs(HDC hDC, HGLRC hShareContext,
                               const int *attribList) const;

    // Overrides
    virtual void resolve(const APIResolver *resolver) override;

private:
    ARBCreateContext _api;
};

// Manages the entry points for the WGL_ARB_extensions_string extension API.
class ARBExtensionsStringAPI : public gl::BaseExtension
{
public:
    // Construction
    ARBExtensionsStringAPI();

    // Accessors
    const ARBExtensionsString &getRawAPI() const;

    // Operations
    const char *getExtensionsString(HDC hdc) const;

    // Overrides
    virtual void resolve(const APIResolver *resolver) override;

private:
    ARBExtensionsString _api;
};

// Manages the entry points for the WGL_ARB_make_current_read extension API.
class ARBMakeCurrentReadAPI : public gl::BaseExtension
{
public:
    // Construction
    ARBMakeCurrentReadAPI();

    // Accessors
    const ARBMakeCurrentRead &getRawAPI() const;

    // Operations
    HDC getCurrentReadDC() const;
    BOOL makeContextCurrent(HDC hDrawDC, HDC hReadDC, HGLRC hglrc) const;

    // Overrides
    virtual void resolve(const APIResolver *resolver) override;

private:
    ARBMakeCurrentRead _api;
};

// Manages the entry points for the WGL_ARB_pbuffer extension API.
class ARBPbufferAPI : public gl::BaseExtension
{
public:
    // Construction
    ARBPbufferAPI();

    // Accessors
    const ARBPbuffer &getRawAPI() const;

    // Operations
    HPBUFFERARB createPbuffer(HDC hDC, int iPixelFormat, int iWidth, int iHeight,
                              const int *piAttribList) const;
    BOOL destroyPbuffer(HPBUFFERARB hPbuffer) const;
    HDC getPbufferDC(HPBUFFERARB hPbuffer) const;
    BOOL queryPbuffer(HPBUFFERARB hPbuffer, int iAttribute, int *piValue) const;
    int releasePbufferDC(HPBUFFERARB hPbuffer, HDC hDC) const;

    // Overrides
    virtual void resolve(const APIResolver *resolver) override;

private:
    ARBPbuffer _api;
};

// Manages the entry points for the WGL_ARB_pixel_format extension API.
class ARBPixelFormatAPI : public gl::BaseExtension
{
public:
    // Construction
    ARBPixelFormatAPI();

    // Accessors
    const ARBPixelFormat &getRawAPI() const;

    // Operations
    BOOL choosePixelFormat(HDC hdc, const int *piAttribIList,
                           const FLOAT *pfAttribFList, UINT nMaxFormats,
                           int *piFormats, UINT *nNumFormats) const;
    BOOL getPixelFormatAttribFV(HDC hdc, int iPixelFormat, int iLayerPlane,
                                UINT nAttributes, const int *piAttributes,
                                FLOAT *pfValues) const;
    BOOL getPixelFormatAttribIV(HDC hdc, int iPixelFormat, int iLayerPlane,
                                UINT nAttributes, const int *piAttributes,
                                int *piValues) const;

    // Overrides
    virtual void resolve(const APIResolver *resolver) override;

private:
    ARBPixelFormat _api;
};

// Manages the entry points for the WGL_ARB_render_texture extension API.
class ARBRenderTextureAPI : public gl::BaseExtension
{
public:
    // Construction
    ARBRenderTextureAPI();

    // Accessors
    const ARBRenderTexture &getRawAPI() const;

    // Operations
    BOOL bindTexImage(HPBUFFERARB hPbuffer, int iBuffer) const;
    BOOL releaseTexImage(HPBUFFERARB hPbuffer, int iBuffer) const;
    BOOL setPbufferAttrib(HPBUFFERARB hPbuffer, const int *piAttribList) const;

    // Overrides
    virtual void resolve(const APIResolver *resolver) override;

private:
    ARBRenderTexture _api;
};

} // namespace wgl
#endif // ifdef _WIN32

#ifdef _USES_GLX
namespace glx {

// Manages the entry points for the GLX_ARB_create_context extension API.
class ARBCreateContextAPI : public gl::BaseExtension
{
public:
    // Construction
    ARBCreateContextAPI();

    // Accessors
    const ARBCreateContext &getRawAPI() const;

    // Operations
    GLXContext xCreateContextAttribs(Display *dpy, GLXFBConfig config,
                                     GLXContext share_context, Bool direct,
                                     const int *attrib_list) const;

    // Overrides
    virtual void resolve(const APIResolver *resolver) override;

private:
    ARBCreateContext _api;
};

// Manages the entry points for the GLX_ARB_get_proc_address extension API.
class ARBGetProcAddressAPI : public gl::BaseExtension
{
public:
    // Construction
    ARBGetProcAddressAPI();

    // Accessors
    const ARBGetProcAddress &getRawAPI() const;

    // Operations
    __GLXextFuncPtr xGetProcAddress(const GLubyte *procName) const;

    // Overrides
    virtual void resolve(const APIResolver *resolver) override;

private:
    ARBGetProcAddress _api;
};

} // namespace glx
#endif // ifdef _USES_GLX

#endif // Header guard
////////////////////////////////////////////////////////////////////////////////
