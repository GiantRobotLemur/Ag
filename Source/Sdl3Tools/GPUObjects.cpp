//! @file Sdl3Tools/GPUObjects.cpp
//! @brief The definition of wrappers for GPU-related SDL 3 Data types.
//! @author GiantRobotLemur@na-se.co.uk
//! @date 2025
//! @copyright This file is part of the Silver (Ag) project which is released
//! under LGPL 3 license. See LICENSE file at the repository root or go to
//! https://github.com/GiantRobotLemur/Ag for full license details.
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Header File Includes
////////////////////////////////////////////////////////////////////////////////
#include "Ag/Sdl3Tools/ApiException.hpp"
#include "Ag/Sdl3Tools/GPUObjects.hpp"
#include "Ag/Sdl3Tools/Window.hpp"

namespace Ag {
namespace SDL3 {
namespace GPU {

namespace {

////////////////////////////////////////////////////////////////////////////////
// Local Functions
////////////////////////////////////////////////////////////////////////////////
uint32_t vertexAttribSize(SDL_GPUVertexElementFormat format)
{
    // Define a static mapping of vertex attribute format to byte count.
    using FormatMap = Ag::StaticMap<SDL_GPUVertexElementFormat, uint32_t>;
    static FormatMap::MappingType mappings[] = {
        /* 32-bit Signed Integers */
        { SDL_GPU_VERTEXELEMENTFORMAT_INT, 4 },
        { SDL_GPU_VERTEXELEMENTFORMAT_INT2, 8 },
        { SDL_GPU_VERTEXELEMENTFORMAT_INT3, 12 },
        { SDL_GPU_VERTEXELEMENTFORMAT_INT4, 16 },

        /* 32-bit Unsigned Integers */
        { SDL_GPU_VERTEXELEMENTFORMAT_UINT, 4 },
        { SDL_GPU_VERTEXELEMENTFORMAT_UINT2, 8 },
        { SDL_GPU_VERTEXELEMENTFORMAT_UINT3, 12 },
        { SDL_GPU_VERTEXELEMENTFORMAT_UINT4, 16 },

        /* 32-bit Floats */
        { SDL_GPU_VERTEXELEMENTFORMAT_FLOAT, 4 },
        { SDL_GPU_VERTEXELEMENTFORMAT_FLOAT2, 8 },
        { SDL_GPU_VERTEXELEMENTFORMAT_FLOAT3, 12 },
        { SDL_GPU_VERTEXELEMENTFORMAT_FLOAT4, 16 },

        /* 8-bit Signed Integers */
        { SDL_GPU_VERTEXELEMENTFORMAT_BYTE2, 2 },
        { SDL_GPU_VERTEXELEMENTFORMAT_BYTE4, 4 },

        /* 8-bit Unsigned Integers */
        { SDL_GPU_VERTEXELEMENTFORMAT_UBYTE2, 2 },
        { SDL_GPU_VERTEXELEMENTFORMAT_UBYTE4, 4 },

        /* 8-bit Signed Normalized */
        { SDL_GPU_VERTEXELEMENTFORMAT_BYTE2_NORM, 2 },
        { SDL_GPU_VERTEXELEMENTFORMAT_BYTE4_NORM, 4 },

        /* 8-bit Unsigned Normalized */
        { SDL_GPU_VERTEXELEMENTFORMAT_UBYTE2_NORM, 2 },
        { SDL_GPU_VERTEXELEMENTFORMAT_UBYTE4_NORM, 4 },

        /* 16-bit Signed Integers */
        { SDL_GPU_VERTEXELEMENTFORMAT_SHORT2, 4 },
        { SDL_GPU_VERTEXELEMENTFORMAT_SHORT4, 8 },

        /* 16-bit Unsigned Integers */
        { SDL_GPU_VERTEXELEMENTFORMAT_USHORT2, 4 },
        { SDL_GPU_VERTEXELEMENTFORMAT_USHORT4, 8 },

        /* 16-bit Signed Normalized */
        { SDL_GPU_VERTEXELEMENTFORMAT_SHORT2_NORM, 4 },
        { SDL_GPU_VERTEXELEMENTFORMAT_SHORT4_NORM, 8 },

        /* 16-bit Unsigned Normalized */
        { SDL_GPU_VERTEXELEMENTFORMAT_USHORT2_NORM, 4 },
        { SDL_GPU_VERTEXELEMENTFORMAT_USHORT4_NORM, 8 },

        /* 16-bit Floats */
        { SDL_GPU_VERTEXELEMENTFORMAT_HALF2, 4 },
        { SDL_GPU_VERTEXELEMENTFORMAT_HALF4, 8 },
    };

    static const FormatMap attribSizeByFormat(mappings);

    size_t index = 0;

    return attribSizeByFormat.tryFindValue(format, index) ? attribSizeByFormat.getValue(index) : 0;
}

} // Anonymous namespace


////////////////////////////////////////////////////////////////////////////////
// Fence Member Definitions
////////////////////////////////////////////////////////////////////////////////
//! @brief Constructs an empty wrapper for a GPU Fence synchronisation primitive.
Fence::Fence() :
    _parentDevice(nullptr),
    _fence(nullptr)
{
}

//! @brief Acquires a GPU fence from another wrapper.
//! @param[in] rhs The wrapper to acquire the fence resource from.
Fence::Fence(Fence &&rhs) noexcept :
    _parentDevice(rhs._parentDevice),
    _fence(rhs._fence)
{
    rhs._parentDevice = nullptr;
    rhs._fence = nullptr;
}

//! @brief Initialises a new object with a fence synchronisation resource.
//! @param[in] parentDevice The GPU device the fence is associated with.
//! @param[in] fence The pointer to the fence primitive, can be nullptr.
Fence::Fence(SDL_GPUDevice *parentDevice, SDL_GPUFence *fence) :
    _parentDevice((fence == nullptr) ? nullptr : parentDevice),
    _fence(fence)
{
}

//! @brief Ensures the fence is released on destruction.
Fence::~Fence()
{
    release();
}

//! @brief Determines if the wrapper is bound to an underlying fence resource.
//! @retval true The object is bound to a GPU fence synchronisation primitive.
//! @retval false The object is unbound.
bool Fence::isBound() const
{
    return (_fence != nullptr);
}

//! @brief Determines if the fence is in a signalled state.
//! @retval true The fence is in a signalled state.
//! @retval false The fence is not in a signalled state, or the object is not
//! bound to an underlying fence resource.
bool Fence::isSignalled() const
{
    return (_fence != nullptr) && SDL_QueryGPUFence(_parentDevice, _fence);
}

//! @brief Gets a pointer to the underlying synchronization primitive.
SDL_GPUFence *Fence::get() const
{
    return _fence;
}

//! @brief Attempts to wait until the fence has been passed.
//! @retval true The GPU device finished processing the command buffer the
//! fence was created from.
//! @retval false The object was unbound or an error occurred.
bool Fence::tryWait() const noexcept
{
    if (_fence == nullptr)
        return false;

    return SDL_WaitForGPUFences(_parentDevice, true, &_fence, 1);
}

//! @brief Waits until the fence has been passed.
//! @throws ApiException If an error occurred waiting for the GPU device.
//! @throws ObjectNotBoundException If the wrapper is not bound to a fence.
void Fence::wait() const
{
    auto fence = verifyAccess("wait");

    if (SDL_WaitForGPUFences(_parentDevice, true, &fence, 1) == false)
    {
        throw ApiException("SDL_WaitForGPUFences(1)");
    }
}

//! @brief Explicitly releases any underlying fence resource.
void Fence::release() noexcept
{
    auto device = std::exchange(_parentDevice, nullptr);
    auto fence = std::exchange(_fence, nullptr);

    if ((device != nullptr) && (fence != nullptr))
    {
        SDL_ReleaseGPUFence(device, fence);
    }
}

//! @brief Acquires a fence resource from another wrapper.
//! @param[in] rhs The wrapper to acquire the fence primitive from.
//! @return A reference to the current object.
//! @note Any previously bound fence primitive is released before
//! acquisition.
Fence &Fence::operator=(Fence &&rhs) noexcept
{
    if (_fence == rhs._fence)
        return *this;

    release();

    _parentDevice = std::exchange(rhs._parentDevice, nullptr);
    _fence = std::exchange(rhs._fence, nullptr);

    return *this;
}

//! @brief Verifies the object is bound to an underlying fence primitive.
//! @param[in] operation The operation being attempted.
//! @return A pointer to the fence resource.
//! @throws ObjectNotBoundException If the wrapper is not bound to an underlying
//! GPU fence synchronisation primitive.
SDL_GPUFence *Fence::verifyAccess(utf8_cptr_t operation) const
{
    if (_fence == nullptr)
        throw ObjectNotBoundException("GPU Fence", operation);

    return _fence;
}

////////////////////////////////////////////////////////////////////////////////
// TransferMapping Member Definitions
////////////////////////////////////////////////////////////////////////////////
//! Constructs an empty wrapper for a block of system memory inside a GPU
//! transfer buffer.
TransferMapping::TransferMapping() :
    _parentDevice(nullptr),
    _buffer(nullptr)
{
}

//! @brief Constructs a wrapper for a block of system memory inside a GPU
//! transfer buffer.
//! @param[in] parentDevice The GPU device the buffer will transfer to/from.
//! @param[in] buffer The underlying buffer object.
//! @param[in] mapping A pointer to the mapped block of memory.
//! @param[in] size The count of bytes in the mapped block.
TransferMapping::TransferMapping(SDL_GPUDevice *parentDevice,
                                 SDL_GPUTransferBuffer *buffer,
                                 void *mapping, uint32_t size) :
    _parentDevice((mapping == nullptr) ? nullptr : parentDevice),
    _buffer((mapping == nullptr) ? nullptr : buffer),
    _mappedBlock(mapping),
    _size(size)
{
}

//! @brief Acquires a GPU transfer buffer resource from another wrapper.
//! @param[in] rhs The wrapper object to acquire the resource from.
TransferMapping::TransferMapping(TransferMapping &&rhs) noexcept :
    _parentDevice(rhs._parentDevice),
    _buffer(rhs._buffer),
    _mappedBlock(rhs._mappedBlock),
    _size(rhs._size)
{
    rhs._parentDevice = nullptr;
    rhs._buffer = nullptr;
    rhs._mappedBlock = nullptr;
    rhs._size = 0;
}

//! @brief Ensures any underlying buffer resource is disposed of.
TransferMapping::~TransferMapping()
{
    unmap();
}

//! @brief Determines if the wrapper is mapped to a block of system memory.
//! @retval true The object wraps a valid memory block.
//! @retval false The object is in an unbound state.
bool TransferMapping::isMapped() const
{
    return (_buffer != nullptr);
}

//! @brief Gets the count of bytes in the mapped block.
uint32_t TransferMapping::getSize() const
{
    return _size;
}

//! @brief Gets a pointer to the start of the mapped block, or nullptr if unmapped.
void *TransferMapping::getMapping() const
{
    return _mappedBlock;
}

//! @brief Explicitly release the underlying transfer buffer.
void TransferMapping::unmap()
{
    auto device = std::exchange(_parentDevice, nullptr);
    auto buffer = std::exchange(_buffer, nullptr);
    _mappedBlock = nullptr;
    _size = 0;

    if (buffer != nullptr)
    {
        SDL_UnmapGPUTransferBuffer(device, buffer);
    }
}

//! @brief Acquires a GPU transfer buffer resource from another wrapper.
//! @param[in] rhs The wrapper object to acquire the resource from.
//! @return A reference to the current object.
TransferMapping &TransferMapping::operator=(TransferMapping &&rhs) noexcept
{
    if (rhs._buffer == _buffer)
        return *this;

    unmap();

    _parentDevice = std::exchange(rhs._parentDevice, nullptr);
    _buffer = std::exchange(rhs._buffer, nullptr);
    _mappedBlock = std::exchange(rhs._mappedBlock, nullptr);
    _size = std::exchange(rhs._size, 0);

    return *this;
}

////////////////////////////////////////////////////////////////////////////////
// TransferBuffer Member Definitions
////////////////////////////////////////////////////////////////////////////////
//! Constructs an empty wrapper for a GPU transfer buffer.
TransferBuffer::TransferBuffer() :
    _parentDevice(nullptr),
    _buffer(nullptr),
    _size(0)
{
}

//! @brief Constructs a wrapper for a GPU transfer buffer.
//! @param[in] parentDevice The GPU device the buffer will transfer to/from.
//! @param[in] buffer The underlying buffer object.
//! @param[in] size The count of bytes in the buffer.
TransferBuffer::TransferBuffer(SDL_GPUDevice *parentDevice,
                               SDL_GPUTransferBuffer *buffer, uint32_t size) :
    _parentDevice((buffer == nullptr) ? nullptr : parentDevice),
    _buffer(buffer),
    _size((buffer == nullptr) ? 0 : size)
{
}

//! @brief Acquires a GPU transfer buffer resource from another wrapper.
//! @param[in] rhs The wrapper object to acquire the resource from.
TransferBuffer::TransferBuffer(TransferBuffer &&rhs) noexcept :
    _parentDevice(rhs._parentDevice),
    _buffer(rhs._buffer),
    _size(rhs._size)
{
    rhs._parentDevice = nullptr;
    rhs._buffer = nullptr;
    rhs._size = 0;
}

//! @brief Ensures any underlying buffer resource is disposed of.
TransferBuffer::~TransferBuffer()
{
    release();
}

//! @brief Determines if the wrapper is bound to an underlying resource.
//! @retval true The object wraps a valid GPU transfer buffer.
//! @retval false The object is in an unbound state.
bool TransferBuffer::isBound() const
{
    return (_buffer != nullptr);
}

//! @brief Gets the count of bytes in the buffer.
uint32_t TransferBuffer::getSize() const
{
    return _size;
}

//! @brief Maps the transfer buffer so it can be accessed by the program.
//! @param[in] cycle If true, cycles the transfer buffer if it is already bound.
//! @return An object representing the mapped buffer.
TransferMapping TransferBuffer::map(bool cycle) const
{
    auto buffer = verifyAccess("map buffer");

    void *mapping = SDL_MapGPUTransferBuffer(_parentDevice, _buffer, cycle);

    if (mapping == nullptr)
        throw ApiException("SDL_MapGPUTransferBuffer()");

    return TransferMapping(_parentDevice, buffer, mapping, _size);
}

//! @brief Explicitly release the underlying transfer buffer.
void TransferBuffer::release()
{
    auto device = std::exchange(_parentDevice, nullptr);
    auto buffer = std::exchange(_buffer, nullptr);
    _size = 0;

    if (buffer != nullptr)
    {
        SDL_ReleaseGPUTransferBuffer(device, buffer);
    }
}

//! @brief Acquires a GPU transfer buffer resource from another wrapper.
//! @param[in] rhs The wrapper object to acquire the resource from.
//! @return A reference to the current object.
TransferBuffer &TransferBuffer::operator=(TransferBuffer &&rhs) noexcept
{
    if (rhs._buffer == _buffer)
        return *this;

    release();

    _parentDevice = std::exchange(rhs._parentDevice, nullptr);
    _buffer = std::exchange(rhs._buffer, nullptr);
    _size = std::exchange(rhs._size, 0);

    return *this;
}

//! @brief Ensures the object wraps a valid transfer buffer resource before
//! performing an operation.
//! @param[in] operation A description of the operation to be performed.
//! @return A valid pointer to the underlying buffer object.
//! @throws ObjectNotBoundException If the object is in an unbound state.
SDL_GPUTransferBuffer *TransferBuffer::verifyAccess(utf8_cptr_t operation) const
{
    if (_buffer == nullptr)
        throw ObjectNotBoundException("GPU Transfer Buffer", operation);

    return _buffer;
}

////////////////////////////////////////////////////////////////////////////////
// ResourceBuffer Member Definitions
////////////////////////////////////////////////////////////////////////////////
//! Constructs an empty wrapper for a block of GPU memory to hold vertices or indices.
ResourceBuffer::ResourceBuffer() :
    _parentDevice(nullptr),
    _buffer(nullptr),
    _size(0)
{
}

//! @brief Constructs a wrapper for a block of GPU memory to hold vertices or indices.
//! @param[in] parentDevice The GPU device the buffer will transfer to/from.
//! @param[in] buffer The underlying buffer object.
//! @param[in] size The count of bytes in the buffer.
ResourceBuffer::ResourceBuffer(SDL_GPUDevice *parentDevice,
                               SDL_GPUBuffer *buffer, uint32_t size) :
    _parentDevice((buffer == nullptr) ? nullptr : parentDevice),
    _buffer(buffer),
    _size((buffer == nullptr) ? 0 : size)
{
}

//! @brief Acquires a GPU transfer buffer resource from another wrapper.
//! @param[in] rhs The wrapper object to acquire the resource from.
ResourceBuffer::ResourceBuffer(ResourceBuffer &&rhs) noexcept :
    _parentDevice(rhs._parentDevice),
    _buffer(rhs._buffer),
    _size(rhs._size)
{
    rhs._parentDevice = nullptr;
    rhs._buffer = nullptr;
    rhs._size = 0;
}

//! @brief Ensures any underlying buffer resource is disposed of.
ResourceBuffer::~ResourceBuffer()
{
    release();
}

//! @brief Determines if the wrapper is bound to an underlying resource.
//! @retval true The object wraps a valid GPU resource buffer.
//! @retval false The object is in an unbound state.
bool ResourceBuffer::isBound() const
{
    return (_buffer != nullptr);
}

//! @brief Gets the count of bytes in the buffer.
uint32_t ResourceBuffer::getSize() const
{
    return _size;
}

//! @brief Explicitly release the underlying transfer buffer.
void ResourceBuffer::release()
{
    auto device = std::exchange(_parentDevice, nullptr);
    auto buffer = std::exchange(_buffer, nullptr);
    _size = 0;

    if (buffer != nullptr)
    {
        SDL_ReleaseGPUBuffer(device, buffer);
    }
}

//! @brief Acquires a GPU buffer resource from another wrapper.
//! @param[in] rhs The wrapper object to acquire the resource from.
//! @return A reference to the current object.
ResourceBuffer &ResourceBuffer::operator=(ResourceBuffer &&rhs) noexcept
{
    if (rhs._buffer == _buffer)
        return *this;

    release();

    _parentDevice = std::exchange(rhs._parentDevice, nullptr);
    _buffer = std::exchange(rhs._buffer, nullptr);
    _size = std::exchange(rhs._size, 0);

    return *this;
}

//! @brief Ensures the object wraps a valid buffer before performing an operation.
//! @param[in] operation A description of the operation to be performed.
//! @return A valid pointer to the underlying buffer object.
//! @throws ObjectNotBoundException If the object is in an unbound state.
SDL_GPUBuffer *ResourceBuffer::verifyAccess(utf8_cptr_t operation) const
{
    if (_buffer == nullptr)
        throw ObjectNotBoundException("GPU Buffer", operation);

    return _buffer;
}

////////////////////////////////////////////////////////////////////////////////
// Texture Member Definitions
////////////////////////////////////////////////////////////////////////////////
//! @brief Constructs an empty wrapper for a GPU texture resource.
Texture::Texture() :
    _parentDevice(nullptr),
    _texture(nullptr),
    _releaseOnDestroy(false)
{
}

//! @brief Constructs a wrapper for a GPU texture resource.
//! @param[in] parentDevice The device which owns the texture.
//! @param[in] texture The texture resource to wrap, can be nullptr.
//! @param[in] releaseOnDestroy True if the object should release the texture
//! resource when it is no longer required, false to do nothing.
Texture::Texture(SDL_GPUDevice *parentDevice, SDL_GPUTexture *texture, bool releaseOnDestroy /*= true*/) :
    _parentDevice((texture == nullptr) ? nullptr : parentDevice),
    _texture(texture),
    _releaseOnDestroy(releaseOnDestroy)
{
}

//! @brief Acquires a GPU texture resource from another wrapper.
//! @param[in] rhs The wrapper of the texture resource to acquire.
Texture::Texture(Texture &&rhs) noexcept :
    _parentDevice(rhs._parentDevice),
    _texture(rhs._texture),
    _releaseOnDestroy(rhs._releaseOnDestroy)
{
    rhs._parentDevice = nullptr;
    rhs._texture = nullptr;
    rhs._releaseOnDestroy = false;
}

//! @brief Ensures the underlying texture resource is released, if necessary.
Texture::~Texture()
{
    release();
}

//! @brief Determines if the object is bound to a texture resource.
//! @retval true The object wraps a valid texture resource.
//! @retval false The object is in an unbound state.
bool Texture::isBound() const
{
    return _texture != nullptr;
}

//! @brief Gets a pointer to the underlying texture resource, nullptr if unbound.
SDL_GPUTexture *Texture::get() const
{
    return _texture;
}

//! @brief Explicitly releases the texture if one is bound which needs release.
//! @note On exit, the object is guaranteed to be in an unbound state.
void Texture::release()
{
    auto parentDevice = std::exchange(_parentDevice, nullptr);
    auto texture = std::exchange(_texture, nullptr);

    if (_releaseOnDestroy && (parentDevice != nullptr) && (texture != nullptr))
    {
        SDL_ReleaseGPUTexture(parentDevice, texture);
    }

    _releaseOnDestroy = false;
}

//! @brief Acquires a texture from another wrapper.
//! @param[in] rhs The wrapper object to transfer the resource from.
//! @return A reference to the current object.
Texture &Texture::operator=(Texture &&rhs) noexcept
{
    if (_texture == rhs._texture)
        return *this;

    release();

    _parentDevice = std::exchange(rhs._parentDevice, nullptr);
    _texture = std::exchange(rhs._texture, nullptr);
    _releaseOnDestroy = std::exchange(rhs._releaseOnDestroy, false);

    return *this;
}

//! @brief Ensures the object is in a bound state before an operation.
//! @param[in] operation A description of the operation to perform.
//! @return A pointer to the underlying texture resource.
//! @throws ObjectNotBoundException If the object is in an unbound state.
SDL_GPUTexture *Texture::verifyAccess(utf8_cptr_t operation) const
{
    if (_texture == nullptr)
        throw ObjectNotBoundException("GPU Texture", operation);

    return _texture;
}

////////////////////////////////////////////////////////////////////////////////
// Shader Member Definitions
////////////////////////////////////////////////////////////////////////////////
//! @brief Constructs an empty wrapper for a GPU shader program.
Shader::Shader() :
    _parentDevice(nullptr),
    _shader(nullptr)
{
}

//! @brief Constructs a wrapper for a GPU shader program.
//! @param[in] device The device the shader operates on.
//! @param[in] shader The SDL GPU shader program resource.
Shader::Shader(SDL_GPUDevice *device, SDL_GPUShader *shader) :
    _parentDevice((shader == nullptr) ? nullptr : device),
    _shader((device == nullptr) ? nullptr : shader)
{
}

//! @brief Acquires a shader program resource from another wrapper.
//! @param[in] rhs The wrapper to acquire the shader from.
Shader::Shader(Shader &&rhs) noexcept :
    _parentDevice(std::exchange(rhs._parentDevice, nullptr)),
    _shader(std::exchange(rhs._shader, nullptr))
{
}

//! @brief Ensure any underlying shader program is properly disposed of.
Shader::~Shader()
{
    release();
}

//! @brief Determines if the object is bound to a shader resource.
//! @retval true The object wraps a valid shader resource.
//! @retval false The object is in an unbound state.
bool Shader::isBound() const
{
    return _shader != nullptr;
}

//! @brief Gets the wrapped resource.
SDL_GPUShader *Shader::get() const
{
    return _shader;
}

//! @brief Disposes of any underlying shader resource, setting the object to
//! an unbound state.
void Shader::release()
{
    auto device = std::exchange(_parentDevice, nullptr);
    auto shader = std::exchange(_shader, nullptr);

    if (shader != nullptr)
    {
        SDL_ReleaseGPUShader(device, shader);
    }
}

//! @brief Acquires a shader resource from another wrapper.
//! @param[in] rhs The wrapper to acquire the shader from.
//! @return A reference to the current object.
Shader &Shader::operator=(Shader &&rhs) noexcept
{
    if ((_parentDevice == rhs._parentDevice) &&
        (_shader == rhs._shader))
        return *this;

    release();

    _parentDevice = std::exchange(rhs._parentDevice, nullptr);
    _shader = std::exchange(rhs._shader, nullptr);

    return *this;
}

////////////////////////////////////////////////////////////////////////////////
// ShaderBuilder Member Definitions
////////////////////////////////////////////////////////////////////////////////
//! @brief Constructs an object to assist with the creation of shader objects.
//! @param[in] device The device on which the shader objects should be created.
//! @param[in] format The shader format to be assumed if none is supplied.
ShaderBuilder::ShaderBuilder(const Device &device,
                             SDL_GPUShaderFormat format) :
    _device(device.verifyAccess("Build shader")),
    _defaultFormat(format)
{
    Ag::zeroFill(_info);
}

//! @brief Creates a shader program from the parameters previously specified.
//! @return A wrapper for a newly created shader object.
//! @throws OperationException If no shader code has been specified.
//! @throws ObjectNotBoundException If an invalid device was specified at
//! construction.
Shader ShaderBuilder::createShader() const
{
    if ((_info.code_size == 0) || (_info.code == nullptr))
        throw OperationException("Cannot create a shader object with no program.");

    if (_device == nullptr)
        throw ObjectNotBoundException("GPU device", "Create shader");

    SDL_GPUShader *shader = SDL_CreateGPUShader(_device, &_info);

    if (shader == nullptr)
        throw ApiException("SDL_CreateGPUShader()");

    return Shader(_device, shader);
}

//! @brief Starts building a new shader.
//! @param[in] code The array of bytes of the compiled shader program.
//! @param[in] byteCount The count of bytes in @p code.
//! @param[in] stage The stage at which the shader program is intended to be executed.
//! @param[in] format The format of the shader program. The default will be used
//! if SDL_GPU_SHADERFORMAT_INVALID is specified.
void ShaderBuilder::beginShader(const uint8_t *code, size_t byteCount,
                                SDL_GPUShaderStage stage,
                                SDL_GPUShaderFormat format /*= SDL_GPU_SHADERFORMAT_INVALID*/)
{
    Ag::zeroFill(_info);

    _info.code = reinterpret_cast<decltype(_info.code)>(code);
    _info.code_size = byteCount;
    _info.format = (format == SDL_GPU_SHADERFORMAT_INVALID) ? _defaultFormat : format;
    _info.stage = stage;
}

////////////////////////////////////////////////////////////////////////////////
// GraphicsPipeline Member Definitions
////////////////////////////////////////////////////////////////////////////////
//! @brief Constructs an empty wrapper for a graphics pipeline.
GraphicsPipeline::GraphicsPipeline() :
    _parentDevice(nullptr),
    _pipeline(nullptr)
{
}

//! @brief Acquires a graphics pipeline from another wrapper.
//! @param[in] rhs The wrapper to acquire the resource from.
GraphicsPipeline::GraphicsPipeline(GraphicsPipeline &&rhs) noexcept :
    _parentDevice(std::exchange(rhs._parentDevice, nullptr)),
    _pipeline(std::exchange(rhs._pipeline, nullptr))
{
}

//! @brief Constructs a new wrapper for a graphics pipeline.
//! @param[in] parentDevice The GPU device which owns the pipeline.
//! @param[in] pipeline The pipeline object to wrap.
GraphicsPipeline::GraphicsPipeline(SDL_GPUDevice *parentDevice,
                                   SDL_GPUGraphicsPipeline *pipeline) :
    _parentDevice((pipeline == nullptr) ? nullptr : parentDevice),
    _pipeline(pipeline)
{
}

//! @brief Ensures the pipeline is properly disposed of on destruction.
GraphicsPipeline::~GraphicsPipeline()
{
    release();
}

//! @brief Determines if the object is bound to an underlying pipeline.
//! @retval true The object wraps a graphics pipeline.
//! @retval false The object is in an unbound state.
bool GraphicsPipeline::isBound() const
{
    return (_pipeline != nullptr);
}

//! @brief Explicitly releases any graphics pipeline the object wraps.
void GraphicsPipeline::release() noexcept
{
    auto device = std::exchange(_parentDevice, nullptr);
    auto pipeline = std::exchange(_pipeline, nullptr);

    if (pipeline == nullptr)
        return;

    SDL_ReleaseGPUGraphicsPipeline(device, pipeline);
}

//! @brief Acquires a graphics pipeline from another wrapper.
//! @param[in] rhs The wrapper to acquire the underlying pipeline from.
//! @return A reference to the current object.
GraphicsPipeline &GraphicsPipeline::operator=(GraphicsPipeline &&rhs) noexcept
{
    if (_pipeline == rhs._pipeline)
        return *this;

    release();

    _parentDevice = std::exchange(rhs._parentDevice, nullptr);
    _pipeline = std::exchange(rhs._pipeline, nullptr);

    return *this;
}

//! @brief Validates that the object wraps a valid graphics pipeline before
//! performing an operation on it.
//! @param[in] operation The description of the operation.
//! @return A valid pointer to the underling graphics pipeline.
//! @throws ObjectNotBoundException If the object is not bound to a pipeline.
SDL_GPUGraphicsPipeline *GraphicsPipeline::verifyAccess(utf8_cptr_t operation) const
{
    if (_pipeline == nullptr)
        throw ObjectNotBoundException("GPU Graphics Pipeline", operation);

    return _pipeline;
}

////////////////////////////////////////////////////////////////////////////////
// VertexDescriptionBuilder Member Definitions
////////////////////////////////////////////////////////////////////////////////
//! @brief Constructs an object to incrementally describe a vertex buffer.
//! @param[in] pitch The size of each vertex, in bytes. Calculated if not set.
//! @param[in] bufferSlot The input slot the target buffer will be mapped to.
//! @param[in] locationOffset The offset of the index to the first attribute
//! input location in the buffer being described.
VertexDescriptionBuilder::VertexDescriptionBuilder(size_t pitch /*= 0*/,
                                                   uint32_t bufferSlot /*= 0*/,
                                                   uint32_t locationOffset /*= 0*/) :
    _locationOffset(locationOffset)
{
    Ag::zeroFill(_desc);
    _desc.slot = bufferSlot;
    _desc.pitch = static_cast<decltype(_desc.pitch)>(pitch);
    _desc.input_rate = SDL_GPU_VERTEXINPUTRATE_VERTEX;
    _attributes.reserve(16);
}

//! @brief Marks vertices in the buffer being described as being consumed
//! per-instance rather than per vertex.
void VertexDescriptionBuilder::makeInstanced()
{
    _desc.input_rate = SDL_GPU_VERTEXINPUTRATE_VERTEX;
}

//! @brief Starts describing the next buffer, incrementing the input slot and
//! resetting vertex and attribute description properties.
//! @param[in] pitch The size of each vertex, in bytes. Calculated if not set.
void VertexDescriptionBuilder::beginNextBuffer(size_t pitch /*= 0*/)
{
    auto oldSlot = _desc.slot;
    Ag::zeroFill(_desc);

    _desc.slot = oldSlot + 1;
    _desc.pitch = static_cast<decltype(_desc.pitch)>(pitch);
    _desc.input_rate = SDL_GPU_VERTEXINPUTRATE_VERTEX;
    _attributes.clear();
}

//! @brief Adds a description of an attribute within the vertex buffer.
//! @param[in] format The format of the attribute being described.
//! @param[in] offset The attribute's byte offset within the vertex, calculated
//! if not specified.
//! @param[in] location The input slot which receives the attribute.
//! @return The final location of the attribute.
uint32_t VertexDescriptionBuilder::addAttribute(SDL_GPUVertexElementFormat format,
                                                size_t offset /*= SIZE_MAX*/,
                                                uint32_t location /*= UINT32_MAX*/)
{
    size_t oldSize = _attributes.size();
    SDL_GPUVertexAttribute &attrib = _attributes.emplace_back();
    Ag::zeroFill(attrib);

    // TODO: Location may not be solely based on this buffer.
    attrib.location = (location == UINT32_MAX) ?
        static_cast<decltype(attrib.location)>(oldSize + _locationOffset) :
        location;

    attrib.buffer_slot = _desc.slot;
    attrib.format = format;

    if (offset == SIZE_MAX)
    {
        // Calculate the offset from the last attribute.
        if (_attributes.size() > 1)
        {
            auto &prevAttrib = _attributes[_attributes.size() - 2];
            attrib.offset = prevAttrib.offset + vertexAttribSize(prevAttrib.format);
        }
        else
        {
            // There were no previous attributes.
            attrib.offset = 0;
        }
    }
    else
    {
        // Fix the offset.
        attrib.offset = static_cast<decltype(attrib.offset)>(offset);
    }

    return attrib.location;
}

//! @brief Gets the completed description of the vertex buffer.
//! @param[out] desc Receives a description of the buffer.
//! @return A collection of vertex attribute descriptions.
const SDL_GPUVertexAttributeVector &VertexDescriptionBuilder::build(SDL_GPUVertexBufferDescription &desc) const
{
    desc = _desc;

    if (desc.pitch == 0)
    {
        // Calculate the buffer pitch from the attributes defined.
        for (const auto &attrib : _attributes)
        {
            auto vertexSize = vertexAttribSize(attrib.format);

            desc.pitch = std::max(attrib.offset + vertexSize, desc.pitch);
        }
    }

    return _attributes;
}

////////////////////////////////////////////////////////////////////////////////
// GraphicsPipelineBuilder Member Definitions
////////////////////////////////////////////////////////////////////////////////
//! @brief Creates an object used to build a graphics pipeline on a GPU device.
//! @param[in] gpu A wrapper for the device one which pipelines will be created.
GraphicsPipelineBuilder::GraphicsPipelineBuilder(const Device &gpu) :
    _device(gpu.verifyAccess("Build graphics pipeline"))
{
    _colourTargets.reserve(4);
    _bufferDescriptions.reserve(4);
    _vertexAttributes.reserve(16);
    reset();
}

//! @brief Begins constructing the definition of a graphics pipeline.
//! @param[in] vertex The vertex shader to run in the pipeline.
//! @param[in] fragment The fragment/pixel shader to run in the pipeline.
//! @param[in] primitiveType The type of primitives the pipeline will render.
void GraphicsPipelineBuilder::begin(const Shader &vertex, const Shader &fragment,
                                    SDL_GPUPrimitiveType primitiveType)
{
    _info.vertex_shader = vertex.get();
    _info.fragment_shader = fragment.get();
    _info.primitive_type = primitiveType;
}

//! @brief Adds a colour swap chain render target to the pipeline.
//! @param[in] swapchain The swap chain to render to.
//! @return The index of the newly added render target.
uint32_t GraphicsPipelineBuilder::addRenderTarget(const Swapchain &swapchain)
{
    SDL_GPUColorTargetDescription target;
    uint32_t targetIndex = static_cast<uint32_t>(_colourTargets.size());

    Ag::zeroFill(target);
    target.format = swapchain.getFormat();

    _colourTargets.push_back(target);

    return targetIndex;
}

//! @brief Adds the definition of a vertex buffer to be processed by the
//! vertex shader.
//! @param[in] builder The object used to incrementally define the
//! vertex buffer input format and usage.
//! @return The index of the newly added vertex buffer.
uint32_t GraphicsPipelineBuilder::addVertexBufferDescription(const VertexDescriptionBuilder &builder)
{
    SDL_GPUVertexBufferDescription bufferDesc;
    uint32_t bufferId = static_cast<uint32_t>(_bufferDescriptions.size());

    const auto &attribs = builder.build(bufferDesc);

    size_t attribCount = Ag::bulkAppend(_vertexAttributes, attribs.begin(), attribs.end());

    if (attribCount > 0)
        _bufferDescriptions.push_back(bufferDesc);

    return bufferId;
}

//! @brief Constructs a graphics pipeline from the currently
//! accumulated definition.
//! @return An object wrapping the new graphics pipeline.
GraphicsPipeline GraphicsPipelineBuilder::createPipeline() const
{
    if (_device == nullptr)
        throw ObjectNotBoundException("GraphicsPipelineBuilder", "Build graphics pipeline");

    SDL_GPUGraphicsPipelineCreateInfo info = _info;

    if (_colourTargets.empty() == false)
    {
        auto &targetInfo = info.target_info;

        targetInfo.num_color_targets = static_cast<decltype(info.target_info.num_color_targets)>(_colourTargets.size());
        targetInfo.color_target_descriptions = _colourTargets.data();
    }

    if ((_bufferDescriptions.empty() == false) &&
        (_vertexAttributes.empty() == false))
    {
        // Fill in the vertex input state.
        auto &input = info.vertex_input_state;

        input.num_vertex_buffers = static_cast<decltype(input.num_vertex_buffers)>(_bufferDescriptions.size());
        input.vertex_buffer_descriptions = _bufferDescriptions.data();
        input.num_vertex_attributes = static_cast<decltype(input.num_vertex_attributes)>(_vertexAttributes.size());
        input.vertex_attributes = _vertexAttributes.data();
    }

    auto pipeline = SDL_CreateGPUGraphicsPipeline(_device, &info);

    if (pipeline == nullptr)
        throw ApiException("SDL_CreateGPUGraphicsPipeline()");

    return GraphicsPipeline(_device, pipeline);
}

//! @brief Resets the definition of the graphic pipeline to an empty state.
void GraphicsPipelineBuilder::reset()
{
    Ag::zeroFill(_info);
    _colourTargets.clear();
    _bufferDescriptions.clear();
    _vertexAttributes.clear();
}

////////////////////////////////////////////////////////////////////////////////
// CopyPass Member Definitions
////////////////////////////////////////////////////////////////////////////////
//! @brief Constructs an empty wrapper for a GPU copy pass resource.
CopyPass::CopyPass() :
    _copyPass(nullptr)
{
}

//! @brief Constructs a wrapper for a GPU copy pass resource.
//! @param[in] CopyPass The SDL copy pass object to wrap, can be nullptr.
CopyPass::CopyPass(SDL_GPUCopyPass *CopyPass) :
    _copyPass(CopyPass)
{
}

//! @brief Acquires a copy pass resource form another wrapper object.
//! @param[in] rhs The wrapper object to acquire the resource from.
CopyPass::CopyPass(CopyPass &&rhs) noexcept :
    _copyPass(std::exchange(rhs._copyPass, nullptr))
{
}

//! @brief Ensures any wrapped copy pass resource is ended on destruction.
CopyPass::~CopyPass()
{
    endPass();
}

//! @brief Determines if the wrapper is bound to an underlying GPU copy
//! pass resource.
//! @retval true The object is bound to a render pass.
//! @retval false The object is in an unbound state.
bool CopyPass::isBound() const
{
    return _copyPass != nullptr;
}

//! @brief Explicitly ends the wrapped copy pass, if any, leaving the object
//! in an unbound state.
void CopyPass::endPass()
{
    auto copyPass = std::exchange(_copyPass, nullptr);

    if (copyPass != nullptr)
    {
        SDL_EndGPUCopyPass(copyPass);
    }
}

//! @brief Acquires a copy pass resource form another wrapper object.
//! @param[in] rhs The wrapper object to acquire the resource from.
//! @returns A reference to the current object.
CopyPass &CopyPass::operator=(CopyPass &&rhs) noexcept
{
    if (_copyPass == rhs._copyPass)
        return *this;

    endPass();

    _copyPass = std::exchange(rhs._copyPass, nullptr);

    return *this;
}

//! @brief Requests an upload into a GPU resource buffer.
//! @param[in] destBuffer The GPU resource to copy the data to.
//! @param[in] destOffset The offset into the receiving buffer to start copying to.
//! @param[in] sourceBuffer The transfer buffer to copy from.
//! @param[in] sourceOffset The offset into the transfer buffer to start copying from.
//! @param[in] size The count of bytes to copy.
//! @param[in] cycle If true, cycles the buffer if it is already bound, otherwise
//! overwrites the data.
void CopyPass::uploadToBuffer(const ResourceBuffer &destBuffer, uint32_t destOffset,
                              const TransferBuffer &sourceBuffer, uint32_t sourceOffset,
                              uint32_t size, bool cycle) const
{
    utf8_cptr_t op = "Upload to resource buffer";

    auto copyPass = verifyAccess(op);

    SDL_GPUTransferBufferLocation source = { 0 };
    source.transfer_buffer = sourceBuffer.verifyAccess(op);
    source.offset = sourceOffset;

    SDL_GPUBufferRegion dest = { 0 };
    dest.buffer = destBuffer.verifyAccess(op);
    dest.offset = destOffset;
    dest.size = size;

    SDL_UploadToGPUBuffer(copyPass, &source, &dest, cycle);
}

//! @brief Verifies that the object is in a bound state before an operation.
//! @param[in] operation A description of the operation about to be performed.
//! @return A pointer to a valid render pass resource.
//! @throws ObjectNotBoundException If the object is in an unbound state.
SDL_GPUCopyPass *CopyPass::verifyAccess(utf8_cptr_t operation) const
{
    if (_copyPass == nullptr)
        throw ObjectNotBoundException("GPU Copy Pass", operation);

    return _copyPass;
}

////////////////////////////////////////////////////////////////////////////////
// VertexBufferBindingBuilder Member Definitions
////////////////////////////////////////////////////////////////////////////////
//! @brief Constructs an object to incrementally build up a set of vertex
//! buffers to be bound to a render pass.
//! @param[in] firstSlot The index of the slot of the first buffer to bind.
VertexBufferBindingBuilder::VertexBufferBindingBuilder(uint32_t firstSlot /*= 0*/) :
    _firstSlot(firstSlot)
{
    _bindings.reserve(16);
}

//! @brief Gets the index of the slot of the first buffer to bind.
uint32_t VertexBufferBindingBuilder::getFirstSlot() const
{
    return _firstSlot;
}

//! @brief Resets the object, removing all previous buffer bindings.
//! @param[in] firstSlot The index of the slot of the first buffer to bind.
void VertexBufferBindingBuilder::begin(uint32_t firstSlot /*= 0*/)
{
    _firstSlot = firstSlot;
    _bindings.clear();
}

//! @brief Adds a buffer to be bound.
//! @param[in] buffer The wrapper of the vertex buffer resource to bind.
//! @param[in] offset The first byte of data in the buffer to access via the binding.
void VertexBufferBindingBuilder::addBinding(const ResourceBuffer &buffer, uint32_t offset /*= 0*/)
{
    auto rawBuffer = buffer.verifyAccess("Bind vertex buffer");

    SDL_GPUBufferBinding &binding = _bindings.emplace_back();
    binding.buffer = rawBuffer;
    binding.offset = offset;
}

//! @brief Gets a collection of all accumulated bindings.
const BufferBindingCollection &VertexBufferBindingBuilder::getBindings() const
{
    return _bindings;
}

////////////////////////////////////////////////////////////////////////////////
// Sampler Member Definitions
////////////////////////////////////////////////////////////////////////////////
//! @brief Constructs an empty wrapper for a GPU texture sampler.
Sampler::Sampler() :
    _parentDevice(nullptr),
    _sampler(nullptr)
{
}

//! @brief Creates a wrapper for a GPU texture sampler.
//! @param[in] parentDevice The device on which the sampler as created.
//! @param[in] sampler The sampler resource to wrap.
Sampler::Sampler(SDL_GPUDevice *parentDevice, SDL_GPUSampler *sampler) :
    _parentDevice((sampler == nullptr) ? nullptr : parentDevice),
    _sampler((parentDevice == nullptr) ? nullptr : sampler)
{
}

//! @brief Acquires a sampler resource from another wrapper.
//! @param[in] rhs The wrapper to obtain the resource from.
Sampler::Sampler(Sampler &&rhs) noexcept :
    _parentDevice(std::exchange(rhs._parentDevice, nullptr)),
    _sampler(std::exchange(rhs._sampler, nullptr))
{
}

//! @brief Ensures any underlying sampler resource is properly disposed of.
Sampler::~Sampler()
{
    release();
}

//! @brief Determines if the object is bound to a valid sampler resource.
//! @retval true The object is bound to an underlying GPU sampler.
//! @retval false The object is in an unbound state.
bool Sampler::isBound() const
{
    return _sampler != nullptr;
}

//! @brief Disposes of any wrapped sampler resource.
void Sampler::release()
{
    auto device = std::exchange(_parentDevice, nullptr);
    auto sampler = std::exchange(_sampler, nullptr);

    if ((device != nullptr) && (sampler != nullptr))
    {
        SDL_ReleaseGPUSampler(device, sampler);
    }
}

//! @brief Acquires a sampler resource from another wrapper, disposing of any
//! currently wrapped sampler resource.
//! @param[in] rhs The wrapper to obtain the resource from.
//! @returns A reference to the current object.
Sampler &Sampler::operator=(Sampler &&rhs) noexcept
{
    if ((_parentDevice == rhs._parentDevice) &&
        (_sampler == rhs._sampler))
        return *this;

    release();

    _parentDevice = std::exchange(rhs._parentDevice, nullptr);
    _sampler = std::exchange(rhs._sampler, nullptr);

    return *this;
}

//! @brief Verifies that the object is in a bound state before returning the
//! valid GPU sampler resource.
//! @param[in] operation The description of the operation the sampler will be
//! used for.
//! @return A pointer to the underlying sampler resource.
//! @throws ObjectNotBoundException If the object is not currently bound to
//! a valid sampler resource.
SDL_GPUSampler *Sampler::verifyAccess(utf8_cptr_t operation) const
{
    if (_sampler == nullptr)
        throw ObjectNotBoundException("GPU Sampler", operation);

    return _sampler;
}

////////////////////////////////////////////////////////////////////////////////
// RenderPass Member Definitions
////////////////////////////////////////////////////////////////////////////////
//! @brief Constructs an empty wrapper for a GPU render pass resource.
RenderPass::RenderPass() :
    _renderPass(nullptr)
{
}

//! @brief Constructs a wrapper for a GPU render pass resource.
//! @param[in] renderPass The SDL render pass object to wrap, can be nullptr.
RenderPass::RenderPass(SDL_GPURenderPass *renderPass) :
    _renderPass(renderPass)
{
}

//! @brief Acquires a render pass resource form another wrapper object.
//! @param[in] rhs The wrapper object to acquire the resource from.
RenderPass::RenderPass(RenderPass &&rhs) noexcept :
    _renderPass(std::exchange(rhs._renderPass, nullptr))
{
}

//! @brief Ensures any wrapped render pass resource is ended on destruction.
RenderPass::~RenderPass()
{
    endPass();
}

//! @brief Determines if the wrapper is bound to an underlying GPU render
//! pass resource.
//! @retval true The object is bound to a render pass.
//! @retval false The object is in an unbound state.
bool RenderPass::isBound() const
{
    return _renderPass != nullptr;
}

//! @brief Binds a graphic pipeline to the render pass.
//! @param[in] pipeline The wrapper for the pipeline to bind.
//! @throws ObjectNotBoundException If either the object or @p pipeline are not
//! bound to valid underlying resources.
void RenderPass::bindPipeline(const GraphicsPipeline &pipeline) const
{
    utf8_cptr_t operation = "Bind graphics pipeline";
    auto renderPass = verifyAccess(operation);
    auto rawPipeline = pipeline.verifyAccess(operation);

    SDL_BindGPUGraphicsPipeline(renderPass, rawPipeline);
}

//! @brief Binds a set of vertex buffers to the pass.
//! @param[in] bindings The accumulated set of buffer bindings to apply.
void RenderPass::bindVertexBuffers(const VertexBufferBindingBuilder &bindings) const
{
    auto renderPass = verifyAccess("Bind vertex buffers");
    const auto &bindingDescriptions = bindings.getBindings();

    SDL_BindGPUVertexBuffers(renderPass, bindings.getFirstSlot(),
                             bindingDescriptions.data(),
                             static_cast<uint32_t>(bindingDescriptions.size()));
}

//! @brief Draw data using the currently bound graphics state.
//! @param[in] vertexCount The number of vertices to draw.
//! @param[in] instanceCount The number of instances that will be drawn.
//! @param[in] firstVertex The index of the first vertex to draw.
//! @param[in] firstInstance The ID of the first instance to draw.
void RenderPass::drawPrimitives(uint32_t vertexCount,
                                uint32_t instanceCount /*= 1*/,
                                uint32_t firstVertex /*= 0*/,
                                uint32_t firstInstance /*= 0*/) const
{
    if ((vertexCount < 1) || (instanceCount < 1))
        return;

    auto renderPass = verifyAccess("Draw primitives");

    SDL_DrawGPUPrimitives(renderPass, vertexCount, instanceCount,
                          firstVertex, firstInstance);
}

//! @brief Explicitly ends the wrapped render pass, if any, leaving the object
//! in an unbound state.
void RenderPass::endPass()
{
    auto renderPass = std::exchange(_renderPass, nullptr);

    if (renderPass != nullptr)
    {
        SDL_EndGPURenderPass(renderPass);
    }
}

//! @brief Acquires a render pass resource form another wrapper object.
//! @param[in] rhs The wrapper object to acquire the resource from.
//! @returns A reference to the current object.
RenderPass &RenderPass::operator=(RenderPass &&rhs) noexcept
{
    if (_renderPass == rhs._renderPass)
        return *this;

    endPass();

    _renderPass = std::exchange(rhs._renderPass, nullptr);

    return *this;
}

//! @brief Verifies that the object is in a bound state before an operation.
//! @param[in] operation A description of the operation about to be performed.
//! @return A pointer to a valid render pass resource.
//! @throws ObjectNotBoundException If the object is in an unbound state.
SDL_GPURenderPass *RenderPass::verifyAccess(utf8_cptr_t operation) const
{
    if (_renderPass == nullptr)
        throw ObjectNotBoundException("GPU Render Pass", operation);

    return _renderPass;
}

////////////////////////////////////////////////////////////////////////////////
// CommandBuffer Member Definitions
////////////////////////////////////////////////////////////////////////////////
//! @brief Constructs an empty wrapper for a GPU command buffer.
CommandBuffer::CommandBuffer() :
    _parentDevice(nullptr),
    _commandBuffer(nullptr)
{
}

//! @brief Constructs a wrapper for a GPU command buffer acquired form
//! another wrapper.
//! @param[in] rhs The wrapper to acquire the buffer from.
CommandBuffer::CommandBuffer(CommandBuffer &&rhs) noexcept :
    _parentDevice(rhs._parentDevice),
    _commandBuffer(rhs._commandBuffer)
{
    rhs._commandBuffer = nullptr;
}

//! @brief Constructs a wrapper for a GPU command buffer.
//! @param[in] commandBuffer The buffer to wrap, can be nullptr.
CommandBuffer::CommandBuffer(SDL_GPUDevice *device, SDL_GPUCommandBuffer *commandBuffer) :
    _parentDevice(device),
    _commandBuffer(commandBuffer)
{
}

//! @brief Ensures any wrapped buffer is submitted for processing without
//! throwing an exceptions on failure.
CommandBuffer::~CommandBuffer()
{
    auto commandBuffer = std::exchange(_commandBuffer, nullptr);
    _parentDevice = nullptr;

    // If a buffer is outstanding, submit it without throwing an exception,
    // destructions should not throw exceptions.
    if (commandBuffer != nullptr)
    {
        SDL_SubmitGPUCommandBuffer(commandBuffer);
    }
}

//! @brief Determines if the wrapper is bound to an underlying command
//! buffer resource.
//! @retval true The object is bound to a resource.
//! @retval false The object is in an unbound state.
bool CommandBuffer::isBound() const
{
    return _commandBuffer != nullptr;
}

//! @brief Cancels the use of the command buffer, setting the object to an
//! unbound state.
void CommandBuffer::cancel()
{
    auto commandBuffer = std::exchange(_commandBuffer, nullptr);
    _parentDevice = nullptr;

    if (commandBuffer == nullptr)
        return;

    if (SDL_CancelGPUCommandBuffer(commandBuffer) == false)
    {
        throw ApiException("SDL_CancelGPUCommandBuffer()");
    }
}

//! @brief Submits the command buffer for processing, setting the object to
//! an unbound state.
void CommandBuffer::submit()
{
    auto commandBuffer = std::exchange(_commandBuffer, nullptr);
    _parentDevice = nullptr;

    if (commandBuffer == nullptr)
        return;

    if (SDL_SubmitGPUCommandBuffer(commandBuffer) == false)
    {
        throw ApiException("SDL_CancelGPUCommandBuffer()");
    }
}

//! @brief Submits the command buffer for processing, setting the object to
//! an unbound state and then waits for completion of the commands.
void CommandBuffer::submitAndWait()
{
    auto fence = submitAndAcquireFence();

    fence.wait();
}

//! @brief Submits the command buffer for processing and returns a
//! synchronisation primitive which can be used to await completion.
//! @return A fence primitive which can be waited on for completion
//! of the submitted commands.
Fence CommandBuffer::submitAndAcquireFence()
{
    auto parentDevice = std::exchange(_parentDevice, nullptr);
    auto commandBuffer = std::exchange(_commandBuffer, nullptr);

    if (commandBuffer == nullptr)
        return Fence();

    SDL_GPUFence *fence = SDL_SubmitGPUCommandBufferAndAcquireFence(commandBuffer);

    if (fence == nullptr)
    {
        throw ApiException("SDL_CancelGPUCommandBuffer()");
    }

    return Fence(parentDevice, fence);
}

//! @brief Blocks the thread until a swap chain texture is available to be
//! acquired, and then acquires it.
//! @param[in] window The window connected to the swap chain.
//! @param[out] width Receives the width of the texture.
//! @param[out] height Receives the height of the texture.
//! @return A wrapper for the acquired texture.
//! @throws ObjectNotBoundException If the object is not bound to an underlying
//! command buffer resource.
//! @throws ApiException If the SDL operation fails.
Texture CommandBuffer::waitAndAcquireSwapchainTexture(const Window &window, uint32_t &width,
                                                      uint32_t &height) const
{
    return waitAndAcquireSwapchainTexture(window.verifyAccess("Obtain swap chain texture"),
                                          width, height);
}

//! @brief Blocks the thread until a swap chain texture is available to be
//! acquired, and then acquires it.
//! @param[in] window A pointer to the window connected to the swap chain.
//! @param[out] width Receives the width of the texture.
//! @param[out] height Receives the height of the texture.
//! @return A wrapper for the acquired texture.
//! @throws ObjectNotBoundException If the object is not bound to an underlying
//! command buffer resource.
//! @throws ApiException If the SDL operation fails.
Texture CommandBuffer::waitAndAcquireSwapchainTexture(SDL_Window *window, uint32_t &width,
                                                      uint32_t &height) const
{
    auto commandBuffer = verifyAccess("Acquire swapchain texture");
    SDL_GPUTexture *rawTexture = nullptr;
    width = 0;
    height = 0;

    if (SDL_WaitAndAcquireGPUSwapchainTexture(commandBuffer, window, &rawTexture, &width, &height))
    {
        return Texture(_parentDevice, rawTexture, false);
    }

    throw ApiException("SDL_WaitAndAcquireGPUSwapchainTexture()");
}

//! @brief Begins a describing a copy pass in the command buffer.
//! @return A new copy pass to be populated with copy operations.
//! @throws ObjectNotBoundException If the object is not bound to an underlying
//! command buffer resource.
//! @throws ApiException If the SDL operation fails.
CopyPass CommandBuffer::beginCopyPass() const
{
    auto commandBuffer = verifyAccess("Begin render pass");

    SDL_GPUCopyPass *copyPass = SDL_BeginGPUCopyPass(commandBuffer);

    if (copyPass == nullptr)
        throw ApiException("SDL_BeginGPUCopyPass()");

    return CopyPass(copyPass);
}

//! @brief Begins a render pass on a simple render target texture.
//! @param[in] target The texture to receive the result of the render pass.
//! @param[in] clearColour The colour used to fill the texture before processing
//! any further rendering instructions.
//! @return An object wrapping the render pass object to record graphic operations.
//! @throws ObjectNotBoundException If the object is not bound to an underlying
//! command buffer resource.
//! @throws ApiException If the SDL operation fails.
RenderPass CommandBuffer::beginRenderPass(const Texture &target, const FColour &clearColour) const
{
    auto commandBuffer = verifyAccess("Begin render pass");

    if (target.isBound() == false)
        throw ObjectNotBoundException("GPU Render Target Texture", "Begin render pass");

    SDL_GPUColorTargetInfo colorTargetInfo = { 0 };
    colorTargetInfo.texture = target.get();
    colorTargetInfo.clear_color = clearColour;
    colorTargetInfo.load_op = SDL_GPU_LOADOP_CLEAR;
    colorTargetInfo.store_op = SDL_GPU_STOREOP_STORE;

    SDL_GPURenderPass *renderPass = SDL_BeginGPURenderPass(commandBuffer,
                                                           &colorTargetInfo,
                                                           1, nullptr);

    if (renderPass == nullptr)
        throw ApiException("SDL_BeginGPURenderPass()");

    return RenderPass(renderPass);
}

//! @brief Acquires a command buffer from another wrapper.
//! @param[in] rhs The wrapper to transfer the underlying resource from.
//! @return A reference to the current object.
//! @note No exception is thrown if the original command buffer failed to be
//! submitted for processing.
CommandBuffer &CommandBuffer::operator=(CommandBuffer &&rhs) noexcept
{
    if (rhs._commandBuffer == _commandBuffer)
        return *this;

    // Dispose of the old command buffer (if any) without throwing an exception.
    auto oldCommandBuffer = std::exchange(_commandBuffer, nullptr);
    _parentDevice = nullptr;

    if (oldCommandBuffer != nullptr)
    {
        // Submit the old command buffer without throwing an exception.
        SDL_SubmitGPUCommandBuffer(oldCommandBuffer);
    }

    // Acquire the assigned command buffer, whether valid or not.
    _parentDevice = std::exchange(rhs._parentDevice, nullptr);
    _commandBuffer = std::exchange(rhs._commandBuffer, nullptr);

    return *this;
}

//! @brief Verifies that the object is in a bound state to commence a named
//! operation.
//! @param[in] operation The operation about to be performed.
//! @return A pointer to a valid command buffer resource.
//! @throws ObjectNotBoundException If the object is in an unbound state.
SDL_GPUCommandBuffer *CommandBuffer::verifyAccess(utf8_cptr_t operation) const
{
    if (_commandBuffer == nullptr)
        throw ObjectNotBoundException("GPU Command Buffer", operation);

    return _commandBuffer;
}

////////////////////////////////////////////////////////////////////////////////
// Swapchain Member Definitions
////////////////////////////////////////////////////////////////////////////////
//! Constructs an empty wrapper for a render target window.
Swapchain::Swapchain() :
    _device(nullptr),
    _window(nullptr)
{
}

//! @brief Constructs a wrapper for a render target window.
//! @param[in] device The GPU device attached to the window swap chain.
//! @param[in] window The window the swap chain renders to.
Swapchain::Swapchain(SDL_GPUDevice *device, SDL_Window *window) :
    _device((_window == nullptr) ? nullptr : device),
    _window((_device == nullptr) ? nullptr : window)
{
}

//! @brief Acquires a window render target from another wrapper.
//! @param[in] rhs The wrapper to acquire the render target from.
Swapchain::Swapchain(Swapchain &&rhs) noexcept :
    _device(std::exchange(rhs._device, nullptr)),
    _window(std::exchange(rhs._window, nullptr))
{
}

//! @brief Ensures the swap chain associated with the window is disposed of.
Swapchain::~Swapchain()
{
    release();
}

//! @brief Determines if the object wraps a valid swap chain.
//! @retval true The object wraps a GPU device and associated window.
//! @retval false The object is in an unbound state.
bool Swapchain::isBound() const
{
    return (_device != nullptr) && (_window != nullptr);
}

//! @brief Gets the format of the swap chain back buffer.
//! @returns A valid texture format, or SDL_GPU_TEXTUREFORMAT_INVALID if the
//! object is in an unbound state.
SDL_GPUTextureFormat Swapchain::getFormat() const
{
    SDL_GPUTextureFormat format = SDL_GPU_TEXTUREFORMAT_INVALID;

    if (isBound())
    {
        format = SDL_GetGPUSwapchainTextureFormat(_device, _window);
    }

    return format;
}

//! @brief Determines if a specified presentation mode is valid on the
//! swap chain.
//! @param[in] mode The presentation mode to query.
//! @retval true The presentation mode is supported.
//! @retval false The mode is not supported or the object is unbound.
bool Swapchain::supportPresentMode(SDL_GPUPresentMode mode) const
{
    bool isSupported = false;

    if (isBound())
    {
        isSupported = SDL_WindowSupportsGPUPresentMode(_device, _window, mode);
    }

    return isSupported;
}

//! @brief Determines whether the swap chain supports a specified
//! composition mode.
//! @param[in] composition The mode to query for.
//! @retval true The specified composition mode is supported.
//! @retval false The mode is not supported or the object is in an unbound state.
bool Swapchain::supportsComposition(SDL_GPUSwapchainComposition composition) const
{
    bool isSupported = false;

    if (isBound())
    {
        isSupported = SDL_WindowSupportsGPUSwapchainComposition(_device, _window,
                                                                composition);
    }

    return isSupported;
}

//! @brief Ensures any wrapped swap chain is properly disposed of.
void Swapchain::release()
{
    auto device = std::exchange(_device, nullptr);
    auto window = std::exchange(_window, nullptr);

    if ((device != nullptr) && (window != nullptr))
    {
        SDL_ReleaseWindowFromGPUDevice(device, window);
    }
}

//! @brief Acquires a swap chain resource from another wrapper.
//! @param[in] rhs The wrapper to obtain the swap chain from.
//! @return A reference to the current object.
Swapchain &Swapchain::operator=(Swapchain &&rhs) noexcept
{
    if ((_device == rhs._device) && (_window == rhs._window))
        return *this;

    release();

    _device = std::exchange(rhs._device, nullptr);
    _window = std::exchange(rhs._window, nullptr);

    return *this;
}

////////////////////////////////////////////////////////////////////////////////
// SamplerBuilder Member Definitions
////////////////////////////////////////////////////////////////////////////////
//! @brief Constructs an object which can be used to incrementally configure a
//! GPU texture sampler for creation.
//! @param[in] gpu A wrapper for the GPU device on which samplers are to be
//! created.
//! @throws ObjectNotBoundException If @p gpu is in an unbound state.
SamplerBuilder::SamplerBuilder(const Device &gpu) :
    _parentDevice(gpu.verifyAccess("Create sampler"))
{
    reset();
}

//! @brief Gets the current set of sampler creation parameters.
const SDL_GPUSamplerCreateInfo &SamplerBuilder::getCreationParameters() const
{
    return _info;
}

//! @brief Resets the sampler creation parameters to their default state.
void SamplerBuilder::reset()
{
    Ag::zeroFill(_info);
}

//! @brief Sets minification and magnification filter modes to apply to lookups.
//! @param[in] bothFilters The mode used for both minification and
//! magnification, such as SDL_GPU_FILTER_LINEAR.
void SamplerBuilder::setFilter(SDL_GPUFilter bothFilters)
{
    _info.min_filter = _info.mag_filter = bothFilters;
}

//! @brief Sets minification and magnification filter modes to apply to lookups.
//! @param[in] minFilter The mode used for minification, such as
//! SDL_GPU_FILTER_LINEAR.
//! @param[in] magFilter The mode used for magnification, such as
//! SDL_GPU_FILTER_NEAREST.
void SamplerBuilder::setFilter(SDL_GPUFilter minFilter, SDL_GPUFilter magFilter)
{
    _info.min_filter = minFilter;
    _info.mag_filter = magFilter;
}

//! @brief Sets the mipmap filter mode to apply to lookups.
//! @param[in] mode The new mipmap mode, such as
//! SDL_GPU_SAMPLERMIPMAPMODE_NEAREST or SDL_GPU_SAMPLERMIPMAPMODE_LINEAR.
void SamplerBuilder::setMipMapMode(SDL_GPUSamplerMipmapMode mode)
{
    _info.mipmap_mode = mode;
}

//! @brief Sets the addressing mode for texture coordinates on the U, V and W
//! axes outside of the range [0, 1).
//! @param[in] mode The mode to apply, such as SDL_GPU_SAMPLERADDRESSMODE_REPEAT,
//! SDL_GPU_SAMPLERADDRESSMODE_MIRRORED_REPEAT or
//! SDL_GPU_SAMPLERADDRESSMODE_CLAMP_TO_EDGE.
void SamplerBuilder::setAddressMode(SDL_GPUSamplerAddressMode mode)
{
    _info.address_mode_u = _info.address_mode_v = _info.address_mode_w = mode;
}

//! @brief Sets the addressing mode for texture coordinates on the U, V and W
//! axes outside of the range [0, 1).
//! @param[in] uMode The mode to apply to the U texture axis.
//! @param[in] vMode The mode to apply to the V texture axis.
//! @param[in] wMode The mode to apply to the W texture axis.
void SamplerBuilder::setAddressMode(SDL_GPUSamplerAddressMode uMode,
                                    SDL_GPUSamplerAddressMode vMode,
                                    SDL_GPUSamplerAddressMode wMode)
{
    _info.address_mode_u = uMode;
    _info.address_mode_v = vMode;
    _info.address_mode_w = wMode;
}

//! @brief Sets mipmap Level of Detail parameters.
//! @param[in] bias The bias added to LOD calculations.
//! @param[in] minLOD The minimum of the computed LOD value.
//! @param[in] maxLOD The maximum of the computed LOD value.
void SamplerBuilder::setLODParameters(float bias, float minLOD, float maxLOD)
{
    _info.mip_lod_bias = bias;
    _info.min_lod = minLOD;
    _info.max_lod = maxLOD;
}

//! @brief Enables anisotropy and sets the anisotropy value clamp used by
//! the sampler
//! @param[in] max The maximum value.
void SamplerBuilder::setMaxAnisotropy(float max)
{
    _info.max_anisotropy = max;
    _info.enable_anisotropy = true;
}

//! @brief Disables anisotropy in the sampler.
void SamplerBuilder::disableAnisotropy()
{
    _info.max_anisotropy = 0;
    _info.enable_anisotropy = false;
}

//! @brief Enables comparisons and sets the comparison operator to apply to
//! fetched data before filtering.
//! @param[in] op The comparison operator to apply.
void SamplerBuilder::setComparisonOperator(SDL_GPUCompareOp op)
{
    _info.compare_op = op;
    _info.enable_compare = (op != SDL_GPU_COMPAREOP_INVALID);
}

//! @brief Disables comparisons on fetched data.
void SamplerBuilder::disableComparison()
{
    _info.compare_op = SDL_GPU_COMPAREOP_INVALID;
    _info.enable_compare = false;
}

//! @brief Creates a sampler on the GPU device the object is bound to.
//! @return A wrapper for the created Sampler.
//! @throws ObjectNotBound If the object was not bound to a valid GPU device.
//! @throws ApiException If SDL cannot create the sampler.
Sampler SamplerBuilder::create() const
{
    auto sampler = SDL_CreateGPUSampler(_parentDevice, &_info);

    if (sampler == nullptr)
        throw ApiException("SDL_CreateGPUSampler()");

    return Sampler(_parentDevice, sampler);
}

////////////////////////////////////////////////////////////////////////////////
// Device Member Definitions
////////////////////////////////////////////////////////////////////////////////
//! @brief Constructs an unbound wrapper for a GPU device.
Device::Device() :
    _device(nullptr)
{
}

//! @brief Constructs a wrapper to a GPU device bound to an underlying resource.
//! @param[in] resource The GPU resource to bind to, possibly nullptr.
Device::Device(SDL_GPUDevice *resource) :
    _device(nullptr)
{
    init(resource);
}

//! @brief Acquires a GPU resource from another wrapper.
//! @param[in] rhs The wrapper containing the resource to acquire.
Device::Device(Device &&rhs) noexcept :
    _device(rhs._device)
{
    rhs._device = nullptr;
    rhs._backendName = String::Empty;
}

//! @brief Ensures any bound device is disposed of at destruction.
Device::~Device()
{
    release();
}

//! @brief Determines if the wrapper is bound to an underlying GPU device resource.
//! @retval true The object is bound to a GPU device.
//! @retval false The object is unbound.
bool Device::isBound() const { return _device != nullptr; }

//! @brief Gets the name of the SDL3 back end of the bound GPU device.
//! @return The back end name or an empty string if the object is unbound.
string_cref_t Device::getBackendName() const { return _backendName; }

//! @brief Gets the shader format supported by the wrapped GPU device.
//! @return A bit mask of supported formats, such as SDL_GPU_SHADERFORMAT_SPIRV.
SDL_GPUShaderFormat Device::getSupportedShaderFormats() const
{
    SDL_GPUShaderFormat format = 0;

    if (_device != nullptr)
    {
        format = SDL_GetGPUShaderFormats(_device);
    }

    return format;
}

//! @brief Gets the names of the available GPU back ends supported by SDL on the
//! current system.
//! @return A list of GPU back end names.
StringCollection Device::getAvailableBackends()
{
    StringCollection backendNames;
    int backendCount = SDL_GetNumGPUDrivers();

    if (backendCount > 0)
    {
        backendNames.reserve(Ag::toSize(backendCount));

        for (int i = 0; i < backendCount; ++i)
        {
            const char *backendName = SDL_GetGPUDriver(i);

            if (backendName != nullptr)
                backendNames.emplace_back(backendName);
        }
    }

    return backendNames;
}

// TODO: Uncomment when SDL_GetGPUDeviceProperties() entry point becomes
// available. Documentation marks it as requiring SDL 3.4.

////! @brief Gets metadata properties associated with the GPU device.
////! @return A set of properties, empty if not device is bound.
//PropertySet Device::getProperties() const
//{
//    SDL_PropertiesID props = 0;
//
//    if (isBound())
//    {
//        props = SDL_GetGPUDeviceProperties(_device);
//    }
//
//    return PropertySet(props);
//}


//! @brief Gets the set of shader formats supported by the bound device.
//! @return A bitfield defining the supported shader program formats, 0 if no
//! device is bound.
SDL_GPUShaderFormat Device::getShaderFormats() const
{
    SDL_GPUShaderFormat formats = 0;

    if (isBound())
    {
        formats = SDL_GetGPUShaderFormats(_device);
    }

    return formats;
}

//! @brief Determines if the bound device supports a specific combination of
//! texture format, type and usage.
//! @param[in] format The binary format of the texture data to test, such as
//! SDL_GPU_TEXTUREFORMAT_R8G8B8A8_UNORM.
//! @param[in] type The arrangements of images in the texture to test, such as
//! SDL_GPU_TEXTURETYPE_2D.
//! @param[in] usage A bitfield of possible texture usages, for example.
//! SDL_GPU_TEXTUREUSAGE_GRAPHICS_STORAGE_READ.
//! @retval true If that combination of format, type and usage is supported by
//! the device.
//! @retval false The combination is not supported or the object is unbound.
bool Device::supportsTextureFormat(SDL_GPUTextureFormat format,
                                   SDL_GPUTextureType type,
                                   SDL_GPUTextureUsageFlags usage) const
{
    bool isSupported = false;

    if (isBound())
    {
        isSupported = SDL_GPUTextureSupportsFormat(_device, format, type, usage);
    }

    return isSupported;
}

//! @brief Determines if a sample count for a texture format is supported on
//! the bound GPU device.
//! @param[in] format The texture format to query, such as
//! SDL_GPU_TEXTUREFORMAT_R8G8B8A8_UNORM.
//! @param[in] sampleCount The multi-sampling mode to query, for example
//! SDL_GPU_SAMPLECOUNT_4.
//! @retval true The sample count is supported on the bound device with the
//! given texture format.
//! @retval false The sample count is not supported or the object is unbound.
bool Device::supportsTextureSampleCount(SDL_GPUTextureFormat format,
                                        SDL_GPUSampleCount sampleCount) const
{
    bool isSupported = false;

    if (isBound())
    {
        isSupported = SDL_GPUTextureSupportsSampleCount(_device, format,
                                                        sampleCount);
    }

    return isSupported;
}

//! @brief Creates a GPU device resource, replacing any previously bound resource.
//! @param[in] shaderFormatFlags Flags defining the required shader formats such as
//! SDL_GPU_SHADERFORMAT_SPIRV.
//! @param[in] debug True for debug mode, false otherwise.
//! @param[in] preferredBackEnd The optional name of the preferred back end, nullptr for
//! the default back end on the current system.
//! @retval true A GPU device was successfully created and bound.
//! @retval false A GPU device resource was not created, the object is unbound.
//! @throws ApiException If a GPU object cannot be created.
void Device::create(SDL_GPUShaderFormat shaderFormatFlags, bool debug, utf8_cptr_t preferredBackEnd)
{
    if (tryCreate(shaderFormatFlags, debug, preferredBackEnd) == false)
    {
        throw ApiException("SDL_CreateGPUDevice()");
    }
}

//! @brief Attempts to create a GPU device resource, replacing any previously bound resource.
//! @param[in] shaderFormatFlags Flags defining the required shader formats such as
//! SDL_GPU_SHADERFORMAT_SPIRV.
//! @param[in] debug True for debug mode, false otherwise.
//! @param[in] preferredBackEnd The optional name of the preferred back end, nullptr for
//! the default back end on the current system.
//! @retval true A GPU device was successfully created and bound.
//! @retval false A GPU device resource was not created, the object is unbound.
bool Device::tryCreate(SDL_GPUShaderFormat shaderFormatFlags, bool debug,
                       utf8_cptr_t preferredBackEnd)
{
    SDL_GPUDevice *device = SDL_CreateGPUDevice(shaderFormatFlags, debug, preferredBackEnd);

    return init(device);
}

//! @brief Creates a system memory buffer used to transfer to/from GPU memory.
//! @param[in] usage The intended usage of the buffer, generally either
//! SDL_GPU_TRANSFERBUFFERUSAGE_UPLOAD or SDL_GPU_TRANSFERBUFFERUSAGE_DOWNLOAD.
//! @param[in] size The count of bytes in the buffer.
//! @return An object representing the newly created buffer object.
//! @throws ObjectNotBound If the object does not wrap a valid GPU device.
//! @throws ApiException If SDL cannot create the texture.
TransferBuffer Device::createTransferBuffer(SDL_GPUTransferBufferUsage usage,
                                            uint32_t size) const
{
    auto device = verifyAccess("Create transfer buffer");

    SDL_GPUTransferBufferCreateInfo info = { usage, size, 0 };

    auto buffer = SDL_CreateGPUTransferBuffer(device, &info);

    if (buffer == nullptr)
        throw ApiException("SDL_CreateGPUTransferBuffer()");

    return TransferBuffer(device, buffer, size);
}

//! @brief Attempts to create a block of GPU memory to hold vertices or indices.
//! @param[in] usage Flags defining the intended usage for the buffer, such
//! as SDL_GPU_BUFFERUSAGE_VERTEX and SDL_GPU_BUFFERUSAGE_GRAPHICS_STORAGE_READ.
//! @param[in] size The count of bytes in the buffer.
//! @return An object representing the buffer.
//! @throws ObjectNotBound If the object does not wrap a valid GPU device.
//! @throws ApiException If SDL cannot create the texture.
ResourceBuffer Device::createResourceBuffer(SDL_GPUBufferUsageFlags usage,
                                            uint32_t size) const
{
    auto device = verifyAccess("Create buffer");

    SDL_GPUBufferCreateInfo info = { usage, size, 0 };

    auto buffer = SDL_CreateGPUBuffer(device, &info);

    if (buffer == nullptr)
        throw ApiException("SDL_CreateGPUBuffer()");

    return ResourceBuffer(device, buffer, size);
}

//! @brief Creates a texture on the device.
//! @param[in] info The requirements of the texture to create.
//! @return An object wrapping the newly created texture.
//! @throws ObjectNotBound If the object does not wrap a valid GPU device.
//! @throws ApiException If SDL cannot create the texture.
Texture Device::createTexture(const SDL_GPUTextureCreateInfo &info) const
{
    auto device = verifyAccess("Create texture");
    auto texture = SDL_CreateGPUTexture(device, &info);

    if (texture == nullptr)
        throw ApiException("SDL_CreateGPUTexture()");

    return Texture(device, texture);
}

//! @brief Creates a shader program on the device.
//! @param[in] info Details of the shader to create.
//! @return An object wrapping the newly created shader resource.
//! @throws ObjectNotBound If the object does not wrap a valid GPU device.
//! @throws ApiException If SDL cannot create the shader.
Shader Device::createShader(const SDL_GPUShaderCreateInfo &info) const
{
    auto device = verifyAccess("Create shader");
    auto shader = SDL_CreateGPUShader(device, &info);

    if (shader == nullptr)
        throw ApiException("SDL_CreateGPUShader()");

    return Shader(device, shader);
}

//! @brief Creates an object which can be bound to a pipeline to sample
//! texture data.
//! @param[in] info Details of the sampler to create.
//! @return An object wrapping the newly created sampler.
//! @throws ObjectNotBound If the object does not wrap a valid GPU device.
//! @throws ApiException If SDL cannot create the sampler.
Sampler Device::createSampler(const SDL_GPUSamplerCreateInfo &info) const
{
    auto device = verifyAccess("Create sampler");
    auto sampler = SDL_CreateGPUSampler(device, &info);

    if (sampler == nullptr)
        throw ApiException("SDL_CreateGPUSampler()");

    return Sampler(device, sampler);
}

//! @brief Creates a graphic pipeline on the current GPU device.
//! @param[in] info The parameters required to create the pipeline.
//! @return A newly created graphic pipeline object.
//! @throws ObjectNotBound If the object does not wrap a valid GPU device.
//! @throws ApiException If SDL cannot create the texture.
GraphicsPipeline Device::createGraphicsPipeline(const SDL_GPUGraphicsPipelineCreateInfo &info) const
{
    auto device = verifyAccess("Create graphics pipeline");

    auto pipeline = SDL_CreateGPUGraphicsPipeline(device, &info);

    if (pipeline == nullptr)
        throw ApiException("SDL_CreateGPUGraphicsPipeline()");

    return GraphicsPipeline(device, pipeline);
}

//! @brief Ensures any previously bound GPU device resource is disposed of.
void Device::release()
{
    auto device = std::exchange(_device, nullptr);

    if (device != nullptr)
    {
        SDL_DestroyGPUDevice(device);
    }

    _backendName = String::Empty;
}

//! @brief Binds a GPU device resource to this object.
//! @param[in] rhs The resource to bind, nullptr for none.
//! @return A reference to the current object.
Device &Device::operator=(SDL_GPUDevice *rhs)
{
    init(rhs);

    return *this;
}

//! @brief Acquires a GPU device resource from another wrapper object.
//! @param[in] rhs The wrapper object to transfer the resource from, if any.
//! @return A reference to the current object.
Device &Device::operator=(Device &&rhs) noexcept
{
    release();
    _device = std::exchange(rhs._device, nullptr);
    _backendName = rhs._backendName;
    rhs._backendName = String::Empty;

    return *this;
}

//! @brief Creates a swap chain to render to a specified window.
//! @param[in] window The window to render to.
//! @return An object representing the swap chain.
Swapchain Device::createSwapchain(SDL_Window *window) const
{
    if (window == nullptr)
        throw ArgumentException("window");

    auto device = verifyAccess("Create GPU swap chain");

    if (SDL_ClaimWindowForGPUDevice(device, window) == false)
    {
        throw ApiException("SDL_ClaimWindowForGPUDevice");
    }

    return Swapchain(device, window);
}

//! @brief Creates a swap chain to render to a specified window.
//! @param[in] window The window to render to.
//! @return An object representing the swap chain.
Swapchain Device::createSwapchain(const Window &window) const
{
    return createSwapchain(window.verifyAccess("Creates GPU swap chain"));
}

//! @brief Acquires a buffer to send commands to the GPU device.
//! @return A wrapper for a command buffer resource.
//! @throws ObjectNotBoundException If the object is not bound to a GPU device.
//! @throws ApiException If the attempt to acquire the command buffer fails.
CommandBuffer Device::acquireCommandBuffer() const
{
    auto device = verifyAccess("AcquireCommandBuffer");
    SDL_GPUCommandBuffer *commandBuffer = SDL_AcquireGPUCommandBuffer(device);

    if (commandBuffer == nullptr)
        throw ApiException("SDL_AcquireGPUCommandBuffer()");

    return CommandBuffer(device, commandBuffer);
}

//! @brief Gets a pointer to the underlying GPU device resource if one is bound,
//! throws an exception if not.
//! @param[in] operation The description of the operation being attempted to note
//! in the exception if verification fails.
//! @return A pointer to a valid GPU device resource.
//! @throws ObjectNotBoundException If the object is in an unbound state.
SDL_GPUDevice *Device::verifyAccess(const char *operation) const
{
    if (_device == nullptr)
        throw ObjectNotBoundException("GPU Device", operation);

    return _device;
}

//! @brief Initialises the object with a new GPU resource, disposing of any previous resource.
//! @param[in] device The GPU device resource to bind, possibly nullptr.
//! @retval true If a GPU device resource was successfully bound.
//! @retval false If the object was left in an unbound state.
bool Device::init(SDL_GPUDevice *device)
{
    if (device == _device)
        return (device != nullptr);

    release();

    if (device == nullptr)
    {
        return false;
    }
    else
    {
        _device = device;
        _backendName = SDL_GetGPUDeviceDriver(_device);
        return true;
    }
}

}}} // namespace Ag::SDL3::GPU
////////////////////////////////////////////////////////////////////////////////

