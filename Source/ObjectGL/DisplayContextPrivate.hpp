//! @file ObjectGL/DisplayContextPrivate.hpp
//! @brief The declaration of the inner implementation of the Display Context
//! object.
//! @author GiantRobotLemur@na-se.co.uk
//! @date 2022-2025
//! @copyright This file is part of the Silver (Ag) project which is released
//! under LGPL 3 license. See LICENSE file at the repository root or go to
//! https://github.com/GiantRobotLemur/Ag for full license details.
////////////////////////////////////////////////////////////////////////////////

#ifndef __AG_OBJECT_GL_DISPLAY_CONTEXT_PRIVATE_HPP__
#define __AG_OBJECT_GL_DISPLAY_CONTEXT_PRIVATE_HPP__

////////////////////////////////////////////////////////////////////////////////
// Dependant Header Files
////////////////////////////////////////////////////////////////////////////////
#include <memory>
#include <mutex>
#include <vector>

#include "Ag/Core/Version.hpp"
#include "Ag/ObjectGL/BaseTypes.hpp"
#include "Ag/ObjectGL/CommandSets.hpp"
#include "Ag/ObjectGL/DisplayContext.hpp"

////////////////////////////////////////////////////////////////////////////////
// Data Type Declarations
////////////////////////////////////////////////////////////////////////////////
struct APIResolver;

namespace gl {

//! @brief Enumerates resources by the function required to dispose of them.
enum class ResourceType
{
    Texture,
    Query,
    Buffer,
    Program,
    Shader,
    FrameBuffer,
    RenderBuffer,
    VertexArray,
    Sampler,
    TransformFeedback,
    ProgramPipeline,
};

using TaggedResource = std::pair<ResourceType, GLuint>;

////////////////////////////////////////////////////////////////////////////////
// Class Declarations
////////////////////////////////////////////////////////////////////////////////
class IDriver;
class ContextOptions;
class RenderContextPrivate;

struct TextureName;
struct QueryName;
struct BufferName;
struct ProgramName;
struct ShaderName;
struct FramebufferName;
struct RenderbufferName;
struct VertexArrayName;
struct SamplerName;
struct TransformFeedbackName;
struct ProgramPipelineName;

//! @brief The inner implementation of the Display Context object.
class DisplayContextPrivate : public std::enable_shared_from_this<DisplayContextPrivate>
{
public:
    // Construction/Destruction
    DisplayContextPrivate();
    virtual ~DisplayContextPrivate() = default;

    // Accessors
    const GLAPI &getAPI() const;
    const Ag::Version &getMaxSupportedVersion() const;
    virtual const APIResolver *getResolver() const = 0;

    // Operations
    void dispose(const TextureName &resource);
    void dispose(const QueryName &resource);
    void dispose(const BufferName &resource);
    void dispose(const ProgramName &resource);
    void dispose(const ShaderName &resource);
    void dispose(const FramebufferName &resource);
    void dispose(const RenderbufferName &resource);
    void dispose(const VertexArrayName &resource);
    void dispose(const SamplerName &resource);
    void dispose(const TransformFeedbackName &resource);
    void dispose(const ProgramPipelineName &resource);
    void flushResources();

    // Overrides
    virtual std::shared_ptr<RenderContextPrivate> createContext(uintptr_t drawable,
                                                                const ContextOptions &option) = 0;

protected:
    void initialiseAPI();

private:
    // Internal Functions
    void dispose(ResourceType type, GLuint id);

    // Internal Fields
    std::mutex _disposalLock;
    std::vector<TaggedResource> _resourcesForDisposal;
    GLAPI _api;
    Ag::Version _maxVersion;
};

//! @brief An alias for a shared pointer to an inner Display Context.
typedef std::shared_ptr<DisplayContextPrivate> DisplayContextPrivateSPtr;

//! @brief An implementation of DisplayContext which allows the inner
//! context to be assigned.
class AssignableDisplayContext : public DisplayContext
{
public:
    AssignableDisplayContext(const DisplayContextPrivateSPtr &display);
};

} // namespace gl

#endif // Header guard
////////////////////////////////////////////////////////////////////////////////
