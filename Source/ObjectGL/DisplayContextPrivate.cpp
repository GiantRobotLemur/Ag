//! @file ObjectGL/DisplayContextPrivate.cpp
//! @brief The definition of the inner implementation of the Display Context
//! object.
//! @author GiantRobotLemur@na-se.co.uk
//! @date 2022-2025
//! @copyright This file is part of the Silver (Ag) project which is released
//! under LGPL 3 license. See LICENSE file at the repository root or go to
//! https://github.com/GiantRobotLemur/Ag for full license details.
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Header File Includes
////////////////////////////////////////////////////////////////////////////////
#include <algorithm>

#include "Ag/Core/Exception.hpp"
#include "Ag/Core/CollectionTools.hpp"
#include "Ag/ObjectGL/Identifiers.hpp"
#include "DisplayContextPrivate.hpp"
#include "RenderContextPrivate.hpp"

namespace gl {

namespace {

////////////////////////////////////////////////////////////////////////////////
// Local Data
////////////////////////////////////////////////////////////////////////////////
//struct ResourceComparer
//{
//    bool operator()(const TaggedResource &lhs, const TaggedResource &rhs) const
//    {
//        bool isLess = false;
//
//        if (lhs.first == rhs.first)
//        {
//            isLess = (lhs.second < rhs.second);
//        }
//        else
//        {
//            isLess = lhs.first < rhs.first;
//        }
//
//        return isLess;
//    }
//};

using ResourceComparer = Ag::LessThanKeyComparer<ResourceType, GLuint>;
using GroupByType = Ag::LessThanPairComparer<ResourceType, GLuint>;

//struct GroupByType
//{
//    bool operator()(const TaggedResource &lhs, const TaggedResource &rhs) const
//    {
//        return lhs.first < rhs.first;
//    }
//};

////////////////////////////////////////////////////////////////////////////////
// Local Functions
////////////////////////////////////////////////////////////////////////////////
//! @brief Extracts the identifiers of a run of tagged resources.
//! @tparam T The data type of the iterators used to define the run.
//! @param[in] begin The iterator pointing to the first tagged resource to
//! extract an identifier from.
//! @param[in] end The iterator pointing to just after the last tagged resource
//! to extract an identifier from.
//! @param[out] ids A collection to append the identifiers to.
template<typename T, typename U>
void extractResourceIDs(const T &begin, const T &end,
                        std::vector<U> &ids)
{
    if (begin == end)
    {
        return;
    }

    // Minimise the amount of memory reallocation in the vector.
    size_t count = std::distance(begin, end);
    size_t totalSize = ids.size() + count;

    if (totalSize > ids.capacity())
    {
        ids.reserve(totalSize);
    }

    // Extract the identifiers.
    bool isFirst = true;
    unsigned int previousId = begin->second;

    for (auto pos = begin; pos != end; ++pos)
    {
        // Filter out any duplicate IDs, which should be
        // consecutive.
        if (isFirst || (pos->second != previousId))
        {
            isFirst = false;
            previousId = pos->second;
            ids.emplace_back(pos->second);
        }
    }
}

} // Anonymous namespace

////////////////////////////////////////////////////////////////////////////////
// DisplayContextPrivate Member Definitions
////////////////////////////////////////////////////////////////////////////////
//! @brief Constructs an object which can manage OpenGL contexts and the
//! resources they share.
DisplayContextPrivate::DisplayContextPrivate()
{
    _resourcesForDisposal.reserve(32);
}

//! @brief Gets the API resolved through a root context.
const GLAPI &DisplayContextPrivate::getAPI() const
{
    return _api;
}

//! @brief Gets the maximum supported version of the OpenGL API supported by
//! the current display.
const Ag::Version &DisplayContextPrivate::getMaxSupportedVersion() const
{
    return _maxVersion;
}

//! @brief Disposes of a texture resource created on the current display.
//! @param[in] resource The identifier of the resource to schedule for disposal.
//! @note Disposal maybe deferred until an appropriate render context is
//! selected on a running thread.
void DisplayContextPrivate::dispose(const TextureName &resource)
{
    dispose(ResourceType::Texture, resource.ID);
}

//! @brief Disposes of a query resource created on the current display.
//! @param[in] resource The identifier of the resource to schedule for disposal.
//! @note Disposal maybe deferred until an appropriate render context is
//! selected on a running thread.
void DisplayContextPrivate::dispose(const QueryName &resource)
{
    dispose(ResourceType::Query, resource.ID);
}

//! @brief Disposes of a buffer resource created on the current display.
//! @param[in] resource The identifier of the resource to schedule for disposal.
//! @note Disposal maybe deferred until an appropriate render context is
//! selected on a running thread.
void DisplayContextPrivate::dispose(const BufferName &resource)
{
    dispose(ResourceType::Buffer, resource.ID);
}

//! @brief Disposes of a program resource created on the current display.
//! @param[in] resource The identifier of the resource to schedule for disposal.
//! @note Disposal maybe deferred until an appropriate render context is
//! selected on a running thread.
void DisplayContextPrivate::dispose(const ProgramName &resource)
{
    dispose(ResourceType::Program, resource.ID);
}

//! @brief Disposes of a shader resource created on the current display.
//! @param[in] resource The identifier of the resource to schedule for disposal.
//! @note Disposal maybe deferred until an appropriate render context is
//! selected on a running thread.
void DisplayContextPrivate::dispose(const ShaderName &resource)
{
    dispose(ResourceType::Shader, resource.ID);
}

//! @brief Disposes of a frame buffer resource created on the current display.
//! @param[in] resource The identifier of the resource to schedule for disposal.
//! @note Disposal maybe deferred until an appropriate render context is
//! selected on a running thread.
void DisplayContextPrivate::dispose(const FramebufferName &resource)
{
    dispose(ResourceType::FrameBuffer, resource.ID);
}

//! @brief Disposes of a render buffer resource created on the current display.
//! @param[in] resource The identifier of the resource to schedule for disposal.
//! @note Disposal maybe deferred until an appropriate render context is
//! selected on a running thread.
void DisplayContextPrivate::dispose(const RenderbufferName &resource)
{
    dispose(ResourceType::RenderBuffer, resource.ID);
}

//! @brief Disposes of a VAO resource created on the current display.
//! @param[in] resource The identifier of the resource to schedule for disposal.
//! @note Disposal maybe deferred until an appropriate render context is
//! selected on a running thread.
void DisplayContextPrivate::dispose(const VertexArrayName &resource)
{
    dispose(ResourceType::VertexArray, resource.ID);
}

//! @brief Disposes of a sampler resource created on the current display.
//! @param[in] resource The identifier of the resource to schedule for disposal.
//! @note Disposal maybe deferred until an appropriate render context is
//! selected on a running thread.
void DisplayContextPrivate::dispose(const SamplerName &resource)
{
    dispose(ResourceType::Sampler, resource.ID);
}

//! @brief Disposes of a transform feedback resource created on the current display.
//! @param[in] resource The identifier of the resource to schedule for disposal.
//! @note Disposal maybe deferred until an appropriate render context is
//! selected on a running thread.
void DisplayContextPrivate::dispose(const TransformFeedbackName &resource)
{
    dispose(ResourceType::TransformFeedback, resource.ID);
}

//! @brief Disposes of a program pipeline resource created on the current display.
//! @param[in] resource The identifier of the resource to schedule for disposal.
//! @note Disposal maybe deferred until an appropriate render context is
//! selected on a running thread.
void DisplayContextPrivate::dispose(const ProgramPipelineName &resource)
{
    dispose(ResourceType::ProgramPipeline, resource.ID);
}

//! @brief Disposes of all resources scheduled for disposal at a point when a
//! context associated with the current display is selected.
void DisplayContextPrivate::flushResources()
{
    if (_resourcesForDisposal.empty())
    {
        return;
    }

    std::lock_guard guard(_disposalLock);

    // Sort the resources by type.
    std::sort(_resourcesForDisposal.begin(), _resourcesForDisposal.end(),
              ResourceComparer());

  // Group the resources by type for disposal.
    auto groupStart = _resourcesForDisposal.begin();
    GroupByType groupPredicate;

    while (groupStart != _resourcesForDisposal.end())
    {
        // Find the end of the group.
        auto groupEnd = std::upper_bound(groupStart,
                                         _resourcesForDisposal.end(),
                                         *groupStart, groupPredicate);

        switch (groupStart->first)
        {
        case ResourceType::Texture: {
            std::vector<TextureName> names;

            extractResourceIDs(groupStart, groupEnd, names);
            _api.deleteTextures(static_cast<GLsizei>(names.size()),
                                names.data());
        } break;

        case ResourceType::Query: {
            std::vector<QueryName> names;

            extractResourceIDs(groupStart, groupEnd, names);
            _api.deleteQueries(static_cast<GLsizei>(names.size()), names.data());
        } break;

        case ResourceType::Buffer: {
            std::vector<BufferName> names;

            extractResourceIDs(groupStart, groupEnd, names);
            _api.deleteBuffers(static_cast<GLsizei>(names.size()), names.data());
        } break;

        case ResourceType::Program:
            // The API for managing program resources doesn't work on groups :-(
            for (auto program = groupStart; program != groupEnd; ++program)
            {
                _api.deleteProgram(program->second);
            }
            break;

        case ResourceType::Shader:
            // The API for managing shader resources doesn't work on groups :-(
            for (auto shader = groupStart; shader != groupEnd; ++shader)
            {
                _api.deleteShader(shader->second);
            }
            break;

        case ResourceType::FrameBuffer: {
            std::vector<FramebufferName> names;

            extractResourceIDs(groupStart, groupEnd, names);
            _api.deleteFramebuffers(static_cast<GLsizei>(names.size()), names.data());
        } break;

        case ResourceType::RenderBuffer: {
            std::vector<RenderbufferName> names;

            extractResourceIDs(groupStart, groupEnd, names);
            _api.deleteRenderbuffers(static_cast<GLsizei>(names.size()), names.data());
        } break;

        case ResourceType::VertexArray: {
            std::vector<VertexArrayName> names;

            extractResourceIDs(groupStart, groupEnd, names);
            _api.deleteVertexArrays(static_cast<GLsizei>(names.size()), names.data());
        } break;

        case ResourceType::Sampler: {
            std::vector<SamplerName> names;

            extractResourceIDs(groupStart, groupEnd, names);
            _api.deleteSamplers(static_cast<GLsizei>(names.size()), names.data());
        } break;

        case ResourceType::TransformFeedback: {
            std::vector<TransformFeedbackName> names;

            extractResourceIDs(groupStart, groupEnd, names);
            _api.deleteTransformFeedbacks(static_cast<GLsizei>(names.size()),
                                          names.data());
        } break;

        case ResourceType::ProgramPipeline: {
            std::vector<ProgramPipelineName> names;

            extractResourceIDs(groupStart, groupEnd, names);
            _api.deleteProgramPipelines(static_cast<GLsizei>(names.size()),
                                        names.data());
        } break;

        }
    }
}

//! @brief Must be called by derived classes when the root context has been
//! created and selected into the current thread.
//! @note At the time of call, getResolver() must return a valid result.
void DisplayContextPrivate::initialiseAPI()
{
    _api.resolve(getResolver());

    // Get the maximum version supported by the context.
    GLint major = 0, minor = 0;
    _api.getIntegerV(GetPName::MajorVersion, &major);
    _api.getIntegerV(GetPName::MinorVersion, &minor);

    _maxVersion.setMajor(static_cast<uint16_t>(major));
    _maxVersion.setMinor(static_cast<uint16_t>(minor));
}

//! @brief Schedules a resource for disposal.
//! @param[in] type The type of resource to dispose of.
//! @param[in] id The identifier of the resource.
//! @note Disposal maybe deferred until an appropriate render context is
//! selected on a running thread.
void DisplayContextPrivate::dispose(ResourceType type, GLuint id)
{
    std::lock_guard guard(_disposalLock);

    _resourcesForDisposal.emplace_back(type, id);
}


////////////////////////////////////////////////////////////////////////////////
// AssignableDisplayContext Member Function Definitions
////////////////////////////////////////////////////////////////////////////////
//! @brief A public constructor which allows a DisplayContext to be created
//! which is in a bound state.
//! @param[in] display The inner display implementation to bind to.
AssignableDisplayContext::AssignableDisplayContext(const DisplayContextPrivateSPtr &display) :
    DisplayContext(display)
{
}

////////////////////////////////////////////////////////////////////////////////
// Global Function Definitions
////////////////////////////////////////////////////////////////////////////////

} // namespace gl
////////////////////////////////////////////////////////////////////////////////

